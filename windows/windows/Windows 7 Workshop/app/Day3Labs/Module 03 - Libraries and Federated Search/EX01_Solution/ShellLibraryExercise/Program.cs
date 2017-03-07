using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.SDK.Samples.VistaBridge.ShellLibrary;

namespace ShellLibraryExercise
{
    class Program
    {
        static int Main(string[] args)
        {
            CommandLineInterpreter cli = new CommandLineInterpreter(args);
            return cli.Execute();
        }
    }
 }
