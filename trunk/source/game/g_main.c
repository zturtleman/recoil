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

#include "g_local.h"

level_locals_t	level;

typedef struct
{
    cvar_t	**cvar;
    char		*name;
    char		*defaultString;
    int			flags;
    int			modificationCount;  // for tracking changes
    qboolean	trackChange;	    // track this variable, and announce if changed
    qboolean teamShader;        // track and if changed, update shader state
}
cvarTable_t;

gentity_t		g_entities[MAX_GENTITIES];
gclient_t		g_clients[MAX_CLIENTS];

cvar_t	*g_gametype;
cvar_t	*g_dmflags;
cvar_t	*g_fraglimit;
cvar_t	*g_timelimit;
cvar_t	*g_capturelimit;
cvar_t	*g_friendlyFire;
cvar_t	*g_password;
cvar_t	*g_needpass;
cvar_t	*g_maxclients;
cvar_t	*g_maxGameClients;
cvar_t	*g_dedicated;
cvar_t	*g_speed;
cvar_t	*g_gravity;
cvar_t	*g_cheats;
cvar_t	*g_knockback;
cvar_t	*g_quadfactor;
cvar_t	*g_forcerespawn;
cvar_t	*g_inactivity;
cvar_t	*g_debugMove;
cvar_t	*g_debugDamage;
cvar_t	*g_debugAlloc;
cvar_t	*g_weaponRespawn;
cvar_t	*g_weaponTeamRespawn;
cvar_t	*g_motd;
cvar_t	*g_synchronousClients;
cvar_t	*g_warmup;
cvar_t	*g_doWarmup;
cvar_t	*g_restarted;
cvar_t	*g_log;
cvar_t	*g_logSync;
cvar_t	*g_blood;
cvar_t	*g_podiumDist;
cvar_t	*g_podiumDrop;
cvar_t	*g_allowVote;
cvar_t	*g_teamAutoJoin;
cvar_t	*g_teamForceBalance;
cvar_t	*g_banIPs;
cvar_t	*g_filterBan;
cvar_t	*g_smoothClients;
cvar_t	*pmove_fixed;
cvar_t	*pmove_msec;
cvar_t	*g_rankings;
cvar_t	*g_listEntity;

// bk001129 - made static to avoid aliasing
static cvarTable_t		gameCvarTable[] = {
                                          // don't override the cheat state set by the system
                                          { &g_cheats, "sv_cheats", "", 0, 0, qfalse },

                                          // noset vars
                                          { NULL, "gamename", GAMEVERSION , CVAR_SERVERINFO | CVAR_ROM, 0, qfalse  },
                                          { NULL, "gamedate", __DATE__ , CVAR_ROM, 0, qfalse  },
                                          { &g_restarted, "g_restarted", "0", CVAR_ROM, 0, qfalse  },
                                          { NULL, "sv_mapname", "", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse  },

                                          // latched vars
                                          { &g_gametype, "g_gametype", "0", CVAR_SERVERINFO | CVAR_USERINFO | CVAR_LATCH, 0, qfalse  },

                                          { &g_maxclients, "sv_maxclients", "8", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse  },
                                          { &g_maxGameClients, "g_maxGameClients", "0", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse  },

                                          // change anytime vars
                                          { &g_dmflags, "dmflags", "0", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue  },
                                          { &g_fraglimit, "fraglimit", "20", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue },
                                          { &g_timelimit, "timelimit", "0", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue },
                                          { &g_capturelimit, "capturelimit", "8", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue },

                                          { &g_synchronousClients, "g_synchronousClients", "0", CVAR_SYSTEMINFO, 0, qfalse  },

                                          { &g_friendlyFire, "g_friendlyFire", "0", CVAR_ARCHIVE, 0, qtrue  },

                                          { &g_teamAutoJoin, "g_teamAutoJoin", "0", CVAR_ARCHIVE  },
                                          { &g_teamForceBalance, "g_teamForceBalance", "0", CVAR_ARCHIVE  },

                                          { &g_warmup, "g_warmup", "20", CVAR_ARCHIVE, 0, qtrue  },
                                          { &g_doWarmup, "g_doWarmup", "0", 0, 0, qtrue  },
                                          { &g_log, "g_log", "games.log", CVAR_ARCHIVE, 0, qfalse  },
                                          { &g_logSync, "g_logSync", "0", CVAR_ARCHIVE, 0, qfalse  },

                                          { &g_password, "g_password", "", CVAR_USERINFO, 0, qfalse  },

                                          { &g_banIPs, "g_banIPs", "", CVAR_ARCHIVE, 0, qfalse  },
                                          { &g_filterBan, "g_filterBan", "1", CVAR_ARCHIVE, 0, qfalse  },

                                          { &g_needpass, "g_needpass", "0", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse },

                                          { &g_dedicated, "dedicated", "0", 0, 0, qfalse  },

                                          { &g_speed, "g_speed", "240", 0, 0, qtrue  },
                                          { &g_gravity, "g_gravity", "200", 0, 0, qtrue  },
                                          { &g_knockback, "g_knockback", "1000", 0, 0, qtrue  },
                                          { &g_quadfactor, "g_quadfactor", "3", 0, 0, qtrue  },
                                          { &g_weaponRespawn, "g_weaponrespawn", "5", 0, 0, qtrue  },
                                          { &g_weaponTeamRespawn, "g_weaponTeamRespawn", "30", 0, 0, qtrue },
                                          { &g_forcerespawn, "g_forcerespawn", "20", 0, 0, qtrue },
                                          { &g_inactivity, "g_inactivity", "0", 0, 0, qtrue },
                                          { &g_debugMove, "g_debugMove", "0", 0, 0, qfalse },
                                          { &g_debugDamage, "g_debugDamage", "0", 0, 0, qfalse },
                                          { &g_debugAlloc, "g_debugAlloc", "0", 0, 0, qfalse },
                                          { &g_motd, "g_motd", "", 0, 0, qfalse },
                                          { &g_blood, "com_blood", "1", 0, 0, qfalse },

                                          { &g_podiumDist, "g_podiumDist", "80", 0, 0, qfalse },
                                          { &g_podiumDrop, "g_podiumDrop", "70", 0, 0, qfalse },

                                          { &g_allowVote, "g_allowVote", "1", CVAR_ARCHIVE, 0, qfalse },
                                          { &g_listEntity, "g_listEntity", "0", 0, 0, qfalse },

                                          { &g_smoothClients, "g_smoothClients", "1", 0, 0, qfalse},
                                          { &pmove_fixed, "pmove_fixed", "0", CVAR_SYSTEMINFO, 0, qfalse},
                                          { &pmove_msec, "pmove_msec", "8", CVAR_SYSTEMINFO, 0, qfalse},

                                          { &g_rankings, "g_rankings", "0", 0, 0, qfalse}

                                      };

