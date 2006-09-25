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

#include "client.h"

#include "../game/botlib.h"

extern	botlib_export_t	*botlib_export;

/*
====================
GetClientState
====================
*/
void GetClientState( uiClientState_t *state )
{
    state->connectPacketCount = clc.connectPacketCount;
    state->connState = cls.state;
    Q_strncpyz( state->servername, cls.servername, sizeof( state->servername ) );
    Q_strncpyz( state->updateInfoString, cls.updateInfoString, sizeof( state->updateInfoString ) );
    Q_strncpyz( state->messageString, clc.serverMessage, sizeof( state->messageString ) );
    state->clientNum = cl.snap.ps.clientNum;
}

/*
====================
LAN_LoadCachedServers
====================
*/
void LAN_LoadCachedServers( )
{
    int size;
    fileHandle_t fileIn;
    cls.numglobalservers = cls.nummplayerservers = cls.numfavoriteservers = 0;
    cls.numGlobalServerAddresses = 0;
    if (FS_SV_FOpenFileRead("servercache.dat", &fileIn))
    {
        FS_Read(&cls.numglobalservers, sizeof(int), fileIn);
        FS_Read(&cls.nummplayerservers, sizeof(int), fileIn);
        FS_Read(&cls.numfavoriteservers, sizeof(int), fileIn);
        FS_Read(&size, sizeof(int), fileIn);
        if (size == sizeof(cls.globalServers) + sizeof(cls.favoriteServers) + sizeof(cls.mplayerServers))
        {
            FS_Read(&cls.globalServers, sizeof(cls.globalServers), fileIn);
            FS_Read(&cls.mplayerServers, sizeof(cls.mplayerServers), fileIn);
            FS_Read(&cls.favoriteServers, sizeof(cls.favoriteServers), fileIn);
        }
        else
        {
            cls.numglobalservers = cls.nummplayerservers = cls.numfavoriteservers = 0;
            cls.numGlobalServerAddresses = 0;
        }
        FS_FCloseFile(fileIn);
    }
}

/*
====================
LAN_SaveServersToCache
====================
*/
void LAN_SaveServersToCache( )
{
    int size;
    fileHandle_t fileOut = FS_SV_FOpenFileWrite("servercache.dat");
    FS_Write(&cls.numglobalservers, sizeof(int), fileOut);
    FS_Write(&cls.nummplayerservers, sizeof(int), fileOut);
    FS_Write(&cls.numfavoriteservers, sizeof(int), fileOut);
    size = sizeof(cls.globalServers) + sizeof(cls.favoriteServers) + sizeof(cls.mplayerServers);
    FS_Write(&size, sizeof(int), fileOut);
    FS_Write(&cls.globalServers, sizeof(cls.globalServers), fileOut);
    FS_Write(&cls.mplayerServers, sizeof(cls.mplayerServers), fileOut);
    FS_Write(&cls.favoriteServers, sizeof(cls.favoriteServers), fileOut);
    FS_FCloseFile(fileOut);
}


/*
====================
LAN_ResetPings
====================
*/
void LAN_ResetPings(int source)
{
    int count,i;
    serverInfo_t *servers = NULL;
    count = 0;

    switch (source)
    {
    case AS_LOCAL :
        servers = &cls.localServers[0];
        count = MAX_OTHER_SERVERS;
        break;
    case AS_MPLAYER :
        servers = &cls.mplayerServers[0];
        count = MAX_OTHER_SERVERS;
        break;
    case AS_GLOBAL :
        servers = &cls.globalServers[0];
        count = MAX_GLOBAL_SERVERS;
        break;
    case AS_FAVORITES :
        servers = &cls.favoriteServers[0];
        count = MAX_OTHER_SERVERS;
        break;
    }
    if (servers)
    {
        for (i = 0; i < count; i++)
        {
            servers[i].ping = -1;
        }
    }
}

/*
====================
LAN_AddServer
====================
*/
int LAN_AddServer(int source, const char *name, const char *address)
{
    int max, *count, i;
    netadr_t adr;
    serverInfo_t *servers = NULL;
    max = MAX_OTHER_SERVERS;
    count = 0;

    switch (source)
    {
    case AS_LOCAL :
        count = &cls.numlocalservers;
        servers = &cls.localServers[0];
        break;
    case AS_MPLAYER :
        count = &cls.nummplayerservers;
        servers = &cls.mplayerServers[0];
        break;
    case AS_GLOBAL :
        max = MAX_GLOBAL_SERVERS;
        count = &cls.numglobalservers;
        servers = &cls.globalServers[0];
        break;
    case AS_FAVORITES :
        count = &cls.numfavoriteservers;
        servers = &cls.favoriteServers[0];
        break;
    }
    if (servers && *count < max)
    {
        NET_StringToAdr( address, &adr );
        for ( i = 0; i < *count; i++ )
        {
            if (NET_CompareAdr(servers[i].adr, adr))
            {
                break;
            }
        }
        if (i >= *count)
        {
            servers[*count].adr = adr;
            Q_strncpyz(servers[*count].hostName, name, sizeof(servers[*count].hostName));
            servers[*count].visible = qtrue;
            (*count)++;
            return 1;
        }
        return 0;
    }
    return -1;
}

