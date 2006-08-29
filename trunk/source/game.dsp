# Microsoft Developer Studio Project File - Name="game" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GAME - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "game.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "game.mak" CFG="GAME - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "game - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "game - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MissionPack/code/game", CYAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "game - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\game\bin\Debug"
# PROP BASE Intermediate_Dir ".\game\bin\Debug"
# PROP BASE Target_Dir ".\engine\bin\Debug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\game\bin\Debug"
# PROP Intermediate_Dir ".\game\bin\Debug"
# PROP Target_Dir ".\engine\bin\Debug"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
LINK32=link.exe -lib
# ADD BASE CPP /nologo /G5 /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_REF_GL" /D "DEBUG" /D "GLOBALRANK" /FR /YX /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "BUILDING_REF_GL" /D "DEBUG" /D "GLOBALRANK" /FR /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\engine\bin\Debug\qagamex86.lib"

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\game\bin\Release"
# PROP BASE Intermediate_Dir ".\game\bin\Release"
# PROP BASE Target_Dir ".\engine\bin\Release"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\game\bin\Release"
# PROP Intermediate_Dir ".\game\bin\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ".\engine\bin\Release"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
LINK32=link.exe -lib
# ADD BASE CPP /nologo /G6 /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "GLOBALRANK" /YX /GF /c
# ADD CPP /nologo /G6 /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "GLOBALRANK" /D "STATIC_GAME" /FR /GF /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\engine\bin\Release\qagamex86.lib"

!ENDIF 

# Begin Target

# Name "game - Win32 Debug"
# Name "game - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "chars"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\game\bg_default.c
DEP_CPP_BG_DE=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	
# End Source File
# End Group
# Begin Source File

SOURCE=game\ai_chat.c
DEP_CPP_AI_CH=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\ai_chat.h"\
	".\game\ai_cmd.h"\
	".\game\ai_dmnet.h"\
	".\game\ai_dmq3.h"\
	".\game\ai_main.h"\
	".\game\be_aas.h"\
	".\game\be_ai_char.h"\
	".\game\be_ai_chat.h"\
	".\game\be_ai_gen.h"\
	".\game\be_ai_goal.h"\
	".\game\be_ai_move.h"\
	".\game\be_ai_weap.h"\
	".\game\be_ea.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\chars.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\inv.h"\
	".\game\match.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\game\syn.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\ai_cmd.c
DEP_CPP_AI_CM=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\ai_chat.h"\
	".\game\ai_cmd.h"\
	".\game\ai_dmnet.h"\
	".\game\ai_dmq3.h"\
	".\game\ai_main.h"\
	".\game\ai_team.h"\
	".\game\be_aas.h"\
	".\game\be_ai_char.h"\
	".\game\be_ai_chat.h"\
	".\game\be_ai_gen.h"\
	".\game\be_ai_goal.h"\
	".\game\be_ai_move.h"\
	".\game\be_ai_weap.h"\
	".\game\be_ea.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\chars.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\inv.h"\
	".\game\match.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\game\syn.h"\
	".\ui\menudef.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\ai_dmnet.c
DEP_CPP_AI_DM=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\ai_chat.h"\
	".\game\ai_cmd.h"\
	".\game\ai_dmnet.h"\
	".\game\ai_dmq3.h"\
	".\game\ai_main.h"\
	".\game\ai_team.h"\
	".\game\be_aas.h"\
	".\game\be_ai_char.h"\
	".\game\be_ai_chat.h"\
	".\game\be_ai_gen.h"\
	".\game\be_ai_goal.h"\
	".\game\be_ai_move.h"\
	".\game\be_ai_weap.h"\
	".\game\be_ea.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\chars.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\inv.h"\
	".\game\match.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\game\syn.h"\
	".\ui\menudef.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\ai_dmq3.c
DEP_CPP_AI_DMQ=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\ai_chat.h"\
	".\game\ai_cmd.h"\
	".\game\ai_dmnet.h"\
	".\game\ai_dmq3.h"\
	".\game\ai_main.h"\
	".\game\ai_team.h"\
	".\game\be_aas.h"\
	".\game\be_ai_char.h"\
	".\game\be_ai_chat.h"\
	".\game\be_ai_gen.h"\
	".\game\be_ai_goal.h"\
	".\game\be_ai_move.h"\
	".\game\be_ai_weap.h"\
	".\game\be_ea.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\chars.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\inv.h"\
	".\game\match.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\game\syn.h"\
	".\ui\menudef.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\ai_main.c
DEP_CPP_AI_MA=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\ai_chat.h"\
	".\game\ai_cmd.h"\
	".\game\ai_dmnet.h"\
	".\game\ai_dmq3.h"\
	".\game\ai_main.h"\
	".\game\ai_vcmd.h"\
	".\game\be_aas.h"\
	".\game\be_ai_char.h"\
	".\game\be_ai_chat.h"\
	".\game\be_ai_gen.h"\
	".\game\be_ai_goal.h"\
	".\game\be_ai_move.h"\
	".\game\be_ai_weap.h"\
	".\game\be_ea.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\chars.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\inv.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\game\syn.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\ai_team.c