// bk001129 - made static to avoid aliasing
static int gameCvarTableSize = sizeof( gameCvarTable ) / sizeof( gameCvarTable[0] );


void G_InitGame( int levelTime, int randomSeed, int restart );
void G_RunFrame( int levelTime );
void G_ShutdownGame( int restart );
void CheckExitRules( void );

/*
================
G_FindTeams
 
Chain together all entities with a matching team field.
Entity teams are used for item groups and multi-entity mover groups.
 
All but the first will have the FL_TEAMSLAVE flag set and teammaster field set
All but the last will have the teamchain field set to the next one
================
*/
void G_FindTeams( void )
{
    gentity_t    *e, *e2;
    unsigned int i, j, c, c2;

    c = 0;
    c2 = 0;
    for ( i=1, e=g_entities+i ; i < level.num_entities ; i++,e++ )
    {
        if (!e->inuse)
            continue;
        if (!e->team)
            continue;
        if (e->flags & FL_TEAMSLAVE)
            continue;
        e->teammaster = e;
        c++;
        c2++;
        for (j=i+1, e2=e+1 ; j < level.num_entities ; j++,e2++)
        {
            if (!e2->inuse)
                continue;
            if (!e2->team)
                continue;
            if (e2->flags & FL_TEAMSLAVE)
                continue;
            if (!strcmp(e->team, e2->team))
            {
                c2++;
                e2->teamchain = e->teamchain;
                e->teamchain = e2;
                e2->teammaster = e;
                e2->flags |= FL_TEAMSLAVE;

                // make sure that targets only point at the master
                if ( e2->targetname )
                {
                    e->targetname = e2->targetname;
                    e2->targetname = NULL;
                }
            }
        }
    }

    Com_Printf ("%i teams with %i entities\n", c, c2);
}

void G_RemapTeamShaders(void)
{
}


/*
=================
G_RegisterCvars
=================
*/
void G_RegisterCvars( void )
{
    int			i;
    cvarTable_t	*cv;
    qboolean remapped = qfalse;

    for ( i = 0, cv = gameCvarTable ; i < gameCvarTableSize ; i++, cv++ )
    {
        if(cv->cvar)
            *cv->cvar = Cvar_Get(cv->name, cv->defaultString, cv->flags);
        else
            Cvar_Get(cv->name, cv->defaultString, cv->flags);

        if (cv->teamShader)
            remapped = qtrue;
    }

    if (remapped)
        G_RemapTeamShaders();

    // check some things
    if ( g_gametype->integer < 0 || g_gametype->integer >= GT_MAX_GAME_TYPE )
    {
        Com_Printf( "g_gametype %i is out of range, defaulting to 0\n", g_gametype->integer );
        Cvar_Set( "g_gametype", "0" );
    }

    level.warmupModificationCount = g_warmup->modificationCount;
}

/*
=================
G_UpdateCvars
=================
*/
void G_UpdateCvars( void )
{
    int			i;
    cvarTable_t	*cv;
    qboolean remapped = qfalse;
    cvar_t *cvar;

    for ( i = 0, cv = gameCvarTable ; i < gameCvarTableSize ; i++, cv++ )
    {
        if ( cv->cvar )
        {
            cvar = cv->cvar[0];
            if ( cv->modificationCount != cvar->modificationCount )
            {
                cv->modificationCount = cvar->modificationCount;

                if ( cv->trackChange )
                {
                    SV_GameSendServerCommand( -1, va("print \"Server: %s changed to %s\n\"",
                                                     cv->name, cvar->string ) );
                }

                if (cv->teamShader)
                {
                    remapped = qtrue;
                }
            }
        }
    }

    if (remapped)
    {
        G_RemapTeamShaders();
    }
}

/*
============
G_InitGame
 
============
*/
void G_InitGame( int levelTime, int randomSeed, int restart )
{
    unsigned int i;

    Com_Printf ("------- Game Initialization -------\n");
    Com_Printf ("gamename: %s\n", GAMEVERSION);
    Com_Printf ("gamedate: %s\n", __DATE__);

    srand( randomSeed );

    G_RegisterCvars();

    G_ProcessIPBans();

    G_InitMemory();

    // set some level globals
    memset( &level, 0, sizeof( level ) );
    level.time = levelTime;
    level.startTime = levelTime;

    level.snd_fry = G_SoundIndex("sound/player/fry.wav");	// FIXME standing in lava / slime

    if ( g_gametype->integer != GT_SINGLE_PLAYER && g_log->string[0] )
    {
        if ( g_logSync->integer )
        {
            FS_FOpenFileByMode( g_log->string, &level.logFile, FS_APPEND_SYNC );
        }
        else
        {
            FS_FOpenFileByMode( g_log->string, &level.logFile, FS_APPEND );
        }
        if ( !level.logFile )
        {
            Com_Printf( "WARNING: Couldn't open logfile: %s\n", g_log->string );
        }
        else
        {
            char	serverinfo[MAX_INFO_STRING];

            SV_GetServerinfo( serverinfo, sizeof( serverinfo ) );

            G_LogPrintf("------------------------------------------------------------\n" );
            G_LogPrintf("InitGame: %s\n", serverinfo );
        }
    }
    else
    {
        Com_Printf( "Not logging to disk.\n" );
    }

    G_InitWorldSession();

    // initialize all entities for this game
    memset( g_entities, 0, MAX_GENTITIES * sizeof(g_entities[0]) );
    level.gentities = g_entities;

    // initialize all clients for this game
    level.maxclients = g_maxclients->integer;
    memset( g_clients, 0, MAX_CLIENTS * sizeof(g_clients[0]) );
    level.clients = g_clients;

    // set client fields on player ents
    for ( i=0 ; i<level.maxclients ; i++ )
        g_entities[i].client = level.clients + i;

    // always leave room for the max number of clients,
    // even if they aren't all used, so numbers inside that
    // range are NEVER anything but clients
    level.num_entities = MAX_CLIENTS;

    // let the server system know where the entites are
    SV_LocateGameData(level.gentities, level.num_entities, &level.clients[0].ps, sizeof(level.clients[0]));

    // reserve some spots for dead player bodies
    InitBodyQue();

    ClearRegisteredItems();

    // parse the key/value pairs and spawn gentities
    G_SpawnEntitiesFromString();

    // general initialization
    G_FindTeams();

    // make sure we have flags for CTF, etc
    if( g_gametype->integer >= GT_TEAM )
    {
        G_CheckTeamItems();
    }

    SaveRegisteredItems();

    Com_Printf ("-----------------------------------\n");

    if( g_gametype->integer == GT_SINGLE_PLAYER || Cvar_VariableIntegerValue( "com_buildScript" ) )
    {
        G_ModelIndex( SP_PODIUM_MODEL );
        G_SoundIndex( "sound/player/gurp1.wav" );
        G_SoundIndex( "sound/player/gurp2.wav" );
    }

    if ( Cvar_VariableIntegerValue( "bot_enable" ) )
    {
        BotAISetup( restart );
        BotAILoadMap( restart );
        G_InitBots( restart );
    }

    G_RemapTeamShaders();

}



