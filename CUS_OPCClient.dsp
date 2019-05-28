# Microsoft Developer Studio Project File - Name="CUS_OPCClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CUS_OPCClient - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CUS_OPCClient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CUS_OPCClient.mak" CFG="CUS_OPCClient - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CUS_OPCClient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CUS_OPCClient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CUS_OPCClient - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 mpr.lib /nologo /subsystem:windows /machine:I386 /out:"Release/CMX_OPCClient.exe"

!ELSEIF  "$(CFG)" == "CUS_OPCClient - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mpr.lib /nologo /subsystem:windows /pdb:".\Debug/CUS_OPCClient.pdb" /debug /machine:I386 /out:".\Debug/CMX_OPCClient.exe"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "CUS_OPCClient - Win32 Release"
# Name "CUS_OPCClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ConnectionPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\CUS_OPCClient.cpp
# End Source File
# Begin Source File

SOURCE=.\CUS_OPCClient.rc
# End Source File
# Begin Source File

SOURCE=.\GroupDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\IAdvsink.CPP
# End Source File
# Begin Source File

SOURCE=.\ItemDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageView.cpp
# End Source File
# Begin Source File

SOURCE=.\MySQL_DIALOG.cpp
# End Source File
# Begin Source File

SOURCE=.\OPCClientDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\OPCClientView.cpp
# End Source File
# Begin Source File

SOURCE=.\opcserver.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UPDATE.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteDialog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ConnectionPoint.h
# End Source File
# Begin Source File

SOURCE=.\CUS_OPCClient.h
# End Source File
# Begin Source File

SOURCE=.\GroupDialog.h
# End Source File
# Begin Source File

SOURCE=.\IAdvsink.h
# End Source File
# Begin Source File

SOURCE=.\ItemDialog.h
# End Source File
# Begin Source File

SOURCE=.\ItemPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\Lock.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\message.h
# End Source File
# Begin Source File

SOURCE=.\MessageView.h
# End Source File
# Begin Source File

SOURCE=.\MySQL_DIALOG.h
# End Source File
# Begin Source File

SOURCE=.\OPCClientDoc.h
# End Source File
# Begin Source File

SOURCE=.\OPCClientView.h
# End Source File
# Begin Source File

SOURCE=.\OPCServer.h
# End Source File
# Begin Source File

SOURCE=.\opcwrap.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ServerDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UPDATE.h
# End Source File
# Begin Source File

SOURCE=.\WriteDialog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CUS_OPCClient.ico
# End Source File
# Begin Source File

SOURCE=.\res\CUS_OPCClient.rc2
# End Source File
# Begin Source File

SOURCE=.\res\OPCClientDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
