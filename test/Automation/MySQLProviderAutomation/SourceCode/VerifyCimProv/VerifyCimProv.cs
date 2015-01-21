//-----------------------------------------------------------------------
// <copyright file="VerifyCimProv.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-jeali</author>
// <description></description>
// <history>11/28/2014 10:29:44 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.Test.MySQL.Provider.VerifyCimProv
{
    using Infra.Frmwrk;
    using System;

    ///// <summary>
    ///// VerifyCimProv Installation
    ///// </summary>
    public class VerifyCimProv : VerifyCimProvHelper, ISetup, IRun, IVerify, ICleanup
    {
        string commandStdOut = string.Empty;
        string verifyFolderExistCmd = string.Empty;
        string verifyMySQLInstalledCmd = string.Empty;
        string mysqlCmd = string.Empty;
        string expectedFolderCount = string.Empty;
        string installLogKeyWorlds = string.Empty;
        bool isInValidInstall = false;

        /// <summary>
        /// Case setup. Get values from case suite. and Uninstall MySQLAgent.
        /// </summary>
        /// <param name="ctx"></param>
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

            if (ctx.Records.HasKey("isInvalidInstall") &&
                   ctx.Records.GetValue("isInvalidInstall") == "true")
            {
                this.isInValidInstall = true;
            }

            if (ctx.Records.HasKey("installLogKeyWorlds"))
            {
                this.installLogKeyWorlds = ctx.Records.GetValue("installLogKeyWorlds");
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

            // if has to install twice don't need uninstall.
            if (!ctx.Records.HasKey("installTwice") && !ctx.Records.HasKey("isHelpOption") && !ctx.Records.HasKey("isRemoveOption"))
            {
                // Uninstall MySQL Agent. 
                this.MySQLHelper.UninstallMySQLAgent(this.UninstallMySQLCmd);
            }

        }

        /// <summary>
        /// Running Case. install mysql using command 
        /// </summary>
        /// <param name="ctx">ctx</param>
        public void Run(IContext ctx)
        {
            try
            {
                commandStdOut = this.MySQLHelper.RunCmd(string.Format(this.mysqlCmd, this.MySQLHelper.mysqlAgentName)).StdOut;
            }
            catch (Exception e)
            {
                if (!this.isInValidInstall)
                {
                    throw new Exception("Install mysql CimProv agent failed: " + e.Message);
                }

            }
        }

        /// <summary>
        /// Verify the mysql agent install successfully.
        /// </summary>
        /// <param name="ctx">ctx</param>
        public void Verify(IContext ctx)
        {
            if (!this.isInValidInstall && !ctx.Records.HasKey("isHelpOption") && !ctx.Records.HasKey("isRemoveOption"))
            {
                this.VerifyCommandStdOutLog(commandStdOut, this.installLogKeyWorlds, true);

                this.VerifyFolderExist(verifyFolderExistCmd, this.expectedFolderCount, true);

                this.VerifyMySQLInstalled(verifyMySQLInstalledCmd, true);
            }

            if (ctx.Records.HasKey("isHelpOption"))
            {
                this.VerifyCommandStdOutLog(commandStdOut, this.installLogKeyWorlds, true);
            }

            if (ctx.Records.HasKey("isRemoveOption"))
            {
                this.VerifyFolderExist(verifyFolderExistCmd, this.expectedFolderCount, false);

                this.VerifyMySQLInstalled(verifyMySQLInstalledCmd, false);
            }
        }


        /// <summary>
        /// Cleanup
        /// </summary>
        /// <param name="ctx"></param>
        public void Cleanup(IContext ctx)
        {
            if ((this.isInValidInstall && !ctx.Records.HasKey("installTwice")) || ctx.Records.HasKey("isRemoveOption"))
            {
                this.MySQLHelper.InstallMySQLAgent(this.InstallMySQLCmd);
            }
            // the uninstall will be down via group clean up.
        }
    }
}