/*
=================
G_ShutdownGame
=================
*/
void G_ShutdownGame( int restart )
{
    Com_Printf ("==== ShutdownGame ====\n");

    if ( level.logFile )
    {
        G_LogPrintf("ShutdownGame:\n" );
        G_LogPrintf("------------------------------------------------------------\n" );
        FS_FCloseFile( level.logFile );
    }

    // write all the client session data so we can get it back
    G_WriteSessionData();

    if ( Cvar_VariableIntegerValue( "bot_enable" ) )
    {
        BotAIShutdown( restart );
    }
}

/*
========================================================================
 
PLAYER COUNTING / SCORE SORTING
 
========================================================================
*/

/*
=============
AddTournamentPlayer
 
If there are less than two tournament players, put a
spectator in the game and restart
=============
*/
void AddTournamentPlayer( void )
{
    unsigned int    i;
    gclient_t       *client;
    gclient_t       *nextInLine;

    if ( level.numPlayingClients >= 2 )
        return;

    // never change during intermission
    if ( level.intermissiontime )
        return;

    nextInLine = NULL;

    for ( i = 0 ; i < level.maxclients ; i++ )
    {
        client = &level.clients[i];
        if ( client->pers.connected != CON_CONNECTED )
            continue;
        if ( client->sess.sessionTeam != TEAM_SPECTATOR )
            continue;

        // never select the dedicated follow or scoreboard clients
        if ( client->sess.spectatorState == SPECTATOR_SCOREBOARD || client->sess.spectatorClient < 0  )
            continue;

        if ( !nextInLine || client->sess.spectatorTime < nextInLine->sess.spectatorTime )
            nextInLine = client;
    }

    if ( !nextInLine )
        return;

    level.warmupTime = -1;

    // set them to free-for-all team
    SetTeam( &g_entities[ nextInLine - level.clients ], "f" );
}

/*
=======================
RemoveTournamentLoser
 
Make the loser a spectator at the back of the line
=======================
*/
void RemoveTournamentLoser( void )
{
    int			clientNum;

    if ( level.numPlayingClients != 2 )
    {
        return;
    }

    clientNum = level.sortedClients[1];

    if ( level.clients[ clientNum ].pers.connected != CON_CONNECTED )
    {
        return;
    }

    // make them a spectator
    SetTeam( &g_entities[ clientNum ], "s" );
}

/*
=======================
RemoveTournamentWinner
=======================
*/
void RemoveTournamentWinner( void )
{
    int			clientNum;

    if ( level.numPlayingClients != 2 )
    {
        return;
    }

    clientNum = level.sortedClients[0];

    if ( level.clients[ clientNum ].pers.connected != CON_CONNECTED )
    {
        return;
    }

    // make them a spectator
    SetTeam( &g_entities[ clientNum ], "s" );
}

/*
=======================
AdjustTournamentScores
=======================
*/
void AdjustTournamentScores( void )
{
    int			clientNum;

    clientNum = level.sortedClients[0];
    if ( level.clients[ clientNum ].pers.connected == CON_CONNECTED )
    {
        level.clients[ clientNum ].sess.wins++;
        ClientUserinfoChanged( clientNum );
    }

    clientNum = level.sortedClients[1];
    if ( level.clients[ clientNum ].pers.connected == CON_CONNECTED )
    {
        level.clients[ clientNum ].sess.losses++;
        ClientUserinfoChanged( clientNum );
    }

}

/*
=============
SortRanks
 
=============
*/
int QDECL SortRanks( const void *a, const void *b )
{
    gclient_t	*ca, *cb;

    ca = &level.clients[*(int *)a];
    cb = &level.clients[*(int *)b];

    // sort special clients last
    if ( ca->sess.spectatorState == SPECTATOR_SCOREBOARD || ca->sess.spectatorClient < 0 )
    {
        return 1;
    }
    if ( cb->sess.spectatorState == SPECTATOR_SCOREBOARD || cb->sess.spectatorClient < 0  )
    {
        return -1;
    }

    // then connecting clients
    if ( ca->pers.connected == CON_CONNECTING )
    {
        return 1;
    }
    if ( cb->pers.connected == CON_CONNECTING )
    {
        return -1;
    }


    // then spectators
    if ( ca->sess.sessionTeam == TEAM_SPECTATOR && cb->sess.sessionTeam == TEAM_SPECTATOR )
    {
        if ( ca->sess.spectatorTime < cb->sess.spectatorTime )
        {
            return -1;
        }
        if ( ca->sess.spectatorTime > cb->sess.spectatorTime )
        {
            return 1;
        }
        return 0;
    }
    if ( ca->sess.sessionTeam == TEAM_SPECTATOR )
    {
        return 1;
    }
    if ( cb->sess.sessionTeam == TEAM_SPECTATOR )
    {
        return -1;
    }

    // then sort by score
    if ( ca->ps.persistant[PERS_SCORE]
            > cb->ps.persistant[PERS_SCORE] )
    {
        return -1;
    }
    if ( ca->ps.persistant[PERS_SCORE]
            < cb->ps.persistant[PERS_SCORE] )
    {
        return 1;
    }
    return 0;
}

