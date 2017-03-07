using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace ImageSettingsElevatedProxy
{
    class Program
    {
        static void Main(string[] args)
        {
            string pathToSave = args[0];
            string fileToSave = args[1];

            File.WriteAllText(pathToSave, File.ReadAllText(fileToSave));
        }
    }
}
