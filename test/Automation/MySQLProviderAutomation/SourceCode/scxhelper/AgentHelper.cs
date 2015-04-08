//-----------------------------------------------------------------------
// <copyright file="AgentHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>a-brmill</author>
// <description></description>
// <history>4/1/2009 5:33:56 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.Test.Common
{
    using System;
    using System.IO;
    using System.Net;

    /// <summary>
    /// The AgentHelper class provides functionality to install and remove
    /// an agent on a Posix host.
    /// </summary>
    /// <example>
    /// AgentHelper helper = new AgentHelper("scxom-rhel51-01.scx.com", "root", "OpsMgr2007R2", "rpm -i", "rpm -e scx");    
    /// helper.Install();
    /// </example>
    public class AgentHelper
    {
        #region Private Fields

        /// <summary>
        /// Generic logger. This is the ConsoleLogger by default.
        /// </summary>
        private ILogger genericLogger = new ConsoleLogger();

        /// <summary>
        /// UNC path to agent directory 
        /// </summary>
        private string dropLocation;

        /// <summary>
        /// Path to local UnixAgents directory 
        /// </summary>
        private string localAgentPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles),
                        @"System Center 2012\Operations Manager\Server\AgentManagement\UnixAgents");

        /// <summary>
        /// Path to the SCX log on the remote client.
        /// </summary>
        private const string scxLogPath = "/var/opt/microsoft/scx/log/scx.log";

        /// <summary>
        /// Path to the SCX CIMD log on the remote client
        /// </summary>
        private const string scxcimLogPath = "/var/opt/microsoft/scx/log/scxcimd.log";

        /// <summary>
        /// Full path to the agent package file.
        /// </summary>
        private string fullAgentPath;

        /// <summary>
        /// The agent name eg.scx-1.6.0-150.rhel.6.x64.
        /// </summary>
        private string agentName;

        /// <summary>
        /// Specific agent date to wait for
        /// </summary>
        private DateTime specificAgentDate;

        /// <summary>
        /// Text contained within directory structure denoting agent architecture
        /// </summary>
        private string directoryTag;

        /// <summary>
        /// Posix host name
        /// </summary>
        private string hostName;

        /// <summary>
        /// Valid user name on Posix host
        /// </summary>
        private string userName;

        /// <summary>
        /// Password for user
        /// </summary>
        private string password;

        /// <summary>
        /// Installation command for agent on Posix host
        /// </summary>
        private string installOmCmd;

        /// <summary>
        /// Uninstallation command for agent on Posix host
        /// </summary>
        private string uninstallOmCmd;

        /// <summary>
        /// Log Delegate to allow writing using a log mechanism provided by the user.
        /// </summary>
        private ScxLogDelegate logger = ScxMethods.ScxNullLogDelegate;

        /// <summary>
        /// platformTag eg.sles.10.x86. 
        /// </summary>
        private string platformTag;

        /// <summary>
        /// platformTag eg.sles.10.x86. 
        /// </summary>
        public string PlatformTag
        {
            get { return platformTag; }
            set { platformTag = value; }
        }

        /// <summary>
        /// AgentName eg.scx-1.6.0-164.sles.10.x86.sh
        /// </summary>
        public string AgentName
        {
            get { return agentName; }
            set { agentName = value; }
        }

        #endregion Private Fields


        #region Constructors

        /// <summary>
        /// Initializes a new instance of the AgentHelper class.
        /// </summary>
        /// <param name="logger">Log delegate method (takes single string as argument)</param>
        /// <param name="hostName">Name of Posix host</param>
        /// <param name="userName">Valid user on Posix host</param>
        /// <param name="password">Password for user</param>
        public AgentHelper(ScxLogDelegate logger, string hostName, string userName, string password)
        {
            if (string.IsNullOrEmpty(hostName))
            {
                throw new ArgumentNullException("hostName not set");
            }

            if (string.IsNullOrEmpty(userName))
            {
                throw new ArgumentNullException("userName not set");
            }

            if (string.IsNullOrEmpty(password))
            {
                throw new ArgumentNullException("password not set");
            }

            this.logger = logger;
            this.hostName = hostName;
            this.userName = userName;
            this.password = password;
            this.PlatformTag = GetPlatformTag(this.hostName);
        }

        /// <summary>
        /// Initializes a new instance of the AgentHelper class.
        /// </summary>
        /// <param name="logger">Log delegate method (takes single string as argument)</param>
        /// <param name="hostName">Name of Posix host</param>
        /// <param name="userName">Valid user on Posix host</param>
        /// <param name="password">Password for user</param>
        /// <param name="installOmCmd">Command to install agent package on Posix host</param>
        /// <param name="uninstallOmCmd">Command to uninstall agent package from Posix host</param>
        public AgentHelper(ScxLogDelegate logger, string hostName, string userName, string password, string installOmCmd, string uninstallOmCmd)
        {
            if (string.IsNullOrEmpty(hostName))
            {
                throw new ArgumentNullException("hostName not set");
            }

            if (string.IsNullOrEmpty(userName))
            {
                throw new ArgumentNullException("userName not set");
            }

            if (string.IsNullOrEmpty(password))
            {
                throw new ArgumentNullException("password not set");
            }

            if (string.IsNullOrEmpty(installOmCmd))
            {
                throw new ArgumentNullException("installOmCmd not set");
            }

            if (string.IsNullOrEmpty(uninstallOmCmd))
            {
                throw new ArgumentNullException("uninstallOmCmd not set");
            }

            this.specificAgentDate = new DateTime(0);
            this.logger = logger;
            this.hostName = hostName;
            this.userName = userName;
            this.password = password;
            this.installOmCmd = installOmCmd;
            this.uninstallOmCmd = uninstallOmCmd;
            this.PlatformTag = GetPlatformTag(this.hostName);
        }

        /// <summary>
        /// Need this for calling the public methods directly from the varmap.
        /// </summary>
        public AgentHelper() { }

        #endregion Constructors

        #region Properties

        /// <summary>
        /// Bad name is due to conflict with previous logger class. Changing that might break other code. TODO: Fix this later.
        /// </summary>
        public ILogger GenericLogger { set { genericLogger = value; } }

        /// <summary>
        /// Gets or sets the DropLocation property 
        /// </summary>
        public string DropLocation
        {
            get { return this.dropLocation; }
            set { this.dropLocation = value; }
        }

        /// <summary>
        /// Gets or sets the FullAgentPath property
        /// </summary>
        public string FullAgentPath
        {
            get { return this.fullAgentPath; }
            set { this.fullAgentPath = value; }
        }

        /// <summary>
        /// Gets or sets the DirectoryTag property to match within directory name
        /// </summary>
        public string DirectoryTag
        {
            get { return this.directoryTag; }
            set { this.directoryTag = value; }
        }

        /// <summary>
        /// Gets or sets the InstallOmCmd property to install the SCX agent.  Use formatted specification with {0} for file name
        /// </summary>
        public string InstallOmCmd
        {
            get { return this.installOmCmd; }
            set { this.installOmCmd = value; }
        }

        /// <summary>
        /// Gets or sets the UninstallOmCmd property to uninstall the SCX agent
        /// </summary>
        public string UninstallOmCmd
        {
            get { return this.uninstallOmCmd; }
            set { this.uninstallOmCmd = value; }
        }

        #endregion Properties

        #region Methods

        #region Public Methods

        /// <summary>
        /// Run special cmd.
        /// </summary>
        /// <remarks>WaitForNewAgent is optional.  If it is not run, then FullMySQLPath must be set.</remarks>
        public RunPosixCmd RunCmd(string cmd, string arguments = "")
        {
            // Begin cmd
            RunPosixCmd execCmd = new RunPosixCmd(this.hostName, this.userName, this.password);

            // Execute command
            execCmd.FileName = cmd;
            execCmd.Arguments = arguments;
            this.logger(string.Format("Run Command {0} on host {1} ", execCmd.FileName, this.hostName));
            execCmd.RunCmd();
            this.logger(string.Format("Command {0} out: {1}", execCmd.FileName, execCmd.StdOut));
            return execCmd;
        }
        /// <summary>
        /// Execute 'echo' on the remote machine as a test of the ability to make an ssh connection.
        /// </summary>
        /// <exception cref="Exception"></exception>
        public void VerifySSH()
        {
            this.logger("Verifying if client respond to SSH login");
            RunPosixCmd echoTest = new RunPosixCmd(this.hostName, this.userName, this.password);

            try
            {
                echoTest.RunCmd("echo test", 3);

                if (echoTest.ExitCode != 0)
                {
                    throw new Exception(echoTest.ExitCode.ToString());
                }
            }
            catch (Exception e)
            {
                throw new Exception(string.Format("VerifySSH(): Could not SSH to remote host: '{0}' ExitCode: {1}", hostName, e.Message));
            }

            this.logger(string.Format("Ssh test against {0} succeeded", hostName));
        }

        /// <summary>
        /// Set the time on the remote UNIX machine to equal that on the local server running MCF
        /// </summary>
        public void SynchDateTime()
        {
            RunPosixCmd dateCmd = new RunPosixCmd(this.hostName, this.userName, this.password);

            try
            {
                DateTime now = DateTime.Now;

                string dateCmdString = string.Format("date {0:00}{1:00}{2:00}{3:00}{4:0000}", now.Month, now.Day, now.Hour, now.Minute, now.Year);

                if (this.directoryTag.StartsWith("AIX"))
                {
                    this.logger("Seconds field not updated in AIX");
                }
                else if (this.directoryTag.StartsWith("HPUX"))
                {
                    this.logger("Seconds field not updated in HPUX");

                    // HPUX forces you to answer 'yes' at the prompt when moving time backwards.
                    dateCmdString = "echo \"yes\" | " + dateCmdString;
                }
                else
                {
                    dateCmdString += string.Format(".{0:00}", now.Second);
                }

                this.logger("Synchronizing client date to server date: " + now.ToString());
                dateCmd.RunCmd(dateCmdString, 3);

                dateCmd.RunCmd("date");
                this.logger("Verifying client date: " + dateCmd.StdOut);
            }
            catch (Exception e)
            {
                this.logger(string.Format("SynchTime(): Unable to synchronize time on remote host: '{0}' - {1}", this.hostName, e.Message));
            }
        }

        /// <summary>
        /// Install an agent on Posix host. Set AgentArchitecture and DirectoryTag properties.
        /// </summary>
        /// <remarks>WaitForNewAgent is optional.  If it is not run, then FullAgentPath must be set.</remarks>
        public void Install()
        {
            if (string.IsNullOrEmpty(this.fullAgentPath) == true)
            {
                throw new ArgumentNullException("FullAgentPath not set");
            }

            if (string.IsNullOrEmpty(this.installOmCmd) == true)
            {
                throw new ArgumentNullException("InstallOmCmd not set");
            }

            try
            {
                // User-specified agent path takes precedent
                PosixCopy copyToHost = new PosixCopy(this.hostName, this.userName, this.password);

                // Copy from server to Posix host
                this.logger("Copying agent from drop server to host");
                copyToHost.CopyTo(this.fullAgentPath, "/tmp/" + this.agentName);
            }
            catch (Exception e)
            {
                throw new Exception("Copying agent from drop server to host failed: " + e.Message);
            }

            try
            {
                // Begin installation
                RunPosixCmd execInstall = new RunPosixCmd(this.hostName, this.userName, this.password);

                // Execute installation command
                execInstall.FileName = string.Format(this.installOmCmd, agentName);
                execInstall.Arguments = string.Empty;
                this.logger(string.Format("Installing agent to {0}: command: {1} ", this.hostName, execInstall.FileName));
                execInstall.RunCmd();
                this.logger("Install() installation out: " + execInstall.StdOut);
                // record installation in SCX CIMD log
                string serverHostName = Dns.GetHostEntry(Dns.GetHostName()).HostName;
                execInstall.RunCmd(string.Format("echo \"{0} INFO agentHelper: agent {1} installed by {2} from {3}\" >> {4}", DateTime.Now.ToString(), agentName, serverHostName, this.fullAgentPath, scxcimLogPath));
            }
            catch (Exception e)
            {
                throw new Exception("Install OMI agent to host failed: " + e.Message);
            }
        }

        /// <summary>
        /// Uninstall an agent from a Posix host
        /// </summary>
        public void Uninstall()
        {
            Uninstall(this.hostName, this.uninstallOmCmd, this.userName, this.password);
        }

        /// <summary>
        /// Uninstall an agent from a Posix host.
        /// This is a generic method which can be called from varmap, for example in multihost tests
        /// </summary>
        /// <param name="hostName">The hostNames you want to uninstall. Seperated by comma.</param>
        /// <param name="uninstallOmCmd">Uninstall commands. Seperated by comma.</param>
        /// <param name="userName">username to connect host.</param>
        /// <param name="password">password for username.</param>
        public void Uninstall(string hostName, string uninstallOmCmd, string userName, string password)
        {
            if (string.IsNullOrEmpty(hostName))
            {
                throw new ArgumentNullException("hostName");
            }
            if (string.IsNullOrEmpty(uninstallOmCmd))
            {
                throw new ArgumentNullException("UninstallOmCmd");
            }
            uninstallOmCmd = string.Format(uninstallOmCmd, this.agentName);
            genericLogger.Write("Uninstalling agent: from {0}: {1} ", hostName, uninstallOmCmd);

            RunPosixCmd execUninstall = new RunPosixCmd(hostName, userName, password)
            {
                FileName = uninstallOmCmd,
                Arguments = string.Empty
            };

            try
            {
                execUninstall.RunCmd();
                genericLogger.Write("Uninstall agent from '{0}' successfully.", hostName);
            }
            catch (Exception e)
            {
                this.logger(string.Format("Uninstall agent from '{0}' failed. Error message: '{1}'", hostName, e.ToString()));
            }

        }

        /// <summary>
        /// SetOmAgentFullPath
        /// </summary>
        /// <param name="omiAgentPath">omiAgentPath</param>
        /// <param name="platformTag">platformTag</param>
        /// <param name="needCopyFile">needCopyFile</param>
        /// <returns>agentName</returns>
        public string SetOmAgentFullPath(string omiAgentPath, string platformTag, bool needCopyFile = false)
        {
            this.DirectoryTag = platformTag;
            //"Searching for omi in " + this.FullAgentPath;
            DirectoryInfo di = new DirectoryInfo(omiAgentPath);
            FileInfo[] fi = di.GetFiles("*" + platformTag + "*");
            if (fi.Length == 0)
            {
                throw new Exception("Found no platform installer matching platformTag: " + platformTag);
            }

            if (fi.Length > 1)
            {
                throw new Exception("Found more than one platform installer matching platformTag: " + platformTag);
            }

            // User-specified MySQL path takes precedent
            this.FullAgentPath = fi[0].FullName;
            this.AgentName = Path.GetFileName(this.FullAgentPath);

            if (needCopyFile)
            {
                PosixCopy copyToHost = new PosixCopy(this.hostName, this.userName, this.password);
                // Copy from server to Posix host
                this.logger("Copying MySQL from drop server to host");
                copyToHost.CopyTo(this.FullAgentPath, "/tmp/" + this.agentName);
            }
            return this.AgentName;
        }

        /// <summary>
        /// SetOmAgentPath
        /// </summary>
        /// <param name="omilocation">omilocation</param>
        /// <returns></returns>
        public string SetOmAgentPath(string omilocation)
        {
            return this.SetOmAgentFullPath(omilocation, this.platformTag, true);
        }

        /// <summary>
        /// Added this class to be able to call methods from the varmap.
        /// </summary>
        /// <param name="hostname">Client to talk to.</param>
        /// <param name="user">Super user.</param>
        /// <param name="pwd">Password for the super user.</param>
        /// <param name="instOmCmd">Command that can be used to install the agent. (Optional) Can be left empty if not required.</param>
        /// <param name="uninstOmCmd">Command that can be used to uninstall the agent. (Optional) Can be left empty if not required.</param>
        public void Init(string hostname, string user, string pwd, string instOmCmd = "", string uninstOmCmd = "")
        {
            hostName = hostname;
            userName = user;
            password = pwd;
            installOmCmd = instOmCmd;
            uninstallOmCmd = uninstOmCmd;
        }

        /// <summary>
        /// LogHelper Method to report Error and Warning Messages in the Scx*.log
        /// </summary>
        /// <param name="automationName">The name of automation, such sdk, wsman or wsmanstress.</param>
        /// <param name="logSeverity">the log file severity</param>
        /// <param name="scxlogIgnore">Ignore scxlog or not</param>
        /// <param name="platformTag">the platform tag in the test file</param>
        /// <param name="zoneName">the zone name of solaris platform</param>
        public void ScxLogHelper(string automationName, string logSeverity, bool scxlogIgnore, string platformTag, string zoneName)
        {
            RunPosixCmd runcmd = new RunPosixCmd(this.hostName, this.userName, this.password);
            PosixCopy posixCopy = new PosixCopy(this.hostName, this.userName, this.password);
            string logFileName = string.IsNullOrEmpty(zoneName) ? logFileName = string.Format("scx.test.{0}.{1}.{2}.log", automationName, platformTag, logSeverity) :
                string.Format("scx.test.{0}.{1}.{2}.{3}.log", automationName, platformTag, zoneName, logSeverity);

            string remoteFilePath = "/var/opt/microsoft/scx/log/" + logFileName;
            string localFilePath = Path.Combine(System.Environment.CurrentDirectory, logFileName);

            // Grep for LogSeverity in SCX and SCXCIMD log          
            string grepScxLog = string.Format("cat {0}|grep {1}>>{2}", scxLogPath, logSeverity, remoteFilePath);
            string grepScxCimdLog = string.Format("cat {0}|grep {1}>>{2}", scxcimLogPath, logSeverity, remoteFilePath);
            string fullCommand = string.Format("{0};{1};", grepScxLog, grepScxCimdLog);

            try
            {
                // This command will always return exit code "1". While the command execute successfully without any error message.
                // You can use command "echo $?" to see the exit code after you run the command by manual on UNIX/Linux machine.
                runcmd.RunCmd(fullCommand);
            }
            catch (Exception e)
            {
                // Exception happens when there is 0 results while doing Grep So tracing this exception
                this.logger(e.Message);
            }

            try
            {
                posixCopy.CopyFrom(remoteFilePath, localFilePath);
            }
            catch (Exception ex)
            {
                throw new InvalidOperationException("Exception in PosixCopyFrom" + ex.Message);
            }

            FileInfo file = new FileInfo(localFilePath);
            if (file.Exists && (file.Length != 0))
            {
                if (!scxlogIgnore)
                {
                    throw new FileNotFoundException(string.Format("Unexpected {0} Messages in SCX Logs(scx.log/scxcimd.log).Please see the {1} for more details", logSeverity, logFileName));
                }
            }
            else if (file.Exists && file.Length == 0)
            {
                file.Delete();
            }
        }

        /// <summary>
        /// restart omi agent
        /// </summary>
        public void RestartOmAgent(string restartOmAgentCmd)
        {
            try
            {
                this.RunCmd(restartOmAgentCmd);
            }
            catch (Exception e)
            {
                throw new Exception("Restart OM Agent failed: " + e.Message);
            }
        }

        /// <summary>
        /// stop omi agent
        /// </summary>
        public void StopOmAgent(string stoptOmAgentCmd)
        {
            try
            {
                this.RunCmd(stoptOmAgentCmd);
            }
            catch (Exception e)
            {
                throw new Exception("Stop OM Agent failed: " + e.Message);
            }
        }

        /// <summary>
        /// start omi agent
        /// </summary>
        public void StartOmAgent(string startOmAgentCmd)
        {
            try
            {
                this.RunCmd(startOmAgentCmd);
            }
            catch (Exception e)
            {
                throw new Exception("Start OM Agent failed: " + e.Message);
            }
        }

        /// <summary>
        /// GetPlatformTag
        /// </summary>
        /// <param name="hostName">hostName</param>
        /// <returns>platformtag</returns>
        public string GetPlatformTag(string hostName)
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
        #endregion Public Methods

        #region Private Methods
        #endregion Private Methods

        #endregion Methods
    }
}