/*
============
CalculateRanks
 
Recalculates the score ranks of all players
This will be called on every client connect, begin, disconnect, death,
and team change.
============
*/
void CalculateRanks( void )
{
    unsigned int    i;
    int		        rank, score, newScore;
    gclient_t       *cl;

    level.follow1 = MAX_CLIENTS;
    level.follow2 = MAX_CLIENTS;
    level.numConnectedClients = 0;
    level.numNonSpectatorClients = 0;
    level.numPlayingClients = 0;
    level.numVotingClients = 0;		// don't count bots
    for ( i = 0; i < TEAM_NUM_TEAMS; i++ )
        level.numteamVotingClients[i] = 0;

    for ( i = 0 ; i < level.maxclients ; i++ )
    {
        if ( level.clients[i].pers.connected != CON_DISCONNECTED )
        {
            level.sortedClients[level.numConnectedClients] = i;
            level.numConnectedClients++;

            if ( level.clients[i].sess.sessionTeam != TEAM_SPECTATOR )
            {
                level.numNonSpectatorClients++;

                // decide if this should be auto-followed
                if ( level.clients[i].pers.connected == CON_CONNECTED )
                {
                    level.numPlayingClients++;
                    if ( !(g_entities[i].r.svFlags & SVF_BOT) )
                    {
                        level.numVotingClients++;
                        if ( level.clients[i].sess.sessionTeam == TEAM_RED )
                            level.numteamVotingClients[0]++;
                        else if ( level.clients[i].sess.sessionTeam == TEAM_BLUE )
                            level.numteamVotingClients[1]++;
                    }

                    if ( level.follow1 == MAX_CLIENTS )
                        level.follow1 = i;
                    else if ( level.follow2 == MAX_CLIENTS )
                        level.follow2 = i;
                }
            }
        }
    }

    qsort( level.sortedClients, level.numConnectedClients,
           sizeof(level.sortedClients[0]), SortRanks );

    // set the rank value for all clients that are connected and not spectators
    if ( g_gametype->integer >= GT_TEAM )
    {
        // in team games, rank is just the order of the teams, 0=red, 1=blue, 2=tied
        for ( i = 0;  i < level.numConnectedClients; i++ )
        {
            cl = &level.clients[ level.sortedClients[i] ];
            if ( level.teamScores[TEAM_RED] == level.teamScores[TEAM_BLUE] )
            {
                cl->ps.persistant[PERS_RANK] = 2;
            }
            else if ( level.teamScores[TEAM_RED] > level.teamScores[TEAM_BLUE] )
            {
                cl->ps.persistant[PERS_RANK] = 0;
            }
            else
            {
                cl->ps.persistant[PERS_RANK] = 1;
            }
        }
    }
    else
    {
        rank = -1;
        score = 0;
        for ( i = 0;  i < level.numPlayingClients; i++ )
        {
            cl = &level.clients[ level.sortedClients[i] ];
            newScore = cl->ps.persistant[PERS_SCORE];
            if ( i == 0 || newScore != score )
            {
                rank = i;
                // assume we aren't tied until the next client is checked
                level.clients[ level.sortedClients[i] ].ps.persistant[PERS_RANK] = rank;
            }
            else
            {
                // we are tied with the previous client
                level.clients[ level.sortedClients[i-1] ].ps.persistant[PERS_RANK] = rank | RANK_TIED_FLAG;
                level.clients[ level.sortedClients[i] ].ps.persistant[PERS_RANK] = rank | RANK_TIED_FLAG;
            }
            score = newScore;
            if ( g_gametype->integer == GT_SINGLE_PLAYER && level.numPlayingClients == 1 )
            {
                level.clients[ level.sortedClients[i] ].ps.persistant[PERS_RANK] = rank | RANK_TIED_FLAG;
            }
        }
    }

    // set the CS_SCORES1/2 configstrings, which will be visible to everyone
    if ( g_gametype->integer >= GT_TEAM )
    {
        SV_SetConfigstring( CS_SCORES1, va("%i", level.teamScores[TEAM_RED] ) );
        SV_SetConfigstring( CS_SCORES2, va("%i", level.teamScores[TEAM_BLUE] ) );
    }
    else
    {
        if ( level.numConnectedClients == 0 )
        {
            SV_SetConfigstring( CS_SCORES1, va("%i", SCORE_NOT_PRESENT) );
            SV_SetConfigstring( CS_SCORES2, va("%i", SCORE_NOT_PRESENT) );
        }
        else if ( level.numConnectedClients == 1 )
        {
            SV_SetConfigstring( CS_SCORES1, va("%i", level.clients[ level.sortedClients[0] ].ps.persistant[PERS_SCORE] ) );
            SV_SetConfigstring( CS_SCORES2, va("%i", SCORE_NOT_PRESENT) );
        }
        else
        {
            SV_SetConfigstring( CS_SCORES1, va("%i", level.clients[ level.sortedClients[0] ].ps.persistant[PERS_SCORE] ) );
            SV_SetConfigstring( CS_SCORES2, va("%i", level.clients[ level.sortedClients[1] ].ps.persistant[PERS_SCORE] ) );
        }
    }

    // see if it is time to end the level
    CheckExitRules();

    // if we are at the intermission, send the new info to everyone
    if ( level.intermissiontime )
    {
        SendScoreboardMessageToAllClients();
    }
}


/*
========================================================================
 
MAP CHANGING
 
========================================================================
*/

/*
========================
SendScoreboardMessageToAllClients
 
Do this at BeginIntermission time and whenever ranks are recalculated
due to enters/exits/forced team changes
========================
*/
void SendScoreboardMessageToAllClients( void )
{
    unsigned int i;

    for ( i = 0 ; i < level.maxclients ; i++ )
        if ( level.clients[ i ].pers.connected == CON_CONNECTED )
            DeathmatchScoreboardMessage( g_entities + i );
}

