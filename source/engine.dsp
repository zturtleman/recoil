# Microsoft Developer Studio Project File - Name="engine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=engine - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "engine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "engine.mak" CFG="engine - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "engine - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "engine - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MissionPack/code", CAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "engine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\engine\bin\Debug"
# PROP BASE Intermediate_Dir ".\engine\bin\Debug"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\engine\bin\Debug"
# PROP Intermediate_Dir ".\engine\bin\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /G5 /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /fo"win32\winquake.res" /d "_DEBUG"
# ADD RSC /l 0x409 /fo"win32\winquake.res" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib wsock32.lib /nologo /stack:0x800000 /subsystem:windows /map /debug /machine:IX86 /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib wsock32.lib /nologo /stack:0x800000 /subsystem:windows /map /debug /machine:IX86 /out:"..\bin\engine.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\engine\bin\Release"
# PROP BASE Intermediate_Dir ".\engine\bin\Release"
# PROP BASE Target_Dir "..\bin\"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\engine\bin\Release"
# PROP Intermediate_Dir ".\engine\bin\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "..\bin\"
# ADD BASE CPP /nologo /G6 /W4 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /GF /c
# ADD CPP /nologo /G6 /W4 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "STATIC_GAME" /FR /GF /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib wsock32.lib /nologo /stack:0x800000 /subsystem:windows /map /debug /machine:IX86 /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib wsock32.lib /nologo /stack:0x800000 /subsystem:windows /map /debug /machine:IX86 /out:"..\bin\engine.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "engine - Win32 Debug"
# Name "engine - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=engine\cl_cgame.c
DEP_CPP_CL_CG=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cl_cin.c
DEP_CPP_CL_CI=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_local.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cl_console.c
DEP_CPP_CL_CO=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cl_input.c
DEP_CPP_CL_IN=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cl_keys.c
DEP_CPP_CL_KE=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cl_main.c
DEP_CPP_CL_MA=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cl_net_chan.c
DEP_CPP_CL_NE=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cl_parse.c
DEP_CPP_CL_PA=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cl_scrn.c
DEP_CPP_CL_SC=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cl_ui.c
DEP_CPP_CL_UI=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cm_load.c
DEP_CPP_CM_LO=\
	".\engine\cm_local.h"\
	".\engine\cm_polylib.h"\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
NODEP_CPP_CM_LO=\
	".\bspc\l_qfiles.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cm_patch.c
DEP_CPP_CM_PA=\
	".\engine\cm_local.h"\
	".\engine\cm_patch.h"\
	".\engine\cm_polylib.h"\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cm_polylib.c
DEP_CPP_CM_PO=\
	".\engine\cm_local.h"\
	".\engine\cm_polylib.h"\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cm_test.c
DEP_CPP_CM_TE=\
	".\engine\cm_local.h"\
	".\engine\cm_polylib.h"\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cm_trace.c
DEP_CPP_CM_TR=\
	".\engine\cm_local.h"\
	".\engine\cm_polylib.h"\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cmd.c
DEP_CPP_CMD_C=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\common.c
DEP_CPP_COMMO=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\cvar.c
DEP_CPP_CVAR_=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\files.c
DEP_CPP_FILES=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\unzip.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\huffman.c
DEP_CPP_HUFFM=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\md4.c

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\msg.c
DEP_CPP_MSG_C=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\net_chan.c
DEP_CPP_NET_C=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\python.c
DEP_CPP_PYTHO=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
NODEP_CPP_PYTHO=\
	".\engine\python.h"\
	
# End Source File
# Begin Source File

SOURCE=game\q_math.c
DEP_CPP_Q_MAT=\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\q_shared.c
DEP_CPP_Q_SHA=\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\snd_adpcm.c
DEP_CPP_SND_A=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_local.h"\
	".\engine\snd_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\snd_dma.c
DEP_CPP_SND_D=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_local.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\snd_mem.c
DEP_CPP_SND_M=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_local.h"\
	".\engine\snd_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\snd_mix.c
DEP_CPP_SND_MI=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_local.h"\
	".\engine\snd_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\snd_wavelet.c
DEP_CPP_SND_W=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_local.h"\
	".\engine\snd_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\sv_bot.c
DEP_CPP_SV_BO=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\sv_ccmds.c
DEP_CPP_SV_CC=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\sv_client.c
DEP_CPP_SV_CL=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\sv_game.c
DEP_CPP_SV_GA=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\sv_init.c
DEP_CPP_SV_IN=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\sv_main.c
DEP_CPP_SV_MA=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\sv_net_chan.c
DEP_CPP_SV_NE=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\sv_snapshot.c
DEP_CPP_SV_SN=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\sv_world.c
DEP_CPP_SV_WO=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\unzip.c
DEP_CPP_UNZIP=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\engine\unzip.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\win32\win_input.c
DEP_CPP_WIN_I=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\engine\win32\win_local.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\win32\win_main.c
DEP_CPP_WIN_M=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\engine\win32\resource.h"\
	".\engine\win32\win_local.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\win32\win_net.c
