
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
        /// Required: Command to install MySQL
        /// </summary>
        private string installMySQLCmd;

        /// <summary>
        /// Required: Command to install MySQL
        /// </summary>
        public string InstallMySQLCmd
        {
            get { return installMySQLCmd; }
            set { installMySQLCmd = value; }
        }

        /// <summary>
        /// Required: Command to remove MySQL 
        /// </summary>
        private string uninstallMySQLCmd;

        /// <summary>
        /// Required: Command to remove MySQL 
        /// </summary>
        public string UninstallMySQLCmd
        {
            get { return uninstallMySQLCmd; }
            set { uninstallMySQLCmd = value; }
        }

        /// <summary>
        /// Required: Command to clean mysql:Uninstall and delete direcotries
        /// </summary>
        private string cleanupMySQLCmd;

        /// <summary>
        /// Required: Command to clean mysql:Uninstall and delete direcotries
        /// </summary>
        public string CleanupMySQLCmd
        {
            get { return cleanupMySQLCmd; }
            set { cleanupMySQLCmd = value; }
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
        ///  Required: mysql Location path on local machine
        /// </summary>
        private string mysqlLocation;

        /// <summary>
        ///  Required: mysql Location path on local machine
        /// </summary>
        public string MySQLLocation
        {
            get { return mysqlLocation; }
            set { mysqlLocation = value; }
        }

        /// <summary>
        ///  Optional: useNonSuperUser
        /// </summary>
        private bool useNonSuperUser;

        /// <summary>
        ///  Optional: useNonSuperUser
        /// </summary>
        public bool UseNonSuperUser
        {
            get { return useNonSuperUser; }
            set { useNonSuperUser = value; }
        }

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

            this.InstallMySQLCmd = ctx.ParentContext.Records.GetValue("installMySQLCmd");
            if (String.IsNullOrEmpty(this.InstallMySQLCmd))
            {
                throw new VarAbort("hostname not specified");
            }

            this.UninstallMySQLCmd = ctx.ParentContext.Records.GetValue("UninstallMySQLCmd");
            if (String.IsNullOrEmpty(this.UninstallMySQLCmd))
            {
                throw new VarAbort("hostname not specified");
            }

            this.CleanupMySQLCmd = ctx.ParentContext.Records.GetValue("CleanupMySQLCmd");
            if (String.IsNullOrEmpty(this.CleanupMySQLCmd))
            {
                throw new VarAbort("hostname not specified");
            }

            this.MySQLTag = ctx.ParentContext.Records.GetValue("MySQLTag");
            if (String.IsNullOrEmpty(this.MySQLTag))
            {
                throw new VarAbort("hostname not specified");
            }

            this.MySQLLocation = ctx.ParentContext.Records.GetValue("MySQLsLocation");
            if (String.IsNullOrEmpty(this.MySQLLocation))
            {
                throw new VarAbort("MySQLsLocation not specified");
            }
            mysqlHelper = new MySQLHelper(ctx.Trc, this.hostName, this.userName, this.password, this.MySQLLocation, this.MySQLTag, true);
        }

        #region HelpMethod

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
                // verify the mysql pakage version.
                // file name like mysql-cimprov-1.0.0-29.universal.1.i686.sh.
                // version is 1.0.0.29.
                // get expected version number:
                string[] nameParts = this.MySQLHelper.mysqlAgentName.Split('-');
                string versionNumber = nameParts[2] + '.' + nameParts[3].Split('.')[0];
                string versionNumber01 = nameParts[2] + '-' + nameParts[3].Split('.')[0];

                // get acutally version number using cmd.
                string commandStdOut = this.MySQLHelper.RunCmd(verifyMySQLInstalledCmd).StdOut;
                if (!commandStdOut.Contains(versionNumber) && !commandStdOut.Contains(versionNumber01))
                {
                    throw new VarAbort("verify the mysql version failed");
                }
            }
            catch
            {
                if (isInstalled)
                {
                    throw new VarAbort("running verifyMySQLInstalledCmd failed");
                }
            }
        }

        #endregion HelpMethod
    }
}
