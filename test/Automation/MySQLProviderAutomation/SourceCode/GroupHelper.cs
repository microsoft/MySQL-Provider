//-----------------------------------------------------------------------
// <copyright file="GroupHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-jeyin@microsoft.com</author>
// <description></description>
//-----------------------------------------------------------------------

namespace Scx.Test.MySQL.Provider
{
    using System;
    using Infra.Frmwrk;
    using Scx.Test.Common;

    public class GroupHelper : ISetup, ICleanup
    /*ICleanup*/
    {
        //private SshHelper sshHelper;

        #region Private Fields

        /// <summary>
        /// Required: Name of Posix host (DNS or IP)
        /// </summary>
        private string hostName;

        /// <summary>
        /// Required: User name
        /// </summary>
        private string userName;

        /// <summary>
        /// Required: User's password
        /// </summary>
        private string password;

        /// <summary>
        /// Required: Command to install agent
        /// </summary>
        private string installOmCmd;
        private string installMySQLCmd;

        /// <summary>
        /// Required: Command to remove agent
        /// </summary>
        private string uninstallOmCmd;
        private string uninstallMySQLCmd;

        /// <summary>
        /// Required: Command to clean the Client Machine:Uninstall/delete scx direcotries
        /// </summary>
        private string cleanupOmCmd;
        private string cleanupMySQLCmd;

        /// <summary>
        /// Required: string tag used in identifying the platform
        /// </summary>
        private string platformTag;
        private string MySQLTag;

        ///<summary>
        ///Optional: check MySQL status command
        ///</summary>

        private string startMySQLCmd;
        private string checkServiceCmd;

        /// <summary>
        /// Class AgentHelper : contain some operations of agent.
        /// </summary>
        private AgentHelper agentHelper;
        private MySQLHelper mySQLHelper;

        #endregion

        #region Public method
        public void Setup(IContext ctx)
        {
            try
            {
                if (ctx.Records.HasKey("skipagentdeploy") &&
                    ctx.Records.GetValue("skipagentdeploy") == "true")
                {
                    ctx.Trc("Skipping agent deployment/cleanup");
                    return;
                }

                foreach (string key in ctx.Records.GetKeys())
                {
                    ctx.Trc("Setup key=" + key + ", value=" + ctx.Records.GetValue(key));
                }

                this.hostName = ctx.Records.GetValue("hostname");
                if (string.IsNullOrEmpty(this.hostName))
                {
                    throw new GroupAbort("hostname not specified");
                }

                ctx.Trc("GroupAgentDeploy: hostname = " + this.hostName);

                this.userName = ctx.Records.GetValue("username");
                this.password = ctx.Records.GetValue("password");
                this.installOmCmd = ctx.Records.GetValue("InstallOMCmd");
                this.uninstallOmCmd = ctx.Records.GetValue("UninstallOMCmd");
                this.cleanupOmCmd = ctx.Records.GetValue("CleanupOMCmd");
                // get GetPlatformTag
                // this.platformTag = ctx.Records.GetValue("PlatformTag");
                this.platformTag = GetPlatformTag(this.hostName);
                this.MySQLTag = ctx.Records.GetValue("MySQLTag");
                this.installMySQLCmd = ctx.Records.GetValue("installmySQLCmd");
                this.uninstallMySQLCmd = ctx.Records.GetValue("UninstallMySQLCmd");
                this.cleanupMySQLCmd = ctx.Records.GetValue("CleanupMySQLCmd");
                this.startMySQLCmd = ctx.Records.GetValue("startMySQLCmd");
                this.checkServiceCmd = ctx.Records.GetValue("checkServiceCmd");

                if (string.IsNullOrEmpty(this.userName) ||
                    string.IsNullOrEmpty(this.password) || string.IsNullOrEmpty(this.installOmCmd) ||
                    string.IsNullOrEmpty(this.platformTag) || string.IsNullOrEmpty(this.uninstallOmCmd) || string.IsNullOrEmpty(this.cleanupOmCmd))
                {
                    throw new GroupAbort("Error, check UserName, Password, installOmCmd, uninstallOmCmd, cleanupOmCmd, platformTag");
                }

                this.agentHelper = new AgentHelper(ctx.Trc, this.hostName, this.userName, this.password, this.installOmCmd, this.cleanupOmCmd);

                this.agentHelper.VerifySSH();

                this.agentHelper.SynchDateTime();

                this.mySQLHelper = new MySQLHelper(ctx.Trc, this.hostName, this.userName, this.password);

                this.mySQLHelper.CheckMySQLServiceStatus(this.checkServiceCmd);

                this.SetMySQLAgentPath(ctx);

                this.mySQLHelper.UninstallMySQLAgent(this.uninstallMySQLCmd);

                this.SetOmAgentPath(ctx);

                this.CleanupAgent(ctx);

                this.agentHelper.Install();

                this.mySQLHelper.InstallMySQLAgent(this.installMySQLCmd);
            }
            catch (Exception ex)
            {
                throw new GroupAbort(ex.Message);
            }
        }

        /// <summary>
        /// GetPlatformTag
        /// </summary>
        /// <param name="hostName">hostName</param>
        /// <returns>platformtag</returns>
        private string GetPlatformTag(string hostName)
        {
            string platformtagstr = string.Empty;
            if (hostName.ToLower().Contains("rhel") || hostName.ToLower().Contains("sles"))
            {
                string[] names = hostName.Split('-');
                platformtagstr = names[1].Substring(0, 4) + "." + (hostName.ToLower().Contains("sles") ? names[1].Substring(4, 2) : names[1].Substring(4, 1));
            }
            else if (hostName.ToLower().Contains("deb") || hostName.ToLower().Contains("ubun"))
            {
                platformtagstr = ".universald.1";
            }
            else
            {
                platformtagstr = ".universalr.1";
            }

            if (hostName.Contains("64"))
            {
                platformtagstr = platformtagstr + ".x64";
            }
            else
            {
                platformtagstr = platformtagstr + ".x86";
            }

            return platformtagstr;
        }

        /// <summary>
        /// Remove agent from Posix host
        /// </summary>
        /// <param name="ctx">MCF group context</param>
        public void Cleanup(IContext ctx)
        {
            try
            {
                // Check for Warnings in SCX logs
                this.agentHelper.ScxLogHelper("wsman", "Warning", true, this.platformTag, null);

                // Check for Errors in SCX logs
                this.agentHelper.ScxLogHelper("wsman", "Error", false, this.platformTag, null);

                bool installOnly = false;   // Optional: If exists in records and has a value, then agent won't be removed

                if (ctx.Records.HasKey("skipagentdeploy") &&
                    ctx.Records.GetValue("skipagentdeploy") == "true")
                {
                    ctx.Trc("Skipping agent deployment/cleanup");
                    return;
                }

                if (ctx.Records.HasKey("installonly") &&
                    ctx.Records.GetValue("installonly") == "true")
                {
                    installOnly = true;
                }

                if (installOnly == false)
                {
                    this.mySQLHelper.UninstallMySQLAgent(this.uninstallMySQLCmd);
                    this.mySQLHelper.Cleanup();
                    this.CleanupAgent(ctx);
                }
            }
            catch (Exception ex)
            {
                throw new GroupAbort(ex.Message);
            }

        }

        #endregion
        #region private method

        private void SetMySQLAgentPath(IContext ctx)
        {
            string mysqllocation = ctx.Records.GetValue("MySQLsLocation");

            this.mySQLHelper.SetMySQLAgentFullPath(mysqllocation, this.MySQLTag, true);
        }

        /// <summary>
        /// Set om agent path
        /// </summary>
        /// <param name="ctx"></param>
        private void SetOmAgentPath(IContext ctx)
        {
            string omilocation = ctx.Records.GetValue("OMAgentLocation");

            this.agentHelper.SetOmAgentFullPath(omilocation, this.platformTag, true);
        }

        private void CleanupAgent(IContext ctx)
        {
            try
            {
                // Calling the AgentHelper Uninstall method with Cleanup OM CMD
                this.agentHelper.Uninstall();
            }
            catch (Exception ex)
            {
                ctx.Trc("Cleanup failed: " + ex.Message);
            }
        }

        #endregion
    }
}
