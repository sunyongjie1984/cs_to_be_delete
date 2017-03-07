using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using UsbCopyService;
using System.ServiceProcess;
using System.IO;
using System.Runtime.InteropServices;
using ServiceControlInterop;

namespace RegisterService
{
    public partial class RegisterServiceForm : Form
    {
        public RegisterServiceForm()
        {
            InitializeComponent();
        }

        const string ServiceName = "UsbCopyService";
        string ServiceLocation = typeof(UsbCopyService.USBService).Assembly.Location;

        private void btnRegisterDemandStart_Click(object sender, EventArgs e)
        {
            ServiceControl.AddService(
                ServiceName, ServiceName, typeof(USBService).Assembly.Location);
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            ServiceControl.ActivateService(ServiceName);

            StopLogReaderTimer();
            StartLogReaderTimer();
        }

        private void StartLogReaderTimer()
        {
            _logReaderTimer = new Timer();
            _logReaderTimer.Interval = 1000;
            _logReaderTimer.Tick += delegate
            {
                string logFile = @"C:\FromUSB\USBService.log";
                if (File.Exists(logFile))
                {
                    txtLog.Text = File.ReadAllText(logFile);
                }
            };
            _logReaderTimer.Start();
        }

        Timer _logReaderTimer;

        private void btnStop_Click(object sender, EventArgs e)
        {
            ServiceControl.DeactivateService(ServiceName);

            StopLogReaderTimer();
        }

        private void StopLogReaderTimer()
        {
            if (_logReaderTimer != null)
            {
                _logReaderTimer.Stop();
                _logReaderTimer.Dispose();
                _logReaderTimer = null;
            }
        }

        private void btnRegisterTriggerStart_Click(object sender, EventArgs e)
        {
            btnRegisterDemandStart_Click(sender, e);
            
            //

            StopLogReaderTimer();
            StartLogReaderTimer();
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            ServiceControl.RemoveService(ServiceName);
        }

        private void btnRemovePrivileges_Click(object sender, EventArgs e)
        {
            //
        }
    }
}
