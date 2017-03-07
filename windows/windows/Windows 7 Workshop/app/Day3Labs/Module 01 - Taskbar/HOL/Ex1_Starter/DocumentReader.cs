using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.SDK.Samples.SevenBridge.Taskbar;
using System.Reflection;
using System.IO;

namespace WindowsSeven.Ex1
{
    public partial class DocumentReader : Form
    {
        public DocumentReader()
        {
            InitializeComponent();
        }

        private const string APP_ID = "WindowsSeven.Ex1_DocumentReader";

        private void DocumentReader_Load(object sender, EventArgs e)
        {
            //
            Windows7Taskbar.SetCurrentProcessAppId(APP_ID);
            
            rtbText.Text = "Mary had a little lamb,\r\nHer fur as white as snow,\r\nAnd everywhere that Mary went,\r\nThe lamb was sure to go.\r\n\r\n";
            for (int i = 0; i < 5; ++i)
                rtbText.Text = rtbText.Text + rtbText.Text;

            if (Environment.CommandLine.Contains("/doc"))
            {
                string doc = Environment.CommandLine.Substring(
                    Environment.CommandLine.IndexOf("/doc") + "/doc".Length + 1);
                rtbText.LoadFile(doc);
            }

        }

        private JumpListManager _jumpListManager;

        protected override void WndProc(ref Message m)
        {
            //

            if (m.Msg == Windows7Taskbar.TaskbarButtonCreatedMessage)
            {
                _jumpListManager = new JumpListManager(APP_ID);
                _jumpListManager.UserRemovedItems += delegate { };
                _jumpListManager.AddUserTask(new ShellLink
                {
                    Path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), @"Windows NT\Accessories\wordpad.exe"),
                    Title = "Launch Wordpad"
                });


                _jumpListManager.AddCustomDestination(new ShellItem
                {
                    Path = "C:\\Document1.rtf",
                    Category = "Interesting"
                });
                _jumpListManager.Refresh();
                
            }




            base.WndProc(ref m);
        }

        private void btnTogglePreview_Click(object sender, EventArgs args)
        {
            //
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            //
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() != DialogResult.OK)
                return;

            rtbText.LoadFile(ofd.FileName);
        }

        private void btnToggleClip_Click(object sender, EventArgs e)
        {
            //
        }

        private void SetClip()
        {
            //
        }

        private void btnRegisterAssociation_Click(object sender, EventArgs e)
        {
            //
            RegistrationHelper.RegisterFileAssociations(
                APP_ID, false, Windows7Taskbar.GetCurrentProcessAppId(),
                Assembly.GetExecutingAssembly().Location + " /doc:%1",
                ".rtf");

        }
    }
}
