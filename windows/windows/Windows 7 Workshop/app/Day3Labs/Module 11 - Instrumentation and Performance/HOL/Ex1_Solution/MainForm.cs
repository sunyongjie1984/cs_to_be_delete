using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;

namespace Ex1_Starter
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            FileCopyPerformanceCounters.Initialize();
        }

        private void btnBrowseSource_Click(object sender, EventArgs e)
        {
            txtSourceDirectory.Text = BrowseForFolder("Choose source folder.", false) ?? txtSourceDirectory.Text;
        }

        private void btnBrowseDestination_Click(object sender, EventArgs e)
        {
            txtDestinationDirectory.Text = BrowseForFolder("Choose destination folder.", true) ?? txtDestinationDirectory.Text;
        }

        private static string BrowseForFolder(string description, bool showNewFolderButton)
        {
            FolderBrowserDialog browser = new FolderBrowserDialog();
            browser.RootFolder = Environment.SpecialFolder.MyComputer;
            browser.Description = description;
            browser.ShowNewFolderButton = showNewFolderButton;
            if (browser.ShowDialog() == DialogResult.OK)
                return browser.SelectedPath;
            return null;
        }

        private BackgroundWorker _worker;

        private void btnCopy_Click(object sender, EventArgs args)
        {
            string source = txtSourceDirectory.Text;
            string dest = txtDestinationDirectory.Text;

            if (!Directory.Exists(source) || !Directory.Exists(dest))
            {
                MessageBox.Show("The source and destinations folder must exist.", "Error");
                return;
            }

            btnCopy.Enabled = false;
            progressBar.Value = 0;
            progressBar.Style = ProgressBarStyle.Continuous;

            _worker = new BackgroundWorker();

            _worker.DoWork += (o, e) =>
            {
                string[] files = Directory.GetFiles(source);
                for (int i = 0; i < files.Length; ++i)
                {
                    Thread.Sleep(1000);
                    File.Copy(files[i], Path.Combine(dest, Path.GetFileName(files[i])));
                    _worker.ReportProgress((int) ((100.0f * i) / files.Length));

                    FileCopyPerformanceCounters.UpdateTotalFiles(i);
                }
            };
            _worker.WorkerReportsProgress = true;
            _worker.ProgressChanged += (o, e) =>
            {
                this.BeginInvoke((MethodInvoker)delegate
                {
                    progressBar.Value = e.ProgressPercentage;

                    FileCopyPerformanceCounters.UpdatePercentDone(e.ProgressPercentage);
                });
            };

            _worker.RunWorkerCompleted += (o, e) =>
            {
                this.BeginInvoke((MethodInvoker)delegate
                {
                    btnCopy.Enabled = true;
                    progressBar.Style = ProgressBarStyle.Marquee;
                });
            };

            _worker.RunWorkerAsync();
        }
    }
}
