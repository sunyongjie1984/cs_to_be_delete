using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace ImageViewer
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private ImageViewerConfiguration _settings;

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("ImageViewer - part of the Windows 7 course.", "About Image Viewer");
        }

        private void saveSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //TODO: Refactor into a separate, *elevated* process

            _settings.Save(DEFAULT_CONFIG_PATH);
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            //TODO: Add a manifest to the executable to run asInvoker
            
            string pictures = Environment.GetFolderPath(Environment.SpecialFolder.MyPictures);
            foreach (string picture in Directory.GetFiles(pictures, "*.jpg", SearchOption.AllDirectories))
            {
                listBox1.Items.Add(picture);
            }

            try
            {
                _settings = ImageViewerConfiguration.Load(DEFAULT_CONFIG_PATH);
                listBox1.SelectedItem = _settings.SelectedImagePath;
            }
            catch (FileNotFoundException)
            {
                _settings = new ImageViewerConfiguration();
            }

            //TODO: Add shield icon to saveSettingsToolStripMenuItem
        }

        //Bad for two reasons: hard-coded path and Program Files (don't store settings there!)
        private const string DEFAULT_CONFIG_PATH = @"C:\Program Files\ImageViewer.config";

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string picture = listBox1.SelectedItem as string;
            if (picture == null)
                return;

            pictureBox1.ImageLocation = picture;

            _settings.SelectedImagePath = picture;
        }
    }
}
