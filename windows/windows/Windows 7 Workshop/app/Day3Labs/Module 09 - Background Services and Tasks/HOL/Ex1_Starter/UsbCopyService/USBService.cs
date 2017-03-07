using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.IO;
using System.Threading;
using System.Runtime.InteropServices;
using ServiceControlInterop;

namespace UsbCopyService
{
    public partial class USBService : ServiceBase
    {
        public USBService()
        {
            InitializeComponent();
        }

        const string DIRECTORY_TO_MONITOR = "ToCopy";
        const string COPY_TO = "FromUSB";
        const string LOG_FILE = "USBService.log";

        public void DoWork()
        {
            Thread.Sleep(TimeSpan.FromSeconds(2));

            string destDirectory = Path.Combine(
                @"C:\",
                COPY_TO);

            if (!Directory.Exists(destDirectory))
                Directory.CreateDirectory(destDirectory);

            string logFile = Path.Combine(destDirectory, LOG_FILE);
            if (!File.Exists(logFile))
                File.WriteAllText(logFile, "");
            StreamWriter log = File.AppendText(logFile);
            log.WriteLine(DateTime.Now.TimeOfDay + " USB service started working");

            foreach (DriveInfo removableDrive in DriveInfo.GetDrives().Where(
                d => d.DriveType == DriveType.Removable && d.IsReady))
            {
                log.WriteLine("Detected removable drive " + removableDrive.Name);

                DirectoryInfo rootDirectory = removableDrive.RootDirectory;
                string monitoredDirectory = Path.Combine(rootDirectory.FullName, DIRECTORY_TO_MONITOR);
                string localDestDirectory = Path.Combine(destDirectory, removableDrive.VolumeLabel);
                if (!Directory.Exists(localDestDirectory))
                    Directory.CreateDirectory(localDestDirectory);

                log.WriteLine("Checking whether " + monitoredDirectory + " exists");

                if (Directory.Exists(monitoredDirectory))
                {
                    log.WriteLine("Directory exists, copying files to " + localDestDirectory);
                    foreach (string file in Directory.GetFiles(monitoredDirectory))
                    {
                        log.WriteLine("Copying " + file);
                        File.Copy(file, Path.Combine(localDestDirectory, Path.GetFileName(file)), true);
                    }
                }
            }

            log.WriteLine("Service finished working");
            log.Close();
        }

        protected override void OnStart(string[] args)
        {
            //

            _timer = new Timer(delegate
            {
                DoWork();
            });
            _timer.Change(0, 5000);
        }

        Timer _timer;

        protected override void OnStop()
        {
            if (_timer != null)
                _timer.Dispose();
        }
    }
}
