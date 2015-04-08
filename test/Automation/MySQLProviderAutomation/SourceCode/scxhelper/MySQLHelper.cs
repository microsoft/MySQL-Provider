//-----------------------------------------------------------------------
// <copyright file="MySQLHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-litin</author>
// <description></description>
// <history>7/15/2014 11:33:56 AM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.Test.Common
{
    using System;
    using System.IO;
    using System.Linq;
    using System.Net;
    using System.Text.RegularExpressions;

    /// <summary>
    /// The MySQLHelper class provides functionality to install and remove
    /// an agent on a Posix host.
    /// </summary>
    /// <example>
    /// MySQLHelper helper = new MySQLHelper("scxom-rhel51-01.scx.com", "root", "OpsMgr2007R2", "rpm -i", "rpm -e scx");
    /// helper.Install();
    /// </example>
    public class MySQLHelper
    {
        #region Private Fields

        /// <summary>
        /// Generic logger. This is the ConsoleLogger by default.
        /// </summary>
        private ILogger genericLogger = new ConsoleLogger();

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
        /// Log Delegate to allow writing using a log mechanism provided by the user.
        /// </summary>
        private ScxLogDelegate logger = ScxMethods.ScxNullLogDelegate;

        #endregion Private Fields

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the MySQLHelper class.
        /// </summary>
        /// <param name="logger">Log delegate method (takes single string as argument)</param>
        /// <param name="hostName">Name of Posix host</param>
        /// <param name="userName">Valid user on Posix host</param>
        /// <param name="password">Password for user</param>
        public MySQLHelper(ScxLogDelegate logger, string hostName, string userName, string password)
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
        }

        /// <summary>
        /// MySQLHelper
        /// </summary>
        public MySQLHelper() { }

        #endregion Constructors

        #region Properties

        /// <summary>
        /// Bad name is due to conflict with previous logger class. Changing that might break other code. TODO: Fix this later.
        /// </summary>
        public ILogger GenericLogger { set { genericLogger = value; } }

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
        /// Check mysql server status
        /// return values:
        /// true: running
        /// false: not running
        /// </summary>
        public bool CheckMySQLServiceStatus(string checkMySQLServiceStatus)
        {
            try
            {
                RunPosixCmd returnValue = this.RunCmd(checkMySQLServiceStatus);
                if (returnValue.StdOut.ToLower().Contains("running"))
                {
                    return true;
                }
            }
            catch (Exception e)
            {
                throw new Exception("Check mysql status failed: " + e.Message);
            }
            return false;
        }

        /// <summary>
        /// Start mysql server
        /// </summary>
        public void StartMySQLServiceStatus(string startMySQLService)
        {
            try
            {
                this.RunCmd(startMySQLService);
            }
            catch (Exception e)
            {
                throw new Exception("Start mysql Service failed: " + e.Message);
            }
        }

        /// <summary>
        /// Stop mysql server
        /// </summary>
        public void StopMySQLServiceStatus(string stopMySQLService)
        {
            try
            {
                this.RunCmd(stopMySQLService);
            }
            catch (Exception e)
            {
                throw new Exception("Stop mysql service failed: " + e.Message);
            }
        }

        /// <summary>
        /// restart mysql server
        /// </summary>
        public void RestartMySQLServiceStatus(string restartMySQLService)
        {
            try
            {
                this.RunCmd(restartMySQLService);
            }
            catch (Exception e)
            {
                throw new Exception("Restart mysql service failed: " + e.Message);
            }
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

        #endregion Public Methods

        #endregion Methods
    }
}
