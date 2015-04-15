//-----------------------------------------------------------------------
// <copyright file="VerifyMySQLValue.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-jeali</author>
// <description></description>
// <history>2/4/2015 10:29:44 PM: Created</history>
//-----------------------------------------------------------------------
namespace Scx.Test.MySQL.Provider.VerifyMySQLValue
{
    using Infra.Frmwrk;
    using Scx.Test.Common;
    using Scx.Test.MySQL.Provider.VerifyCimProv;
    using System;
    using System.Collections.Generic;
    using System.Text.RegularExpressions;
    using System.Xml;

    /// <summary>
    /// VerifyMySQLValue
    /// </summary>
    class VerifyMySQLValue : VerifyEnumerateBase, ISetup, IRun, IVerify, ICleanup
    {
        /// <summary>
        /// XML fragment returned by query
        /// </summary>
        private List<string> queryXmlResult = new List<string>();

        /// <summary>
        /// Query class
        /// </summary>
        /// <remarks>E.g., MySQL_Server</remarks>
        private string queryClass;

        /// <summary>
        /// XML Schema prefix
        /// </summary>
        private string xmlSchemaPrefix = "http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/";

        /// <summary>
        /// XML Schema suffix
        /// </summary>
        private string xmlSchemaSuffix = "?__cimnamespace=root/mysql";

        /// <summary>
        /// XML Schema Instance.
        /// </summary>
        private string xsi = "http://www.w3.org/2001/XMLSchema-instance";

        /// <summary>
        /// Language
        /// </summary>
        private string lang = "";

        /// <summary>
        /// required Instance
        /// </summary>
        private bool requiredInstance = false;

        /// <summary>
        /// propertyLists
        /// </summary>
        Dictionary<string, string> propertyLists = new Dictionary<string, string>();

        string hostIp = "127.0.0.1";
        string defaultPort = "3307";


        /// <summary>
        /// set up
        /// </summary>
        /// <param name="ctx">Context</param>
        public void Setup(IContext ctx)
        {
            this.InitializeHelper(ctx);

            if (this.QueryClass == "MySQL_Server")
            {
                this.GetExpectedMySQLServerValues(ctx);
                this.InsertMySQLServerValues(ctx);
                // Can't get the configuration file path so skip this verify.
                int start = this.ResultTemplate.IndexOf("<ConfigurationFile>", 0);
                int end = this.ResultTemplate.IndexOf("</ConfigurationFile>", 0);
                int count = end - start + "</ConfigurationFile>".Length;
                this.ResultTemplate = this.ResultTemplate.Remove(start, count);
            }
            else if (this.QueryClass == "MySQL_ServerStatistics")
            {
                this.InsertMySQLServerStatisticsValues(ctx);
            }
            else if (this.QueryClass == "MySQL_Server_Database")
            {
                this.InsertMySQLDataBaseValues(ctx);
            }

            ctx.Trc("Expected Result: " + this.ResultTemplate);
        }

        /// <summary>
        /// Running 
        /// </summary>
        /// <param name="mcfContext">Context</param>
        public void Run(IContext mcfContext)
        {
            if (this.QueryClass == "MySQL_Server")
            {
                GetMySQLServerMap();
            }
            else if (this.QueryClass == "MySQL_ServerStatistics")
            {
                GetMySQLServerStatisticsMap();
            }
            else if (this.QueryClass == "MySQL_Server_Database")
            {
                GetMySQLServerDataBasesMap();
            }
            foreach (var item in this.QueryXmlResult)
            {
                mcfContext.Trc("Actual Result: " + item.ToString());
            }
        }

        /// <summary>
        /// Verify
        /// </summary>
        /// <param name="ctx"></param>
        public void Verify(IContext ctx)
        {
            if (this.QueryClass == "MySQL_Server")
            {
                VerifyWSMANValues(ctx, this.ResultTemplate, "ProductIdentifyingNumber");
            }
            else
            {
                VerifyWSMANValues(ctx, this.ResultTemplate, "InstanceID");
            }
        }

        /// <summary>
        /// Clean up
        /// </summary>
        /// <param name="ctx"></param>
        public void Cleanup(IContext ctx)
        {
            // will removed agent in Goup Clean up.
        }