/*
====================
LAN_RemoveServer
====================
*/
void LAN_RemoveServer(int source, const char *addr)
{
    int *count, i;
    serverInfo_t *servers = NULL;
    count = 0;
    switch (source)
    {
    case AS_LOCAL :
        count = &cls.numlocalservers;
        servers = &cls.localServers[0];
        break;
    case AS_MPLAYER :
        count = &cls.nummplayerservers;
        servers = &cls.mplayerServers[0];
        break;
    case AS_GLOBAL :
        count = &cls.numglobalservers;
        servers = &cls.globalServers[0];
        break;
    case AS_FAVORITES :
        count = &cls.numfavoriteservers;
        servers = &cls.favoriteServers[0];
        break;
    }
    if (servers)
    {
        netadr_t comp;
        NET_StringToAdr( addr, &comp );
        for (i = 0; i < *count; i++)
        {
            if (NET_CompareAdr( comp, servers[i].adr))
            {
                int j = i;
                while (j < *count - 1)
                {
                    Com_Memcpy(&servers[j], &servers[j+1], sizeof(servers[j]));
                    j++;
                }
                (*count)--;
                break;
            }
        }
    }
}


/*
====================
LAN_GetServerCount
====================
*/
int LAN_GetServerCount( int source )
{
    switch (source)
    {
    case AS_LOCAL :
        return cls.numlocalservers;
        break;
    case AS_MPLAYER :
        return cls.nummplayerservers;
        break;
    case AS_GLOBAL :
        return cls.numglobalservers;
        break;
    case AS_FAVORITES :
        return cls.numfavoriteservers;
        break;
    }
    return 0;
}

/*
====================
LAN_GetLocalServerAddressString
====================
*/
void LAN_GetServerAddressString( int source, int n, char *buf, int buflen )
{
    switch (source)
    {
    case AS_LOCAL :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            Q_strncpyz(buf, NET_AdrToString( cls.localServers[n].adr) , buflen );
            return;
        }
        break;
    case AS_MPLAYER :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            Q_strncpyz(buf, NET_AdrToString( cls.mplayerServers[n].adr) , buflen );
            return;
        }
        break;
    case AS_GLOBAL :
        if (n >= 0 && n < MAX_GLOBAL_SERVERS)
        {
            Q_strncpyz(buf, NET_AdrToString( cls.globalServers[n].adr) , buflen );
            return;
        }
        break;
    case AS_FAVORITES :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            Q_strncpyz(buf, NET_AdrToString( cls.favoriteServers[n].adr) , buflen );
            return;
        }
        break;
    }
    buf[0] = '\0';
}

/*
====================
LAN_GetServerInfo
====================
*/
void LAN_GetServerInfo( int source, int n, char *buf, int buflen )
{
    char info[MAX_STRING_CHARS];
    serverInfo_t *server = NULL;
    info[0] = '\0';
    switch (source)
    {
    case AS_LOCAL :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            server = &cls.localServers[n];
        }
        break;
    case AS_MPLAYER :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            server = &cls.mplayerServers[n];
        }
        break;
    case AS_GLOBAL :
        if (n >= 0 && n < MAX_GLOBAL_SERVERS)
        {
            server = &cls.globalServers[n];
        }
        break;
    case AS_FAVORITES :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            server = &cls.favoriteServers[n];
        }
        break;
    }
    if (server && buf)
    {
        buf[0] = '\0';
        Info_SetValueForKey( info, "hostname", server->hostName);
        Info_SetValueForKey( info, "mapname", server->mapName);
        Info_SetValueForKey( info, "clients", va("%i",server->clients));
        Info_SetValueForKey( info, "sv_maxclients", va("%i",server->maxClients));
        Info_SetValueForKey( info, "ping", va("%i",server->ping));
        Info_SetValueForKey( info, "minping", va("%i",server->minPing));
        Info_SetValueForKey( info, "maxping", va("%i",server->maxPing));
        Info_SetValueForKey( info, "game", server->game);
        Info_SetValueForKey( info, "gametype", va("%i",server->gameType));
        Info_SetValueForKey( info, "nettype", va("%i",server->netType));
        Info_SetValueForKey( info, "addr", NET_AdrToString(server->adr));
        Info_SetValueForKey( info, "punkbuster", va("%i", server->punkbuster));
        Q_strncpyz(buf, info, buflen);
    }
    else
    {
        if (buf)
        {
            buf[0] = '\0';
        }
    }
}

