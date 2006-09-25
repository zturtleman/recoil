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
// sv_game.c -- interface to the game dll

#include "server.h"

#include "../game/botlib.h"

botlib_export_t	*botlib_export;

qboolean gamelib_started = qfalse;

/*
===============
SV_GameSendServerCommand
 
Sends a command string to a client
===============
*/
void SV_GameSendServerCommand( int clientNum, const char *text )
{
    if ( clientNum == -1 )
        SV_SendServerCommand( NULL, "%s", text );
    else if( clientNum >= 0 && clientNum < sv_maxclients->integer )
        SV_SendServerCommand( svs.clients + clientNum, "%s", text );
}

/*
===============
SV_GameDropClient
 
Disconnects the client with a message
===============
*/
void SV_GameDropClient( int clientNum, const char *reason )
{
    if ( clientNum >= 0 && clientNum < sv_maxclients->integer )
        SV_DropClient( svs.clients + clientNum, reason );
}

/*
=================
SV_SetBrushModel
 
sets mins and maxs for inline bmodels
=================
*/
void SV_SetBrushModel( gentity_t *ent, const char *name )
{
    clipHandle_t	h;
    vec3_t			mins, maxs;

    if (!name)
    {
        Com_Error( ERR_DROP, "SV_SetBrushModel: NULL" );
    }

    if (name[0] != '*')
    {
        Com_Error( ERR_DROP, "SV_SetBrushModel: %s isn't a brush model", name );
    }


    ent->s.modelindex = atoi( name + 1 );

    h = CM_InlineModel( ent->s.modelindex );
    CM_ModelBounds( h, mins, maxs );
    VectorCopy (mins, ent->r.mins);
    VectorCopy (maxs, ent->r.maxs);
    ent->r.bmodel = qtrue;

    ent->r.contents = -1;		// we don't know exactly what is in the brushes

    SV_LinkEntity( ent );		// FIXME: remove
}



/*
=================
SV_inPVS
 
Also checks portalareas so that doors block sight
=================
*/
qboolean SV_inPVS (const vec3_t p1, const vec3_t p2)
{
    int		leafnum;
    int		cluster;
    int		area1, area2;
    byte	*mask;

    leafnum = CM_PointLeafnum (p1);
    cluster = CM_LeafCluster (leafnum);
    area1 = CM_LeafArea (leafnum);
    mask = CM_ClusterPVS (cluster);

    leafnum = CM_PointLeafnum (p2);
    cluster = CM_LeafCluster (leafnum);
    area2 = CM_LeafArea (leafnum);
    if ( mask && (!(mask[cluster>>3] & (1<<(cluster&7)) ) ) )
        return qfalse;
    if (!CM_AreasConnected (area1, area2))
        return qfalse;		// a door blocks sight
    return qtrue;
}


/*
=================
SV_inPVSIgnorePortals
 
Does NOT check portalareas
=================
*/
qboolean SV_inPVSIgnorePortals( const vec3_t p1, const vec3_t p2)
{
    int		leafnum;
    int		cluster;
    int		area1, area2;
    byte	*mask;

    leafnum = CM_PointLeafnum (p1);
    cluster = CM_LeafCluster (leafnum);
    area1 = CM_LeafArea (leafnum);
    mask = CM_ClusterPVS (cluster);

    leafnum = CM_PointLeafnum (p2);
    cluster = CM_LeafCluster (leafnum);
    area2 = CM_LeafArea (leafnum);

    if ( mask && (!(mask[cluster>>3] & (1<<(cluster&7)) ) ) )
        return qfalse;

    return qtrue;
}


/*
========================
SV_AdjustAreaPortalState
========================
*/
void SV_AdjustAreaPortalState( gentity_t *ent, qboolean open )
{
    svEntity_t	*svEnt;

    svEnt = SV_SvEntityForGentity(ent);
    if ( svEnt->areanum2 == -1 )
    {
        return;
    }
    CM_AdjustAreaPortalState( svEnt->areanum, svEnt->areanum2, open );
}


