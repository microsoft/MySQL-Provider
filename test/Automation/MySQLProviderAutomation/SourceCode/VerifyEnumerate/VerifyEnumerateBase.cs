//-----------------------------------------------------------------------
// <copyright file="VerifyEnumerateBase.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-jeali</author>
// <description></description>
// <history>2/12/2015 2:27:44 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.Test.MySQL.Provider
{
    using Infra.Frmwrk;
    using Scx.Test.Common;
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Text.RegularExpressions;
    using System.Xml.Linq;
    class VerifyEnumerateBase
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
        /// agentHelper
        /// </summary>
        private AgentHelper agentHelper;

        /// <summary>
        /// new a agentHelper
        /// </summary>
        public AgentHelper AgentHelper
        {
            get { return agentHelper; }
            set { agentHelper = value; }
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
        /// Required: root's password
        /// </summary>
        private string rootPassword;

        /// <summary>
        ///  Required: root's password
        /// </summary>
        public string RootPassword
        {
            get { return rootPassword; }
            set { rootPassword = value; }
        }

        /// <summary>
        /// Required: get OS Version Cmd
        /// </summary>
        private string getOSVersionCmd;

        /// <summary>
        ///  Required: get OS Version Cmd.
        /// </summary>
        public string GetOSVersionCmd
        {
            get { return getOSVersionCmd; }
            set { getOSVersionCmd = value; }
        }

        /// <summary>
        /// Required: get MySQL Version Cmd.
        /// </summary>
        private string getMySQLVersionCmd;

        /// <summary>
        ///  Required: get MySQL Version Cmd.
        /// </summary>
        public string GetMySQLVersionCmd
        {
            get { return getMySQLVersionCmd; }
            set { getMySQLVersionCmd = value; }
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
        /// XML fragment returned by query
        /// </summary>
        private List<string> queryXmlResult;

        /// <summary>
        ///  XML fragment returned by query
        /// </summary>
        public List<string> QueryXmlResult
        {
            get { return queryXmlResult; }
            set { queryXmlResult = value; }
        }

        /// <summary>
        /// queryClass eg.MySQL_Server
        /// </summary>
        private string queryClass;

        /// <summary>
        ///  queryClass eg.MySQL_Server
        /// </summary>
        public string QueryClass
        {
            get { return queryClass; }
            set { queryClass = value; }
        }

        /// <summary>
        /// Time to wait before attempting retry of query after a failed query
        /// </summary>
        private TimeSpan queryRetryInterval = new TimeSpan(0, 0, 20);

        /// <summary>
        /// IP Adress of the POSIX host
        /// </summary>
        private string ipaddress;

        /// <summary>
        /// isMySql5. default should be false.
        /// </summary>
        private bool isMySql5 = false;

        /// <summary>
        /// isMySql5. default should be false.
        /// </summary>
        public bool IsMySql5
        {
            get { return isMySql5; }
            set { isMySql5 = value; }
        }

        /// <summary>
        /// isMySql51. default should be false.
        /// </summary>
        private bool isMySql51 = false;

        /// <summary>
        /// isMySql51. default should be false.
        /// </summary>
        public bool IsMySql51
        {
            get { return isMySql51; }
            set { isMySql51 = value; }
        }
        /// <summary>
        /// isMySql55. default should be false.
        /// </summary>
        private bool isMySql55 = false;

        /// <summary>
        /// isMySql55. default should be false.
        /// </summary>
        public bool IsMySql55
        {
            get { return isMySql55; }
            set { isMySql55 = value; }
        }
        /// <summary>
        /// isMySql56. default should be false.
        /// </summary>
        private bool isMySql56 = false;

        /// <summary>
        /// isMySql56. default should be false.
        /// </summary>
        public bool IsMySql56
        {
            get { return isMySql56; }
            set { isMySql56 = value; }
        }
        /// <summary>
        /// isMySql57. default should be false.
        /// </summary>
        private bool isMySql57 = false;

        /// <summary>
        /// isMySql57. default should be false.
        /// </summary>
        public bool IsMySql57
        {
            get { return isMySql57; }
            set { isMySql57 = value; }
        }

        /// <summary>
        /// enumerateresult. default should be true.
        /// </summary>
        private bool shouldEnumerateResult = true;

        /// <summary>
        /// enumerateresult. default should be true.
        /// </summary>
        public bool ShouldEnumerateresult
        {
            get { return shouldEnumerateResult; }
            set { shouldEnumerateResult = value; }
        }

        /// <summary>
        /// Expected Result xml Template. we can change the expected value.
        /// </summary>
        private string resultTemplate;

        /// <summary>
        /// Expected Result template.
        /// </summary>
        public string ResultTemplate
        {
            get { return resultTemplate; }
            set { resultTemplate = value; }
        }

        /// <summary>
        /// host IP
        /// </summary>
        private string hostIp = "127.0.0.1";

        /// <summary>
        /// defaultport
        /// </summary>
        private string defaultport = "3306";

        /// <summary>
        /// version
        /// </summary>
        private string version = "5.0";

        /// <summary>
        /// collectionID
        /// </summary>
        private string collectionID = "[lL]inux";

        /// <summary>
        /// defaultConfigFile
        /// </summary>
        private string defaultConfigFile = "/etc/my.cnf";

        /// <summary>
        /// defaultErrorlogFile
        /// </summary>
        private string defaultErrorlogFile = "/var/log/mysql/error.log";

        /// <summary>
        /// defaultSockFile
        /// </summary>
        private string defaultSockFile = "/var/lib/mysql/mysql.sock";

        /// <summary>
        /// defaultDataDirectory
        /// </summary>
        private string defaultDataDirectory = "/var/lib/mysql/";

        /// <summary>
        /// expecte Status Value
        /// </summary>
        private string expecteStatusValue = "OK";

        /// <summary>
        /// expecte Status Value
        /// </summary>
        public string ExpecteStatusValue
        {
            get { return expecteStatusValue; }
            set { expecteStatusValue = value; }
        }
        /// <summary>
        /// The Current OS is Deb or Ubun.
        /// </summary>
        private bool isDeb = false;

        /// <summary>
        /// defaultMultiPort 3307.
        /// </summary>
        private string defaultMultiPort = "3307";

        /// <summary>
        /// defaultMultiConfigFile
        /// </summary>
        private string defaultMultiProductVersion = "5.0";

        /// <summary>
        /// defaultMultiConfigFile
        /// </summary>
        private string defaultMultiConfigFile = "/etc/my.cnf";

        /// <summary>
        /// defaultMultiErrorlogFile
        /// </summary>
        private string defaultMultiErrorlogFile = "/var/log/mysql/error2.log";

        /// <summary>
        /// defaultMultiSockFile
        /// </summary>
        private string defaultMultiSockFile = "/var/lib/mysql/mysql2.sock";

        /// <summary>
        /// defaultMultiDataDirectory
        /// </summary>
        private string defaultMultiDataDirectory = "/var/lib/mysql/data";

        private string mysqlVersion = string.Empty;

        /// <summary>
        /// InitializeHelper. get all the values from Group or current ctx.
        /// </summary>
        /// <param name="ctx">IContext</param>
        public void InitializeHelper(IContext ctx)
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
            //Get root's password.
            this.RootPassword = ctx.ParentContext.Records.GetValue("password");
            if (String.IsNullOrEmpty(this.RootPassword))
            {
                throw new VarAbort("root's password not specified");
            }

            this.GetOSVersionCmd = ctx.ParentContext.Records.GetValue("getOSVersionCmd");
            if (String.IsNullOrEmpty(this.GetOSVersionCmd))
            {
                throw new VarAbort("GetOSVersionCmd not specified");
            }
            this.GetMySQLVersionCmd = ctx.ParentContext.Records.GetValue("getMySQLVersionCmd");
            if (String.IsNullOrEmpty(this.GetMySQLVersionCmd))
            {
                throw new VarAbort("GetMySQLVersionCmd not specified");
            }

            IVarContext varContext = (IVarContext)ctx;
            this.queryClass = varContext.CustomID;
            if (String.IsNullOrEmpty(this.queryClass))
            {
                throw new VarAbort("cid field not specified, specify query class in cid");
            }

            if (ctx.Records.HasKey("enumerateresult") && ctx.Records.GetValue("enumerateresult") == "false")
            {
                this.ShouldEnumerateresult = false;
            }

            this.MySQLHelper = new MySQLHelper(ctx.Trc, this.HostName, this.UserName, this.Password);
            this.AgentHelper = new AgentHelper(ctx.Trc, this.HostName, this.UserName, this.password);
            GetMySqlVersion(ctx);
            this.queryXmlResult = new List<string>();
        }

        /// <summary>
        /// Enumerate via WSMAN, return xml fragment Query
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>
        public void EnumerateWSMANQuery(IContext mcfContext)
        {
            this.ipaddress = new ClientInfo().GetHostIPv4Address(this.HostName);

            mcfContext.Trc(string.Format("Initialized enumeration test against {0}, ipaddr={1} for enumeration query {2}", this.HostName, this.ipaddress, this.queryClass));
            Scx.Test.WSMAN.Common.WSManQuery posixQuery = new Scx.Test.WSMAN.Common.WSManQuery(mcfContext, this.HostName, this.UserName, this.Password);

            int maxTries = 3;
            bool success = false;

            for (int tries = 0; !success && tries < maxTries; tries++)
            {
                try
                {
                    // If the recordkey haskey 'returnType' do the function EnumerateScx.
                    posixQuery.EnumerateScx(out this.queryXmlResult, this.queryClass);

                    if (this.queryXmlResult != null && this.queryXmlResult.Count > 0)
                    {
                        success = true;
                    }
                    if (this.queryXmlResult.Count == 0 && this.shouldEnumerateResult == false)
                    {
                        success = true;
                    }
                }
                catch (Exception e)
                {
                    mcfContext.Trc("WSMAN Query failed: " + e.Message);
                    success = false;
                }

                if (!success)
                {
                    this.Wait(mcfContext);
                }
            }
            if (!success)
            {
                throw new VarAbort(string.Format("Client does not respond to WSMAN requests after {0} attempts", maxTries));
            }
        }

        /// <summary>
        /// Verify WSMAN Values
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>
        /// <param name="expectedValueString">expectedValueString</param>
        /// <param name="instanceIdentifyPropertyName">Instance Identify Property's Name</param>
        public void VerifyWSMANValues(IContext mcfContext, string expectedValueString, string instanceIdentifyPropertyName)
        {
            // verfication logic
            var expectedValuesInXml = XElement.Parse(expectedValueString);

            if (expectedValuesInXml.Elements().Count() != this.queryXmlResult.Count)
                throw new VarFail(string.Format("The elements Count is different. Expected Count:{0} Actully Count:{1}", expectedValuesInXml.Elements().Count().ToString(), this.queryXmlResult.Count.ToString()));


            foreach (var mySQLItems in expectedValuesInXml.Elements())
            {
                var instanceId = mySQLItems.Element(instanceIdentifyPropertyName).Value;

                if (!this.queryXmlResult.Any(i => i.Contains(instanceId)))
                    throw new VarFail("Can't find the expected instance # " + instanceId);

                // verify instance properties
                var itemToVerfiy = this.queryXmlResult.FirstOrDefault(i => i.Contains(instanceId));
                CompareInstanceProperties(mySQLItems, XElement.Parse(itemToVerfiy), mcfContext);
            }
        }

        /// <summary>
        /// Verify Enumerate Result Is Null the WSMAN return query should be 0.
        /// </summary>
        public void VerifyEnumerateResultIsNull()
        {
            if (this.queryXmlResult.Count != 0)
            {
                throw new VarFail("The elements Count should be 0");
            }
        }

        /// <summary>
        /// Get Expected MySQLServer Values. get values from varmap.
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>
        public void GetExpectedMySQLServerValues(IContext mcfContext)
        {
            this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedMySQLServer");
            if (mcfContext.Records.HasKey("IsBadStatus"))
            {
                this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedBadMySQLServer");
            }
            if (mcfContext.Records.HasKey("IsMulti"))
            {
                this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedMultiInstancesMySQLServer");
            }
            if (mcfContext.Records.HasKey("IsStopOneInstance"))
            {
                this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedStopedOneInstanceInMultiEnvMySQLServer");
            }
            hostIp = mcfContext.ParentContext.Records.GetValue("hostIP");
            defaultport = mcfContext.ParentContext.Records.GetValue("defaultPortID");
            collectionID = mcfContext.ParentContext.Records.GetValue("defaultCollectionID");
            defaultMultiPort = mcfContext.ParentContext.Records.GetValue("multiDefaultPortID");

            this.defaultConfigFile = mcfContext.ParentContext.Records.GetValue("defaultConfigurationFile");
            this.defaultErrorlogFile = mcfContext.ParentContext.Records.GetValue("defaultErrorLogFile");
            this.defaultSockFile = mcfContext.ParentContext.Records.GetValue("defaultSocketFile");
            this.defaultDataDirectory = mcfContext.ParentContext.Records.GetValue("defaultDataDirectory");


            this.defaultMultiConfigFile = mcfContext.ParentContext.Records.GetValue("defaultMultiConfigurationFile");
            this.defaultMultiErrorlogFile = mcfContext.ParentContext.Records.GetValue("defaultMultiErrorLogFile");
            this.defaultMultiSockFile = mcfContext.ParentContext.Records.GetValue("defaultMultiSocketFile");
            this.defaultMultiDataDirectory = mcfContext.ParentContext.Records.GetValue("defaultMultiDataDirectory");

            this.version = this.mysqlVersion;
            this.defaultMultiProductVersion = this.mysqlVersion;
        }

        /// <summary>
        /// GetMySqlVersion
        /// </summary>
        /// <returns>GetMySqlVersion</returns>
        public string GetMySqlVersion(IContext mcfContext)
        {
            string fileExistCmd = "/bin/ls /etc/profile.d/|grep -ic mysql.sh";
            try
            {
                fileExistCmd = this.RunCommandAsRoot(fileExistCmd, this.RootPassword);
                if (fileExistCmd.Contains("1"))
                {
                    this.GetMySQLVersionCmd = "source /etc/profile.d/mysql.sh;" + this.GetMySQLVersionCmd;
                }
            }
            catch
            {

            }

            this.mysqlVersion = this.RunCommandAsRoot(this.GetMySQLVersionCmd, this.RootPassword);
            if (this.mysqlVersion.ToLower().Contains("5.0"))
            {
                IsMySql5 = true;
                this.mysqlVersion = mcfContext.ParentContext.Records.GetValue("ProductVersionM50");
            }
            if (this.mysqlVersion.ToLower().Contains("5.1"))
            {
                IsMySql51 = true;
                this.mysqlVersion = mcfContext.ParentContext.Records.GetValue("ProductVersionM51");
            }
            if (this.mysqlVersion.ToLower().Contains("5.5"))
            {
                IsMySql55 = true;
                this.mysqlVersion = mcfContext.ParentContext.Records.GetValue("ProductVersionM55");
            }
            if (this.mysqlVersion.ToLower().Contains("5.6"))
            {
                IsMySql56 = true;
                this.mysqlVersion = mcfContext.ParentContext.Records.GetValue("ProductVersionM56");
            }
            if (this.mysqlVersion.ToLower().Contains("5.7"))
            {
                IsMySql57 = true;
                this.mysqlVersion = mcfContext.ParentContext.Records.GetValue("ProductVersionM57");
            }
            return this.mysqlVersion;
        }


        /// <summary>
        /// GetOSIsDebInfo
        /// </summary>
        /// <returns>isDeb debian or ubuntu will return true. </returns>
        private bool GetOSIsDebInfo()
        {
            string getOSDistCmd = "python -c \"import platform; print platform.dist()\"";
            RunPosixCmd execCmd = this.MySQLHelper.RunCmd(getOSDistCmd);
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
        /// SetUpMultiMySQLEnv
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>
        public void SetUpMultiMySQLEnv(IContext mcfContext)
        {
            this.GetOSIsDebInfo();
            string mysqllocation = mcfContext.ParentContext.Records.GetValue("MySQLConfigForR");
            if (this.isDeb)
            {
                mysqllocation = mcfContext.ParentContext.Records.GetValue("MySQLConfigForD");
            }
            bool isMulti = mcfContext.Records.HasKey("IsMulti");
            bool isDeleteCredentialsInMulti = mcfContext.Records.HasKey("isDeleteCredentialsInMulti");

            if (isMulti || isDeleteCredentialsInMulti)
            {
                // stop one instance services.
                string stopMySQLServicecmd = mcfContext.ParentContext.Records.GetValue("stopMySQLCmd");
                this.MySQLHelper.RunCmd(stopMySQLServicecmd);

                // copy multi instances
                DirectoryInfo di = new DirectoryInfo(mysqllocation);
                FileInfo[] multi = di.GetFiles("*" + "my-multi" + "*");
                PosixCopy copyToHost = new PosixCopy(this.HostName, this.UserName, this.Password);
                // Copy from server to Posix host
                copyToHost.CopyTo(multi[0].FullName, "/etc/my.cnf");

                // start multi instances
                string startMultiMySQLCmd = mcfContext.ParentContext.Records.GetValue("startMultiMySQLCmd");
                this.MySQLHelper.RunCmd(startMultiMySQLCmd);
                this.Wait(mcfContext);
                this.Wait(mcfContext);
            }
        }

        /// <summary>
        /// CleanUpMultiMySQLEnv
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>        
        public void CleanUpMultiMySQLEnv(IContext mcfContext)
        {
            this.GetOSIsDebInfo();
            string mysqllocation = mcfContext.ParentContext.Records.GetValue("MySQLConfigForR");
            if (this.isDeb)
            {
                mysqllocation = mcfContext.ParentContext.Records.GetValue("MySQLConfigForD");
            }
            bool isMulti = mcfContext.Records.HasKey("IsMulti");
            bool isDeleteCredentialsInMulti = mcfContext.Records.HasKey("isDeleteCredentialsInMulti");

            if (isMulti || isDeleteCredentialsInMulti)
            {
                // stop one instance services.
                string stopMySQLServiceCmd = mcfContext.ParentContext.Records.GetValue("stopMultiMySQLCmd");
                this.MySQLHelper.RunCmd(stopMySQLServiceCmd);

                // copy multi instances
                DirectoryInfo di = new DirectoryInfo(mysqllocation);
                FileInfo[] multi = di.GetFiles("*" + "my-oneInstance" + "*");
                PosixCopy copyToHost = new PosixCopy(this.HostName, this.UserName, this.Password);
                // Copy from server to Posix host
                copyToHost.CopyTo(multi[0].FullName, "/etc/my.cnf");

                // start multi instances
                string startMultiMySQLCmd = mcfContext.ParentContext.Records.GetValue("startMySQLCmd");
                this.MySQLHelper.RunCmd(startMultiMySQLCmd);
                this.Wait(mcfContext);
                this.Wait(mcfContext);
            }
        }

        /// <summary>
        /// Insert Expected MySQLServe value
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>
        public void InsertMySQLServerValues(IContext mcfContext)
        {
            // Take Default value.
            this.resultTemplate = this.resultTemplate.Replace("{MachineName}", this.HostName.ToLower());
            this.resultTemplate = this.resultTemplate.Replace("{LocalIP}", this.hostIp);
            this.resultTemplate = this.resultTemplate.Replace("{DefaultPort}", this.defaultport);
            // Product Version Info.
            this.resultTemplate = this.resultTemplate.Replace("{ProductVersionInfo}", this.version);
            // CollectionID.
            this.resultTemplate = this.resultTemplate.Replace("{CollectionIDInfo}", this.collectionID);
            // Config file
            this.resultTemplate = this.resultTemplate.Replace("{ConfigurationFileInfo}", this.defaultConfigFile);
            // Error file
            this.resultTemplate = this.resultTemplate.Replace("{ErrorLogFileInfo}", this.defaultErrorlogFile);
            // sock File.
            this.resultTemplate = this.resultTemplate.Replace("{SocketFileInfo}", this.defaultSockFile);
            // Data Directory
            this.resultTemplate = this.resultTemplate.Replace("{DataDirectoryInfo}", this.defaultDataDirectory);
            // ExpectedStatus
            this.resultTemplate = this.resultTemplate.Replace("{ExpectedStatus}", this.ExpecteStatusValue);
            // Take Mulit Instance Values.
            if (mcfContext.Records.HasKey("IsMulti"))
            {
                // default Multi ProductVersion Info
                this.resultTemplate = this.resultTemplate.Replace("{MultiProductVersionInfo}", this.defaultMultiProductVersion);
                // default Multi Port.
                this.resultTemplate = this.resultTemplate.Replace("{MultiDefaultPort}", this.defaultMultiPort);
                // Config file
                this.resultTemplate = this.resultTemplate.Replace("{MultiConfigurationFileInfo}", this.defaultMultiConfigFile);
                // Error file
                this.resultTemplate = this.resultTemplate.Replace("{MultiErrorLogFileInfo}", this.defaultMultiErrorlogFile);
                // sock File.
                this.resultTemplate = this.resultTemplate.Replace("{MultiSocketFileInfo}", this.defaultMultiSockFile);
                // Data Directory
                this.resultTemplate = this.resultTemplate.Replace("{MultiDataDirectoryInfo}", this.defaultMultiDataDirectory);
            }
        }

        /// <summary>
        /// Insert MySQLDataBase Values
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>
        public void InsertMySQLDataBaseValues(IContext mcfContext)
        {
            // get expected Value
            this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedDatabase");

            // Take Mulit Instance Values.
            if (mcfContext.Records.HasKey("IsMulti"))
            {
                this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedMultiInstancesDatabase");
                string defaultMultiPort = mcfContext.ParentContext.Records.GetValue("multiDefaultPortID");
                this.resultTemplate = this.resultTemplate.Replace("{MultiDefaultPort}", defaultMultiPort);
            }
            if (mcfContext.Records.HasKey("IsStopOneInstance"))
            {
                this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedStopedOneInstanceInMultiEnvDatabase");
            }

            string hostIp = mcfContext.ParentContext.Records.GetValue("hostIP");
            string defaultport = mcfContext.ParentContext.Records.GetValue("defaultPortID");

            // The Default data base name different in MySQL 5.0 and MySQL 55
            string diffDatabase = mcfContext.ParentContext.Records.GetValue("DiffDataBase50");
            if (this.HostName.Contains("m55") || this.HostName.Contains("m56") || this.HostName.Contains("m57"))
            {
                diffDatabase = mcfContext.ParentContext.Records.GetValue("DiffDataBase55");
            }

            // Take Default value.
            this.resultTemplate = this.resultTemplate.Replace("{MachineName}", this.HostName);
            this.resultTemplate = this.resultTemplate.Replace("{LocalIP}", hostIp);
            this.resultTemplate = this.resultTemplate.Replace("{DefaultPort}", defaultport);
            this.resultTemplate = this.resultTemplate.Replace("{DiffDataBase}", diffDatabase);
        }

        /// <summary>
        /// Insert MySQLServer Statistics Values
        /// </summary>
        /// <param name="mcfContext">mcfContext</param>
        public void InsertMySQLServerStatisticsValues(IContext mcfContext)
        {
            // get expected Value
            this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedMySQLServerStatistics");

            // Take Mulit Instance Values.
            if (mcfContext.Records.HasKey("IsMulti"))
            {
                this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedMultiInstancesMySQLServerStatistics");
                string defaultMultiPort = mcfContext.ParentContext.Records.GetValue("multiDefaultPortID");
                this.resultTemplate = this.resultTemplate.Replace("{MultiDefaultPort}", defaultMultiPort);
            }

            // after stoped one instance the expected mysql sever statistices value should same as one instance.
            if (mcfContext.Records.HasKey("IsStopOneInstance"))
            {
                this.resultTemplate = mcfContext.ParentContext.Records.GetValue("expectedMySQLServerStatistics");
            }

            // Take Default value.
            string hostIp = mcfContext.ParentContext.Records.GetValue("hostIP");
            string defaultport = mcfContext.ParentContext.Records.GetValue("defaultPortID");
            this.resultTemplate = this.resultTemplate.Replace("{MachineName}", this.HostName);
            this.resultTemplate = this.resultTemplate.Replace("{LocalIP}", hostIp);
            this.resultTemplate = this.resultTemplate.Replace("{DefaultPort}", defaultport);
        }

        /// <summary>
        /// Compare Instance Properties Values
        /// </summary>
        /// <param name="mySQLItems">mySQLItems. The Expected result</param>
        /// <param name="itemToVerfiy">itemToVerfiy. Actul Result from wsman or get from SQL command.</param>
        /// <param name="mcfContext">mcfContext</param>
        private void CompareInstanceProperties(XElement mySQLItems, XElement itemToVerfiy, IContext mcfContext)
        {
            foreach (var property in mySQLItems.Elements())
            {
                var propertyToVerify = itemToVerfiy.Elements().FirstOrDefault(i => i.Name.ToString().Contains(property.Name.ToString()));

                if (propertyToVerify == null)
                    throw new VarFail("Can't find the expected property, " + property.Name.ToString());

                // Create a regex using expected property value.
                System.Text.RegularExpressions.Regex criteria = new Regex(property.Value.ToLower());

                // verify the property value from wsman same as expected value.
                if (criteria != null)
                {
                    if (criteria.IsMatch(propertyToVerify.Value.ToLower()) == true)
                    {
                        mcfContext.Trc(propertyToVerify.Value + " passed criteria check");
                    }
                    else
                    {
                        mcfContext.Err(string.Format("{0}.{1} with value '{2}' failed criteria check, McfRecord='{3}', regex='{4}'", this.queryClass, propertyToVerify.Name, propertyToVerify.Value, property.Name, property.Value));
                        mcfContext.Err("Outer XML=" + propertyToVerify.ToString());
                        throw new VarFail("Values in WSMAN query failed criteria check");
                    }
                }
            }
        }

        /// <summary>
        /// Run remote command using root user.
        /// </summary>
        /// <param name="cmd">The command need to be executed</param>
        /// <param name="password">root's password</param>
        /// <returns>Command executed result</returns>
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
        /// Generic wait method for use to allow the state of the installed agent to stabilize
        /// </summary>
        /// <param name="ctx">Current MCF context</param>
        public void Wait(IContext ctx)
        {
            ctx.Trc(string.Format("Waiting for {0}...", this.queryRetryInterval));
            System.Threading.Thread.Sleep(this.queryRetryInterval);
        }
    }
}
