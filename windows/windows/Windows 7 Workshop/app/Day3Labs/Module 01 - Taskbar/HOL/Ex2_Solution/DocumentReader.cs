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

namespace WindowsSeven.Ex2
{
    public partial class DocumentReader : Form
    {
        public DocumentReader()
        {
            InitializeComponent();
        }

        private const string APP_ID = "WindowsSeven.Ex2_DocumentReader";

        private void DocumentReader_Load(object sender, EventArgs e)
        {
            Windows7Taskbar.SetCurrentProcessAppId(APP_ID);

            if (Environment.CommandLine.Contains("/doc"))
            {
                string doc = Environment.CommandLine.Substring(
                    Environment.CommandLine.IndexOf("/doc") + "/doc".Length+1);
                rtbText.LoadFile(doc);
            }
            else
            {
                rtbText.Text = "Mary had a little lamb,\r\nHer fur as white as snow,\r\nAnd everywhere that Mary went,\r\nThe lamb was sure to go.\r\n\r\n";
                for (int i = 0; i < 5; ++i)
                    rtbText.Text = rtbText.Text + rtbText.Text;
            }
        }

        JumpListManager _jumpListManager;

        protected override void WndProc(ref Message m)
        {
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
                    Path = @"D:\Users\Sasha\Documents\Courses\Windows 7\Code\SampleDocument.rtf",
                    Category = "Interesting"
                });
                _jumpListManager.Refresh();
            }

            if (_clipToggled)
                SetClip();

            if (_customWindowManager != null)
            {
                _customWindowManager.DispatchMessage(ref m);
                _customWindowManager.InvalidatePreviews();
            }

            base.WndProc(ref m);
        }

        private CustomWindowsManager _customWindowManager;

        private void btnTogglePreview_Click(object sender, EventArgs args)
        {
            if (_customWindowManager != null)
            {
                _customWindowManager.DisablePreview();
                _customWindowManager = null;
            }
            else
            {
                _customWindowManager = CustomWindowsManager.CreateWindowsManager(Handle);
                _customWindowManager.PeekRequested += (o, e) => e.UseWindowScreenshot = true;
                _customWindowManager.ThumbnailRequested += (o, e) =>
                {
                    int index = rtbText.GetFirstCharIndexOfCurrentLine();
                    string textAround = rtbText.Text.Substring(index,
                        Math.Min(rtbText.Text.Length - index, 200));
                    Bitmap bitmap = new Bitmap(e.Width, e.Height);
                    using (Graphics g = Graphics.FromImage(bitmap))
                    {
                        g.DrawString(textAround,
                            new Font(new FontFamily("Calibri"), 9, FontStyle.Italic),
                            new SolidBrush(Color.Blue), 0, 0);
                    }
                    e.Bitmap = bitmap;
                };
            }
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() != DialogResult.OK)
                return;

            rtbText.LoadFile(ofd.FileName);
        }

        private bool _clipToggled;

        private void btnToggleClip_Click(object sender, EventArgs e)
        {
            _clipToggled = !_clipToggled;
            if (_clipToggled)
            {
                SetClip();
            }
        }

        private void SetClip()
        {
            int index = rtbText.GetFirstCharIndexOfCurrentLine();
            Point point = rtbText.GetPositionFromCharIndex(index);

            Windows7Taskbar.SetThumbnailClip(Handle,
                new Rectangle(point, new Size(200, 119)));
        }

        private void btnRegisterAssociation_Click(object sender, EventArgs e)
        {
            RegistrationHelper.RegisterFileAssociations(
                APP_ID, false, Windows7Taskbar.GetCurrentProcessAppId(),
                Assembly.GetExecutingAssembly().Location + " /doc:%1",
                ".rtf");
        }
    }
}
