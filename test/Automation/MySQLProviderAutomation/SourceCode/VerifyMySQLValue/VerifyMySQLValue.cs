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
    class VerifyMySQLValue : VerifyCimProvHelper, ISetup, IRun, IVerify, ICleanup
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


        /// <summary>
        /// set up
        /// </summary>
        /// <param name="ctx">Context</param>
        public void Setup(IContext ctx)
        {
            this.GetValueFromVarList(ctx);
            IVarContext varContext = (IVarContext)ctx;
            this.queryClass = varContext.CustomID;
            if (String.IsNullOrEmpty(this.queryClass))
            {
                throw new VarAbort("cid field not specified, specify query class in cid");
            }

            if (this.queryClass == "MySQL_Server")
            {
                GetMySQLServerMap();
            }
            else if (this.queryClass == "MySQL_ServerStatistics")
            {
                GetMySQLServerStatisticsMap();
            }
            else if (this.queryClass == "MySQL_Server_Database")
            {
                GetMySQLServerDataBasesMap();
            }
        }

        /// <summary>
        /// Running 
        /// </summary>
        /// <param name="mcfContext">Context</param>
        public void Run(IContext mcfContext)
        {
            mcfContext.Trc("Run entered");
            string debugRecord = null;
            bool requiredInstanceFound = false;
            bool printDebug = false;
            string[] recordKeys = mcfContext.Records.GetKeys();

            // Check records for DebugXML record flag from mcf command line. For example: MCF.exe /m:%VarMap%.xml /debugxml:true
            if (string.IsNullOrEmpty(debugRecord) == false)
            {
                printDebug = bool.Parse(debugRecord);
            }
            // Enumerate through context variation records and execute record values as regular expressions
            foreach (string wsmanQuery in this.queryXmlResult)
            {
                XmlDocument queryXmlDoc = new XmlDocument();
                queryXmlDoc.LoadXml(wsmanQuery);
                XmlElement root = queryXmlDoc.DocumentElement;
                bool matchingInstance = true;

                // Pretty-print XML
                if (printDebug == true)
                {
                    XmlTextWriter xmlWriter = new XmlTextWriter(Console.Out);
                    xmlWriter.Formatting = Formatting.Indented;
                    queryXmlDoc.WriteContentTo(xmlWriter);
                    xmlWriter.Flush();
                    Console.WriteLine();
                }

                XmlNodeList nameNodeList = root.GetElementsByTagName("InstanceID");
                string xmlDocumentName = nameNodeList.Count > 0 ? nameNodeList[0].InnerText : "unknown";
                mcfContext.Trc("Processing new XML document: " + xmlDocumentName);

                // this property used to be fillter multi instances
                if (mcfContext.Records.HasKey("InstanceID"))
                {
                    string portRecordValue = mcfContext.Records.GetValue("InstanceID");
                    System.Text.RegularExpressions.Regex criteriaPort = new Regex(portRecordValue);

                    if (!criteriaPort.IsMatch(nameNodeList[0].InnerText))
                    {
                        continue;
                    }
                }

                // Test entries in MCF variation map records agains fields returned by WSMAN
                // The WSMAN fields will be start with 'p:','wsa:','wsman:'.
                // WSMAN XML query may return 'parameter' nodes.  These are ignored.
                foreach (string recordKey in recordKeys)
                {
                    // If we want to get the inner text of node which has node name wsman:Selector, we need 2 properties.
                    // so we has 2 properties in such recordkey. Once we read the recordkey, we get 2 properties by splitting it with ','.
                    // So that we need a string array to save those 2 properties.
                    string[] recordKeyForEPR = new string[2];
                    string recordValue = mcfContext.Records.GetValue(recordKey);
                    XmlNodeList nodes = root.GetElementsByTagName(recordKey);

                    // If the recordkey contains "wsman:Selector",we try to get the nodes by the tagname.
                    if (recordKey.Contains("stopMySQLServer"))
                    {
                        continue;
                    }

                    if (nodes != null)
                    {
                        // A matching recordKey result in 1 or more XML nodes from search
                        if (nodes.Count > 0)
                        {
                            foreach (XmlNode node in nodes)
                            {
                                System.Text.RegularExpressions.Regex criteria = new Regex(recordValue);
                                if (criteria != null)
                                {
                                    if (recordKeyForEPR[0] != null)
                                    {
                                        if (node.Attributes[0].Value.Equals(recordKeyForEPR[1]))
                                        {
                                            if (criteria.IsMatch(node.InnerText))
                                            {
                                                mcfContext.Trc(recordKey + " passed criteria check");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (criteria.IsMatch(node.InnerText) == true)
                                        {
                                            mcfContext.Trc(recordKey + " passed criteria check");
                                        }
                                        else
                                        {
                                            matchingInstance = false;
                                            mcfContext.Err(string.Format("{0}.{1} with value '{2}' failed criteria check, McfRecord='{3}', regex='{4}'", this.queryClass, node.LocalName, node.InnerText, recordKey, recordValue));
                                            mcfContext.Err("Outer XML=" + node.OuterXml);
                                        }
                                    }
                                }
                                else
                                {
                                    mcfContext.Err("Error: test " + recordKey + "Invalid Regex '" + recordValue + "'");
                                }
                            }
                        }
                        else
                        {
                            // Non-query record-value pairs are ignored
                            if ((recordKey.StartsWith("p:") == true) || (recordKey.StartsWith("wsa:") == true) || (recordKey.StartsWith("wsman:") == true))
                            {
                                matchingInstance = false;
                                mcfContext.Err("Expected to find " + recordKey + " in WSMAN query");
                            }
                        }
                    }
                    else
                    {
                        mcfContext.Alw("'nodes' == null for " + recordKey);
                    }
                }

                if (this.requiredInstance)
                {
                    if (matchingInstance)
                    {
                        requiredInstanceFound = true;
                        break;
                    }
                }
                else
                {
                    if (!matchingInstance)
                    {
                        throw new VarAbort("Values in WSMAN query failed criteria check");
                    }
                }
            }

            if (this.requiredInstance &&
                requiredInstanceFound == false)
            {
                throw new VarAbort("Required instance of WSMAN object not found");
            }
        }
        /// <summary>
        /// Verify
        /// </summary>
        /// <param name="ctx"></param>
        public void Verify(IContext ctx)
        {
            // the verify running in run method.
        }

        /// <summary>
        /// Clean up
        /// </summary>
        /// <param name="ctx"></param>
        public void Cleanup(IContext ctx)
        {
            // the clean up will be done in Group Clean up Method.
        }

        /// <summary>
        /// Get MySQL_Server Map 
        /// </summary>
        private void GetMySQLServerMap()
        {
            string productIdentifyingNumber = "p:ProductIdentifyingNumber";
            string productName = "p:ProductName";
            string productVendor = "p:ProductVendor";
            string productVersion = "p:ProductVersion";
            string errorLogFile = "p:ErrorLogFile";
            string socketFile = "p:SocketFile";
            string dataDirectory = "p:DataDirectory";
            string port = "p:Port";
            XmlDocument xdoc = new XmlDocument();
            XmlElement root = xdoc.CreateElement("p:MySQL_Server");
            root.SetAttribute("xmlns:p", string.Concat(this.xmlSchemaPrefix, queryClass));
            root.SetAttribute("xmlns:xsi", xsi);
            root.SetAttribute("xml:lang", lang);
            xdoc.AppendChild(root);
            propertyLists.Add(productIdentifyingNumber, this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"hostname\"").ToLower());
            propertyLists.Add(productName, "MySQL");
            propertyLists.Add(productVendor, "Oracle");
            propertyLists.Add(productVersion, this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"version\""));
            propertyLists.Add(errorLogFile, this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"log_error\";"));
            propertyLists.Add(socketFile, this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"socket\";"));
            propertyLists.Add(dataDirectory, this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"datadir\";"));
            propertyLists.Add(port, this.GetVariablesValueFromMySQLCmd("show variables where Variable_name =\"port\";"));

            foreach (var item in propertyLists)
            {
                XmlElement element = xdoc.CreateElement(item.Key);
                element.InnerText = item.Value;
                root.AppendChild(element);
            }
            queryXmlResult.Add(xdoc.InnerXml);
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
            if (this.HostName.ToLower().Contains("m50"))
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
            if (this.HostName.ToLower().Contains("m50"))
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

            // IDB_BP_WriteWaitPct
            string innodbBufferPoolWaitFreeValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"innodb_buffer_pool_wait_free\";");
            double innodbBufferPoolWaitFree = double.Parse(innodbBufferPoolWaitFreeValue);
            string innodbBufferPoolWriteRequestsValue = this.GetVariablesValueFromMySQLCmd("SHOW GLOBAL STATUS where Variable_name= \"innodb_buffer_pool_write_requests\";");
            double innodbBufferPoolWriteRequests = double.Parse(innodbBufferPoolWriteRequestsValue);
            double idbBpWriteWaitPct = Math.Round((innodbBufferPoolWaitFree / innodbBufferPoolWriteRequests) * 100, 0);
            if (Double.IsNaN(idbBpWriteWaitPct))
            {
                idbBpWriteWaitPct = 0;
            }

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
            propertyLists.Add("p:InstanceID", string.Format("{0}:127.0.0.1:3306", this.HostName));
            propertyLists.Add("p:CurrentNumConnections", currentNumConnections);
            propertyLists.Add("p:MaxConnections", maxConnections);
            propertyLists.Add("p:Uptime", upTime);
            propertyLists.Add("p:ServerDiskUseInBytes", serverDiskUseInBytes);
            propertyLists.Add("p:ConnectionsUsePct", connectionsUsePct.ToString());
            propertyLists.Add("p:AbortedConnectionPct", abortedConnnetionPct.ToString());
            propertyLists.Add("p:SlowQueryPct", slowQueryPct.ToString());
            propertyLists.Add("p:KeyCacheHitPct", keyCacheHitPct.ToString());
            propertyLists.Add("p:KeyCacheWritePct", keyCacheWritePct.ToString());
            propertyLists.Add("p:KeyCacheUsePct", keyCacheUsePct.ToString());
            propertyLists.Add("p:QCacheHitPct", qCacheHitPct.ToString());
            propertyLists.Add("p:QCachePrunesPct", qCachePrunesPct.ToString());
            propertyLists.Add("p:QCacheUsePct", qCacheUsePct.ToString());
            propertyLists.Add("p:TCacheHitPct", tCacheHitPct.ToString());
            propertyLists.Add("p:TableLockContentionPct", tableLockContentionPct.ToString());
            propertyLists.Add("p:TableCacheUsePct", tableCacheUsePct.ToString());
            propertyLists.Add("p:IDB_BP_HitPct", idbBpHitPct.ToString());
            propertyLists.Add("p:IDB_BP_WriteWaitPct", idbBpWriteWaitPct.ToString());
            propertyLists.Add("p:IDB_BP_UsePct", idbBpUsePct.ToString());
            propertyLists.Add("p:FullTableScanPct", fullTableScanPct.ToString());

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
            queryXmlResult.Add(xdoc.InnerXml);
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

                propertyLists.Add("p:InstanceID", string.Format("{0}:127.0.0.1:3306:{1}", this.HostName, database));
                propertyLists.Add("p:DatabaseName", database);
                propertyLists.Add("p:NumberOfTables", this.GetVariablesValueFromMySQLCmd(string.Format("use information_schema;SELECT count(*) FROM information_schema.tables WHERE TABLE_SCHEMA = \"{0}\"", database), "count"));
                propertyLists.Add("p:DiskSpaceInBytes", this.GetVariablesValueFromMySQLCmd(string.Format("use information_schema;select concat(round(sum(data_length),2)) as data from tables where table_schema=\"{0}\";", database), "data"));
                foreach (var item in propertyLists)
                {
                    XmlElement element = xdoc.CreateElement(item.Key);
                    element.InnerText = item.Value;
                    root.AppendChild(element);
                }
                propertyLists.Clear();
                queryXmlResult.Add(xdoc.InnerXml);
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
            try
            {
                string mysqlCmd = "mysql -E -e '{0}'| grep '{1}'";
                RunPosixCmd execCmd = new RunPosixCmd(this.HostName, this.UserName, this.Password);
                string cmd = string.Format(mysqlCmd, getVariablesCmd, value) + "| awk '{print $2}'";
                execCmd.FileName = cmd;
                execCmd.RunCmd(cmd);
                cmdoutput = execCmd.StdOut;
            }
            catch
            {
                throw new VarAbort("cid field not specified, specify query class in cid");
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