DEP_CPP_WIN_N=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\win32\win_local.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\win32\win_shared.c
DEP_CPP_WIN_S=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\win32\win_local.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\win32\win_snd.c
DEP_CPP_WIN_SN=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_local.h"\
	".\engine\snd_public.h"\
	".\engine\win32\win_local.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\win32\win_syscon.c
DEP_CPP_WIN_SY=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\engine\win32\resource.h"\
	".\engine\win32\win_local.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=engine\win32\win_wndproc.c
DEP_CPP_WIN_W=\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\client.h"\
	".\engine\cm_public.h"\
	".\engine\keys.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\snd_public.h"\
	".\engine\tr_public.h"\
	".\engine\win32\win_local.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\ui_public.h"\
	

!IF  "$(CFG)" == "engine - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "engine - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=game\bg_public.h
# End Source File
# Begin Source File

SOURCE=cgame\cg_public.h
# End Source File
# Begin Source File

SOURCE=engine\client.h
# End Source File
# Begin Source File

SOURCE=engine\cm_local.h
# End Source File
# Begin Source File

SOURCE=engine\cm_patch.h
# End Source File
# Begin Source File

SOURCE=engine\cm_polylib.h
# End Source File
# Begin Source File

SOURCE=game\g_public.h
# End Source File
# Begin Source File

SOURCE=ui\keycodes.h
# End Source File
# Begin Source File

SOURCE=engine\keys.h
# End Source File
# Begin Source File

SOURCE=engine\win32\resource.h
# End Source File
# Begin Source File

SOURCE=engine\server.h
# End Source File
# Begin Source File

SOURCE=engine\snd_local.h
# End Source File
# Begin Source File

SOURCE=engine\snd_public.h
# End Source File
# Begin Source File

SOURCE=ui\ui_public.h
# End Source File
# Begin Source File

SOURCE=engine\unzip.h
# End Source File
# Begin Source File

SOURCE=engine\vm_local.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=engine\win32\cursor2.cur
# End Source File
# Begin Source File

SOURCE=engine\win32\cursor3.cur
# End Source File
# Begin Source File

SOURCE=engine\win32\qe3.ico
# End Source File
# Begin Source File

SOURCE=engine\win32\winquake.rc
# ADD BASE RSC /l 0x409 /i "engine\win32" /i "win32"
# ADD RSC /l 0x409 /i "engine\win32" /i "win32"
# End Source File
# End Group
# Begin Group "renderer"

# PROP Default_Filter ""
# Begin Group "renderer c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=engine\tr_animation.c
DEP_CPP_TR_AN=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_backend.c
DEP_CPP_TR_BA=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_bsp.c
DEP_CPP_TR_BS=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_cmds.c
DEP_CPP_TR_CM=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_curve.c
DEP_CPP_TR_CU=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_extentions.c
DEP_CPP_TR_EX=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_flares.c
DEP_CPP_TR_FL=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_font.c
DEP_CPP_TR_FO=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_glshader.c
DEP_CPP_TR_GL=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_image.c
DEP_CPP_TR_IM=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_init.c
DEP_CPP_TR_IN=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_light.c
DEP_CPP_TR_LI=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_main.c
DEP_CPP_TR_MA=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_marks.c
DEP_CPP_TR_MAR=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_mesh.c
DEP_CPP_TR_ME=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_model.c
DEP_CPP_TR_MO=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_noise.c
DEP_CPP_TR_NO=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_rtt.c
DEP_CPP_TR_RT=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_scene.c
DEP_CPP_TR_SC=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_shade.c
DEP_CPP_TR_SH=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_shade_calc.c
DEP_CPP_TR_SHA=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_shader.c
DEP_CPP_TR_SHAD=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_shadows.c
DEP_CPP_TR_SHADO=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_sky.c
DEP_CPP_TR_SK=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_surface.c
DEP_CPP_TR_SU=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=.\engine\tr_texgen.c
DEP_CPP_TR_TE=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\texgen\tg_shared.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\tr_world.c
DEP_CPP_TR_WO=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\win32\win_gamma.c
DEP_CPP_WIN_G=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\engine\win32\glw_win.h"\
	".\engine\win32\win_local.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\win32\win_glimp.c
DEP_CPP_WIN_GL=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\engine\win32\glw_win.h"\
	".\engine\win32\resource.h"\
	".\engine\win32\win_local.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE=engine\win32\win_qgl.c
