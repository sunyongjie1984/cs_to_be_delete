using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceProcess;
using System.Text;

namespace UsbCopyService
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main()
        {
            if (Environment.CommandLine.Contains("/console"))
            {
                new USBService().DoWork();
                return;
            }

            ServiceBase[] ServicesToRun;
            ServicesToRun = new ServiceBase[] 
			{ 
				new USBService() 
			};
            ServiceBase.Run(ServicesToRun);
        }
    }
}
