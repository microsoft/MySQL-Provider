//-----------------------------------------------------------------------
// <copyright file="VerifyEnumerateMySQLServerStatistics.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-jeali</author>
// <description></description>
// <history>2/12/2015 2:27:44 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.Test.MySQL.Provider
{
    using Infra.Frmwrk;
    using Scx.Test.Common;
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Text.RegularExpressions;
    using System.Threading;
    using System.Xml;
    using System.Xml.Linq;
    class VerifyEnumerateMySQLServer : VerifyEnumerateBase, ISetup, IRun, IVerify, ICleanup
    {
        #region Private Fields
        /// <summary>
        /// Class use to run posix command
        /// </summary>
        private RunPosixCmd rPC;

        /// <summary>
        /// addMySQLAuthCmd eg./opt/microsoft/omi/bin/omicli iv root/mysql { MySQL_Server } UpdateCredentials { Port 3306 BindAddress 127.0.0.1 Username root Password OpsMgr2007R2 }
        /// </summary>
        private string addMySQLAuthCmd;

        /// <summary>
        /// addMySQLAuthCmd eg./opt/microsoft/omi/bin/omicli iv root/mysql { MySQL_Server } UpdateCredentials { Port 3306 BindAddress 127.0.0.1 Username test Password test }
        /// </summary>
        private string addBadMySQLAuthCmd;

        /// <summary>
        /// expecte Status Value
        /// </summary>
        private string expecteStatusValue = "OK";


        /// <summary>
        /// should stop mysql server or not.
        /// </summary>
        private bool stopMySQLServer = false;

        /// <summary>
        /// Stop OMI agent
        /// </summary>
        private bool stopOmAgent = false;

        /// <summary>
        /// isAddBadAuthor.
        /// </summary>
        private bool isAddBadAuthor = false;

        #endregion Private Fields

        #region Methods

        #region Public Methods

        /// <summary>
        /// Implements MCF Setup interface. Setup. Caculate the expected xml value.
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>
        public void Setup(IContext mcfContext)
        {
            mcfContext.Trc("Setup entered");
            InitializeHelper(mcfContext);

            if (mcfContext.Records.HasKey("addMySQLAuthCmd"))
            {
                this.addMySQLAuthCmd = mcfContext.Records.GetValue("addMySQLAuthCmd");
                this.MySQLHelper.SetupMySqlAuth(this.addMySQLAuthCmd);
            }

            // Get Values
            GetExpectedMySQLServerValues(mcfContext);
            if (mcfContext.Records.HasKey("IsBadStatus"))
            {
                this.ExpecteStatusValue = mcfContext.Records.GetValue("expecteStatusValue");
            }

            InsertMySQLServerValues(mcfContext);
            mcfContext.Trc("Expected Result: " + this.ResultTemplate);

            // set up Multi instances env.
            SetUpMultiMySQLEnv(mcfContext);
        }

        /// <summary>
        /// Implements MCF Run interface. Running. Get value from WSMAN.
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>
        public void Run(IContext mcfContext)
        {
            mcfContext.Trc("Run entered");
            // stop MySQL Server
            if (mcfContext.Records.HasKey("stopMySQLServer") &&
               mcfContext.Records.GetValue("stopMySQLServer") == "true")
            {
                this.stopMySQLServer = true;
                string stopMySQLCmd = mcfContext.Records.GetValue("stopMySQLCmd");
                this.MySQLHelper.StopMySQLServiceStatus(stopMySQLCmd);
            }

            if (mcfContext.Records.HasKey("restartMySQLServer") &&
                mcfContext.Records.GetValue("restartMySQLServer") == "true")
            {
                string restartMySQLCmd = mcfContext.Records.GetValue("restartMySQLCmd");
                this.MySQLHelper.RestartMySQLServiceStatus(restartMySQLCmd);
            }

            if (mcfContext.Records.HasKey("deleteCredentials") && mcfContext.Records.GetValue("deleteCredentials") == "true")
            {
                mcfContext.Trc("Run deleteCredentialsCmd ...");
                string deleteCredentialsCmd = mcfContext.Records.GetValue("deleteCredentialsCmd");
                this.RunCommandAsRoot(deleteCredentialsCmd, this.RootPassword);
            }

            // Stop one instance in Multi instances Env.
            if (mcfContext.Records.HasKey("IsStopOneInstance") && mcfContext.Records.GetValue("IsStopOneInstance") == "true")
            {
                mcfContext.Trc("Run stopOneInstanceCmd ...");
                string stopOneInstanceCmd = mcfContext.Records.GetValue("stopOneInstanceCmd");
                this.RunCommandAsRoot(stopOneInstanceCmd, this.RootPassword);
            }

            if (mcfContext.Records.HasKey("stopOmAgent") &&
              mcfContext.Records.GetValue("stopOmAgent") == "true")
            {
                mcfContext.Trc("Run stopOmAgent ...");
                stopOmAgent = true;
                string stopOmAgentCmd = mcfContext.Records.GetValue("stopOmAgentCmd");
                this.AgentHelper.StopOmAgent(stopOmAgentCmd);
            }

            if (mcfContext.Records.HasKey("restartOmAgent") &&
               mcfContext.Records.GetValue("restartOmAgent") == "true")
            {
                mcfContext.Trc("Run restartOmAgentCmd ...");
                string restartOmAgentCmd = mcfContext.ParentContext.Records.GetValue("restartOmAgentCmd");
                this.AgentHelper.RestartOmAgent(restartOmAgentCmd);
            }
            // Verfy add bad autor file can't enumerate.
            if (mcfContext.Records.HasKey("addBadMySQLAuthCmd"))
            {
                mcfContext.Trc("Run add Bad MySQLAuth Cmd ...");
                try
                {
                    this.addBadMySQLAuthCmd = mcfContext.Records.GetValue("addBadMySQLAuthCmd");
                    this.MySQLHelper.SetupMySqlAuth(this.addBadMySQLAuthCmd);
                }
                catch (Exception e)
                {
                    this.isAddBadAuthor = true;
                }
            }
            // Get the WSMANQuery.
            try
            {
                EnumerateWSMANQuery(mcfContext);
            }
            catch (Exception e)
            {
                if (stopOmAgent)
                {
                    mcfContext.Trc("Verify When the OMI Stoped Can't Enumerate WSMAN Element Pass.");
                }
                else
                {
                    throw e;
                }
            }
        }

        /// <summary>
        /// Implements MCF Verify interface. Verify the WSMAN Query Value.
        /// </summary>
        /// <param name="mcfContext">MCF context</param>
        public void Verify(IContext mcfContext)
        {
            // Don't need verify the values when we added the BadMySQLAuthCmd
            if (mcfContext.Records.HasKey("addBadMySQLAuthCmd") && this.isAddBadAuthor)
            {
                mcfContext.Trc("Verfiy add bad mysql auth file using mycimprovauth will throw error Passed.");
                return;
            }

            // Verify the Enumerate Result Is Null
            if (this.ShouldEnumerateresult == false)
            {
                VerifyEnumerateResultIsNull();
                return;
            }

            // Verify WSMAN Values
            VerifyWSMANValues(mcfContext, this.ResultTemplate, "ProductIdentifyingNumber");
        }

        /// <summary>
        /// Implements MCF Cleanup interface
        /// </summary>
        /// <param name="mcfContext">MCF context</param>
        public void Cleanup(IContext mcfContext)
        {
            mcfContext.Trc("Cleanup entered");
            if (stopMySQLServer)
            {
                string startServerCmd = mcfContext.ParentContext.Records.GetValue("startMySQLCmd");
                this.MySQLHelper.StartMySQLServiceStatus(startServerCmd);
            }
            if (stopOmAgent)
            {
                string startServerCmd = mcfContext.ParentContext.Records.GetValue("startOmAgentCmd");
                this.MySQLHelper.StartMySQLServiceStatus(startServerCmd);
            }
            if (mcfContext.Records.HasKey("IsStopOneInstance") && mcfContext.Records.GetValue("IsStopOneInstance") == "true")
            {
                string startServerCmd = mcfContext.Records.GetValue("startStopedInstanceCmd");
                this.RunCommandAsRoot(startServerCmd, this.RootPassword);
            }
            if (mcfContext.Records.HasKey("removeMySQLAuthCmd"))
            {
                string removeMySQLAuthCmd = mcfContext.Records.GetValue("removeMySQLAuthCmd");
                this.RunCommandAsRoot(removeMySQLAuthCmd, this.RootPassword);
            }

            // CleanUpMultiMySQLEnv
            CleanUpMultiMySQLEnv(mcfContext);
        }

        #endregion Public Methods
        #region Private Methods


        #endregion Private Methods
        #endregion Methods
    }
}
