
---

# Introduction #
The "Illusions Engine" project has a few dependencies that are required before the project can be successfully compiled and run.  This document will try to explain how to setup and configure those dependencies.

In most cases, the dependency will have it's own installation instructions and the reader is encouraged to refer to those instructions when available as they may change more often than this page is updated.

This document describes how to install the prerequisites in a Windows 32-bit development environment using Microsoft's Visual Studio 2008 SP1.  The reason for this is because the engine is currently being developed in this environment and there has been minimal effort to port the engine to a different development environment.

This document assumes that you have Microsoft's Visual Studio 2008 SP1 installed on your computer.  It is also assumed that you have already checked-out the latest version of the IllusionsEngine's SVN repository.


---

# Project Dependencies #
The "Illusions Engine" project requires several 3rd party projects in order to build and run from code.  Those dependencies were not included directly in the project's subversion repository because that would result in a massive subversion repository with duplicate copies of all these projects.  In most cases, 3rd party projects will be included in the subversion checkout using the "svn:externals" property on the appropriate directory (usually /development/externals ).  The "externals" SVN property will "pull-in" the project's source code from other subversion sources.  This way, most of the dependencies can "virtually" be contained in a single check-out of the "Illusions Engine" project.

In most cases, these project will still need to be compiled before they can be linked-in with the Illusions Engine binaries.