/*
====================
LAN_GetServerPing
====================
*/
int LAN_GetServerPing( int source, int n )
{
    serverInfo_t *server = NULL;
    switch (source)
    {
    case AS_LOCAL :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            server = &cls.localServers[n];
        }
        break;
    case AS_MPLAYER :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            server = &cls.mplayerServers[n];
        }
        break;
    case AS_GLOBAL :
        if (n >= 0 && n < MAX_GLOBAL_SERVERS)
        {
            server = &cls.globalServers[n];
        }
        break;
    case AS_FAVORITES :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            server = &cls.favoriteServers[n];
        }
        break;
    }
    if (server)
    {
        return server->ping;
    }
    return -1;
}

/*
====================
LAN_GetServerPtr
====================
*/
serverInfo_t *LAN_GetServerPtr( int source, int n )
{
    switch (source)
    {
    case AS_LOCAL :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            return &cls.localServers[n];
        }
        break;
    case AS_MPLAYER :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            return &cls.mplayerServers[n];
        }
        break;
    case AS_GLOBAL :
        if (n >= 0 && n < MAX_GLOBAL_SERVERS)
        {
            return &cls.globalServers[n];
        }
        break;
    case AS_FAVORITES :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            return &cls.favoriteServers[n];
        }
        break;
    }
    return NULL;
}

/*
====================
LAN_CompareServers
====================
*/
int LAN_CompareServers( int source, int sortKey, int sortDir, int s1, int s2 )
{
    int res;
    serverInfo_t *server1, *server2;

    server1 = LAN_GetServerPtr(source, s1);
    server2 = LAN_GetServerPtr(source, s2);
    if (!server1 || !server2)
    {
        return 0;
    }

    res = 0;
    switch( sortKey )
    {
    case SORT_HOST:
        res = Q_stricmp( server1->hostName, server2->hostName );
        break;

    case SORT_MAP:
        res = Q_stricmp( server1->mapName, server2->mapName );
        break;
    case SORT_CLIENTS:
        if (server1->clients < server2->clients)
        {
            res = -1;
        }
        else if (server1->clients > server2->clients)
        {
            res = 1;
        }
        else
        {
            res = 0;
        }
        break;
    case SORT_GAME:
        if (server1->gameType < server2->gameType)
        {
            res = -1;
        }
        else if (server1->gameType > server2->gameType)
        {
            res = 1;
        }
        else
        {
            res = 0;
        }
        break;
    case SORT_PING:
        if (server1->ping < server2->ping)
        {
            res = -1;
        }
        else if (server1->ping > server2->ping)
        {
            res = 1;
        }
        else
        {
            res = 0;
        }
        break;
    }

    if (sortDir)
    {
        if (res < 0)
            return 1;
        if (res > 0)
            return -1;
        return 0;
    }
    return res;
}

/*
====================
LAN_GetPingQueueCount
====================
*/
int LAN_GetPingQueueCount( void )
{
    return (CL_GetPingQueueCount());
}

/*
====================
LAN_ClearPing
====================
*/
void LAN_ClearPing( int n )
{
    CL_ClearPing( n );
}

/*
====================
LAN_GetPing
====================
*/
void LAN_GetPing( int n, char *buf, int buflen, int *pingtime )
{
    CL_GetPing( n, buf, buflen, pingtime );
}

/*
====================
LAN_GetPingInfo
====================
*/
void LAN_GetPingInfo( int n, char *buf, int buflen )
{
    CL_GetPingInfo( n, buf, buflen );
}

