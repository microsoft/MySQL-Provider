using System;
using System.Collections.Generic;
using System.IO;

using Microsoft.EnterpriseManagement.Monitoring;
using Scx.Test.Common;

namespace Scx.Test.MySQL.SDK.MySQLSDKHelper
{
    public class MySQLAgentHelper
    {
        #region Private Fields

        /// <summary>
        /// The MySQL Agent is installed or not.
        /// </summary>
        private bool isInstalled;

        /// <summary>
        /// The Current OS is Deb or Ubun.
        /// </summary>
        private bool isDeb = false;

        /// <summary>
        /// Helper class for checking monitor status
        /// </summary>
        private MonitorHelper monitorHelper;

        /// <summary>
        /// Store information about the client machine to be discovered.
        /// </summary>
        private ClientInfo clientInfo;

        /// <summary>
        /// Logger function
        /// </summary>
        private ScxLogDelegate logger = ScxMethods.ScxNullLogDelegate;

        /// <summary>
        /// Store the POSIX command shell mechanism
        /// </summary>
        private RunPosixCmd posixCmd;

        /// <summary>
        /// Store the POSIX remote file transfer mechanism
        /// </summary>
        private PosixCopy posixCopy;

        /// <summary>
        /// Helper class to run task
        /// </summary>
        private TasksHelper tasksHelper;

        #endregion

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the MySQLAgentHelper class.
        /// </summary>
        /// <param name="rootManagementServerInfo">Information about the OM Root Management Server which will perform discovery.</param>
        public MySQLAgentHelper(OMInfo rootManagementServerInfo)
        {
            this.monitorHelper = new MonitorHelper(rootManagementServerInfo);
            this.tasksHelper = new TasksHelper(logger, rootManagementServerInfo);
        }

        /// <summary>
        /// Initializes a new instance of the MySQLAgentHelper class.
        /// </summary>
        /// <param name="rootManagementServerInfo">Information about the OM Root Management Server which will perform discovery.</param>
        /// <param name="clientInfo">Information about the client machine to discover.</param>
        public MySQLAgentHelper(OMInfo rootManagementServerInfo, ClientInfo clientInfo)
            : this(rootManagementServerInfo)
        {
            this.SetClientInfo(clientInfo);
            GetOSInfo();
        }

        #endregion

        #region Methods

        #region Public Methods

        /// <summary>
        /// Add client information to the current instance
        /// </summary>
        /// <param name="clientInfo">Information about the client</param>
        public void SetClientInfo(ClientInfo clientInfo)
        {
            this.clientInfo = clientInfo;

            this.posixCmd = new RunPosixCmd(
                string.IsNullOrEmpty(clientInfo.HostName) ? clientInfo.IPAddr : clientInfo.HostName,
                clientInfo.SuperUser,
                clientInfo.SuperUserPassword);

            this.posixCopy = new PosixCopy(
                string.IsNullOrEmpty(clientInfo.HostName) ? clientInfo.IPAddr : clientInfo.HostName,
                clientInfo.SuperUser,
                clientInfo.SuperUserPassword);
        }

        /// <summary>
        /// Verify MySQL agent is installed on client (IsInstalled? is true or false)
        /// </summary>
        /// <returns>Whether mysql agent is insalled on client</returns>
        public bool VerifyMySQLAgentInstalled()
        {
            try
            {
                if (this.isDeb)
                {
                    this.RunCmd("dpkg -l|grep -i mysql-cimprov");
                }
                else
                {
                    this.RunCmd("rpm -qa|grep -i mysql-cimprov");
                }
                this.isInstalled = true;
            }
            catch (Exception e)
            {
                this.isInstalled = false;
            }
            return this.isInstalled;
        }

