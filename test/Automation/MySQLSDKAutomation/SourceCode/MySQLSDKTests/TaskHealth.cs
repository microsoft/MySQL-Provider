//-----------------------------------------------------------------------
// <copyright file="TaskHealth.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-ashu</author>
// <description></description>
// <history>5/25/2010 2:30:10 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.Test.MySQL.SDK.MySQLSDKTests
{
    using System;
    using System.Collections.Generic;
    using System.IO; 
    using Infra.Frmwrk;
    using Microsoft.EnterpriseManagement.Monitoring;
    using Scx.Test.Common;
    using Scx.Test.MySQL.SDK.MySQLSDKHelper;
    using System.Text.RegularExpressions;

    /// <summary>
    /// Description for TaskHealth.
    /// </summary>
    public class TaskHealth : ISetup, IRun, ICleanup
    {
        #region Private Fields

        /// <summary>
        /// Period of time to wait for OM Server to update its internal state to match changes on the agent.
        /// </summary>
        private TimeSpan serverWaitTime = new TimeSpan(0, 1, 0);

        /// <summary>
        /// Imformation about the OM server.
        /// </summary>
        private OMInfo info;

        /// <summary>
        /// Information about the client machine
        /// </summary>
        private ClientInfo clientInfo;

        /// <summary>
        /// Path to the agent cache; deployment tasks cannot deploy directly from a network share.
        /// </summary>
        private string agentCachePath = "agentCache";

        /// <summary>
        /// AgentHelper class from ScxCommon for manual finding agent on server.
        /// </summary>
        private AgentHelper agentHelper;

        /// <summary>
        /// Old agent for unix client
        /// </summary>
        private FileInfo oldAgentFile;

        /// <summary>
        /// Discovery helper class
        /// </summary>
        private DiscoveryHelper discoveryHelper;

        /// <summary>
        /// Store the POSIX command shell mechanism
        /// </summary>
        private RunPosixCmd posixCmd;

        /// <summary>
        /// Maximum number of times to wait for server state change
        /// </summary>
        private int maxServerWaitCount = 10;

        #endregion

        #region Methods

        #region Test Framework Methods

        /// <summary>
        /// Test framework setup method
        /// </summary>
        /// <param name="ctx">Current context</param>
        void ISetup.Setup(IContext ctx)
        {
            ctx.Trc("Scx.test.sdk.SDKTests.TaskHealth setup");
            try
            {
                this.info = new OMInfo(
                        ctx.ParentContext.Records.GetValue("omserver"),
                        ctx.ParentContext.Records.GetValue("omusername"),
                        ctx.ParentContext.Records.GetValue("omdomain"),
                        ctx.ParentContext.Records.GetValue("ompassword"),
                        ctx.ParentContext.Records.GetValue("defaultresourcepool"));

                this.clientInfo = new ClientInfo(
                    ctx.ParentContext.Records.GetValue("hostname"),
                    ctx.ParentContext.Records.GetValue("ipaddress"),
                    ctx.ParentContext.Records.GetValue("targetcomputerclass"),
                    ctx.ParentContext.Records.GetValue("managementpack"),
                    ctx.ParentContext.Records.GetValue("architecture"),
                    ctx.ParentContext.Records.GetValue("nonsuperuser"),
                    ctx.ParentContext.Records.GetValue("nonsuperuserpwd"),
                    ctx.ParentContext.Records.GetValue("superuser"),
                    ctx.ParentContext.Records.GetValue("superuserpwd"),
                    ctx.ParentContext.Records.GetValue("packagename"),
                    ctx.ParentContext.Records.GetValue("cleanupcommand"),
                    ctx.ParentContext.Records.GetValue("platformtag"));

                ctx.Trc("OMInfo: " + Environment.NewLine + this.info.ToString());
                ctx.Trc("ClientInfo: " + Environment.NewLine + this.clientInfo.ToString());

                this.discoveryHelper = new DiscoveryHelper(this.info, this.clientInfo);
                this.discoveryHelper.Logger = ctx.Trc;

                this.posixCmd = new RunPosixCmd(this.clientInfo.HostName, this.clientInfo.SuperUser, this.clientInfo.SuperUserPassword);

                this.agentHelper = new AgentHelper(
                         ctx.Trc,
                         this.clientInfo.HostName,
                         this.clientInfo.SuperUser,
                         this.clientInfo.SuperUserPassword,
                         "echo", //// this agent helper instance will never perform an install
                         this.clientInfo.CleanupCommand);

                this.agentHelper.AgentPkgExt = ctx.ParentContext.Records.GetValue("AgentPkgExt");
                this.agentHelper.DirectoryTag = ctx.ParentContext.Records.GetValue("DirectoryTag");
                this.agentHelper.DropLocation = ctx.ParentContext.Records.GetValue("remoteagents");

                this.agentHelper.VerifySSH();
                this.agentHelper.SynchDateTime();

                ctx.Trc("Searching an old agent");
                this.oldAgentFile = this.FindAgent(ctx, false);
                if (this.oldAgentFile == null)
                {
                    throw new Exception("No agent found!");
                }

                ctx.Trc("the old agent found: " + this.oldAgentFile.FullName);
            }
            catch (Exception ex)
            {
                this.Abort(ctx, ex.ToString());
            }

            ctx.Trc("Scx.test.sdk.SDKTests.TaskHealth setup completed!");
        }

        /// <summary>
        /// Test framework run method
        /// </summary>
        /// <param name="ctx">Current context</param>
        void IRun.Run(IContext ctx)
        {
            ctx.Trc("Scx.test.sdk.SDKTests.TaskHealth run");
            try
            {
                ////Uninstall current agent from Unix Client using "Elevated.Agent.Uninstall.Task", for example: "Microsoft.Linux.RHEL.5.Elevated.Agent.Uninstall.Task"                        
                this.ElevatedUninstallAgent(ctx);
                this.VerifyAgentNotExist(ctx);

                ////Install an old agent to Unix Client using "Elevated.Agent.Install.Task", for example: "Microsoft.Linux.RHEL.5.Elevated.Agent.Install.Task"
                this.ElevatedInstallAgent(ctx);
                this.VerifyAgentExist(ctx, this.oldAgentFile);

                ////Upgrade an old agent to the signed agent in Unix Client using "Elevated.Agent.Upgrade.Task", for example: "Microsoft.Linux.RHEL.5.Elevated.Agent.Upgrade.Task"
                FileInfo upgradeAgent = this.ElevatedUpgradeAgent(ctx);
                this.VerifyAgentExist(ctx, upgradeAgent);
            }
            catch (Exception ex)
            {
                this.Fail(ctx, ex.ToString());
            }

            ctx.Trc("Scx.test.sdk.SDKTests.TaskHealth run completed!");
        }

        /// <summary>
        /// Test framework cleanup method
        /// </summary>
        /// <param name="ctx">Current context</param>
        void ICleanup.Cleanup(IContext ctx)
        {
            ctx.Trc("SDKTests.TaskHealth.Cleanup");
            this.RecoveryAgent(ctx);

            ctx.Trc("SDKTests.TaskHealth.Cleanup finished");
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// Upgrade an old agent to the signed agent in Unix Client using "Elevated.Agent.Upgrade.Task", 
        /// for example: "Microsoft.Linux.RHEL.5.Elevated.Agent.Upgrade.Task"
        /// </summary>
        /// <param name="ctx">Object for log</param>
        /// <returns>return a file information of the upgrade agent</returns>
        private FileInfo ElevatedUpgradeAgent(IContext ctx)
        {
            string elevatedUpgradeAgentTask = ctx.Records.GetValue("ElevatedUpgradeAgentTask");
            ctx.Alw("Upgrade the latest agent to " + this.clientInfo.HostName + " using task named: " + elevatedUpgradeAgentTask);

            FileInfo upgradeAgent = this.FindAgent(ctx, true);
            ctx.Alw("The new agent: " + upgradeAgent.FullName);

            IList<Microsoft.EnterpriseManagement.Runtime.TaskResult> taskResults = this.discoveryHelper.ElevatedUpgradeClient(upgradeAgent.FullName, elevatedUpgradeAgentTask);

            foreach (Microsoft.EnterpriseManagement.Runtime.TaskResult result in taskResults)
            {
                if (result.Status != Microsoft.EnterpriseManagement.Runtime.TaskStatus.Succeeded)
                {
                    this.Fail(ctx, "Elevated upgrade agent task not successed");
                }
            }

            ctx.Alw("Upgrade Agent task executed complete successful");            
            return upgradeAgent;
        }

        /// <summary>
        /// Install an old agent to Unix Client using "Elevated.Agent.Install.Task", for example: "Microsoft.Linux.RHEL.5.Elevated.Agent.Install.Task"
        /// </summary>
        /// <param name="ctx">Object for log</param>
        private void ElevatedInstallAgent(IContext ctx)
        {            
            string elevatedInstallAgentTask = ctx.Records.GetValue("ElevatedInstallAgentTask");
            ctx.Alw("Install an old agent from " + this.clientInfo.HostName + " using task named: " + elevatedInstallAgentTask);

            IList<Microsoft.EnterpriseManagement.Runtime.TaskResult> taskResults = this.discoveryHelper.ElevatedInstallClient(this.oldAgentFile.FullName, elevatedInstallAgentTask);

            for (int i = 0; i < taskResults.Count; i++)
            {
                if (taskResults[i].Status != Microsoft.EnterpriseManagement.Runtime.TaskStatus.Succeeded)
                {
                    this.Fail(ctx, "Elevated install agent task failed");
                }
            }

            ctx.Alw("Elevated install agent task executed complete!");
        }

        /// <summary>
        /// Uninstall current agent from Unix Client using "Elevated.Agent.Uninstall.Task", for example: "Microsoft.Linux.RHEL.5.Elevated.Agent.Uninstall.Task"                        
        /// </summary>
        /// <param name="ctx">Object for log</param>
        private void ElevatedUninstallAgent(IContext ctx)
        {
            string elevatedUninstallAgentTask = ctx.Records.GetValue("ElevatedUninstallAgentTask");
            ctx.Alw("Uninstall current agent from " + this.clientInfo.HostName + " using task named: " + elevatedUninstallAgentTask);
            IList<Microsoft.EnterpriseManagement.Runtime.TaskResult> taskResults = this.discoveryHelper.ElevatedUninstallClient(elevatedUninstallAgentTask);

            for (int i = 0; i < taskResults.Count; i++)
            {
                if (taskResults[i].Status != Microsoft.EnterpriseManagement.Runtime.TaskStatus.Succeeded)
                {
                    this.Fail(ctx, "Elevated unnstall agent task failed!");                    
                }
            }

            ctx.Alw("Elevated uninstall agent task execute completed!");
        }
        
        /// <summary>
        /// verify the Agent exist in Unix/Linux client
        /// </summary>
        /// <param name="ctx">Object for log</param>
        /// <param name="agent">the information of upgrade agent</param>
        private void VerifyAgentExist(IContext ctx, FileInfo agent)
        {
            ctx.Alw("Verify that the agent installed success in " + this.clientInfo.HostName);
            try
            {
                string appInstalledVerifyCmd = ctx.Records.GetValue("AppInstalledVerifyCmd");
                this.posixCmd.ExpectToPass = true;
                if (this.clientInfo.ManagementPackName.Contains("Linux"))
                {
                    ////For other platforms
                    string installedAppName = agent.Name.Substring(0, agent.Name.IndexOf(this.clientInfo.PlatformTag) - 1);
                    this.posixCmd.RunCmd(appInstalledVerifyCmd);
                    if (!this.posixCmd.StdOut.Contains(installedAppName))
                    {
                        this.Fail(ctx, string.Format("Agent '{0}' does not exit on '{1}' unexpectedly.", agent.Name, this.clientInfo.HostName));
                    }
                }
                else
                {
                    string agentVersion = agent.Name.Substring(4, agent.Name.IndexOf(this.clientInfo.PlatformTag) - 5).Replace('-', '.');
                    if (this.clientInfo.ManagementPackName.Contains("AIX"))
                    {
                        agentVersion = agent.Name.Substring(4, agent.Name.IndexOf(this.clientInfo.PlatformTag) - 5).Replace('-', '.');
                    }
                    else
                    {
                        agentVersion = agent.Name.Substring(4, agent.Name.IndexOf(this.clientInfo.PlatformTag) - 5);
                    }

                    this.posixCmd.RunCmd(appInstalledVerifyCmd);
                    if (!this.posixCmd.StdOut.Contains(agentVersion))
                    {
                        this.Fail(ctx, string.Format("Agent '{0}' does not exit on {1} unexpectedly.", agent.Name, this.clientInfo.HostName));
                    }
                }

                ctx.Alw(string.Format("Agent {0} is found on {1} as expected", agent.Name, this.clientInfo.HostName));
            }
            catch (Exception ex)
            {
                this.Fail(ctx, ex.Message);
            }
        }

        /// <summary>
        /// verify that no agent installed in Unix client
        /// </summary>
        /// <param name="ctx">Object for log</param>
        private void VerifyAgentNotExist(IContext ctx)
        {         
            ctx.Alw("verify that agent has been uninstalled successfully");
            string appInstalledVerifyCmd = ctx.Records.GetValue("AppInstalledVerifyCmd");
            try
            {
                if (this.clientInfo.ManagementPackName.Contains("HPUX"))
                {
                    FileInfo currentAgent = this.FindAgent(ctx, true);
                    string agentVersion = currentAgent.Name.Substring(4, currentAgent.Name.IndexOf(this.clientInfo.PlatformTag) - 5);
                    this.posixCmd.ExpectToPass = true;
                    this.posixCmd.RunCmd(appInstalledVerifyCmd);
                    if (this.posixCmd.StdOut.Contains(agentVersion))
                    {
                        throw new Exception("The agent uninstalled fail!");
                    }
                }
                else
                {
                    ////For other platforms
                    this.posixCmd.ExpectToPass = false;
                    this.posixCmd.RunCmd(appInstalledVerifyCmd);
                }
            }
            catch (Exception ex)
            {
                this.Fail(ctx, ex.Message);
            }

            ctx.Alw("The agent has been uninstalled successfully");
        }

        /// <summary>
        /// Install current agent to Unix client to recovery the linux client environment
        /// </summary>
        /// <param name="ctx">Object for log</param>
        private void RecoveryAgent(IContext ctx)
        {
            ctx.Alw("Recovery agent to client machine.");

            ctx.Alw("Delete computer from OM...");
            this.discoveryHelper.DeleteSystemFromOM();

            ctx.Trc("Cleaning agent from client machine");
            this.discoveryHelper.CleanupRemoteClient();

            ctx.Trc("Deploying/installing agent on client machine");
            FileInfo newAgent = this.FindAgent(ctx, true);
            this.discoveryHelper.InstallClient(newAgent.FullName);

            ctx.Trc("Signing agent");
            this.discoveryHelper.CreateSignedCert();

            ctx.Trc("Adding client to OM");
            this.discoveryHelper.DiscoverClientWSMan();
            
            ctx.Trc("Verify that client in OM");
            this.WaitForClientVerification(ctx);

            ctx.Trc("Unix client environment recoveried!");
        }

        /// <summary>
        /// To find an agent
        /// </summary>
        /// <param name="ctx">Object for log</param>
        /// <param name="findNewAgent">true: we will find a new agent, false:we will find an old agent</param>
        /// <returns>return an agent file object</returns>
        private FileInfo FindAgent(IContext ctx, bool findNewAgent)
        {
            FileInfo agentFile;
            if (!findNewAgent)
            {
                ctx.Alw("Try to find an old agent path");
                string oldAgentPath = ctx.ParentContext.Records.GetValue("localagents") + "\\old";
                agentFile = this.GetAgent(ctx, oldAgentPath);
            }
            else
            {
                bool useLocalAgent = false;
                if (ctx.ParentContext.Records.GetValue("uselocalagents") == "true")
                {
                    useLocalAgent = true;
                }

                if (useLocalAgent)
                {
                    string localAgents = ctx.ParentContext.Records.GetValue("LocalAgents");

                    ctx.Trc("Searching agent in " + localAgents);
                    agentFile = this.GetAgent(ctx, localAgents);
                }
                else
                {
                    this.agentCachePath = Path.Combine(System.Environment.CurrentDirectory, this.agentCachePath);

                    ctx.Trc("Searching new agent");
                    agentFile = this.GetAgent(ctx, this.agentCachePath);
                    if (agentFile != null)
                    {
                        ctx.Trc("Agent already in cache: " + agentFile.FullName);
                    }
                    else
                    {
                        this.agentHelper.FindAgent(false, string.Empty, 5, true);
                        string fullNewAgentPath = Path.Combine(this.agentCachePath, Path.GetFileName(this.agentHelper.FullAgentPath));
                        ctx.Trc("Copying agent to: " + fullNewAgentPath);
                        File.Copy(this.agentHelper.FullAgentPath, fullNewAgentPath, true);
                        agentFile = this.GetAgent(ctx, this.agentCachePath);
                    }
                }
            }

            return agentFile;
        }

        /// <summary>
        /// To get an agent from the agent path
        /// </summary>
        /// <param name="ctx">Object for log</param>
        /// <param name="agentPath">The path we will look for the agent file in</param>
        /// <returns>Return an agent file object </returns>
        private FileInfo GetAgent(IContext ctx, string agentPath)
        {
            FileInfo agentFile;
            if (Directory.Exists(agentPath))
            {
                ctx.Alw("The directory is already existed: " + agentPath);
            }
            else
            {
                this.Abort(ctx, "The directory of the agent doesn't existed");
            }

            ctx.Alw("Try to find the agent file");
            DirectoryInfo di = new DirectoryInfo(agentPath);
            FileInfo[] agentFiles = di.GetFiles("*" + this.clientInfo.PlatformTag + "*");
            if (agentFiles.Length == 1)
            {
                ctx.Alw("An agent file found: " + agentFiles[0].FullName);
                agentFile = agentFiles[0];
            }
            else
            {
                ctx.Alw("There should be only one agent for the platform " + this.clientInfo.PlatformTag + "!");
                agentFile = null;
            }

            return agentFile;
        }
        
        /// <summary>
        /// Wait until it is possible to verify the client is added to OM and correctly monitoring
        /// at least the heartbeat and certificate monitors on the agent.
        /// </summary>
        /// <param name="ctx">Current context</param>
        private void WaitForClientVerification(IContext ctx)
        {
            bool clientVerified = this.discoveryHelper.VerifySystemInOM();

            int numTries = 0;

            while (numTries < this.maxServerWaitCount && !clientVerified)
            {
                this.Wait(ctx);

                numTries++;

                clientVerified = this.discoveryHelper.VerifySystemInOM();

                ctx.Trc(string.Format("VerifySystem({0})={1} after {2}/{3} tries", this.clientInfo.HostName, clientVerified, numTries, this.maxServerWaitCount));
            }

            if (clientVerified)
            {
                ctx.Alw("client verified: " + this.clientInfo.HostName);
            }
            else
            {
                this.Abort(ctx, "client verification failed: " + this.clientInfo.HostName);
            }
        }

        /// <summary>
        /// Fail the text case by printing out a log message and throwing an exception
        /// </summary>
        /// <param name="ctx">Current context</param>
        /// <param name="msg">Error message</param>
        private void Fail(IContext ctx, string msg)
        {
            ctx.Trc("TaskHealth FAIL: " + msg);
            throw new VarFail(msg);
        }

        /// <summary>
        /// Abort the text case by printing out a log message and throwing an exception
        /// </summary>
        /// <param name="ctx">Current context</param>
        /// <param name="msg">Error message</param>
        private void Abort(IContext ctx, string msg)
        {
            ctx.Trc("TaskHealth ABORT: " + msg);
            throw new VarAbort(msg);
        }

        /// <summary>
        /// Generic wait method for use to allow OM internal state to stabilize.
        /// </summary>
        /// <param name="ctx">Current context</param>
        private void Wait(IContext ctx)
        {
            ctx.Trc(string.Format("Waiting for {0}...", this.serverWaitTime));
            System.Threading.Thread.Sleep(this.serverWaitTime);
        }

        #endregion

        #endregion
    }
}
