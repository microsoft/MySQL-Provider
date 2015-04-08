
//-----------------------------------------------------------------------
// <copyright file="VerifyCimProvHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-jeali</author>
// <description></description>
// <history>11/28/2014 10:29:44 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.Test.MySQL.Provider.VerifyCimProv
{
    using System;
    using Infra.Frmwrk;
    using Scx.Test.Common;
    /// <summary>
    /// VerifyCimProvHelper class. get HostName, UserName... and an MySQLhelper instance.
    /// </summary>
    public class VerifyCimProvHelper
    {
        /// <summary>
        /// new a AgentHelper
        /// </summary>
        private AgentHelper agentHelper;

        /// <summary>
        /// new a AgentHelper
        /// </summary>
        public AgentHelper AgentHelper
        {
            get { return agentHelper; }
            set { agentHelper = value; }
        }

        /// <summary>
        /// new a mysqlHelper
        /// </summary>
        private MySQLHelper mysqlHelper;

        /// <summary>
        /// new a mysqlHelper
        /// </summary>
        public MySQLHelper MySQLHelper
        {
            get { return mysqlHelper; }
            set { mysqlHelper = value; }
        }

        /// <summary>
        /// Required: Name of Posix host (DNS or IP)
        /// </summary>
        private string hostName;

        /// <summary>
        /// Required: Name of Posix host (DNS or IP)
        /// </summary>
        public string HostName
        {
            get { return hostName; }
            set { hostName = value; }
        }

        /// <summary>
        /// Required: User name
        /// </summary>
        private string userName;

        /// <summary>
        /// Required: User name
        /// </summary>
        public string UserName
        {
            get { return userName; }
            set { userName = value; }
        }

        /// <summary>
        /// Required: User's password
        /// </summary>
        private string password;

        /// <summary>
        ///  Required: User's password
        /// </summary>
        public string Password
        {
            get { return password; }
            set { password = value; }
        }

        /// <summary>
        /// Required: Command to install om
        /// </summary>
        private string installOmCmd;

        /// <summary>
        /// Required: Command to Install Om
        /// </summary>
        public string InstallOmCmd
        {
            get { return installOmCmd; }
            set { installOmCmd = value; }
        }
        /// <summary>
        /// Required: Command to Uninstall Om 
        /// </summary>
        private string uninstallOmCmd;

        /// <summary>
        /// Required: Command to Uninstall Om 
        /// </summary>
        public string UninstallOmCmd
        {
            get { return uninstallOmCmd; }
            set { uninstallOmCmd = value; }
        }

        /// <summary>
        /// Required: Command to clean om
        /// </summary>
        private string cleanupOmCmd;

        /// <summary>
        /// Required: Command to clean om.
        /// </summary>
        public string CleanupOmCmd
        {
            get { return cleanupOmCmd; }
            set { cleanupOmCmd = value; }
        }

        /// <summary>
        /// Required: MySQLTag to identify the mysqlinstalled platfrom.
        /// </summary>
        private string mysqlTag;

        /// <summary>
        /// Required: MySQLTag to identify the mysqlinstalled platfrom.
        /// </summary>
        public string MySQLTag
        {
            get { return mysqlTag; }
            set { mysqlTag = value; }
        }

        /// <summary>
        ///  Optional: useNonSuperUser
        /// </summary>
        private bool useNonSuperUser;
        /// <summary>
        /// Time to wait before attempting retry of query after a failed query
        /// </summary>
        private TimeSpan queryRetryInterval = new TimeSpan(0, 0, 20);

        /// <summary>
        ///  Optional: useNonSuperUser
        /// </summary>
        public bool UseNonSuperUser
        {
            get { return useNonSuperUser; }
            set { useNonSuperUser = value; }
        }

        /// <summary>
        /// The Current OS is Deb or Ubun.
        /// </summary>
        private bool isDeb = false;

        /// <summary>
        /// get all the group values from ctx.
        /// </summary>
        /// <param name="ctx">IContext</param>
        public void GetValueFromVarList(IContext ctx)
        {
            // Overrid value from parent.
            this.HostName = ctx.ParentContext.Records.GetValue("hostname");
            if (String.IsNullOrEmpty(this.HostName))
            {
                throw new VarAbort("hostName not specified");
            }

            // in same case need use NonSuperUser.
            if (ctx.Records.HasKey("useNonSuperUser"))
            {
                this.UseNonSuperUser = true;
            }
            string usernamep = this.UseNonSuperUser ? "nonsuperuser" : "username";
            string passwordp = this.UseNonSuperUser ? "nonsuperuserpwd" : "password";

            this.UserName = ctx.ParentContext.Records.GetValue(usernamep);
            if (String.IsNullOrEmpty(this.UserName))
            {
                throw new VarAbort("userName not specified");
            }

            this.Password = ctx.ParentContext.Records.GetValue(passwordp);
            if (String.IsNullOrEmpty(this.Password))
            {
                throw new VarAbort("password not specified");
            }

            this.InstallOmCmd = ctx.ParentContext.Records.GetValue("InstallOMCmd");
            if (String.IsNullOrEmpty(this.InstallOmCmd))
            {
                throw new VarAbort("InstallOMCmd not specified");
            }

            this.UninstallOmCmd = ctx.ParentContext.Records.GetValue("UninstallOMCmd");
            if (String.IsNullOrEmpty(this.UninstallOmCmd))
            {
                throw new VarAbort("UninstallOMCmd not specified");
            }

            this.CleanupOmCmd = ctx.ParentContext.Records.GetValue("CleanupOMCmd");
            if (String.IsNullOrEmpty(this.CleanupOmCmd))
            {
                throw new VarAbort("CleanupOMCmd not specified");
            }

            mysqlHelper = new MySQLHelper(ctx.Trc, this.hostName, this.userName, this.password);
            agentHelper = new AgentHelper(ctx.Trc, this.hostName, this.userName, this.password, this.installOmCmd, this.cleanupOmCmd);

            // get OS Info if the OS is Deb or UBUN it will return true
            GetOSIsDebInfo(ctx);
        }

        #region HelpMethod

        /// <summary>
        /// GetOSIsDebInfo
        /// </summary>
        /// <returns>isDeb</returns>
        private bool GetOSIsDebInfo(IContext ctx)
        {
            string getOSDistCmd = "python -c \"import platform; print platform.dist()\"";
            string password = ctx.ParentContext.Records.GetValue("password");
            RunPosixCmd execCmd = new RunPosixCmd(this.HostName, "root", password);
            execCmd.RunCmd(getOSDistCmd);
            if (execCmd.StdOut.ToLower().Contains("debian") || execCmd.StdOut.ToLower().Contains("ubuntu"))
            {
                this.isDeb = true;
            }
            else
            {
                this.isDeb = false;
            }
            return this.isDeb;
        }

        /// <summary>
        /// Run remote command using root acount.
        /// </summary>
        /// <param name="cmd">The command need to be executed</param>
        /// <param name="password">root password</param>
        /// <returns>Command execute result</returns>
        public string RunCommandAsRoot(string cmd, string password)
        {
            string result = string.Empty;
            RunPosixCmd rPC = new RunPosixCmd(this.HostName, "root", password);
            try
            {
                rPC.RunCmd(cmd);
                result = string.Format("Command executed with output \"{0}\" or Error \"{1}\"", rPC.StdOut, rPC.StdErr);
            }
            catch (Exception e)
            {
                throw new Exception(string.Format("An exception \"{0}\" occured when executing command \"{1}\"", e.Message + ":" + rPC.StdOut + ":" + rPC.StdErr, cmd));
            }

            return result;
        }

        /// <summary>
        /// Verify Installation logs.
        /// </summary>
        /// <param name="commandStdOut">Installation command stdOut put</param>
        /// <param name="keyWorlds"> keyworlds</param>
        /// <param name="shouldContain"> shouldContain</param>
        public void VerifyCommandStdOutLog(string commandStdOut, string keyWorlds, bool shouldContain)
        {
            if (shouldContain && !commandStdOut.ToUpper().Contains(keyWorlds.ToUpper()))
            {
                throw new VarAbort(string.Format("Verify installtion log contains {0} failed", keyWorlds));
            }

            if (!shouldContain && commandStdOut.ToUpper().Contains(keyWorlds.ToUpper()))
            {
                throw new VarAbort(string.Format("Verify installtion log not contains {0} failed", keyWorlds));
            }

        }

        /// <summary>
        /// Verify Folders Exist, eg. the mysql folder should put under folder /opt/microsoft/ and /etc/opt/microsoft/ and /var/opt/microsoft/
        /// </summary>
        /// <param name="verifyFolderExistCmd">verifyFolderExistCmd</param>
        /// <param name="expectFoldercount">expectFoldercount</param>
        /// <param name="isfolderExist">isfolderExist</param>
        public void VerifyFolderExist(string verifyFolderExistCmd, string expectFoldercount, bool isfolderExist)
        {
            try
            {
                // verify after installed the mysql-cimprov folder should place under folder /opt/microsoft/ and /etc/opt/microsoft/ and /var/opt/microsoft/
                RunPosixCmd runCmd = this.MySQLHelper.RunCmd(verifyFolderExistCmd);
                string stdout = runCmd.StdOut.Replace("\n", "");
                expectFoldercount = expectFoldercount.Replace(",", "");

                if (stdout != expectFoldercount)
                {
                    throw new VarAbort(string.Format("verify after installed the mysql-cimprov folder under folder /opt/microsoft/ and /etc/opt/microsoft/ and /var/opt/microsoft/ count should be{0}  failed", expectFoldercount));
                }

            }
            catch
            {
                if (isfolderExist)
                {
                    throw new VarAbort("verify after installed the mysql-cimprov folder should place under folder /opt/microsoft/ and /etc/opt/microsoft/ and /var/opt/microsoft/  failed");
                }
            }
        }

        /// <summary>
        /// VerifyMySQLInstalled if installed verify the version like 1.0.0.29
        /// </summary>
        /// <param name="verifyMySQLInstalledCmd">verifyMySQLInstalledCmd</param>
        /// <param name="isInstalled">isInstalled</param>
        public void VerifyMySQLInstalled(string verifyMySQLInstalledCmd, bool isInstalled)
        {
            try
            {
                // get acutally version number using cmd.
                if (!this.isDeb)
                {
                    verifyMySQLInstalledCmd = "rpm -qa|grep -i mysql-cimprov";
                }
                string commandStdOut = this.MySQLHelper.RunCmd(verifyMySQLInstalledCmd).StdOut;
            }
            catch
            {
                if (isInstalled)
                {
                    throw new VarAbort("running verifyMySQLInstalledCmd failed");
                }
            }
        }

        /// <summary>
        /// Generic wait method for use to allow the state of the installed agent to stabilize
        /// </summary>
        /// <param name="ctx">Current MCF context</param>
        public void Wait(IContext ctx)
        {
            ctx.Trc(string.Format("Waiting for {0}...", this.queryRetryInterval));
            System.Threading.Thread.Sleep(this.queryRetryInterval);
        }

        #endregion HelpMethod
    }
}