        /// <summary>
        /// Get MySQL_Server Map 
        /// </summary>
        private void GetMySQLServerMap()
        {
            XmlDocument xdoc = new XmlDocument();
            XmlElement root = xdoc.CreateElement("p:MySQL_Server");
            root.SetAttribute("xmlns:p", string.Concat(this.xmlSchemaPrefix, queryClass));
            root.SetAttribute("xmlns:xsi", xsi);
            root.SetAttribute("xml:lang", lang);
            xdoc.AppendChild(root);
            string hostName = this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"hostname\"").ToLower();
            if (hostName == string.Empty)
            {
                hostName = this.HostName.ToLower();
            }
            propertyLists.Add("ProductIdentifyingNumber", string.Format("{0}:{1}:{2}", hostName, hostIp, this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"port\";")));
            propertyLists.Add("ProductName", "MySQL");
            propertyLists.Add("ProductVendor", "Oracle");
            propertyLists.Add("ProductVersion", this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"version\""));
            propertyLists.Add("SystemID", "[0-9]");
            propertyLists.Add("CollectionID", "linux");
            // Can't get the configuration file path so skip this verify.
            // propertyLists.Add("ConfigurationFile", "/etc/my.cnf");
            propertyLists.Add("ErrorLogFile", this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"log_error\";"));
            propertyLists.Add("Hostname", hostName);
            propertyLists.Add("BindAddress", hostIp);
            propertyLists.Add("Port", this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"port\";"));
            propertyLists.Add("SocketFile", this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"socket\";"));
            propertyLists.Add("DataDirectory", this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"datadir\";"));
            propertyLists.Add("OperatingStatus", "OK");

            foreach (var item in propertyLists)
            {
                XmlElement element = xdoc.CreateElement(item.Key);
                element.InnerText = item.Value;
                root.AppendChild(element);
            }
            this.QueryXmlResult.Add(xdoc.InnerXml);
        }

        /// <summary>
        /// Get MySQL_serviceStatistics Map. all the values get from mysql cmd.
        /// </summary>
        private void GetMySQLServerStatisticsMap()
        {
            // CurrentNumConnections;
            string currentNumConnections = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"Threads_connected\"");

            // MaxConnections
            string maxConnections = this.GetVariablesValueFromMySQLCmd("select @@max_connections", "@@max_connections:");

            // connectionsUsePct
            double connectionsUsePct = Math.Round((double.Parse(currentNumConnections) / double.Parse(maxConnections)) * 100, 0);
            if (Double.IsNaN(connectionsUsePct))
            {
                connectionsUsePct = 0;
            }

            // AbortedConnnetionPct
            string abortedConnects = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where variable_name=\"Aborted_connects\"");
            string connections = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where variable_name=\"Connections\"");
            double abortedConnnetionPct = Math.Round((double.Parse(abortedConnects) / double.Parse(connections)) * 100, 0);

            if (Double.IsNaN(abortedConnnetionPct))
            {
                abortedConnnetionPct = 0;
            }

            // Uptime:
            string upTime = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"uptime\";");

            // ServerDiskUseInBytes 
            string serverDiskUseInBytes = this.GetVariablesValueFromMySQLCmd("SELECT SUM(DATA_LENGTH) + SUM(INDEX_LENGTH) AS SIZE FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = \"mysql\";", "SIZE:");

            // slowQueryPct
            double queries = 0;
            if (this.IsMySql5)
            {
                string questions = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where variable_name=\"Questions\"");
                string comStmtClose = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where variable_name=\"Com_stmt_close\"");
                string comStmtReset = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where variable_name=\"Com_stmt_reset\"");
                string comStmtPrepare = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where variable_name=\"Com_stmt_prepare\"");
                queries = double.Parse(questions) + double.Parse(comStmtClose) + double.Parse(comStmtPrepare) + double.Parse(comStmtReset);
            }
            else
            {
                queries = double.Parse(this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where variable_name=\"Queries\""));
            }

            string slowQueries = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where variable_name=\"Slow_queries\"");
            double slowQueryPct = Math.Round((double.Parse(slowQueries) / queries) * 100, 0);
            if (Double.IsNaN(slowQueryPct))
            {
                slowQueryPct = 0;
            }

            // KeyCacheHitPct
            string keyReadsValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"key_reads\";");
            double keyReads = double.Parse(keyReadsValue);
            string keyReadRequestsValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"key_read_requests\";");
            double keyReadRequests = double.Parse(keyReadRequestsValue);
            double keyCacheHitPct = Math.Round((1 - (keyReads / keyReadRequests)) * 100, 0);
            if (Double.IsNaN(keyCacheHitPct))
            {
                keyCacheHitPct = 0;
            }

            // KeyCacheWritePct
            string keyWritesValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"key_writes\";");
            double keyWrites = double.Parse(keyWritesValue);
            string keyWriteRequestsValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"key_write_requests\";");
            double keyWriteRequests = double.Parse(keyWriteRequestsValue);
            double keyCacheWritePct = Math.Round((keyWrites / keyWriteRequests) * 100, 0);
            if (Double.IsNaN(keyCacheWritePct))
            {
                keyCacheWritePct = 0;
            }

            // KeyCacheUsePct
            string keyBlocksUnusedValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"key_blocks_unused\";");
            double keyBlocksUnused = double.Parse(keyBlocksUnusedValue);
            string keyCacheBlockSizeValue = this.GetVariablesValueFromMySQLCmd("show global VARIABLES where Variable_name= \"key_cache_block_size\";");
            double keyCacheBlockSize = double.Parse(keyCacheBlockSizeValue);
            string keyBufferSizeValue = this.GetVariablesValueFromMySQLCmd("show global VARIABLES where Variable_name= \"key_buffer_size\";");
            double keyBufferSize = double.Parse(keyBufferSizeValue);
            double keyCacheUsePct = Math.Round((1 - (keyBlocksUnused * keyCacheBlockSize / keyBufferSize) * 100), 0);
            if (Double.IsNaN(keyCacheUsePct))
            {
                keyCacheUsePct = 0;
            }

            // QCacheHitPct
            string qCacheHitsValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"QCache_hits\";");
            double qCacheHits = double.Parse(qCacheHitsValue);
            string comSelectValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"Com_select\";");
            double comSelect = double.Parse(comSelectValue);
            double qCacheHitPct = Math.Round(qCacheHits / (qCacheHits + comSelect) * 100, 0);
            if (Double.IsNaN(qCacheHitPct))
            {
                qCacheHitPct = 0;
            }

            // QCachePrunesPct
            string qCacheLowMemPrunesValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"Qcache_lowmem_prunes\";");
            double qCacheLowMemPrunes = double.Parse(qCacheLowMemPrunesValue);
            double qCachePrunesPct = Math.Round(qCacheLowMemPrunes / queries * 100, 0);
            if (Double.IsNaN(qCachePrunesPct))
            {
                qCachePrunesPct = 0;
            }

            // QCacheUsePct
            string qCacheSizeValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL VARIABLES where Variable_name= \"query_cache_size\";");
            double qCacheSize = double.Parse(qCacheSizeValue);
            string qCacheFreeMemoryValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"Qcache_free_memory\";");
            double qCacheFreeMemory = double.Parse(qCacheFreeMemoryValue);
            double qCacheUsePct = Math.Round((qCacheSize - qCacheFreeMemory) / qCacheSize * 100, 0);
            if (Double.IsNaN(qCacheUsePct))
            {
                qCacheUsePct = 0;
            }

            // TCacheHitPct
            string openTablesValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"Open_tables\";");
            double openTables = double.Parse(openTablesValue);
            string openedTablesValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"Opened_tables\";");
            double openedTables = double.Parse(openedTablesValue);
            double tCacheHitPct = Math.Round(openTables / openedTables * 100, 0);
            if (Double.IsNaN(tCacheHitPct))
            {
                tCacheHitPct = 0;
            }

            // TableLockContentionPct
            string tablesLocksWaitedValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"table_locks_waited\";");
            double tablesLocksWaited = double.Parse(tablesLocksWaitedValue);
            string tableLocksImmediateValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"table_locks_immediate\";");
            double tableLocksImmediate = double.Parse(tableLocksImmediateValue);
            double tableLockContentionPct = Math.Round(tablesLocksWaited / (tablesLocksWaited + tableLocksImmediate) * 100, 0);
            if (Double.IsNaN(tableLockContentionPct))
            {
                tableLockContentionPct = 0;
            }
            // TableCacheUsePct
            string tablesOpenCacheValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL Variables where Variable_name= \"table_open_cache\";");
            if (this.IsMySql5)
            {
                tablesOpenCacheValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL Variables where Variable_name= \"table_cache\";");
            }
            double tableOpenCache = double.Parse(tablesOpenCacheValue);
            double tableCacheUsePct = Math.Round(openTables / tableOpenCache * 100, 0);
            if (Double.IsNaN(tableCacheUsePct))
            {
                tableCacheUsePct = 0;
            }

            // IDB_BP_HitPct
            string innodbBufferPoolReadsValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"innodb_buffer_pool_reads\";");
            double innodbBufferPoolReads = double.Parse(innodbBufferPoolReadsValue);
            string innodbBufferPoolReadRequestsValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"innodb_buffer_pool_read_requests\";");
            double innodbBufferPoolReadRequests = double.Parse(innodbBufferPoolReadRequestsValue);
            double idbBpHitPct = Math.Round((1 - (innodbBufferPoolReads / innodbBufferPoolReadRequests)) * 100, 0);
            if (Double.IsNaN(idbBpHitPct))
            {
                idbBpHitPct = 0;
            }

            //// IDB_BP_WriteWaitPct
            //string innodbBufferPoolWaitFreeValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"innodb_buffer_pool_wait_free\";");
            //double innodbBufferPoolWaitFree = double.Parse(innodbBufferPoolWaitFreeValue);
            //string innodbBufferPoolWriteRequestsValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"innodb_buffer_pool_write_requests\";");
            //double innodbBufferPoolWriteRequests = double.Parse(innodbBufferPoolWriteRequestsValue);
            //double idbBpWriteWaitPct = Math.Round((innodbBufferPoolWaitFree / innodbBufferPoolWriteRequests) * 100, 0);
            //if (Double.IsNaN(idbBpWriteWaitPct))
            //{
            //    idbBpWriteWaitPct = 0;
            //}

            // IDB_BP_UsePct
            string innodbBufferPoolPagesDataValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"innodb_buffer_pool_pages_data\";");
            double innodbBufferPoolPagesData = double.Parse(innodbBufferPoolPagesDataValue);
            string innodbBufferPoolPagesTotalValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"innodb_buffer_pool_pages_total\";");
            double innodbBufferPoolPagesTotal = double.Parse(innodbBufferPoolPagesTotalValue);
            double idbBpUsePct = Math.Round((innodbBufferPoolPagesData / innodbBufferPoolPagesTotal) * 100, 0);
            if (Double.IsNaN(idbBpUsePct))
            {
                idbBpUsePct = 0;
            }

            //FullTableScanPct
            string handlerReadRndNextValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"handler_read_rnd_next\";");
            string handlerReadRndValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"handler_read_rnd\";");
            string handlerReadFirstValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"handler_read_first\";");
            string handlerReadKeyValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"handler_read_key\";");
            string handlerReadNextValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"handler_read_next\";");
            string handlerReadPrevValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"handler_read_prev\";");
            double allRowAccess = double.Parse(handlerReadRndNextValue) + double.Parse(handlerReadRndValue) + double.Parse(handlerReadFirstValue) + double.Parse(handlerReadKeyValue) + double.Parse(handlerReadNextValue) + double.Parse(handlerReadPrevValue);
            double fullScanReads = double.Parse(handlerReadRndNextValue) + double.Parse(handlerReadRndValue);
            double fullTableScanPct = Math.Round((fullScanReads / allRowAccess) * 100, 0);
            if (Double.IsNaN(fullTableScanPct))
            {
                fullTableScanPct = 0;
            }
            propertyLists.Add("InstanceID", string.Format("{0}:127.0.0.1:3306", this.HostName));
            propertyLists.Add("CurrentNumConnections", currentNumConnections);
            propertyLists.Add("MaxConnections", maxConnections);
            // todo this part.after confirm with redmond.
            propertyLists.Add("FailedConnections", "0");
            propertyLists.Add("Uptime", upTime);
            propertyLists.Add("ServerDiskUseInBytes", serverDiskUseInBytes);
            propertyLists.Add("ConnectionsUsePct", connectionsUsePct.ToString());
            propertyLists.Add("AbortedConnectionPct", abortedConnnetionPct.ToString());
            propertyLists.Add("SlowQueryPct", slowQueryPct.ToString());
            propertyLists.Add("KeyCacheHitPct", keyCacheHitPct.ToString());
            propertyLists.Add("KeyCacheWritePct", keyCacheWritePct.ToString());
            propertyLists.Add("KeyCacheUsePct", keyCacheUsePct.ToString());
            propertyLists.Add("QCacheHitPct", qCacheHitPct.ToString());
            propertyLists.Add("QCachePrunesPct", qCachePrunesPct.ToString());
            propertyLists.Add("QCacheUsePct", qCacheUsePct.ToString());
            propertyLists.Add("TCacheHitPct", tCacheHitPct.ToString());
            propertyLists.Add("TableLockContentionPct", tableLockContentionPct.ToString());
            propertyLists.Add("TableCacheUsePct", tableCacheUsePct.ToString());
            propertyLists.Add("IDB_BP_HitPct", idbBpHitPct.ToString());
            //propertyLists.Add("IDB_BP_WriteWaitPct", idbBpWriteWaitPct.ToString());
            propertyLists.Add("IDB_BP_UsePct", idbBpUsePct.ToString());
            propertyLists.Add("FullTableScanPct", fullTableScanPct.ToString());

            XmlDocument xdoc = new XmlDocument();
            XmlElement root = xdoc.CreateElement("p:MySQL_ServerStatistics");
            root.SetAttribute("xmlns:p", string.Concat(this.xmlSchemaPrefix, queryClass));
            root.SetAttribute("xmlns:xsi", xsi);
            root.SetAttribute("xml:lang", lang);
            xdoc.AppendChild(root);
            // plist.Add(systemID, "0");
            foreach (var item in propertyLists)
            {
                XmlElement element = xdoc.CreateElement(item.Key);
                element.InnerText = item.Value;
                root.AppendChild(element);
            }
            this.QueryXmlResult.Add(xdoc.InnerXml);
        }

        /// <summary>
        /// Get MySQL_Server_DataBases Map. all the values get from mysql cmd.
        /// </summary>
        private void GetMySQLServerDataBasesMap()
        {
            string dataBasesValue = this.GetVariablesValueFromMySQLCmd("show databases;", "Database", false);
            dataBasesValue = dataBasesValue.TrimEnd('\n');
            string[] dataBases = dataBasesValue.Split('\n');

            foreach (var database in dataBases)
            {
                XmlDocument xdoc = new XmlDocument();
                XmlElement root = xdoc.CreateElement("p:MySQL_Server_Database");
                root.SetAttribute("xmlns:p", string.Concat(this.xmlSchemaPrefix, queryClass));
                root.SetAttribute("xmlns:xsi", xsi);
                root.SetAttribute("xml:lang", lang);
                xdoc.AppendChild(root);

                propertyLists.Add("InstanceID", string.Format("{0}:127.0.0.1:3306:{1}", this.HostName, database));
                propertyLists.Add("DatabaseName", database);
                propertyLists.Add("NumberOfTables", this.GetVariablesValueFromMySQLCmd(string.Format("use information_schema;SELECT count(*) FROM information_schema.tables WHERE TABLE_SCHEMA = \"{0}\"", database), "count"));

                string diskSpaceInBytes = this.GetVariablesValueFromMySQLCmd(string.Format("use information_schema;select concat(round(sum(data_length),2)) as data from tables where table_schema=\"{0}\";", database), "data");
                if (diskSpaceInBytes.ToUpper() == "NULL")
                {
                    diskSpaceInBytes = "0";
                }
                propertyLists.Add("DiskSpaceInBytes", diskSpaceInBytes);

                foreach (var item in propertyLists)
                {
                    XmlElement element = xdoc.CreateElement(item.Key);
                    element.InnerText = item.Value;
                    root.AppendChild(element);
                }
                propertyLists.Clear();
                this.QueryXmlResult.Add(xdoc.InnerXml);
            }
        }

        /// <summary>
        /// Get Variables' Value From MySQL Cmd
        /// </summary>
        /// <param name="getVariablesCmd">getVariablesCmd</param>
        /// <param name="value">Got value</param>
        /// <param name="needTrim">need removed the last one \n</param>
        /// <returns>std output</returns>
        private string GetVariablesValueFromMySQLCmd(string getVariablesCmd, string value = "Value:", bool needTrim = true)
        {
            string cmdoutput = string.Empty;
            string fileExistCmd = "/bin/ls /etc/profile.d/|grep -ic mysql.sh";
            string mysqlCmd = "mysql -E -e '{0}'| grep '{1}'";
            try
            {
                fileExistCmd = this.RunCommandAsRoot(fileExistCmd, this.RootPassword);
                if (fileExistCmd.Contains("1"))
                {
                    mysqlCmd = "source /etc/profile.d/mysql.sh;" + mysqlCmd;
                }
            }
            catch (Exception)
            {

            }

            try
            {
                RunPosixCmd execCmd = new RunPosixCmd(this.HostName, this.UserName, this.Password);
                string cmd = string.Format(mysqlCmd, getVariablesCmd, value) + "| awk '{print $2}'";
                execCmd.FileName = cmd;
                execCmd.RunCmd();
                cmdoutput = execCmd.StdOut;
            }
            catch
            {
                throw new VarAbort("Get Variables value from MySQL CMD Failed!");
            }
            if (needTrim)
            {
                return cmdoutput.Trim('\n');
            }
            else
            {
                return cmdoutput;
            }
        }

    }
}