/*
========================
MoveClientToIntermission
 
When the intermission starts, this will be called for all players.
If a new client connects, this will be called after the spawn function.
========================
*/
void MoveClientToIntermission( gentity_t *ent )
{
    // take out of follow mode if needed
    if ( ent->client->sess.spectatorState == SPECTATOR_FOLLOW )
    {
        StopFollowing( ent );
    }


    // move to the spot
    VectorCopy( level.intermission_origin, ent->s.origin );
    VectorCopy( level.intermission_origin, ent->client->ps.origin );
    VectorCopy (level.intermission_angle, ent->client->ps.viewangles);
    ent->client->ps.pm_type = PM_INTERMISSION;

    // clean up powerup info
    memset( ent->client->ps.powerups, 0, sizeof(ent->client->ps.powerups) );

    ent->client->ps.eFlags = 0;
    ent->s.eFlags = 0;
    ent->s.eType = ET_GENERAL;
    ent->s.modelindex = 0;
    ent->s.loopSound = 0;
    ent->s.event = 0;
    ent->r.contents = 0;
}

/*
==================
FindIntermissionPoint
 
This is also used for spectator spawns
==================
*/
void FindIntermissionPoint( void )
{
    gentity_t	*ent, *target;
    vec3_t		dir;

    // find the intermission spot
    ent = G_Find (NULL, FOFS(classname), "info_player_intermission");
    if ( !ent )
    {	// the map creator forgot to put in an intermission point...
        SelectSpawnPoint ( vec3_origin, level.intermission_origin, level.intermission_angle );
    }
    else
    {
        VectorCopy (ent->s.origin, level.intermission_origin);
        VectorCopy (ent->s.angles, level.intermission_angle);
        // if it has a target, look towards it
        if ( ent->target )
        {
            target = G_PickTarget( ent->target );
            if ( target )
            {
                VectorSubtract( target->s.origin, level.intermission_origin, dir );
                vectoangles( dir, level.intermission_angle );
            }
        }
    }

}

/*
==================
BeginIntermission
==================
*/
void BeginIntermission( void )
{
    unsigned int i;
    gentity_t    *client;

    if ( level.intermissiontime )
        return;		// already active

    // if in tournement mode, change the wins / losses
    if ( g_gametype->integer == GT_TOURNAMENT )
        AdjustTournamentScores();

    level.intermissiontime = level.time;
    FindIntermissionPoint();

    // if single player game
    if ( g_gametype->integer == GT_SINGLE_PLAYER )
    {
        UpdateTournamentInfo();
        SpawnModelsOnVictoryPads();
    }

    // move all clients to the intermission point
    for (i=0 ; i< level.maxclients ; i++)
    {
        client = g_entities + i;
        if (!client->inuse)
            continue;

        // respawn if dead
        if (client->health < 0)
            respawn(client);
        MoveClientToIntermission( client );
    }

    // send the current scoring to all clients
    SendScoreboardMessageToAllClients();
}


/*
=============
ExitLevel
 
When the intermission has been exited, the server is either killed
or moved to a new level based on the "nextmap" cvar 
 
=============
*/
void ExitLevel (void)
{
    int		i;
    gclient_t *cl;

    //bot interbreeding
    BotInterbreedEndMatch();

    // if we are running a tournement map, kick the loser to spectator status,
    // which will automatically grab the next spectator and restart
    if ( g_gametype->integer == GT_TOURNAMENT  )
    {
        if ( !level.restarted )
        {
            RemoveTournamentLoser();
            Cbuf_ExecuteText( EXEC_APPEND, "map_restart 0\n" );
            level.restarted = qtrue;
            level.changemap = NULL;
            level.intermissiontime = 0;
        }
        return;
    }


    Cbuf_ExecuteText( EXEC_APPEND, "vstr nextmap\n" );
    level.changemap = NULL;
    level.intermissiontime = 0;

    // reset all the scores so we don't enter the intermission again
    level.teamScores[TEAM_RED] = 0;
    level.teamScores[TEAM_BLUE] = 0;
    for ( i=0 ; i< g_maxclients->integer ; i++ )
    {
        cl = level.clients + i;
        if ( cl->pers.connected != CON_CONNECTED )
        {
            continue;
        }
        cl->ps.persistant[PERS_SCORE] = 0;
    }

    // we need to do this here before chaning to CON_CONNECTING
    G_WriteSessionData();

    // change all client states to connecting, so the early players into the
    // next level will know the others aren't done reconnecting
    for (i=0 ; i< g_maxclients->integer ; i++)
    {
        if ( level.clients[i].pers.connected == CON_CONNECTED )
        {
            level.clients[i].pers.connected = CON_CONNECTING;
        }
    }

}

/*
=================
G_LogPrintf
 
Print to the logfile with a time stamp if it is open
=================
*/
void QDECL G_LogPrintf( const char *fmt, ... )
{
    va_list		argptr;
    char		string[1024];
    int			min, tens, sec;

    sec = level.time / 1000;

    min = sec / 60;
    sec -= min * 60;
    tens = sec / 10;
    sec -= tens * 10;

    Com_sprintf( string, sizeof(string), "%3i:%i%i ", min, tens, sec );

    va_start( argptr, fmt );
    vsprintf( string +7 , fmt,argptr );
    va_end( argptr );

    if ( g_dedicated->integer )
    {
        Com_Printf( "%s", string + 7 );
    }

    if ( !level.logFile )
    {
        return;
    }

    FS_Write( string, strlen( string ), level.logFile );
}

/*
================
LogExit
 
Append information about this game to the log file
================
*/
void LogExit( const char *string )
{
    int				i, numSorted;
    gclient_t		*cl;
    G_LogPrintf( "Exit: %s\n", string );

    level.intermissionQueued = level.time;

    // this will keep the clients from playing any voice sounds
    // that will get cut off when the queued intermission starts
    SV_SetConfigstring( CS_INTERMISSION, "1" );

    // don't send more than 32 scores (FIXME?)
    numSorted = level.numConnectedClients;
    if ( numSorted > 32 )
    {
        numSorted = 32;
    }

    if ( g_gametype->integer >= GT_TEAM )
    {
        G_LogPrintf( "red:%i  blue:%i\n",
                     level.teamScores[TEAM_RED], level.teamScores[TEAM_BLUE] );
    }

    for (i=0 ; i < numSorted ; i++)
    {
        int		ping;

        cl = &level.clients[level.sortedClients[i]];

        if ( cl->sess.sessionTeam == TEAM_SPECTATOR )
        {
            continue;
        }
        if ( cl->pers.connected == CON_CONNECTING )
        {
            continue;
        }

        ping = cl->ps.ping < 999 ? cl->ps.ping : 999;

        G_LogPrintf( "score: %i  ping: %i  client: %i %s\n", cl->ps.persistant[PERS_SCORE], ping, level.sortedClients[i],	cl->pers.netname );

    }
}


