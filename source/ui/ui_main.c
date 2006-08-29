/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.
 
This file is part of Quake III Arena source code.
 
Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.
 
Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
/*
=======================================================================
 
USER INTERFACE MAIN
 
=======================================================================
*/


#include "ui_local.h"

/*
================
cvars
================
*/

typedef struct
{
    cvar_t	**cvar;
    char		*name;
    char		*defaultString;
    int			flags;
}
cvarTable_t;

cvar_t	*ui_ffa_fraglimit;
cvar_t	*ui_ffa_timelimit;

cvar_t	*ui_tourney_fraglimit;
cvar_t	*ui_tourney_timelimit;

cvar_t	*ui_team_fraglimit;
cvar_t	*ui_team_timelimit;
cvar_t	*ui_team_friendly;

cvar_t	*ui_ctf_capturelimit;
cvar_t	*ui_ctf_timelimit;
cvar_t	*ui_ctf_friendly;

cvar_t	*ui_arenasFile;
cvar_t	*ui_botsFile;
cvar_t	*ui_spScores1;
cvar_t	*ui_spScores2;
cvar_t	*ui_spScores3;
cvar_t	*ui_spScores4;
cvar_t	*ui_spScores5;
cvar_t	*ui_spAwards;
cvar_t	*ui_spVideos;
cvar_t	*ui_spSkill;

cvar_t	*ui_spSelection;

cvar_t	*ui_browserMaster;
cvar_t	*ui_browserGameType;
cvar_t	*ui_browserSortKey;
cvar_t	*ui_browserShowFull;
cvar_t	*ui_browserShowEmpty;

cvar_t	*ui_brassTime;
cvar_t	*ui_drawCrosshair;
cvar_t	*ui_drawCrosshairNames;
cvar_t	*ui_marks;

cvar_t	*ui_server1;
cvar_t	*ui_server2;
cvar_t	*ui_server3;
cvar_t	*ui_server4;
cvar_t	*ui_server5;
cvar_t	*ui_server6;
cvar_t	*ui_server7;
cvar_t	*ui_server8;
cvar_t	*ui_server9;
cvar_t	*ui_server10;
cvar_t	*ui_server11;
cvar_t	*ui_server12;
cvar_t	*ui_server13;
cvar_t	*ui_server14;
cvar_t	*ui_server15;
cvar_t	*ui_server16;

// bk001129 - made static to avoid aliasing.
static cvarTable_t		cvarTable[] = {
                                      { &ui_ffa_fraglimit, "ui_ffa_fraglimit", "20", CVAR_ARCHIVE },
                                      { &ui_ffa_timelimit, "ui_ffa_timelimit", "0", CVAR_ARCHIVE },

                                      { &ui_tourney_fraglimit, "ui_tourney_fraglimit", "0", CVAR_ARCHIVE },
                                      { &ui_tourney_timelimit, "ui_tourney_timelimit", "15", CVAR_ARCHIVE },

                                      { &ui_team_fraglimit, "ui_team_fraglimit", "0", CVAR_ARCHIVE },
                                      { &ui_team_timelimit, "ui_team_timelimit", "20", CVAR_ARCHIVE },
                                      { &ui_team_friendly, "ui_team_friendly",  "1", CVAR_ARCHIVE },

                                      { &ui_ctf_capturelimit, "ui_ctf_capturelimit", "8", CVAR_ARCHIVE },
                                      { &ui_ctf_timelimit, "ui_ctf_timelimit", "30", CVAR_ARCHIVE },
                                      { &ui_ctf_friendly, "ui_ctf_friendly",  "0", CVAR_ARCHIVE },

                                      { &ui_arenasFile, "g_arenasFile", "", CVAR_INIT|CVAR_ROM },
                                      { &ui_botsFile, "g_botsFile", "", CVAR_INIT|CVAR_ROM },
                                      { &ui_spScores1, "g_spScores1", "", CVAR_ARCHIVE | CVAR_ROM },
                                      { &ui_spScores2, "g_spScores2", "", CVAR_ARCHIVE | CVAR_ROM },
                                      { &ui_spScores3, "g_spScores3", "", CVAR_ARCHIVE | CVAR_ROM },
                                      { &ui_spScores4, "g_spScores4", "", CVAR_ARCHIVE | CVAR_ROM },
                                      { &ui_spScores5, "g_spScores5", "", CVAR_ARCHIVE | CVAR_ROM },
                                      { &ui_spAwards, "g_spAwards", "", CVAR_ARCHIVE | CVAR_ROM },
                                      { &ui_spVideos, "g_spVideos", "", CVAR_ARCHIVE | CVAR_ROM },
                                      { &ui_spSkill, "g_spSkill", "2", CVAR_ARCHIVE | CVAR_LATCH },

                                      { &ui_spSelection, "ui_spSelection", "", CVAR_ROM },

                                      { &ui_browserMaster, "ui_browserMaster", "0", CVAR_ARCHIVE },
                                      { &ui_browserGameType, "ui_browserGameType", "0", CVAR_ARCHIVE },
                                      { &ui_browserSortKey, "ui_browserSortKey", "4", CVAR_ARCHIVE },
                                      { &ui_browserShowFull, "ui_browserShowFull", "1", CVAR_ARCHIVE },
                                      { &ui_browserShowEmpty, "ui_browserShowEmpty", "1", CVAR_ARCHIVE },

                                      { &ui_brassTime, "cg_brassTime", "2500", CVAR_ARCHIVE },
                                      { &ui_drawCrosshair, "cg_drawCrosshair", "4", CVAR_ARCHIVE },
                                      { &ui_drawCrosshairNames, "cg_drawCrosshairNames", "1", CVAR_ARCHIVE },
                                      { &ui_marks, "cg_marks", "1", CVAR_ARCHIVE },

                                      { &ui_server1, "server1", "", CVAR_ARCHIVE },
                                      { &ui_server2, "server2", "", CVAR_ARCHIVE },
                                      { &ui_server3, "server3", "", CVAR_ARCHIVE },
                                      { &ui_server4, "server4", "", CVAR_ARCHIVE },
                                      { &ui_server5, "server5", "", CVAR_ARCHIVE },
                                      { &ui_server6, "server6", "", CVAR_ARCHIVE },
                                      { &ui_server7, "server7", "", CVAR_ARCHIVE },
                                      { &ui_server8, "server8", "", CVAR_ARCHIVE },
                                      { &ui_server9, "server9", "", CVAR_ARCHIVE },
                                      { &ui_server10, "server10", "", CVAR_ARCHIVE },
                                      { &ui_server11, "server11", "", CVAR_ARCHIVE },
                                      { &ui_server12, "server12", "", CVAR_ARCHIVE },
                                      { &ui_server13, "server13", "", CVAR_ARCHIVE },
                                      { &ui_server14, "server14", "", CVAR_ARCHIVE },
                                      { &ui_server15, "server15", "", CVAR_ARCHIVE },
                                      { &ui_server16, "server16", "", CVAR_ARCHIVE },
                                  };

// bk001129 - made static to avoid aliasing
static int cvarTableSize = sizeof(cvarTable) / sizeof(cvarTable[0]);


/*
=================
UI_RegisterCvars
=================
*/
void UI_RegisterCvars( void )
{
    int			i;
    cvarTable_t	*cv;

    for ( i = 0, cv = cvarTable ; i < cvarTableSize ; i++, cv++ )
        *cv->cvar = Cvar_Get(cv->name, cv->defaultString, cv->flags);
}

/*
=================
UI_UpdateCvars
=================
*/
void UI_UpdateCvars( void )
{
}
