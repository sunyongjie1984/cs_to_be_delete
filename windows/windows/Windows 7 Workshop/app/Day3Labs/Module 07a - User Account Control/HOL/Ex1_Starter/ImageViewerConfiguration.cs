using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;

namespace ImageViewer
{
    public sealed class ImageViewerConfiguration
    {
        public string SelectedImagePath { get; set; }

        public static ImageViewerConfiguration Load(string path)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(ImageViewerConfiguration));
            //Bad: don't need default FileAccess.ReadWrite here, only FileAccess.Read
            using (Stream file = File.Open(path, FileMode.Open))
            {
                return (ImageViewerConfiguration)serializer.Deserialize(file);
            }
        }

        public void Save(string path)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(ImageViewerConfiguration));
            using (Stream file = File.Open(path, FileMode.Create))
            {
                serializer.Serialize(file, this);
            }
        }
    }
}