/*
=================
CheckIntermissionExit
 
The level will stay at the intermission for a minimum of 5 seconds
If all players wish to continue, the level will then exit.
If one or more players have not acknowledged the continue, the game will
wait 10 seconds before going on.
=================
*/
void CheckIntermissionExit( void )
{
    int			ready, notReady;
    int			i;
    gclient_t	*cl;
    int			readyMask;

    if ( g_gametype->integer == GT_SINGLE_PLAYER )
    {
        return;
    }

    // see which players are ready
    ready = 0;
    notReady = 0;
    readyMask = 0;
    for (i=0 ; i< g_maxclients->integer ; i++)
    {
        cl = level.clients + i;
        if ( cl->pers.connected != CON_CONNECTED )
        {
            continue;
        }
        if ( g_entities[cl->ps.clientNum].r.svFlags & SVF_BOT )
        {
            continue;
        }

        if ( cl->readyToExit )
        {
            ready++;
            if ( i < 16 )
            {
                readyMask |= 1 << i;
            }
        }
        else
        {
            notReady++;
        }
    }

    // copy the readyMask to each player's stats so
    // it can be displayed on the scoreboard
    for (i=0 ; i< g_maxclients->integer ; i++)
    {
        cl = level.clients + i;
        if ( cl->pers.connected != CON_CONNECTED )
        {
            continue;
        }
        cl->ps.stats[STAT_CLIENTS_READY] = readyMask;
    }

    // never exit in less than five seconds
    if ( level.time < level.intermissiontime + 5000 )
    {
        return;
    }

    // if nobody wants to go, clear timer
    if ( !ready )
    {
        level.readyToExit = qfalse;
        return;
    }

    // if everyone wants to go, go now
    if ( !notReady )
    {
        ExitLevel();
        return;
    }

    // the first person to ready starts the ten second timeout
    if ( !level.readyToExit )
    {
        level.readyToExit = qtrue;
        level.exitTime = level.time;
    }

    // if we have waited ten seconds since at least one player
    // wanted to exit, go ahead
    if ( level.time < level.exitTime + 10000 )
    {
        return;
    }

    ExitLevel();
}

/*
=============
ScoreIsTied
=============
*/
qboolean ScoreIsTied( void )
{
    int		a, b;

    if ( level.numPlayingClients < 2 )
    {
        return qfalse;
    }

    if ( g_gametype->integer >= GT_TEAM )
    {
        return level.teamScores[TEAM_RED] == level.teamScores[TEAM_BLUE];
    }

    a = level.clients[level.sortedClients[0]].ps.persistant[PERS_SCORE];
    b = level.clients[level.sortedClients[1]].ps.persistant[PERS_SCORE];

    return a == b;
}

/*
=================
CheckExitRules
 
There will be a delay between the time the exit is qualified for
and the time everyone is moved to the intermission spot, so you
can see the last frag.
=================
*/
void CheckExitRules( void )
{
    int			i;
    gclient_t	*cl;
    // if at the intermission, wait for all non-bots to
    // signal ready, then go to next level
    if ( level.intermissiontime )
    {
        CheckIntermissionExit ();
        return;
    }

    if ( level.intermissionQueued )
    {
        if ( level.time - level.intermissionQueued >= INTERMISSION_DELAY_TIME )
        {
            level.intermissionQueued = 0;
            BeginIntermission();
        }
        return;
    }

    // check for sudden death
    if ( ScoreIsTied() )
    {
        // always wait for sudden death
        return;
    }

    if ( g_timelimit->integer && !level.warmupTime )
    {
        if ( level.time - level.startTime >= g_timelimit->integer*60000 )
        {
            SV_GameSendServerCommand( -1, "print \"Timelimit hit.\n\"");
            LogExit( "Timelimit hit." );
            return;
        }
    }

    if ( level.numPlayingClients < 2 )
    {
        return;
    }

    if ( g_gametype->integer < GT_CTF && g_fraglimit->integer )
    {
        if ( level.teamScores[TEAM_RED] >= g_fraglimit->integer )
        {
            SV_GameSendServerCommand( -1, "print \"Red hit the fraglimit.\n\"" );
            LogExit( "Fraglimit hit." );
            return;
        }

        if ( level.teamScores[TEAM_BLUE] >= g_fraglimit->integer )
        {
            SV_GameSendServerCommand( -1, "print \"Blue hit the fraglimit.\n\"" );
            LogExit( "Fraglimit hit." );
            return;
        }

        for ( i=0 ; i< g_maxclients->integer ; i++ )
        {
            cl = level.clients + i;
            if ( cl->pers.connected != CON_CONNECTED )
            {
                continue;
            }
            if ( cl->sess.sessionTeam != TEAM_FREE )
            {
                continue;
            }

            if ( cl->ps.persistant[PERS_SCORE] >= g_fraglimit->integer )
            {
                LogExit( "Fraglimit hit." );
                SV_GameSendServerCommand( -1, va("print \"%s" S_COLOR_WHITE " hit the fraglimit.\n\"",
                                                 cl->pers.netname ) );
                return;
            }
        }
    }

    if ( g_gametype->integer >= GT_CTF && g_capturelimit->integer )
    {

        if ( level.teamScores[TEAM_RED] >= g_capturelimit->integer )
        {
            SV_GameSendServerCommand( -1, "print \"Red hit the capturelimit.\n\"" );
            LogExit( "Capturelimit hit." );
            return;
        }

        if ( level.teamScores[TEAM_BLUE] >= g_capturelimit->integer )
        {
            SV_GameSendServerCommand( -1, "print \"Blue hit the capturelimit.\n\"" );
            LogExit( "Capturelimit hit." );
            return;
        }
    }
}



/*
========================================================================
 
FUNCTIONS CALLED EVERY FRAME
 
========================================================================
*/


