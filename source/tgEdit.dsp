# Microsoft Developer Studio Project File - Name="tgEdit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=tgEdit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tgEdit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tgEdit.mak" CFG="tgEdit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tgEdit - Win32 Universal Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "tgEdit - Win32 Universal Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "tgEdit - Win32 Universal Release" (based on "Win32 (x86) Application")
!MESSAGE "tgEdit - Win32 Universal Debug" (based on "Win32 (x86) Application")
!MESSAGE "tgEdit - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "tgEdit - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "tgEdit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tgEdit - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tgEdit - Win32 Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "tgEdit\bin\Release"
# PROP BASE Intermediate_Dir "tgEdit\bin\Release"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "tgEdit\bin\Release"
# PROP Intermediate_Dir "tgEdit\bin\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /MD /W4 /GR /O2 /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivu" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswunivu\text.pdb" /FD /EHsc /c
# ADD CPP /nologo /MD /W4 /GR /O2 /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivu" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswunivu\text.pdb" /FD /EHsc /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivu" /i "C:\wxWidgets-2.6.3\include" /i "." /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivu" /i "C:\wxWidgets-2.6.3\include" /i "." /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv26u_core.lib wxbase26u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /machine:I386 /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"
# ADD LINK32 wxmswuniv26u_core.lib wxbase26u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin\tgEdit.exe" /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"

!ELSEIF  "$(CFG)" == "tgEdit - Win32 Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "tgEdit\bin\Debug"
# PROP BASE Intermediate_Dir "tgEdit\bin\Debug"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "tgEdit\bin\Debug"
# PROP Intermediate_Dir "tgEdit\bin\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivud" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswunivud\text.pdb" /FD /GZ /EHsc /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivud" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswunivud\text.pdb" /FD /GZ /EHsc /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivud" /i "C:\wxWidgets-2.6.3\include" /i "." /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivud" /i "C:\wxWidgets-2.6.3\include" /i "." /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv26ud_core.lib wxbase26ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"
# ADD LINK32 wxmswuniv26ud_core.lib wxbase26ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin\tgEdit.exe" /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"

!ELSEIF  "$(CFG)" == "tgEdit - Win32 Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "tgEdit\bin\Release"
# PROP BASE Intermediate_Dir "tgEdit\bin\Release"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "tgEdit\bin\Release"
# PROP Intermediate_Dir "tgEdit\bin\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /MD /W4 /GR /O2 /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswuniv" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswuniv\text.pdb" /FD /EHsc /c
# ADD CPP /nologo /MD /W4 /GR /O2 /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswuniv" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswuniv\text.pdb" /FD /EHsc /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswuniv" /i "C:\wxWidgets-2.6.3\include" /i "." /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswuniv" /i "C:\wxWidgets-2.6.3\include" /i "." /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv26_core.lib wxbase26.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /machine:I386 /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"
# ADD LINK32 wxmswuniv26_core.lib wxbase26.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin\tgEdit.exe" /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"

!ELSEIF  "$(CFG)" == "tgEdit - Win32 Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "tgEdit\bin\Debug"
# PROP BASE Intermediate_Dir "tgEdit\bin\Debug"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "tgEdit\bin\Debug"
# PROP Intermediate_Dir "tgEdit\bin\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivd" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswunivd\text.pdb" /FD /GZ /EHsc /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivd" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswunivd\text.pdb" /FD /GZ /EHsc /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivd" /i "C:\wxWidgets-2.6.3\include" /i "." /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswunivd" /i "C:\wxWidgets-2.6.3\include" /i "." /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv26d_core.lib wxbase26d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"
# ADD LINK32 wxmswuniv26d_core.lib wxbase26d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin\tgEdit.exe" /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"