/*
==================
SV_GameAreaEntities
==================
*/
qboolean	SV_EntityContact( vec3_t mins, vec3_t maxs, const gentity_t *gEnt, int capsule )
{
    const float	*origin, *angles;
    clipHandle_t	ch;
    trace_t			trace;

    // check for exact collision
    origin = gEnt->r.currentOrigin;
    angles = gEnt->r.currentAngles;

    ch = SV_ClipHandleForEntity( gEnt );
    CM_TransformedBoxTrace ( &trace, vec3_origin, vec3_origin, mins, maxs,
                             ch, -1, origin, angles, capsule );

    return trace.startsolid;
}


/*
===============
SV_GetServerinfo
 
===============
*/
void SV_GetServerinfo( char *buffer, int bufferSize )
{
    if ( bufferSize < 1 )
    {
        Com_Error( ERR_DROP, "SV_GetServerinfo: bufferSize == %i", bufferSize );
    }
    Q_strncpyz( buffer, Cvar_InfoString( CVAR_SERVERINFO ), bufferSize );
}

/*
===============
SV_LocateGameData
 
===============
*/
void SV_LocateGameData( gentity_t *gEnts, int numGEntities, playerState_t *clients, int sizeofGameClient )
{
    sv.gentities = gEnts;
    sv.num_entities = numGEntities;

    sv.gameClients = clients;
    sv.gameClientSize = sizeofGameClient;
}

/*
===============
SV_GetUsercmd
 
===============
*/
void SV_GetUsercmd( int clientNum, usercmd_t *cmd )
{
    if ( clientNum < 0 || clientNum >= sv_maxclients->integer )
    {
        Com_Error( ERR_DROP, "SV_GetUsercmd: bad clientNum:%i", clientNum );
    }
    *cmd = svs.clients[clientNum].lastUsercmd;
}

//==============================================

qboolean GetEntityToken(char *buffer, int buffersize)
{
    const char	*s;

    s = COM_Parse( &sv.entityParsePoint );
    Q_strncpyz(buffer, s, buffersize);
    if ( !sv.entityParsePoint && !s[0] )
    {
        return qfalse;
    }
    else
    {
        return qtrue;
    }
}

/*
===============
SV_ShutdownGameProgs
 
Called every time a map changes
===============
*/
void SV_ShutdownGameProgs( void )
{
    if ( !gamelib_started )
    {
        return;
    }
    G_ShutdownGame(qfalse);
    gamelib_started = qfalse;
}

/*
==================
SV_InitGameVM
 
Called for both a full init and a restart
==================
*/
static void SV_InitGameVM( qboolean restart )
{
    int		i;

    // start the entity parsing at the beginning
    sv.entityParsePoint = CM_EntityString();

    // clear all gentity pointers that might still be set from
    // a previous level
    // https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=522
    //   now done before GAME_INIT call
    for ( i = 0 ; i < sv_maxclients->integer ; i++ )
        svs.clients[i].gentity = NULL;

    // use the current msec count for a random seed
    // init for this gamestate
    G_InitGame(svs.time, Com_Milliseconds(), restart);
    gamelib_started = qtrue;
}



/*
===================
SV_RestartGameProgs
 
Called on a map_restart, but not on a normal map change
===================
*/
void SV_RestartGameProgs( void )
{
    if(!gamelib_started)
        return;

    G_ShutdownGame(qtrue);

    // do a restart instead of a free
    SV_InitGameVM( qtrue );
}


/*
===============
SV_InitGameProgs
 
Called on a normal map change, not on a map_restart
===============
*/
void SV_InitGameProgs( void )
{
    cvar_t	*var = Cvar_Get( "bot_enable", "1", CVAR_LATCH );
    extern int	bot_enable;

    bot_enable = (var) ? var->integer : 0;

    SV_InitGameVM( qfalse );
}

/*
====================
SV_GameCommand
 
See if the current console command is claimed by the game
====================
*/
qboolean SV_GameCommand( void )
{
    return (sv.state != SS_GAME) ? qfalse : ConsoleCommand();
}