/*
=============
CheckTournament
 
Once a frame, check for changes in tournement player state
=============
*/
void CheckTournament( void )
{
    // check because we run 3 game frames before calling Connect and/or ClientBegin
    // for clients on a map_restart
    if ( level.numPlayingClients == 0 )
    {
        return;
    }

    if ( g_gametype->integer == GT_TOURNAMENT )
    {

        // pull in a spectator if needed
        if ( level.numPlayingClients < 2 )
        {
            AddTournamentPlayer();
        }

        // if we don't have two players, go back to "waiting for players"
        if ( level.numPlayingClients != 2 )
        {
            if ( level.warmupTime != -1 )
            {
                level.warmupTime = -1;
                SV_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
                G_LogPrintf( "Warmup:\n" );
            }
            return;
        }

        if ( level.warmupTime == 0 )
        {
            return;
        }

        // if the warmup is changed at the console, restart it
        if ( g_warmup->modificationCount != level.warmupModificationCount )
        {
            level.warmupModificationCount = g_warmup->modificationCount;
            level.warmupTime = -1;
        }

        // if all players have arrived, start the countdown
        if ( level.warmupTime < 0 )
        {
            if ( level.numPlayingClients == 2 )
            {
                // fudge by -1 to account for extra delays
                level.warmupTime = level.time + ( g_warmup->integer - 1 ) * 1000;
                SV_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
            }
            return;
        }

        // if the warmup time has counted down, restart
        if ( level.time > level.warmupTime )
        {
            level.warmupTime += 10000;
            Cvar_Set( "g_restarted", "1" );
            Cbuf_ExecuteText( EXEC_APPEND, "map_restart 0\n" );
            level.restarted = qtrue;
            return;
        }
    }
    else if ( g_gametype->integer != GT_SINGLE_PLAYER && level.warmupTime != 0 )
    {
        int		counts[TEAM_NUM_TEAMS];
        qboolean	notEnough = qfalse;

        if ( g_gametype->integer > GT_TEAM )
        {
            counts[TEAM_BLUE] = TeamCount(level.maxclients, TEAM_BLUE );
            counts[TEAM_RED] = TeamCount(level.maxclients, TEAM_RED );

            if (counts[TEAM_RED] < 1 || counts[TEAM_BLUE] < 1)
            {
                notEnough = qtrue;
            }
        }
        else if ( level.numPlayingClients < 2 )
        {
            notEnough = qtrue;
        }

        if ( notEnough )
        {
            if ( level.warmupTime != -1 )
            {
                level.warmupTime = -1;
                SV_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
                G_LogPrintf( "Warmup:\n" );
            }
            return; // still waiting for team members
        }

        if ( level.warmupTime == 0 )
        {
            return;
        }

        // if the warmup is changed at the console, restart it
        if ( g_warmup->modificationCount != level.warmupModificationCount )
        {
            level.warmupModificationCount = g_warmup->modificationCount;
            level.warmupTime = -1;
        }

        // if all players have arrived, start the countdown
        if ( level.warmupTime < 0 )
        {
            // fudge by -1 to account for extra delays
            level.warmupTime = level.time + ( g_warmup->integer - 1 ) * 1000;
            SV_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
            return;
        }

        // if the warmup time has counted down, restart
        if ( level.time > level.warmupTime )
        {
            level.warmupTime += 10000;
            Cvar_Set( "g_restarted", "1" );
            Cbuf_ExecuteText( EXEC_APPEND, "map_restart 0\n" );
            level.restarted = qtrue;
            return;
        }
    }
}


/*
==================
CheckVote
==================
*/
void CheckVote( void )
{
    if ( level.voteExecuteTime && level.voteExecuteTime < level.time )
    {
        level.voteExecuteTime = 0;
        Cbuf_ExecuteText( EXEC_APPEND, va("%s\n", level.voteString ) );
    }
    if ( !level.voteTime )
    {
        return;
    }
    if ( level.time - level.voteTime >= VOTE_TIME )
    {
        SV_GameSendServerCommand( -1, "print \"Vote failed.\n\"" );
    }
    else
    {
        // ATVI Q3 1.32 Patch #9, WNF
        if ( level.voteYes > level.numVotingClients/2 )
        {
            // execute the command, then remove the vote
            SV_GameSendServerCommand( -1, "print \"Vote passed.\n\"" );
            level.voteExecuteTime = level.time + 3000;
        }
        else if ( level.voteNo >= level.numVotingClients/2 )
        {
            // same behavior as a timeout
            SV_GameSendServerCommand( -1, "print \"Vote failed.\n\"" );
        }
        else
        {
            // still waiting for a majority
            return;
        }
    }
    level.voteTime = 0;
    SV_SetConfigstring( CS_VOTE_TIME, "" );

}

/*
==================
PrintTeam
==================
*/
void PrintTeam(int team, char *message)
{
    unsigned int i;

    for ( i = 0 ; i < level.maxclients ; i++ )
    {
        if (level.clients[i].sess.sessionTeam != team)
            continue;
        SV_GameSendServerCommand( i, message );
    }
}

/*
==================
SetLeader
==================
*/
void SetLeader(int team, int client)
{
    unsigned int i;

    if ( level.clients[client].pers.connected == CON_DISCONNECTED )
    {
        PrintTeam(team, va("print \"%s is not connected\n\"", level.clients[client].pers.netname) );
        return;
    }
    if (level.clients[client].sess.sessionTeam != team)
    {
        PrintTeam(team, va("print \"%s is not on the team anymore\n\"", level.clients[client].pers.netname) );
        return;
    }
    for ( i = 0 ; i < level.maxclients ; i++ )
    {
        if (level.clients[i].sess.sessionTeam != team)
            continue;
        if (level.clients[i].sess.teamLeader)
        {
            level.clients[i].sess.teamLeader = qfalse;
            ClientUserinfoChanged(i);
        }
    }
    level.clients[client].sess.teamLeader = qtrue;
    ClientUserinfoChanged( client );
    PrintTeam(team, va("print \"%s is the new team leader\n\"", level.clients[client].pers.netname) );
}