!ELSEIF  "$(CFG)" == "tgEdit - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "tgEdit\bin\Release"
# PROP BASE Intermediate_Dir "tgEdit\bin\Release"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "tgEdit\bin\Release"
# PROP Intermediate_Dir "tgEdit\bin\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /MD /W4 /GR /O2 /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswu" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswu\text.pdb" /FD /EHsc /c
# ADD CPP /nologo /MD /W4 /GR /O2 /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswu" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswu\text.pdb" /FD /EHsc /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswu" /i "C:\wxWidgets-2.6.3\include" /i "." /d "__WXMSW__" /d "_UNICODE" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswu" /i "C:\wxWidgets-2.6.3\include" /i "." /d "__WXMSW__" /d "_UNICODE" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw26u_core.lib wxbase26u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /machine:I386 /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"
# ADD LINK32 wxmsw26u_core.lib wxbase26u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin\tgEdit.exe" /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"

!ELSEIF  "$(CFG)" == "tgEdit - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "tgEdit\bin\Debug"
# PROP BASE Intermediate_Dir "tgEdit\bin\Debug"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "tgEdit\bin\Debug"
# PROP Intermediate_Dir "tgEdit\bin\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswud" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswud\text.pdb" /FD /GZ /EHsc /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswud" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswud\text.pdb" /FD /GZ /EHsc /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswud" /i "C:\wxWidgets-2.6.3\include" /i "." /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswud" /i "C:\wxWidgets-2.6.3\include" /i "." /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw26ud_core.lib wxbase26ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"
# ADD LINK32 wxmsw26ud_core.lib wxbase26ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin\tgEdit.exe" /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"

!ELSEIF  "$(CFG)" == "tgEdit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "tgEdit\bin\Release"
# PROP BASE Intermediate_Dir "tgEdit\bin\Release"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "tgEdit\bin\Release"
# PROP Intermediate_Dir "tgEdit\bin\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /MD /W4 /GR /O2 /I "C:\wxWidgets-2.6.3\lib\vc_lib\msw" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "__WXMSW__" /D "_WINDOWS" /D "NOPCH" /Fd"vc_msw\text.pdb" /FD /EHsc /c
# ADD CPP /nologo /MD /W4 /GR /O2 /I "C:\wxWidgets-2.6.3\lib\vc_lib\msw" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "__WXMSW__" /D "_WINDOWS" /D "NOPCH" /Fd"vc_msw\text.pdb" /FD /EHsc /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\msw" /i "C:\wxWidgets-2.6.3\include" /i "." /d "__WXMSW__" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\msw" /i "C:\wxWidgets-2.6.3\include" /i "." /d "__WXMSW__" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw26_core.lib wxbase26.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /machine:I386 /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"
# ADD LINK32 wxmsw26_core.lib wxbase26.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin\tgEdit.exe" /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"

!ELSEIF  "$(CFG)" == "tgEdit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "tgEdit\bin\Debug"
# PROP BASE Intermediate_Dir "tgEdit\bin\Debug"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "tgEdit\bin\Debug"
# PROP Intermediate_Dir "tgEdit\bin\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswd" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswd\text.pdb" /FD /GZ /EHsc /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I "C:\wxWidgets-2.6.3\lib\vc_lib\mswd" /I "C:\wxWidgets-2.6.3\include" /I "." /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /Fd"vc_mswd\text.pdb" /FD /GZ /EHsc /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswd" /i "C:\wxWidgets-2.6.3\include" /i "." /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i "C:\wxWidgets-2.6.3\lib\vc_lib\mswd" /i "C:\wxWidgets-2.6.3\include" /i "." /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw26d_core.lib wxbase26d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"
# ADD LINK32 wxmsw26d_core.lib wxbase26d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin\tgEdit.exe" /libpath:"C:\wxWidgets-2.6.3\lib\vc_lib"

!ENDIF 

# Begin Target

# Name "tgEdit - Win32 Universal Unicode Release"
# Name "tgEdit - Win32 Universal Unicode Debug"
# Name "tgEdit - Win32 Universal Release"
# Name "tgEdit - Win32 Universal Debug"
# Name "tgEdit - Win32 Unicode Release"
# Name "tgEdit - Win32 Unicode Debug"
# Name "tgEdit - Win32 Release"
# Name "tgEdit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\tgEdit\tgEdit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
