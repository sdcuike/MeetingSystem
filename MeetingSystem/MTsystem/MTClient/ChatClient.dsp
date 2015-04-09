# Microsoft Developer Studio Project File - Name="ChatClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ChatClient - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ChatClient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ChatClient.mak" CFG="ChatClient - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ChatClient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ChatClient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ChatClient - Win32 Release"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /i "..\..\Dll" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\DLL\SkinPlusPlusDLL.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ChatClient - Win32 Debug"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /i "..\..\Dll" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\DLL\SkinPlusPlusDLL.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ChatClient - Win32 Release"
# Name "ChatClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Arc.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatClient.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatClient.rc
# End Source File
# Begin Source File

SOURCE=.\ChatClientDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatClientView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Circle.cpp
# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\Draw.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphPara.cpp
# End Source File
# Begin Source File

SOURCE=.\Line.cpp
# End Source File
# Begin Source File

SOURCE=.\Login.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Message.cpp
# End Source File
# Begin Source File

SOURCE=.\OnlineBar.cpp
# End Source File
# Begin Source File

SOURCE=.\OnlineList.cpp
# End Source File
# Begin Source File

SOURCE=.\PLine.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Text.cpp
# End Source File
# Begin Source File

SOURCE=.\TextFontDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TextWriteDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WhiteBoard.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Arc.h
# End Source File
# Begin Source File

SOURCE=.\ChatClient.h
# End Source File
# Begin Source File

SOURCE=.\ChatClientDoc.h
# End Source File
# Begin Source File

SOURCE=.\ChatClientView.h
# End Source File
# Begin Source File

SOURCE=.\ChatSocket.h
# End Source File
# Begin Source File

SOURCE=.\Circle.h
# End Source File
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\ColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\Draw.h
# End Source File
# Begin Source File

SOURCE=.\GraphPara.h
# End Source File
# Begin Source File

SOURCE=.\Line.h
# End Source File
# Begin Source File

SOURCE=.\Login.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Message.h
# End Source File
# Begin Source File

SOURCE=.\OnlineBar.h
# End Source File
# Begin Source File

SOURCE=.\OnlineList.h
# End Source File
# Begin Source File

SOURCE=.\PLine.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# Begin Source File

SOURCE=.\TextFontDlg.h
# End Source File
# Begin Source File

SOURCE=.\TextWriteDlg.h
# End Source File
# Begin Source File

SOURCE=.\WhiteBoard.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap_d.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap_g.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap_w.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChatClient.ico
# End Source File
# Begin Source File

SOURCE=.\res\ChatClient.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ChatClientDoc.ico
# End Source File
# Begin Source File

SOURCE=.\RES\mycursor.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\whstyle.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
