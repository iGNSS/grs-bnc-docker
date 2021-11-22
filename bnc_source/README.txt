BKG NTRIP Client Version 2.12.18 (Rev. 9505)

This ZIP archive provides the BNC source code as developed under
GNU GPL using Qt Version 4.8.7. The following describes how to produce your
builds of BNC on Windows, Linux and Mac systems.

Static and Shared Libraries
---------------------------
You can produce static or shared builds of BNC. Static builds are sufficient
in case you don't want BNC to produce track maps using Google Map (GM) or Open
StreetMap (OSM). GM/OSM usage would requires the QtWebKit library which can
only be part of BNC builds from shared libraries. So, using a shared library
BNC build requires that you first install your own shared library of Qt.

===============================================================================
Windows Systems, Shared Library
===============================================================================
How to install a shared Qt 4.8.7 library on a Windows system to create your
own shared build of BNC:

(1) Supposing that "Secure Socket Layer (SSL)" is not available on you system,
    you should install OpenSSL libraries in C:\OpenSSL-Win32. They are availabel
    e.g. from http://slproweb.com/download/Win32OpenSSL-1_0_1e.exe
    See http://slproweb.com/products/Win32OpenSSL.html for other SSL resources.
    Ignore possible comments about missing components during installation.

(2) Download MinGW compiler Version 4.4.0 e.g. from
    http://igs.bkg.bund.de/root_ftp/NTRIP/software/MinGW-gcc440_1.zip

(3) Unzip the ZIP archive and move its contents to a directory C:\MinGW

Now you can do either (4) or (5, 6, 8, 9, 10). Following (4) is suggested.

(4) Download file 'qt-win-opensource-4.8.7-mingw.exe' (317 MB) e.g. from
    https://download.qt.io/official_releases/qt/4.8/.
    Execute this file to install a pre-compiled shared Qt library.

(5) Download file 'qt-everywhere-opensource-src-4.8.7.zip' (269 MB) e.g. from
    https://download.qt.io/official_releases/qt/4.8/

(6) Unzip the ZIP archive and move the contents of the contained directory
    into a directory C:\Qt\4.8.7

(7) Create somewhere a file QtEnv.bat with the following contents:
    set QTDIR=C:\Qt\4.8.7
    set PATH=%PATH%;C:\MinGW\bin;C:\Qt\4.8.7\bin
    set QMAKESPEC=C:\Qt\4.8.7\mkspecs\win32-g++

(8) Open a command line window and execute file QtEnv.bat

(9) Go to directory C:\Qt\4.8.7 and configure Qt using command
    configure -fast -webkit -release -nomake examples -nomake tutorial
              -openssl -I C:\OpenSSL-Win32\include

(10) Compile Qt using command
     mingw32-make
     This may take quite a long time. Don't worry if the compilation process
     runs into a problem after some time. It is likely that the libraries
     you require are already generated at that time.

     Should you want to reconfiguring Qt following steps (8)-(10) you
     first need to clean the previous configuration using command
     'mingw32-make confclean'. Run command 'mingw32-make clean' to delete
     previously compiled source code.

(11) Download latest BNC from http://software.rtcm-ntrip.org/svn/trunk/BNC

(12) Open command line window and execute file QtEnv.bat, see (7)

(13) Go to directory BNC and enter command
     qmake bnc.pro

(14) Enter command
     mingw32-make

(15) Find binary file bnc.exe in directory named src.

(16) Extend the Windows environment variable PATH by C:\Qt\4.8.7\bin.

Steps (11)-(15) can be repeated whenever a BNC update becomes available.
Running bnc.exe on a windows system requires (1) when using the
NTRIP Version 2s option for stream transfer over TLS/SSL.

===============================================================================
Linux Systems
===============================================================================
On Linux systems you may use the following procedure to install a
shared Qt version 4.8.7 library.

Download the file 'qt-everywhere-opensource-src-4.8.7.tar.gz' (230 MB)
available from https://download.qt.io/official_releases/qt/4.8.
Unzip file, extract tar archive and change to directory
'qt-everywhere-opensource-src-4.8.7'. Run commands

 (a) ./configure -shared -webkit -nomake examples -nomake tutorial
           -prefix /usr/local/Trolltech/Qt-4.8.7 -prefix-install
 (b) gmake
 (c) gmake install

Qt will be installed into directory /usr/local/Trolltech/Qt-4.8.7.
To reconfigure, run 'gmake confclean' and 'configure'.
Note that the -prefix option allows you to specify a directory for saving
the Qt libraries. This ensures that you don't run into conflicts with other
Qt installations on your host. Note further that the following two lines

export QTDIR="/usr/local/Trolltech/Qt-4.8.7"
export PATH="$QTDIR/bin:$PATH"

need to be introduced either in $HOME/.bash_profile or $HOME/.bashrc. Once
that is done logout/login and start using Qt 4.8.7.

To then compile the BNC program you may use the following commands:

qmake bnc.pro
make

===============================================================================
Mac OS X Systems
===============================================================================
Xcode and Qt Installation
-------------------------
Xcode and Qt are required to compile BNC on OS X. Both tools are freely
available. Xcode can be downloaded from the App Store or the Apple Developer
Connection website. Once installed, run Xcode, go to
Preferences -> Downloads and install the Command Line Tools component.
Qt can be downloaded from the Qt Project website. Note that as of version 2.6
BNC requires Qt version 4.7.3 or higher due to SSL. The Qt libraries for Mac
can be downloaded from http://qt-project.org/downloads.
Once downloaded, mount the disk image, run the Qt.mpkg package and follow the
instructions from the installation wizard.

Compiling BNC
-------------
The version of qmake supplied in the Qt binary package is configured to use
the macx-xcode specification. This can be overridden with the -spec macx-g++
option which makes it possible to use qmake to create a Makefile to be used
by 'make'.

From the directory where bnc.pro is located, run qmake to create the Makefile
and then make to compile the binary.

qmake -spec macx-g++ bnc.pro
make

Refer to the following webpage for further information.
https://doc.qt.io/qt-4.8/qmake-platform-notes.html

Bundle Deployment
-----------------
When distributing BNC it is necessary to bundle in all related Qt resources in
the package. The Mac Deployment Tool has been designed to automate the process
of creating a deployable application bundle that contains the Qt libraries as
private frameworks. To use it, issue the following commands where bnc.app is
located.

macdeployqt bnc.app

Refer to the following webpage for further information:
https://doc.qt.io/qt-4.8/mac-support.html

===============================================================================
Running the Program
===============================================================================
If you are not familiar with the BNC program, we suggest to start with the
Readme.txt file in the Example_Configs directory. See bnchelp.pdf for further
information.


Federal Agency for Cartography and Geodesy (BKG)
Frankfurt, September 2021
euref-ip@bkg.bund.de

