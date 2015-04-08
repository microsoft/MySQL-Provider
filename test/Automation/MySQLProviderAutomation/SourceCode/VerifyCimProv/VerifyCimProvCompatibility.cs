//-----------------------------------------------------------------------
// <copyright file="VerifyCimProvCompatibility.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-jeali</author>
// <description></description>
// <history>12/8/2014 10:29:44 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.Test.MySQL.Provider.VerifyCimProv
{
    using Infra.Frmwrk;
    using Scx.Test.Common;
    using System;
    using System.IO;

    /// <summary>
    /// VerifyCimProvCompatibility
    /// </summary>
    class VerifyCimProvCompatibility : VerifyCimProvHelper, ISetup, IRun, IVerify, ICleanup
    {
        string mysqlCmd = string.Empty;
        string installOlderMySQLCmd = string.Empty;
        bool isUpgrade = false;
        string omOlderAgentFullName = string.Empty;
        string omAgentFullName = string.Empty;
        string commandStdOut = string.Empty;
        string expectedFolderCount = string.Empty;
        string verifyFolderExistCmd = string.Empty;
        string verifyMySQLInstalledCmd = string.Empty;

        /// <summary>
        /// setup
        /// </summary>
        /// <param name="ctx">setup</param>
        public void Setup(IContext ctx)
        {
            // get value from base class.
            this.GetValueFromVarList(ctx);

            // get value from current case.
            mysqlCmd = ctx.Records.GetValue("mysqlCmd");
            if (string.IsNullOrEmpty(this.mysqlCmd))
            {
                throw new VarAbort("installCmd command not specified");
            }

            if (ctx.Records.HasKey("installOlderMySQLCmd"))
            {
                installOlderMySQLCmd = ctx.Records.GetValue("installOlderMySQLCmd");
            }

            if (ctx.Records.HasKey("isUpgrade") && ctx.Records.GetValue("isUpgrade").ToUpper() == "TRUE")
            {
                this.isUpgrade = true;
            }

            if (ctx.Records.HasKey("expectedFolderCount"))
            {
                this.expectedFolderCount = ctx.Records.GetValue("expectedFolderCount");
            }

            if (ctx.Records.HasKey("verifyFolderExistCmd"))
            {
                verifyFolderExistCmd = ctx.Records.GetValue("verifyFolderExistCmd");
            }

            if (ctx.Records.HasKey("verifyMySQLInstalledCmd"))
            {
                verifyMySQLInstalledCmd = ctx.Records.GetValue("verifyMySQLInstalledCmd");
            }

            string omlocation = ctx.ParentContext.Records.GetValue("OMAgentLocation");
            string oldOMlocation = ctx.ParentContext.Records.GetValue("oldOMAgentLocation");
            this.omOlderAgentFullName = this.AgentHelper.SetOmAgentPath(oldOMlocation);
            this.omAgentFullName = this.AgentHelper.SetOmAgentPath(omlocation);

            // install older mysql version.
            if (this.isUpgrade)
            {
                try
                {
                    // Uninstall MySQL Agent. for upgrade test.
                    // this.MySQLHelper.UninstallMySQLAgent(this.UninstallMySQLCmd);
                    this.AgentHelper.Uninstall();
                    this.Wait(ctx);
                    this.MySQLHelper.RunCmd(string.Format(this.installOlderMySQLCmd, Path.GetFileName(this.omOlderAgentFullName)));
                }
                catch (Exception e)
                {
                    // throw new Exception("install older mysql CimProv agent failed: " + e.Message);
                }
            }
        }

        /// <summary>
        /// Running case
        /// </summary>
        /// <param name="ctx">ctx</param>
        public void Run(IContext ctx)
        {
            try
            {
                if (isUpgrade)
                {
                    commandStdOut = this.MySQLHelper.RunCmd(string.Format(this.mysqlCmd, this.omAgentFullName)).StdOut;
                }
                else
                {
                    this.MySQLHelper.RunCmd(string.Format(this.mysqlCmd, Path.GetFileName(this.omOlderAgentFullName)));
                }
            }
            catch (Exception e)
            {
                if (isUpgrade)
                {
                    throw new Exception("Upgrade mysql CimProv agent failed: " + e.Message);
                }
            }

        }

        /// <summary>
        /// Verify 
        /// </summary>
        /// <param name="ctx">ctx</param>
        public void Verify(IContext ctx)
        {
            if (isUpgrade)
            {
                // verify command stdout:
                VerifyCommandStdOutLog(commandStdOut, "FAILED", false);
                this.VerifyFolderExist(verifyFolderExistCmd, this.expectedFolderCount, true);

                this.VerifyMySQLInstalled(verifyMySQLInstalledCmd, true);
            }
        }

        /// <summary>
        /// Cleanup
        /// </summary>
        /// <param name="ctx">ctx</param>
        public void Cleanup(IContext ctx)
        {
            if (isUpgrade)
            {
                // this.AgentHelper.Uninstall();
                // this.MySQLHelper.UninstallMySQLAgent(this.UninstallMySQLCmd);
            }
            else
            {
                this.MySQLHelper.RunCmd(string.Format("sh /tmp/{0} --purge", Path.GetFileName(this.omOlderAgentFullName)));
            }
            this.MySQLHelper.RunCmd(string.Format(this.mysqlCmd, this.omAgentFullName));
            // the uninstall will be down via group clean up.
        }
    }
}
