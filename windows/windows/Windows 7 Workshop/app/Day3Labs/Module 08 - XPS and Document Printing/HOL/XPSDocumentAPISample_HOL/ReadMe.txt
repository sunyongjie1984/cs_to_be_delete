========================================================================
    CONSOLE APPLICATION : SampleDocument Project Overview
========================================================================

This is the sample code that accompanies the white paper titled
"XPS DOcument API in Windows 7" (PDC08_XPS.docx).

This file contains a summary of what you will find in each of the files that
make up your SampleDocument application.

SampleDocument.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

SampleDocument.cpp
    This is the main application source file. Refer to the white paper titled
	"XPS DOcument API in Windows 7" (PDC08_XPS.docx) for more information
	about the program.

macros.h
    Contains helper macros that are used in SampleDocument.cpp

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named SampleDocument.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

Set the working directory to use the folder that contains the boxshot.jpg
image file.

1.	In the Visual Studio Solution Explorer, right click on SampleDocument 
		and select Properties
2.	Under Configuration Properties node in the left panel, 
		click on Debugging
3.	In the right panel, set the Working Directory property to the 
		SampleDocument\Debug folder that contains boxshot.jpg.

When run, this program creates an XPS document file. If the XPS document file 
is locked by another program, such as the XPS viewer, the program will fail. 
Be sure to close all instances of the XPS Viewer that have the output file open
before running the program.

  


/////////////////////////////////////////////////////////////////////////////
