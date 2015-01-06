//-----------------------------------------------------------------------
// <copyright file="VerifyCimProvAuth.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-jeali</author>
// <description></description>
// <history>12/8/2014 10:29:44 PM: Created</history>
//-----------------------------------------------------------------------


namespace Scx.Test.MySQL.Provider.VerifyMySQLValue
{
    using Infra.Frmwrk;
    using Scx.Test.Common;
    using Scx.Test.MySQL.Provider.VerifyCimProv;
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    class VerifyMySQLValue : VerifyCimProvHelper, ISetup, IRun, IVerify, ICleanup
    {
        string productIdentifyingNumberMysqlcmd;
        string ProductIdentifyingNumber;
        string loginMysqlcmd;


        public void Setup(IContext ctx)
        {
            this.GetValueFromVarList(ctx);
            if (ctx.Records.HasKey("ProductIdentifyingNumberMysqlcmd"))
            {
                productIdentifyingNumberMysqlcmd = ctx.Records.GetValue("ProductIdentifyingNumberMysqlcmd");
            }

            if (ctx.Records.HasKey("p:ProductIdentifyingNumber"))
            {
                ProductIdentifyingNumber = ctx.Records.GetValue("ProductIdentifyingNumber");
            }

            if (ctx.Records.HasKey("loginMysqlcmd"))
            {
                loginMysqlcmd = ctx.Records.GetValue("loginMysqlcmd");
            }
        }

        public void Run(IContext ctx)
        {
            // Begin cmd
            RunPosixCmd execCmd = new RunPosixCmd(this.HostName, this.UserName, this.Password);
            execCmd.FileName = loginMysqlcmd;
            execCmd.RunCmd();
            ctx.Trc(string.Format("Command {0} out: {1}", execCmd.FileName, execCmd.StdOut));

            RunPosixCmd execCmd01 = new RunPosixCmd(this.HostName, this.UserName, this.Password);
            execCmd01.FileName = productIdentifyingNumberMysqlcmd;
            execCmd01.RunCmd();
            ctx.Trc(string.Format("Command {0} out: {1}", execCmd.FileName, execCmd.StdOut));
        }

        public void Verify(IContext ctx)
        {
            throw new NotImplementedException();
        }

        public void Cleanup(IContext ctx)
        {
            throw new NotImplementedException();
        }
    }
}
