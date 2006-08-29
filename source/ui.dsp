# Microsoft Developer Studio Project File - Name="q3_ui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ui - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ui.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ui.mak" CFG="ui - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ui - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ui - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MissionPack/code/q3_ui", VFLAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ui - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\ui\bin\Release"
# PROP BASE Intermediate_Dir ".\ui\bin\Release"
# PROP BASE Target_Dir ".\engine\bin\Release"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\ui\bin\Release"
# PROP Intermediate_Dir ".\ui\bin\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ".\engine\bin\Release"
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "Q3_UI_EXPORTS" /D "_MBCS" /YX /GF /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "Q3_UI_EXPORTS" /D "_MBCS" /GF /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\engine\bin\Release\uix86.lib"

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\ui\bin\Debug"
# PROP BASE Intermediate_Dir ".\ui\bin\Debug"
# PROP BASE Target_Dir ".\engine\bin\Debug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\ui\bin\Debug"
# PROP Intermediate_Dir ".\ui\bin\Debug"
# PROP Target_Dir ".\engine\bin\Debug"
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /G5 /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "UI_EXPORTS" /D "_MBCS" /FR /Fp"Debug/q3_ui.pch" /YX /Fo"Debug/" /Fd"Debug/" /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "UI_EXPORTS" /D "_MBCS" /FR /Fp"Debug/q3_ui.pch" /YX /Fo"Debug/" /Fd"Debug/" /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\engine\bin\Debug\uix86.lib"

!ENDIF 

# Begin Target

# Name "ui - Win32 Release"
# Name "ui - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=game\bg_misc.c
DEP_CPP_BG_MI=\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\q_math.c
DEP_CPP_Q_MAT=\
	"..\game\source\bg_lib.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\q_shared.c
DEP_CPP_Q_SHA=\
	"..\game\source\bg_lib.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_addbots.c
DEP_CPP_UI_AD=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_atoms.c
DEP_CPP_UI_AT=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_cinematics.c
DEP_CPP_UI_CI=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_confirm.c
DEP_CPP_UI_CO=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_connect.c
DEP_CPP_UI_CON=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_controls2.c
DEP_CPP_UI_CONT=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_credits.c
DEP_CPP_UI_CR=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_demo2.c
DEP_CPP_UI_DE=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_display.c
DEP_CPP_UI_DI=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_gameinfo.c
DEP_CPP_UI_GA=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_ingame.c
DEP_CPP_UI_IN=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_loadconfig.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=ui\ui_main.c
DEP_CPP_UI_MA=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_menu.c
DEP_CPP_UI_ME=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_mfield.c
DEP_CPP_UI_MF=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_mods.c
DEP_CPP_UI_MO=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_network.c
DEP_CPP_UI_NE=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_options.c
DEP_CPP_UI_OP=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_playermodel.c
DEP_CPP_UI_PL=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_players.c
DEP_CPP_UI_PLA=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_playersettings.c
DEP_CPP_UI_PLAY=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_preferences.c
DEP_CPP_UI_PR=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_qmenu.c
DEP_CPP_UI_QM=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_removebots.c
DEP_CPP_UI_RE=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_saveconfig.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=ui\ui_serverinfo.c
DEP_CPP_UI_SE=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_servers2.c
DEP_CPP_UI_SER=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_setup.c
DEP_CPP_UI_SET=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_sound.c
DEP_CPP_UI_SO=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_sparena.c
DEP_CPP_UI_SP=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_specifyserver.c
DEP_CPP_UI_SPE=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_splevel.c
DEP_CPP_UI_SPL=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_sppostgame.c
DEP_CPP_UI_SPP=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_spreset.c
DEP_CPP_UI_SPR=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_spskill.c
DEP_CPP_UI_SPS=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_startserver.c
DEP_CPP_UI_ST=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_team.c
DEP_CPP_UI_TE=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_teamorders.c
DEP_CPP_UI_TEA=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_video.c
DEP_CPP_UI_VI=\
	"..\cgame\source\tr_types.h"\
	"..\game\source\bg_lib.h"\
	"..\game\source\bg_public.h"\
	"..\game\source\q_shared.h"\
	"..\game\source\surfaceflags.h"\
	".\source\keycodes.h"\
	".\source\ui_local.h"\
	".\source\ui_public.h"\
	

!IF  "$(CFG)" == "ui - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=ui\keycodes.h
# End Source File
# Begin Source File

SOURCE=game\q_shared.h
# End Source File
# Begin Source File

SOURCE=ui\ui_local.h
# End Source File
# Begin Source File

SOURCE=ui\ui_public.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=ui.def

!IF  "$(CFG)" == "ui - Win32 Release"

!ELSEIF  "$(CFG)" == "ui - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