Some of the projects that are dependencies of the "Illusions Engine" project are:
  * System (boost http://www.boost.org/ )
  * Physics (Havok http://www.havok.com/ )
  * Graphics (Ogre3D http://www.ogre3d.org/ )
  * Audio (FMOD http://www.fmod.org/ )
  * Scripting ( Mono http://www.mono-project.com/ )
  * UI (wxWidgets http://www.wxwidgets.org/ )

The following sections will describe how to obtain and build each dependency and add the header files and library paths to your environment.


---

# Utilities #
There are a few utilities I recommend in order to facilitate the setup of this project.
  * SysInternals system utilities

## SysInternals ##
SysInternals is a suite of files system and disk utilities that can help you in your day-to-day tasks.  You can download the SysInternals suite from the Microsoft Technet website: http://technet.microsoft.com/en-us/sysinternals/bb842062.aspx.  I recommend you download the entire SysInternals suite of utilities.

Specifically for our project, we will be using SysInternal's [junction](http://technet.microsoft.com/en-us/sysinternals/bb896768.aspx) utility to create "soft-links" to our prerequisite binaries and header files.  This will simplify the project configuration.

If you downloaded the SysInternals suite, I recommend you extract the files to location on your hard drive (for example D:\SysInternals\bin) add the "D:\SysInternals\bin" directory (where all the utilities should be located) to your PATH environment variable.  That way, you can run the SysInternals utilities independent of the current working directory (this will be useful later).


---

# Boost (1.40.0) #
You can obtain the Boost source from the boost website (http://www.boost.org/users/download/) or directly from the Source Forge boost files page (http://sourceforge.net/projects/boost/files/boost/1.40.0/).  Optionally, you can also obtain the precompiled boost binaries from BoostPro Computing (http://www.boostpro.com/download).  This is recommended if you are not familiar with building libraries from scratch or you don't want to bother reading any more documentation.  If you would prefer to build the Boost library yourself, then read on.

If you don't want to follow this document, you can follow the official boost documentation here: http://www.boost.org/doc/libs/1_40_0/more/getting_started/windows.html

Now that you have obtained the latest boost zip file, extract it to a location on your hard drive.  The compiled boost libraries can occupy a large amount of disk space so I recommend you extract the files to a drive that has enough room for the compiled binaries.

I recommend you create an environment variable called BOOST\_ROOT that points to the location of your Boost installation. In my case, I extracted the Boost zip file to "D:\boost\boost\_1\_40\_0" and created a junction point (using SysInternal's junction utility described in the [Utilities](#Utilities.md) section of this document) to "D:\boost\current" that refers to the latest boost build.  Then I created an environment variable called BOOST\_ROOT with the value of "D:\boost\current".  This way, when a new Boost version is released, I just have to update the "D:\boost\current" junction to point to the newest version of Boost and everything should just keep working fine without having to change any configuration settings.  I'll describe how to do this later in this section.

Enough preliminaries, let's build boost!

Boost is built with an automated build system called BJam ([Building BJam](http://www.boost.org/doc/libs/1_40_0/doc/html/jam/building.html)).  You can obtain the pre-built BJam executable (http://sourceforge.net/projects/boost/files/boost-jam/), or if you prefer to build everything from source (like I do) you can obtain the BJam source code (http://sourceforge.net/projects/boost/files/boost-jam/3.1.17/boost-jam-3.1.17.zip/download) and build BJam yourself!

Building BJam is the easy part.  Simply extract the BJam zip file to a location on your computer (I perfer to keep my Boost and BJam files in the same location).  In my case, I extracted the BJam zip file to "D:\boost\boost-jam-3.1.17".

BJam comes with a build script file that will automatically determine the build system to use based on the presence of specific environment variables.  If you have multiple compiler systems installed on you computer, you will have to specify the build system to use.  In the case of Visual Studio 2008, you would execute the build script like this:
```
cd D:\boost\boost-jam-3.1.17\
.\build.bat vc9
```
If there were no errors, this should result in the "bjam.exe" binary file being created in a sub-directory called "bin.ntx86".  This is the tool that will be used to build the Boost binaries.  All you need to do now is copy the "bjam.exe" file to your BOOST\_ROOT directory.

With the "bjam.exe" file in our BOOST\_ROOT directory, we can build the Boost library.  For the sake of simplicity, we will accept most default options to build the Boost library.  We will also build all variations of the Boost libraries at once.

**Note: The "Visual Studio 2008 Command Prompt" window can be opened from the start menu:
> Start -> All Programs -> Microsoft Visual Studio 2008 -> Visual Studio Tools -> Visual Studio 2008 Command Prompt**


Open a "Visual Studio 2008 Command Prompt" window and enter the following commands:
```
cd D:\boost\boost_1_40_0\
bjam --build-type=complete toolset=msvc stage
```
Now go get a coffee...

Done? Great!  If everything went smoothly, you should notice two new directories in your Boost directory: "bin.v2", and the "stage" directory.  The "bin.v2" directory is an intermediate build directory and can usually be safely removed (unless you want to keep all the debug stuff).  More importantly you have the "stage\lib" directory.  This directory contains the final binaries necessary for linking our project against.  I recommend you move the "stage\lib" directory directly to your BOOST\_ROOT folder.  So in my case I would run the command:
```
cd D:\boost\boost_1_40_0\
move .\stage\lib\ .\lib\
```
This should result in our lib directory at "D:\boost\boost\_1\_40\_0\lib".  You've probably noticed that there is already a "libs" directory in that folder.  This directory contains the documentation, samples and example source code for the different Boost libraries.

Now all that's left to do is tell Visual Studio where to find the Boost header and compiled binaries.

Since we want to make it as easy as possible to update our Boost build, we are going to create a junction (described earlier in this document) to our current Boost build.  To do that, open a command prompt window and enter the following commands:
```
cd D:\boost\
mkdir .\current
junction .\current .\boost_1_40_0
```
(I assume you have added the SysInternals utilities to your PATH environment variable.)

Now add the BOOST\_ROOT environment variable to point to this junction.  Optionally, you can also create a "boost" junction in the "IllusionsEngine\development\external\" directory to point to the latest Boost build.  Either way, I'm going to assume the BOOST\_ROOT environment variable exists and refers to the "D:\boost\current\" folder.

To make life really easy, we're just going to configure Visual Studio to add the Boost headers and compiled binaries to the default search paths when building any project in Visual Studio.

  1. Open Visual Studio 2008 (you don't need to open the project's solution just yet) and open the Options menu (Tools -> Options...).
  1. In the Options window that appears, expand the "Projects and Solutions" section and select the "VC++ Directories" sub-section.
  1. In the "Show directories for:" drop-down menu, select the "Include files" option.
  1. Add "$(BOOST\_ROOT)" to the bottom of the directory list.
  1. Now select the "Library files" option in the "Show Directories For:" drop-down menu.
  1. Add "$(BOOST\_ROOT)lib" to the bottom of the directory list.

Once you have done this, Visual Studio will automatically included these search paths when building and linking your projects.  And since boost is smart enough to auto-link the necessary static library files into your executable, you don't even have to specify which libraries to link with when you build your project (as long as you include the correct header files in your source code).

You may have noticed that we only added "$(BOOST\_ROOT)" to the search path for the include folders.  This is intentional.  Boost does not have a "Include" sub-directory.  Boost headers will be included directly from the BOOST\_ROOT directory.  Static libraries on the other hand, do need to include the "lib" sub-directory.


---

# Ogre3D SDK (v1.6.4 `[`Shoggoth`]`) #