DEP_CPP_WIN_Q=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\engine\win32\glw_win.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# End Group
# Begin Group "renderer h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=engine\cm_public.h
# End Source File
# Begin Source File

SOURCE=engine\win32\glw_win.h
# End Source File
# Begin Source File

SOURCE=game\q_shared.h
# End Source File
# Begin Source File

SOURCE=engine\qcommon.h
# End Source File
# Begin Source File

SOURCE=engine\qfiles.h
# End Source File
# Begin Source File

SOURCE=engine\qgl.h
# End Source File
# Begin Source File

SOURCE=game\surfaceflags.h
# End Source File
# Begin Source File

SOURCE=engine\tr_local.h
# End Source File
# Begin Source File

SOURCE=engine\tr_public.h
# End Source File
# Begin Source File

SOURCE=..\cgame\source\tr_types.h
# End Source File
# Begin Source File

SOURCE=engine\win32\win_local.h
# End Source File
# End Group
# End Group
# Begin Group "jpeg"

# PROP Default_Filter ""
# Begin Group "jpeg c"

# PROP Default_Filter ""
# Begin Source File

SOURCE="engine\jpeg-6\jcapimin.c"
DEP_CPP_JCAPI=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jccoefct.c"
DEP_CPP_JCCOE=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jccolor.c"
DEP_CPP_JCCOL=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcdctmgr.c"
DEP_CPP_JCDCT=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jdct.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jchuff.c"
DEP_CPP_JCHUF=\
	".\engine\jpeg-6\jchuff.h"\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcinit.c"
DEP_CPP_JCINI=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcmainct.c"
DEP_CPP_JCMAI=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcmarker.c"
DEP_CPP_JCMAR=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcmaster.c"
DEP_CPP_JCMAS=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcomapi.c"
DEP_CPP_JCOMA=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcparam.c"
DEP_CPP_JCPAR=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcphuff.c"
DEP_CPP_JCPHU=\
	".\engine\jpeg-6\jchuff.h"\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcprepct.c"
DEP_CPP_JCPRE=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jcsample.c"
DEP_CPP_JCSAM=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jctrans.c"
DEP_CPP_JCTRA=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdapimin.c"
DEP_CPP_JDAPI=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdapistd.c"
DEP_CPP_JDAPIS=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdatadst.c"
DEP_CPP_JDATA=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdatasrc.c"
DEP_CPP_JDATAS=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdcoefct.c"
DEP_CPP_JDCOE=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdcolor.c"
DEP_CPP_JDCOL=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jddctmgr.c"
DEP_CPP_JDDCT=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jdct.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdhuff.c"
DEP_CPP_JDHUF=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jdhuff.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdinput.c"
DEP_CPP_JDINP=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdmainct.c"
DEP_CPP_JDMAI=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdmarker.c"
DEP_CPP_JDMAR=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdmaster.c"
DEP_CPP_JDMAS=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdpostct.c"
DEP_CPP_JDPOS=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdsample.c"
DEP_CPP_JDSAM=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdtrans.c"
DEP_CPP_JDTRA=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jerror.c"
DEP_CPP_JERRO=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	".\engine\jpeg-6\jversion.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jfdctflt.c"
DEP_CPP_JFDCT=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jdct.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jidctflt.c"
DEP_CPP_JIDCT=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jdct.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jmemmgr.c"
DEP_CPP_JMEMM=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmemsys.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jmemnobs.c"
DEP_CPP_JMEMN=\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\glext.h"\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmemsys.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\qgl.h"\
	".\engine\qgl_linked.h"\
	".\engine\tr_local.h"\
	".\engine\tr_public.h"\
	".\engine\wglext.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jutils.c"
DEP_CPP_JUTIL=\
	".\engine\jpeg-6\jconfig.h"\
	".\engine\jpeg-6\jerror.h"\
	".\engine\jpeg-6\jinclude.h"\
	".\engine\jpeg-6\jmorecfg.h"\
	".\engine\jpeg-6\jpegint.h"\
	".\engine\jpeg-6\jpeglib.h"\
	
# End Source File
# End Group
# Begin Group "jpeg h"

# PROP Default_Filter ""
# Begin Source File

SOURCE="engine\jpeg-6\jchuff.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jconfig.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdct.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jdhuff.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jerror.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jinclude.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jmemsys.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jmorecfg.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jpegint.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jpeglib.h"
# End Source File
# Begin Source File

SOURCE="engine\jpeg-6\jversion.h"
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=unix\ChangeLog
# End Source File
# Begin Source File

SOURCE="unix\Conscript-pk3"
# End Source File
# Begin Source File

SOURCE=Construct
# End Source File
# End Target
# End Project