DEP_CPP_AI_TE=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\ai_chat.h"\
	".\game\ai_cmd.h"\
	".\game\ai_dmnet.h"\
	".\game\ai_dmq3.h"\
	".\game\ai_main.h"\
	".\game\ai_team.h"\
	".\game\ai_vcmd.h"\
	".\game\be_aas.h"\
	".\game\be_ai_char.h"\
	".\game\be_ai_chat.h"\
	".\game\be_ai_gen.h"\
	".\game\be_ai_goal.h"\
	".\game\be_ai_move.h"\
	".\game\be_ai_weap.h"\
	".\game\be_ea.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\match.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\menudef.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\ai_vcmd.c
DEP_CPP_AI_VC=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\ai_chat.h"\
	".\game\ai_cmd.h"\
	".\game\ai_dmnet.h"\
	".\game\ai_dmq3.h"\
	".\game\ai_main.h"\
	".\game\ai_team.h"\
	".\game\ai_vcmd.h"\
	".\game\be_aas.h"\
	".\game\be_ai_char.h"\
	".\game\be_ai_chat.h"\
	".\game\be_ai_gen.h"\
	".\game\be_ai_goal.h"\
	".\game\be_ai_move.h"\
	".\game\be_ai_weap.h"\
	".\game\be_ea.h"\
	".\game\bg_public.h"\
	".\game\botlib.h"\
	".\game\chars.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\inv.h"\
	".\game\match.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\game\syn.h"\
	".\ui\menudef.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bg_chars.h
# End Source File
# Begin Source File

SOURCE=game\bg_lib.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=game\bg_misc.c
DEP_CPP_BG_MI=\
	".\cgame\cg_local.h"\
	".\cgame\cg_public.h"\
	".\cgame\tr_types.h"\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

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
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

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
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_active.c
DEP_CPP_G_ACT=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_arenas.c
DEP_CPP_G_ARE=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_bot.c
DEP_CPP_G_BOT=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_client.c
DEP_CPP_G_CLI=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_cmds.c
DEP_CPP_G_CMD=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	".\ui\menudef.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_combat.c
DEP_CPP_G_COM=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_items.c
DEP_CPP_G_ITE=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_main.c
DEP_CPP_G_MAI=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_mem.c
DEP_CPP_G_MEM=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_misc.c
DEP_CPP_G_MIS=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_missile.c
DEP_CPP_G_MISS=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_mover.c
DEP_CPP_G_MOV=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_session.c
DEP_CPP_G_SES=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_spawn.c
DEP_CPP_G_SPA=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_svcmds.c
DEP_CPP_G_SVC=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_target.c
DEP_CPP_G_TAR=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_team.c
DEP_CPP_G_TEA=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_trigger.c
DEP_CPP_G_TRI=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_utils.c
DEP_CPP_G_UTI=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\g_weapon.c
DEP_CPP_G_WEA=\
	".\engine\cm_public.h"\
	".\engine\qcommon.h"\
	".\engine\qfiles.h"\
	".\engine\server.h"\
	".\game\bg_public.h"\
	".\game\g_local.h"\
	".\game\g_public.h"\
	".\game\g_team.h"\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game.def
# End Source File
# Begin Source File

SOURCE=game\q_math.c
DEP_CPP_Q_MAT=\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=game\q_shared.c
DEP_CPP_Q_SHA=\
	".\game\q_shared.h"\
	".\game\surfaceflags.h"\
	

!IF  "$(CFG)" == "game - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ELSEIF  "$(CFG)" == "game - Win32 Release"

# ADD CPP /nologo /GX /O2

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=game\ai_chat.h
# End Source File
# Begin Source File

SOURCE=game\ai_cmd.h
# End Source File
# Begin Source File

SOURCE=game\ai_dmnet.h
# End Source File
# Begin Source File

SOURCE=game\ai_dmq3.h
# End Source File
# Begin Source File

SOURCE=game\ai_main.h
# End Source File
# Begin Source File

SOURCE=game\ai_team.h
# End Source File
# Begin Source File

SOURCE=game\ai_vcmd.h
# End Source File
# Begin Source File

SOURCE=game\be_aas.h
# End Source File
# Begin Source File

SOURCE=game\be_ai_char.h
# End Source File
# Begin Source File

SOURCE=game\be_ai_chat.h
# End Source File
# Begin Source File

SOURCE=game\be_ai_gen.h
# End Source File
# Begin Source File

SOURCE=game\be_ai_goal.h
# End Source File
# Begin Source File

SOURCE=game\be_ai_move.h
# End Source File
# Begin Source File

SOURCE=game\be_ai_weap.h
# End Source File
# Begin Source File

SOURCE=game\be_ea.h
# End Source File
# Begin Source File

SOURCE=game\bg_local.h
# End Source File
# Begin Source File

SOURCE=game\bg_public.h
# End Source File
# Begin Source File

SOURCE=game\botlib.h
# End Source File
# Begin Source File

SOURCE=game\chars.h
# End Source File
# Begin Source File

SOURCE=game\g_local.h
# End Source File
# Begin Source File

SOURCE=game\g_public.h
# End Source File
# Begin Source File

SOURCE=game\g_team.h
# End Source File
# Begin Source File

SOURCE=game\inv.h
# End Source File
# Begin Source File

SOURCE=game\match.h
# End Source File
# Begin Source File

SOURCE=game\q_shared.h
# End Source File
# Begin Source File

SOURCE=game\surfaceflags.h
# End Source File
# Begin Source File

SOURCE=game\syn.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