/*
====================
LAN_MarkServerVisible
====================
*/
void LAN_MarkServerVisible(int source, int n, qboolean visible )
{
    if (n == -1)
    {
        int count = MAX_OTHER_SERVERS;
        serverInfo_t *server = NULL;
        switch (source)
        {
        case AS_LOCAL :
            server = &cls.localServers[0];
            break;
        case AS_MPLAYER :
            server = &cls.mplayerServers[0];
            break;
        case AS_GLOBAL :
            server = &cls.globalServers[0];
            count = MAX_GLOBAL_SERVERS;
            break;
        case AS_FAVORITES :
            server = &cls.favoriteServers[0];
            break;
        }
        if (server)
        {
            for (n = 0; n < count; n++)
            {
                server[n].visible = visible;
            }
        }

    }
    else
    {
        switch (source)
        {
        case AS_LOCAL :
            if (n >= 0 && n < MAX_OTHER_SERVERS)
            {
                cls.localServers[n].visible = visible;
            }
            break;
        case AS_MPLAYER :
            if (n >= 0 && n < MAX_OTHER_SERVERS)
            {
                cls.mplayerServers[n].visible = visible;
            }
            break;
        case AS_GLOBAL :
            if (n >= 0 && n < MAX_GLOBAL_SERVERS)
            {
                cls.globalServers[n].visible = visible;
            }
            break;
        case AS_FAVORITES :
            if (n >= 0 && n < MAX_OTHER_SERVERS)
            {
                cls.favoriteServers[n].visible = visible;
            }
            break;
        }
    }
}


/*
=======================
LAN_ServerIsVisible
=======================
*/
int LAN_ServerIsVisible(int source, int n )
{
    switch (source)
    {
    case AS_LOCAL :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            return cls.localServers[n].visible;
        }
        break;
    case AS_MPLAYER :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            return cls.mplayerServers[n].visible;
        }
        break;
    case AS_GLOBAL :
        if (n >= 0 && n < MAX_GLOBAL_SERVERS)
        {
            return cls.globalServers[n].visible;
        }
        break;
    case AS_FAVORITES :
        if (n >= 0 && n < MAX_OTHER_SERVERS)
        {
            return cls.favoriteServers[n].visible;
        }
        break;
    }
    return qfalse;
}

/*
=======================
LAN_UpdateVisiblePings
=======================
*/
qboolean LAN_UpdateVisiblePings(int source )
{
    return CL_UpdateVisiblePings_f(source);
}

/*
====================
LAN_GetServerStatus
====================
*/
int LAN_GetServerStatus( char *serverAddress, char *serverStatus, int maxLen )
{
    return CL_ServerStatus( serverAddress, serverStatus, maxLen );
}

/*
====================
CL_GetClipboardData
====================
*/
void CL_GetClipboardData( char *buf, int buflen )
{
    char	*cbd;

    cbd = Sys_GetClipboardData();

    if ( !cbd )
    {
        *buf = 0;
        return;
    }

    Q_strncpyz( buf, cbd, buflen );

    Z_Free( cbd );
}

/*
====================
Key_KeynumToStringBuf
====================
*/
void Key_KeynumToStringBuf( int keynum, char *buf, int buflen )
{
    Q_strncpyz( buf, Key_KeynumToString( keynum ), buflen );
}

/*
====================
Key_GetBindingBuf
====================
*/
void Key_GetBindingBuf( int keynum, char *buf, int buflen )
{
    char	*value;

    value = Key_GetBinding( keynum );
    if ( value )
    {
        Q_strncpyz( buf, value, buflen );
    }
    else
    {
        *buf = 0;
    }
}

/*
====================
Key_GetCatcher
====================
*/
int Key_GetCatcher( void )
{
    return cls.keyCatchers;
}

/*
====================
Ket_SetCatcher
====================
*/
void Key_SetCatcher( int catcher )
{
    cls.keyCatchers = catcher;
}

/*
====================
GetConfigString
====================
*/
int GetConfigString(int index, char *buf, int size)
{
    int		offset;

    if (index < 0 || index >= MAX_CONFIGSTRINGS)
        return qfalse;

    offset = cl.gameState.stringOffsets[index];
    if (!offset)
    {
        if( size )
        {
            buf[0] = 0;
        }
        return qfalse;
    }

    Q_strncpyz( buf, cl.gameState.stringData+offset, size);

    return qtrue;
}

/*
====================
CL_ShutdownUI
====================
*/
void CL_ShutdownUI( void )
{
    cls.keyCatchers &= ~KEYCATCH_UI;
    if ( !cls.uiStarted )
        return;

	cls.uiStarted = qfalse;
    UI_Shutdown();
}

void UI_Init(void);
void CL_InitUI(void)
{
	cls.uiStarted = qtrue;
	UI_Init();
}

/*
====================
UI_GameCommand
 
See if the current console command is claimed by the ui
====================
*/
qboolean UI_GameCommand( void )
{
	return (cls.uiStarted) ? UI_ConsoleCommand(cls.realtime) : qfalse;
}