/*
==================
CheckTeamLeader
==================
*/
void CheckTeamLeader( int team )
{
    unsigned int i;

    for ( i = 0 ; i < level.maxclients ; i++ )
    {
        if (level.clients[i].sess.sessionTeam != team)
            continue;
        if (level.clients[i].sess.teamLeader)
            break;
    }
    if (i >= level.maxclients)
    {
        for ( i = 0 ; i < level.maxclients ; i++ )
        {
            if (level.clients[i].sess.sessionTeam != team)
                continue;
            if (!(g_entities[i].r.svFlags & SVF_BOT))
            {
                level.clients[i].sess.teamLeader = qtrue;
                break;
            }
        }
        for ( i = 0 ; i < level.maxclients ; i++ )
        {
            if (level.clients[i].sess.sessionTeam != team)
                continue;
            level.clients[i].sess.teamLeader = qtrue;
            break;
        }
    }
}

/*
==================
CheckTeamVote
==================
*/
void CheckTeamVote( int team )
{
    int cs_offset;

    if ( team == TEAM_RED )
        cs_offset = 0;
    else if ( team == TEAM_BLUE )
        cs_offset = 1;
    else
        return;

    if ( !level.teamVoteTime[cs_offset] )
    {
        return;
    }
    if ( level.time - level.teamVoteTime[cs_offset] >= VOTE_TIME )
    {
        SV_GameSendServerCommand( -1, "print \"Team vote failed.\n\"" );
    }
    else
    {
        if ( level.teamVoteYes[cs_offset] > level.numteamVotingClients[cs_offset]/2 )
        {
            // execute the command, then remove the vote
            SV_GameSendServerCommand( -1, "print \"Team vote passed.\n\"" );
            //
            if ( !Q_strncmp( "leader", level.teamVoteString[cs_offset], 6) )
            {
                //set the team leader
                SetLeader(team, atoi(level.teamVoteString[cs_offset] + 7));
            }
            else
            {
                Cbuf_ExecuteText( EXEC_APPEND, va("%s\n", level.teamVoteString[cs_offset] ) );
            }
        }
        else if ( level.teamVoteNo[cs_offset] >= level.numteamVotingClients[cs_offset]/2 )
        {
            // same behavior as a timeout
            SV_GameSendServerCommand( -1, "print \"Team vote failed.\n\"" );
        }
        else
        {
            // still waiting for a majority
            return;
        }
    }
    level.teamVoteTime[cs_offset] = 0;
    SV_SetConfigstring( CS_TEAMVOTE_TIME + cs_offset, "" );

}


/*
==================
CheckCvars
==================
*/
void CheckCvars( void )
{
    static int lastMod = -1;

    if ( g_password->modificationCount != lastMod )
    {
        lastMod = g_password->modificationCount;
        if ( *g_password->string && Q_stricmp( g_password->string, "none" ) )
        {
            Cvar_Set( "g_needpass", "1" );
        }
        else
        {
            Cvar_Set( "g_needpass", "0" );
        }
    }
}

/*
=============
G_RunThink
 
Runs thinking code for this frame if necessary
=============
*/
void G_RunThink (gentity_t *ent)
{
    float	thinktime;

    thinktime = ent->nextthink;
    if (thinktime <= 0)
    {
        return;
    }
    if (thinktime > level.time)
    {
        return;
    }

    ent->nextthink = 0;
    if (!ent->think)
    {
        Com_Error (ERR_DROP,  "NULL ent->think");
    }
    ent->think (ent);
}

/*
================
G_RunFrame
 
Advances the non-player objects in the world
================
*/
void G_RunFrame( int levelTime )
{
    unsigned int i;
    gentity_t	 *ent;
    int          msec;
    int          start, end;

    // if we are waiting for the level to restart, do nothing
    if ( level.restarted )
        return;

    level.framenum++;
    level.previousTime = level.time;
    level.time = levelTime;
    msec = level.time - level.previousTime;

    // get any cvar changes
    G_UpdateCvars();

    //
    // go through all allocated objects
    //
    start = Sys_Milliseconds();
    ent = &g_entities[0];
    for (i=0 ; i<level.num_entities ; i++, ent++)
    {
        if ( !ent->inuse )
            continue;

        // clear events that are too old
        if ( level.time - ent->eventTime > EVENT_VALID_MSEC )
        {
            if ( ent->s.event )
            {
                ent->s.event = 0;	// &= EV_EVENT_BITS;
                if ( ent->client )
                {
                    ent->client->ps.externalEvent = 0;
                    // predicted events should never be set to zero
                    //ent->client->ps.events[0] = 0;
                    //ent->client->ps.events[1] = 0;
                }
            }
            if ( ent->freeAfterEvent )
            {
                // tempEntities or dropped items completely go away after their event
                G_FreeEntity( ent );
                continue;
            }
            else if ( ent->unlinkAfterEvent )
            {
                // items that will respawn will hide themselves after their pickup event
                ent->unlinkAfterEvent = qfalse;
                SV_UnlinkEntity( ent );
            }
        }

        // temporary entities don't think
        if ( ent->freeAfterEvent )
            continue;

        if ( !ent->r.linked && ent->neverFree )
            continue;

        if ( ent->s.eType == ET_MISSILE )
        {
            G_RunMissile( ent );
            continue;
        }

        if ( ent->s.eType == ET_ITEM || ent->physicsObject )
        {
            G_RunItem( ent );
            continue;
        }

        if ( ent->s.eType == ET_MOVER )
        {
            G_RunMover( ent );
            continue;
        }

        if ( i < MAX_CLIENTS )
        {
            G_RunClient( ent );
            continue;
        }

        G_RunThink( ent );
    }
    end = Sys_Milliseconds();

    start = Sys_Milliseconds();
    // perform final fixups on the players
    ent = &g_entities[0];
    for (i=0 ; i < level.maxclients ; i++, ent++ )
        if ( ent->inuse )
            ClientEndFrame( ent );

    end = Sys_Milliseconds();

    // see if it is time to do a tournement restart
    CheckTournament();

    // see if it is time to end the level
    CheckExitRules();

    // update to team status?
    CheckTeamStatus();

    // cancel vote if timed out
    CheckVote();

    // check team votes
    CheckTeamVote( TEAM_RED );
    CheckTeamVote( TEAM_BLUE );

    // for tracking changes
    CheckCvars();

    if (g_listEntity->integer)
    {
        for (i = 0; i < MAX_GENTITIES; i++)
            Com_Printf("%4i: %s\n", i, g_entities[i].classname);
        Cvar_Set("g_listEntity", "0");
    }
}