//-----------------------------------------------------------------------
// <copyright file="VerifyCimProvAuth.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-jeali</author>
// <description></description>
// <history>12/8/2014 10:29:44 PM: Created</history>
//-----------------------------------------------------------------------
namespace Scx.Test.MySQL.Provider.VerifyCimProv
{
    using Infra.Frmwrk;
    using System;

    /// <summary>
    /// VerifyCimProvAuth
    /// </summary>
    class VerifyCimProvAuth : VerifyCimProvHelper, ISetup, IRun, IVerify, ICleanup
    {
        string addMySQLAuthCmd;
        string mysqlCmd;
        string verifyAuthFolderExistCmd;
        string verifyAuthFileProtectionCmd;
        string expectedAuthFolderCount;
        string expectedAuthFileOwner;
        string expectedAuthFileProtection;
        string expectedOperatingStatus;
        string commandStdOut;

        /// <summary>
        /// set up 
        /// </summary>
        /// <param name="ctx">IContext</param>
        public void Setup(IContext ctx)
        {
            this.GetValueFromVarList(ctx);
            this.Wait(ctx);
            if (ctx.Records.HasKey("AddMySQLAuthCmd"))
            {
                this.addMySQLAuthCmd = ctx.Records.GetValue("AddMySQLAuthCmd");
                this.MySQLHelper.SetupMySqlAuth(this.addMySQLAuthCmd);
            }

            if (ctx.Records.HasKey("mysqlCmd"))
            {
                this.mysqlCmd = ctx.Records.GetValue("mysqlCmd");
            }
            if (ctx.Records.HasKey("VerifyAuthFolderExistCmd"))
            {
                this.verifyAuthFolderExistCmd = ctx.Records.GetValue("VerifyAuthFolderExistCmd");
            }
            if (ctx.Records.HasKey("VerifyAuthFileProtectionCmd"))
            {
                this.verifyAuthFileProtectionCmd = ctx.Records.GetValue("VerifyAuthFileProtectionCmd");
            }
            if (ctx.Records.HasKey("expectedAuthFolderCount"))
            {
                this.expectedAuthFolderCount = ctx.Records.GetValue("expectedAuthFolderCount");
            }
            if (ctx.Records.HasKey("expectedAuthFileOwner"))
            {
                this.expectedAuthFileOwner = ctx.Records.GetValue("expectedAuthFileOwner");
            }
            if (ctx.Records.HasKey("expectedAuthFileProtection"))
            {
                this.expectedAuthFileProtection = ctx.Records.GetValue("expectedAuthFileProtection");
            }
            if (ctx.Records.HasKey("expectedOperatingStatus"))
            {
                this.expectedOperatingStatus = ctx.Records.GetValue("expectedOperatingStatus");
            }
        }

        /// <summary>
        /// running case
        /// </summary>
        /// <param name="ctx">IContext</param>
        public void Run(IContext ctx)
        {
            try
            {
                commandStdOut = this.MySQLHelper.RunCmd(this.mysqlCmd).StdOut;
            }
            catch (Exception e)
            {
                throw new Exception("Enumerate MySQL_Server failed: " + e.Message);
            }
        }

        /// <summary>
        /// Verify
        /// </summary>
        /// <param name="ctx">Context</param>
        public void Verify(IContext ctx)
        {
            // verify AuthFolder Exist. 
            this.VerifyFolderExist(this.verifyAuthFolderExistCmd, this.expectedAuthFolderCount, true);

            // verify Enumerated value OperatingStatus for MySQL_Server.
            this.VerifyCommandStdOutLog(commandStdOut, this.expectedOperatingStatus, true);

            // verify Auth File Protection.
            string expectedAuthFileProtectioncommandStdOut = this.MySQLHelper.RunCmd(this.verifyAuthFileProtectionCmd).StdOut;
            this.VerifyCommandStdOutLog(expectedAuthFileProtectioncommandStdOut, this.expectedAuthFileOwner, true);
            this.VerifyCommandStdOutLog(expectedAuthFileProtectioncommandStdOut, this.expectedAuthFileProtection, true);
        }

        /// <summary>
        /// Clean up test case
        /// </summary>
        /// <param name="ctx"></param>
        public void Cleanup(IContext ctx)
        {
            if (ctx.Records.HasKey("removeMySQLAuthCmd"))
            {
                string removeMySQLAuthCmd = ctx.Records.GetValue("removeMySQLAuthCmd");
                string password = ctx.ParentContext.Records.GetValue("password");
                this.RunCommandAsRoot(removeMySQLAuthCmd, password);
            }
        }
    }
}
