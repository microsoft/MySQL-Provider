//-----------------------------------------------------------------------
// <copyright file="AvailabilityHealth.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-litin</author>
// <description>AvailabilityHealth</description>
//-----------------------------------------------------------------------

namespace Scx.Test.MySQL.SDK.MySQLSDKTests
{
    using System;
    using System.Threading;
    using Infra.Frmwrk;
    using Microsoft.EnterpriseManagement.Configuration;
    using Microsoft.EnterpriseManagement.Monitoring;
    using Scx.Test.Common;
    using Scx.Test.MySQL.SDK.MySQLSDKHelper;

    public class AvailabilityHealth : PerformanceHealthBase, ISetup, IRun, IVerify, ICleanup
    {
        /// <summary>
        /// Initializes a new instance of the AvailabilityHealth class
        /// </summary>
        public AvailabilityHealth()
        {
        }

        /// <summary>
        /// MySQL agent helper class
        /// </summary>
        private MySQLAgentHelper mysqlAgentHelper;

        #region Test Framework Methods

        /// <summary>
        /// Framework setup method
        /// </summary>
        /// <param name="ctx">Current context</param>
        void ISetup.Setup(IContext ctx)
        {
            if (this.SkipThisTest(ctx))
            {
                ctx.Trc("BYPASSING TEST CASE (ISetup.Setup): " + ctx.Records.GetValue("entityname"));
                return;
            }

            ctx.Trc("SDKTests.MySQLServerHealth.Setup");

            try
            {
                this.Info = new OMInfo(
                    ctx.ParentContext.Records.GetValue("omserver"),
                    ctx.ParentContext.Records.GetValue("omusername"),
                    ctx.ParentContext.Records.GetValue("omdomain"),
                    ctx.ParentContext.Records.GetValue("ompassword"),
                    ctx.ParentContext.Records.GetValue("defaultresourcepool"));

                this.ClientInfo = new ClientInfo(
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

                ctx.Trc("OMInfo: " + Environment.NewLine + this.Info.ToString());

                ctx.Trc("ClientInfo: " + Environment.NewLine + this.ClientInfo.ToString());

                this.mysqlAgentHelper = new MySQLAgentHelper(this.Info, this.ClientInfo);

                this.MonitorHelper = new MonitorHelper(this.Info);

                this.AlertHelper = new AlertsHelper(this.Info);

                this.OverrideHelper = new OverrideHelper(ctx.Trc, this.Info, ctx.ParentContext.Records.GetValue("testingoverride"));

                this.ComputerObject = this.MonitorHelper.GetComputerObject(this.ClientInfo.HostName);

                this.RecoverMonitorIfFailed(ctx);

                this.CloseMatchingAlerts(ctx);

                //Because of there is a active bug 831295, so disable the steps
                //this.VerifyMonitor(ctx, HealthState.Success);

                //this.VerifyAlert(ctx, false);

                if (ctx.Records.HasKey("needUninstallMySQL") &&
                    ctx.Records.GetValue("needUninstallMySQL") == "true")
                {
                    string fullMySQLAgentPath = ctx.ParentContext.Records.GetValue("mysqlAgentPath");
                    string tag = ctx.ParentContext.Records.GetValue("mysqlTag");
                    this.mysqlAgentHelper.UninstallMySQLAgentWihCommand(fullMySQLAgentPath, tag);
                }

            }
            catch (Exception ex)
            {
                this.Abort(ctx, ex.ToString());
            }

            ctx.Trc("SDKTests.MySQLServerHealth.Setup complete");
        }

        /// <summary>
        /// Framework Run method
        /// </summary>
        /// <param name="ctx">Current context</param>
        void IRun.Run(IContext ctx)
        {
            string entity = ctx.Records.GetValue("entityname");
            string action = ctx.Records.GetValue("ActionCmd");
            string monitorName = ctx.Records.GetValue("monitorname");
            string diagnosticName = ctx.Records.GetValue("diagnostics");
            string recoveryCmd = ctx.Records.GetValue("PostCmd");
            string targetOSClassName = ctx.ParentContext.Records.GetValue("targetosclass");

            if (this.SkipThisTest(ctx))
            {
                return;
            }

            ctx.Trc("SDKTests.MySQLServerHealth.Run with entity " + entity);

            try
            {
                if (!(string.IsNullOrEmpty(action)))
                {
                    ctx.Alw("Running command synchronously (may take a while): " + action);
                    RunCmd(action);
                }

                string expectedMonitorState = ctx.Records.GetValue("ExpectedState");
                HealthState requiredState = this.GetRequiredState(expectedMonitorState);

                //// Waiting for 5 minutes directly to make sure that OM can get the latest monitor state
                //// because the latest monitor state might be the same as the initial state
                if (ctx.Records.GetValue("ExpectedState").Equals("success", StringComparison.CurrentCultureIgnoreCase))
                {
                    this.Wait(ctx, 300);

                    this.VerifyMonitor(ctx, requiredState);

                    this.VerifyAlert(ctx, false);
                }
                else
                {
                    this.VerifyMonitor(ctx, requiredState);

                    this.VerifyAlert(ctx, false);
                }

                // Run the recovery command
                if (!(string.IsNullOrEmpty(recoveryCmd)))
                {
                    ctx.Trc("Running recovery command: " + recoveryCmd);
                    RunCmd(recoveryCmd);
                    //Because of there is a active bug 727207, so disable the steps
                    //this.VerifyAlert(ctx, false);
                }
            }
            catch (Exception ex)
            {
                this.Fail(ctx, ex.ToString());
            }

            ctx.Trc("SDKTests.MySQLServerHealth.Run complete");
        }

        /// <summary>
        /// Framework verify method
        /// </summary>
        /// <param name="ctx">current context</param>
        void IVerify.Verify(IContext ctx)
        {
            if (this.SkipThisTest(ctx))
            {
                return;
            }

            ctx.Trc("SDKTests.MySQLServerHealth.Verify");

            try
            {
                //Because of there is a active bug 727207, so disable the steps
                //this.VerifyMonitor(ctx, HealthState.Success);
            }
            catch (Exception ex)
            {
                this.Fail(ctx, ex.ToString());
            }

            ctx.Trc("SDKTests.MySQLServerHealth.Verify complete");
        }

        /// <summary>
        /// Framework cleanup method
        /// </summary>
        /// <param name="ctx">Current context</param>
        void ICleanup.Cleanup(IContext ctx)
        {
            if (this.SkipThisTest(ctx))
            {
                return;
            }

            if (ctx.Records.HasKey("needUninstallMySQL") &&
                ctx.Records.GetValue("needUninstallMySQL") == "true")
            {
                string fullMySQLAgentPath = ctx.ParentContext.Records.GetValue("mysqlAgentPath");
                string tag = ctx.ParentContext.Records.GetValue("mysqlTag");
                this.mysqlAgentHelper.InstallMySQLAgentWihCommand(fullMySQLAgentPath, tag);

                // Add the mySQL Auth for superuser and nonsuperuser
                string mySQLAddAuthCmd = ctx.ParentContext.Records.GetValue("mySQLAddAuthCmd");
                this.mysqlAgentHelper.SetupMySqlAuth(mySQLAddAuthCmd);

                string mySQLAddNonSuperUserAuthCmd = ctx.ParentContext.Records.GetValue("mySQLAddNonSuperUserAuthCmd");
                this.mysqlAgentHelper.SetupMySqlAuthForNonSuperUser(mySQLAddNonSuperUserAuthCmd);
            }
            //remove all scripts
            RunCmd("rm -rf /tmp/*.sh");

            ctx.Trc("SDKTests.MySQLServerHealth.Cleanup finished");
        }

        #endregion Test Framework Methods

        #region Private Methods

        private RunPosixCmd RunCmd(string cmd, string arguments = "")
        {
            // Begin cmd
            RunPosixCmd execCmd = new RunPosixCmd(this.ClientInfo.HostName, this.ClientInfo.SuperUser, this.ClientInfo.SuperUserPassword);

            // Execute command
            execCmd.FileName = cmd;
            execCmd.Arguments = arguments;
            execCmd.RunCmd();
            return execCmd;
        }


        #endregion
    }
}
