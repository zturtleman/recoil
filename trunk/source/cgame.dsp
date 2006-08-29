# Microsoft Developer Studio Project File - Name="cgame" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cgame - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cgame.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cgame.mak" CFG="cgame - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cgame - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "cgame - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MissionPack/code/cgame", NPAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cgame - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\cgame\bin\Debug"
# PROP BASE Intermediate_Dir ".\cgame\bin\Debug"
# PROP BASE Target_Dir ".\engine\bin\Debug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\cgame\bin\Debug"
# PROP Intermediate_Dir ".\cgame\bin\Debug"
# PROP Target_Dir ".\engine\bin\Debug"
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /G5 /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\engine\bin\Debug\cgamex86.lib"

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\cgame\bin\Release"
# PROP BASE Intermediate_Dir ".\cgame\bin\Release"
# PROP BASE Target_Dir ".\engine\bin\Release"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\cgame\bin\Release"
# PROP Intermediate_Dir ".\cgame\bin\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ".\engine\bin\Release"
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /G6 /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /GF /c
# ADD CPP /nologo /G6 /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "STATIC_GAME" /FR /GF /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\engine\bin\Release\cgamex86.lib"

!ENDIF 

# Begin Target

# Name "cgame - Win32 Debug"
# Name "cgame - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=game\bg_lib.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=game\bg_misc.c
DEP_CPP_BG_MI=\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\bg_pmove.c
DEP_CPP_BG_PM=\
	".\game\bg_local.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\bg_slidemove.c
DEP_CPP_BG_SL=\
	".\game\bg_local.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_consolecmds.c
DEP_CPP_CG_CO=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\menudef.h"\
	".\ui\ui_shared.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_draw.c
DEP_CPP_CG_DR=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_drawtools.c
DEP_CPP_CG_DRA=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_effects.c
DEP_CPP_CG_EF=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_ents.c
DEP_CPP_CG_EN=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_event.c
DEP_CPP_CG_EV=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_info.c
DEP_CPP_CG_IN=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_localents.c
DEP_CPP_CG_LO=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_main.c
DEP_CPP_CG_MA=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_marks.c
DEP_CPP_CG_MAR=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_newDraw.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=cgame\cg_players.c
DEP_CPP_CG_PL=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_playerstate.c
DEP_CPP_CG_PLA=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_predict.c
DEP_CPP_CG_PR=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_scoreboard.c
DEP_CPP_CG_SC=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_servercmds.c
DEP_CPP_CG_SE=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\menudef.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_snapshot.c
DEP_CPP_CG_SN=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_view.c
DEP_CPP_CG_VI=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cgame\cg_weapons.c
DEP_CPP_CG_WE=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\game\bg_public.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\q_math.c
DEP_CPP_Q_MAT=\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\q_shared.c
DEP_CPP_Q_SHA=\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "cgame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "cgame - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ui\ui_shared.c
DEP_CPP_UI_SH=\
	".\cgame\tr_types.h"\
	".\game\botlib.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\keycodes.h"\
	".\ui\menudef.h"\
	".\ui\ui_shared.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=game\bg_public.h
# End Source File
# Begin Source File

SOURCE=cgame\cg_local.h
# End Source File
# Begin Source File

SOURCE=cgame\cg_public.h
# End Source File
# Begin Source File

SOURCE=game\q_shared.h
# End Source File
# Begin Source File

SOURCE=game\surfaceflags.h
# End Source File
# End Group
# End Target
# End Project
