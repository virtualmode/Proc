@echo off

rem Build Proc for Windows.
rem @param %1 Visual Studio version (for example 2019\Professional).
rem @param %2 Configuration (debug or release).
rem @param %3 Platform (x86 or amd64).

rem Current directory of Visual Studio Code workspace:
set currentDir=%CD%

rem Setup environment variables:
rem https://renenyffenegger.ch/notes/Windows/development/Visual-Studio/environment-variables/index
echo Setting up Visual C/C++ environment...
set vspath=%programfiles(x86)%\Microsoft Visual Studio\%1\Common7\Tools
cd /d %vspath%
rem Use CALL to prevent this script termination after VsDevCmd.bat finishes.
CALL VsDevCmd.bat -arch=%3
echo.

rem Prepare variables:
set vctools=%VCToolsInstallDir%lib\%VSCMD_ARG_TGT_ARCH%
set um=%WindowsSdkDir%lib\%UCRTVersion%\um\%VSCMD_ARG_TGT_ARCH%
set ucrt=%WindowsSdkDir%lib\%UCRTVersion%\ucrt\%VSCMD_ARG_TGT_ARCH%

rem Clean project:
echo Cleaning Proc intermediate files...
cd /d %currentDir%\Proc\
make clean CONFIGURATION=%2 PLATFORM=%3
echo.

rem Assembling Proc:
echo Building...
cd /d %currentDir%\Proc\
make all CONFIGURATION=%2 PLATFORM=%3 TARGET_ENTRY=main LIBRARY_PATH='%vctools%:%um%:%ucrt%' -C %currentDir%\Proc --no-print-directory
echo.

rem Copying files to output directory:
rem echo Copying binaries to output folder...
rem cd %currentDir%
rem mkdir bin\%2
rem Copying script example: for /r %%i in (*.dll) do xcopy "%%i" "%currentDir%\bin\%2\"
rem Manual copying:
rem xcopy Proc\example.dll bin\%2\

rem End of build.bat file.