        /// <summary>
        /// Get OS Info
        /// </summary>
        /// <returns>os version</returns>
        private bool GetOSInfo()
        {
            string getOSDistCmd = "python -c \"import platform; print platform.dist()\"";
            RunPosixCmd execCmd = this.RunCmd(getOSDistCmd);
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
        /// Get the DataBase Monitor.
        /// </summary>
        /// <param name="instanceID">The MySql Data Base instance</param>
        /// <returns>MySql Data Base.Monitor</returns>
        public MonitoringObject GetDataBaseMonitor(string instanceID)
        {
            MonitoringObject mysqlDataBaseInstance;

            try
            {
                //IPHostEntry hostList = Dns.GetHostEntry(this.clientInfo.HostName);
                mysqlDataBaseInstance = this.monitorHelper.GetMonitoringObject("Microsoft.MySQLServer.Database.Unix", instanceID);
            }
            catch (Exception e)
            {
                this.logger("Unable to find computer object with name: " + instanceID);
                throw e;
            }

            return mysqlDataBaseInstance;
        }

        /// <summary>
        /// SetupMySqlAuth
        /// </summary>
        /// <param name="addMySQLAuthCmd">addMySQLAuthCmd</param>
        public void SetupMySqlAuth(string addMySQLAuthCmd)
        {
            try
            {
                this.RunCmd(addMySQLAuthCmd);
            }
            catch (Exception e)
            {
                throw new Exception("Set up mysql auth failed: " + e.Message);
            }
        }

        /// <summary>
        /// Setup MySqlAuth For NonSuperUser
        /// </summary>
        /// <param name="addMySQLAuthCmd">addMySQLAuthCmd</param>
        public void SetupMySqlAuthForNonSuperUser(string addMySQLAuthCmd)
        {
            try
            {
                this.RunCmdUsingNonSuperUser(addMySQLAuthCmd);
            }
            catch (Exception e)
            {
                throw new Exception("Set up mysql auth failed: " + e.Message);
            }
        }

        /// <summary>
        /// Install an agent on Posix host. Set AgentArchitecture and DirectoryTag properties.
        /// </summary>
        /// <remarks>WaitForNewAgent is optional.  If it is not run, then FullMySQLPath must be set.</remarks>
        public void InstallMySQLAgentWihCommand(string mysqlAgentFullPath, string apcheTag)
        {
            if (string.IsNullOrEmpty(mysqlAgentFullPath) == true)
            {
                throw new ArgumentNullException("FullMySQLPath not set");
            }

            string mysqlAgentName = SetMySQLAgentFullPath(mysqlAgentFullPath, apcheTag);

            try
            {
                this.RunCmd(string.Format("sh /tmp/{0} --install", mysqlAgentName));
            }
            catch (Exception e)
            {
                throw new Exception("Install mysql CimProv agent failed: " + e.Message);
            }

        }

        /// <summary>
        /// Install an agent with task "Install/Upgrade MySQL cim module".
        /// </summary>
        /// <remarks>WaitForNewAgent is optional.  If it is not run, then FullMySQLPath must be set.</remarks>
        public bool InstallMySQLAgentWihTask()
        {

            MonitoringObject mysqlServerInstance;

            try
            {
                //IPHostEntry hostList = Dns.GetHostEntry(this.clientInfo.HostName);
                mysqlServerInstance = this.monitorHelper.GetMonitoringObject("Microsoft.MySQLServer.Installation", this.clientInfo.HostName);
            }
            catch (Exception)
            {
                this.logger("Unable to find computer object with name: " + this.clientInfo.HostName);
                return false;
            }
            IList<Microsoft.EnterpriseManagement.Runtime.TaskResult> taskResult = this.tasksHelper.RunConsumerTask(mysqlServerInstance, "Microsoft.MySQLServer.DeployModule.Task");

            if (taskResult != null)
            {
                this.logger(String.Format("Pass: Consumer task execute fine:{0}", "Microsoft.MySQLServer.Installation"));
            }
            else
            {
                throw new Exception("Consumer Task Executes Fail!");
            }

            if (taskResult[0].Status == Microsoft.EnterpriseManagement.Runtime.TaskStatus.Succeeded)
            {
                this.logger(string.Format("Pass: expectedTaskStatus: {0}, actualTaskStatus: {1}", Microsoft.EnterpriseManagement.Runtime.TaskStatus.Succeeded, taskResult[0].Status));
            }
            else
            {
                throw new Exception(string.Format("Fail: expectedTaskStatus: {0}, actualTaskStatus: {1}", Microsoft.EnterpriseManagement.Runtime.TaskStatus.Succeeded, taskResult[0].Status));
            }

            return true;
        }

        /// <summary>
        /// Install an agent on Posix host. Set AgentArchitecture and DirectoryTag properties.
        /// </summary>
        /// <remarks>WaitForNewAgent is optional.  If it is not run, then FullMySQLPath must be set.</remarks>
        public void UninstallMySQLAgentWihCommand(string apcheAgentFullPath, string apcheTag)
        {
            if (string.IsNullOrEmpty(apcheAgentFullPath) == true)
            {
                throw new ArgumentNullException("FullMySQLPath not set");
            }

            string mysqlAgentName = SetMySQLAgentFullPath(apcheAgentFullPath, apcheTag);

            try
            {
                this.RunCmd(string.Format("sh /tmp/{0} --purge", mysqlAgentName));
            }
            catch (Exception e)
            {
                throw new Exception("Install mysql CimProv agent failed: " + e.Message);
            }

        }

        #endregion

        #region Private Methods
        /// <summary>
        /// Set the mysqlFullPath.
        /// </summary>
        /// <returns>The mysql agent file name</returns>
        /// <remarks>WaitForNewAgent is optional.  If it is not run, then FullMySQLPath must be set.</remarks>
        private string SetMySQLAgentFullPath(string mysqlAgentFullPath, string mysqlTag)
        {
            //"Searching for mysql in " + this.fullMySQLAgentPath;
            DirectoryInfo di = new DirectoryInfo(mysqlAgentFullPath);
            FileInfo[] fi = di.GetFiles("*" + mysqlTag + "*");
            if (fi.Length == 0)
            {
                throw new Exception("Found no mysql installer matching MySQLTag: " + mysqlTag);
            }

            if (fi.Length > 1)
            {
                throw new Exception("Found more than one mysql installer matching MySQLTag: " + mysqlTag);
            }

            // User-specified MySQL path takes precedent
            string mysqlAgentName = Path.GetFileName(fi[0].FullName);

            PosixCopy copyToHost = new PosixCopy(this.clientInfo.HostName, this.clientInfo.SuperUser, this.clientInfo.SuperUserPassword);
            // Copy from server to Posix host
            this.logger("Copying MySQL from drop server to host");
            copyToHost.CopyTo(fi[0].FullName, "/tmp/" + mysqlAgentName);

            return mysqlAgentName;
        }

        /// <summary>
        /// Run special cmd via SSH. using Supper user account
        /// </summary>
        /// <param name="cmd">cmd line</param>
        /// <param name="arguments">arguments</param>
        /// <returns>RunPosixCmd</returns>
        private RunPosixCmd RunCmd(string cmd, string arguments = "")
        {
            // Begin cmd
            RunPosixCmd execCmd = new RunPosixCmd(this.clientInfo.HostName, this.clientInfo.SuperUser, this.clientInfo.SuperUserPassword);

            // Execute command
            execCmd.FileName = cmd;
            execCmd.Arguments = arguments;
            this.logger(string.Format("Run Command {0} on host {1} ", execCmd.FileName, this.clientInfo.HostName));
            execCmd.RunCmd();
            this.logger(string.Format("Command {0} out: {1}", execCmd.FileName, execCmd.StdOut));
            return execCmd;
        }

        /// <summary>
        /// Run special cmd.
        /// </summary>
        /// <param name="cmd">cmd line</param>
        /// <param name="arguments">cmd arguments</param>
        /// <returns>cmd</returns>
        private RunPosixCmd RunCmdUsingNonSuperUser(string cmd, string arguments = "")
        {
            // Begin cmd
            RunPosixCmd execCmd = new RunPosixCmd(this.clientInfo.HostName, this.clientInfo.User, this.clientInfo.UserPassword);

            // Execute command
            execCmd.FileName = cmd;
            execCmd.Arguments = arguments;
            this.logger(string.Format("Run Command {0} on host {1} ", execCmd.FileName, this.clientInfo.HostName));
            execCmd.RunCmd();
            this.logger(string.Format("Command {0} out: {1}", execCmd.FileName, execCmd.StdOut));
            return execCmd;
        }

        #endregion

        #endregion

        #region Properties
        /// <summary>
        /// Sets the log file delegate
        /// </summary>
        public ScxLogDelegate Logger
        {
            set
            {
                this.logger = value;
                //this.tasksHelper.Logger = value;
            }
        }

        #endregion
    }
}
