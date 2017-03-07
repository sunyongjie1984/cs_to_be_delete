========================================================================
       MICROSOFT FOUNDATION CLASS PROGRAM : Who's Locking?
========================================================================

Who'sLocking? is a a devpt/system management tool to find which process is locking a DLL.

Whenever a process loads a module (DLL), it locks the DLL and no other process can delete 
and/or write in it: you get "Sharing Violation" errors (or "Access Denied").

Once you know the name of the process who's locking your DLL, you can stop this process and
have full access to the DLL module. There's no need to reboot your system anymore...

PROGRAM FEATURES
================

    * Integrated in Windows Shell (right-mouse menu on DLL, OCX, or EXE files).
    * Automatic installation/registration when launched first time.
    * 1 parameter: name of executable module to search (DLL, OCX)
    * Display list of processes who are locking a DLL (if DLL is loaded by multiples processes)
    * Displays process name, PID, executable pathname (if applicable), and service name (if applicable)


INSTALLATION
============

    The program registers itself in the Windows Shell when you start it the first time.
    * Double-click on the program WhoSLocking.exe
    * Click on the OK button to exit.


USAGE
=====

    To use this program:
    * In Windows Explorer, select on a locked module file.
    * Click on right-mouse button
    * In the menu, select option "Who's Locking?"
    * A dialog box pops-up, showing the list of processes who are locking the module file (if any).


IMPLEMENTATION
==============

    This program uses a C++ class ("CSimpleProcessAPI") to build process/module list and to find 
    the process who's locking a class. This class is reusable (no GUI stuff in it) and runs on
    both Windows NT and Windows 98. Please refer to the "SimpleProcessAPI.h" file for more
    details.


TO DO LIST
==========

    * Stop service button (if applicable)
    * Kill process button

