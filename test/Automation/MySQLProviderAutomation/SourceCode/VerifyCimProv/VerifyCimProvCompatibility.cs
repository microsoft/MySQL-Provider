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
        string mysqlOlderAgentFullName = string.Empty;
        string mysqlAgentFullName = string.Empty;
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

            string mysqllocation = ctx.ParentContext.Records.GetValue("MySQLsLocation");
            string oldMySQLlocation = ctx.Records.GetValue("oldMySQLsLocation");
            this.mysqlOlderAgentFullName = SearchForMySQLInApcheAgentPath(oldMySQLlocation, this.MySQLTag);
            this.mysqlAgentFullName = SearchForMySQLInApcheAgentPath(mysqllocation, this.MySQLTag);
            this.CopyMySQLAgent(this.mysqlAgentFullName, "/tmp/");
            this.CopyMySQLAgent(this.mysqlOlderAgentFullName, "/tmp/");

            // install older mysql version.
            if (this.isUpgrade)
            {
                try
                {
                    // Uninstall MySQL Agent. for upgrade test.
                    this.MySQLHelper.UninstallMySQLAgent(this.UninstallMySQLCmd);
                    this.MySQLHelper.RunCmd(string.Format(this.installOlderMySQLCmd, Path.GetFileName(this.mysqlOlderAgentFullName)));
                }
                catch (Exception e)
                {
                    throw new Exception("install older mysql CimProv agent failed: " + e.Message);
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
                    commandStdOut = this.MySQLHelper.RunCmd(string.Format(this.mysqlCmd, this.MySQLHelper.mysqlAgentName)).StdOut;
                }
                else
                {
                    this.MySQLHelper.RunCmd(string.Format(this.mysqlCmd, Path.GetFileName(this.mysqlOlderAgentFullName)));
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
            // the uninstall will be down via group clean up.
        }

        /// <summary>
        /// CopyMySQLAgent
        /// </summary>
        /// <param name="mysqlAgentFullName">mysqlAgentFullName</param>
        /// <param name="targetHostAgentloaclPath">targetHostAgentloaclPath</param>
        public void CopyMySQLAgent(string mysqlAgentFullName, string targetHostAgentloaclPath)
        {
            CopyFileToHost(mysqlAgentFullName, targetHostAgentloaclPath + Path.GetFileName(mysqlAgentFullName));
        }

        /// <summary>
        /// SearchForMySQLInApcheAgentPath
        /// </summary>
        /// <param name="apcheAgentFullloaclPath">apcheAgentFullloaclPath</param>
        /// <param name="apcheTag">apcheTag</param>
        /// <returns>apcheAgentFullNamePath</returns>
        private static string SearchForMySQLInApcheAgentPath(string apcheAgentFullloaclPath, string apcheTag)
        {
            //"Searching for mysql in " + apcheAgentFullPath;
            DirectoryInfo di = new DirectoryInfo(apcheAgentFullloaclPath);
            FileInfo[] fi = di.GetFiles("*" + apcheTag + "*");
            if (fi.Length == 0)
            {
                throw new Exception("Found no mysql installer matching MySQLTag: " + apcheTag);
            }

            if (fi.Length > 1)
            {
                throw new Exception("Found more than one mysql installer matching MySQLTag: " + apcheTag);
            }

            // User-specified MySQL path takes precedent
            string mysqlAgentName = fi[0].FullName;
            return mysqlAgentName;
        }

        /// <summary>
        /// CopyFileToHost
        /// </summary>
        /// <param name="from">from</param>
        /// <param name="to">to</param>
        private void CopyFileToHost(string from, string to)
        {

            PosixCopy copyToHost = new PosixCopy(this.HostName, this.UserName, this.Password);
            // Copy from server to Posix host
            copyToHost.CopyTo(from, to);
        }
    }
}
