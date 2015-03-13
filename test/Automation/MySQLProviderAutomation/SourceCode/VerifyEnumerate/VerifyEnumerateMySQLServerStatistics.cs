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
    class VerifyEnumerateMySQLServerStatistics : VerifyEnumerateBase, ISetup, IRun, IVerify, ICleanup
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
        /// should stop mysql server or not.
        /// </summary>
        private bool stopMySQLServer = false;

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

            this.InsertMySQLServerStatisticsValues(mcfContext);

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

            // Stop one instance in Multi instances Env.
            if (mcfContext.Records.HasKey("IsStopOneInstance") && mcfContext.Records.GetValue("IsStopOneInstance") == "true")
            {
                mcfContext.Trc("Run stopOneInstanceCmd ...");
                string stopOneInstanceCmd = mcfContext.Records.GetValue("stopOneInstanceCmd");
                this.RunCommandAsRoot(stopOneInstanceCmd, this.RootPassword);
            }

            // Get the WSMANQuery.
            EnumerateWSMANQuery(mcfContext);
        }

        /// <summary>
        /// Implements MCF Verify interface. Verify the WSMAN Query Value.
        /// </summary>
        /// <param name="mcfContext">MCF context</param>
        public void Verify(IContext mcfContext)
        {
            // Verify the Enumerate Result Is Null
            if (this.ShouldEnumerateresult == false)
            {
                VerifyEnumerateResultIsNull();
                return;
            }

            // Verify WSMAN Values
            VerifyWSMANValues(mcfContext, this.ResultTemplate, "InstanceID");
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

        #endregion Methods
    }
}
