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
// cg_main.c -- initialization and primary entry point for cgame
#include "cg_local.h"

int forceModelModificationCount = -1;

void CG_Init( int serverMessageNum, int serverCommandSequence, int clientNum );
void CG_Shutdown( void );

cg_t				cg;
cgs_t				cgs;
centity_t			cg_entities[MAX_GENTITIES];
itemInfo_t			cg_items[MAX_ITEMS];


cvar_t	*cg_railTrailTime;
cvar_t	*cgcentertime;
cvar_t	*cg_runpitch;
cvar_t	*cg_runroll;
cvar_t	*cg_bobup;
cvar_t	*cg_bobpitch;
cvar_t	*cg_bobroll;
cvar_t	*cg_swingSpeed;
cvar_t	*cg_shadows;
cvar_t	*cg_gibs;
cvar_t	*cg_drawTimer;
cvar_t	*cg_drawFPS;
cvar_t	*cg_drawSnapshot;
cvar_t	*cg_draw3dIcons;
cvar_t	*cg_drawIcons;
cvar_t	*cg_drawAmmoWarning;
cvar_t	*cg_drawCrosshair;
cvar_t	*cg_drawCrosshairNames;
cvar_t	*cg_drawRewards;
cvar_t	*cg_crosshairSize;
cvar_t	*cg_crosshairX;
cvar_t	*cg_crosshairY;
cvar_t	*cg_crosshairHealth;
cvar_t	*cg_draw2D;
cvar_t	*cg_drawStatus;
cvar_t	*cg_animSpeed;
cvar_t	*cg_debugAnim;
cvar_t	*cg_debugPosition;
cvar_t	*cg_debugEvents;
cvar_t	*cg_errorDecay;
cvar_t	*cg_nopredict;
cvar_t	*cg_noPlayerAnims;
cvar_t	*cg_showmiss;
cvar_t	*cg_footsteps;
cvar_t	*cg_addMarks;
cvar_t	*cg_brassTime;
cvar_t	*cg_viewsize;
cvar_t	*cg_drawGun;
cvar_t	*cg_gun_frame;
cvar_t	*cg_gun_x;
cvar_t	*cg_gun_y;
cvar_t	*cg_gun_z;
cvar_t	*cg_tracerChance;
cvar_t	*cg_tracerWidth;
cvar_t	*cg_tracerLength;
cvar_t	*cg_autoswitch;
cvar_t	*cg_ignore;
cvar_t	*cg_simpleItems;
cvar_t	*cg_fov;
cvar_t	*cg_zoomFov;
cvar_t	*cg_thirdPerson;
cvar_t	*cg_thirdPersonRange;
cvar_t	*cg_thirdPersonAngle;
cvar_t	*cg_stereoSeparation;
cvar_t	*cg_lagometer;
cvar_t	*cg_drawAttacker;
cvar_t	*cg_synchronousClients;
cvar_t 	*cg_teamChatTime;
cvar_t 	*cg_teamChatHeight;
cvar_t 	*cg_stats;
cvar_t 	*cg_buildScript;
cvar_t 	*cg_forceModel;
cvar_t	*cg_paused;
cvar_t	*cg_blood;
cvar_t	*cg_predictItems;
cvar_t	*cg_deferPlayers;
cvar_t	*cg_drawTeamOverlay;
cvar_t	*cg_teamOverlayUserinfo;
cvar_t	*cg_drawFriend;
cvar_t	*cg_teamChatsOnly;
cvar_t	*cg_noVoiceChats;
cvar_t	*cg_noVoiceText;
cvar_t	*cg_hudFiles;
cvar_t 	*cg_scorePlum;
cvar_t 	*cg_smoothClients;
//cvar_t	*pmove_fixed;
//cvar_t	*cg_pmove_fixed;
//cvar_t	*pmove_msec;
cvar_t	*cg_pmove_msec;
cvar_t	*cg_cameraMode;
cvar_t	*cg_cameraOrbit;
cvar_t	*cg_cameraOrbitDelay;
cvar_t	*cg_timescaleFadeEnd;
cvar_t	*cg_timescaleFadeSpeed;
cvar_t	*cg_timescale;
cvar_t	*cg_smallFont;
cvar_t	*cg_bigFont;
cvar_t	*cg_noTaunt;
cvar_t	*cg_noProjectileTrail;
cvar_t	*cg_oldRail;
cvar_t	*cg_oldRocket;
cvar_t	*cg_oldPlasma;
cvar_t	*cg_trueLightning;

cvar_t		*cg_centertime;

typedef struct
{
    cvar_t	**cvar;
    char		*name;
    char		*defaultString;
    int			flags;
}
cvarTable_t;

static cvarTable_t cvarTable[] = { // bk001129
                                     { &cg_ignore, "cg_ignore", "0", 0 },	// used for debugging
                                     { &cg_autoswitch, "cg_autoswitch", "1", CVAR_ARCHIVE },
                                     { &cg_drawGun, "cg_drawGun", "1", CVAR_ARCHIVE },
                                     { &cg_zoomFov, "cg_zoomfov", "22.5", CVAR_ARCHIVE },
                                     { &cg_fov, "cg_fov", "90", CVAR_ARCHIVE },
                                     { &cg_viewsize, "cg_viewsize", "100", CVAR_ARCHIVE },
                                     { &cg_stereoSeparation, "cg_stereoSeparation", "0.4", CVAR_ARCHIVE  },
                                     { &cg_shadows, "cg_shadows", "1", CVAR_ARCHIVE  },
                                     { &cg_gibs, "cg_gibs", "1", CVAR_ARCHIVE  },
									 { &cg_gun_frame, "cg_gun_frame", "0", CVAR_CHEAT },
                                     { &cg_draw2D, "cg_draw2D", "1", CVAR_ARCHIVE  },
                                     { &cg_drawStatus, "cg_drawStatus", "1", CVAR_ARCHIVE  },
                                     { &cg_drawTimer, "cg_drawTimer", "0", CVAR_ARCHIVE  },
                                     { &cg_drawFPS, "cg_drawFPS", "0", CVAR_ARCHIVE  },
                                     { &cg_drawSnapshot, "cg_drawSnapshot", "0", CVAR_ARCHIVE  },
                                     { &cg_draw3dIcons, "cg_draw3dIcons", "1", CVAR_ARCHIVE  },
                                     { &cg_drawIcons, "cg_drawIcons", "1", CVAR_ARCHIVE  },
                                     { &cg_drawAmmoWarning, "cg_drawAmmoWarning", "1", CVAR_ARCHIVE  },
                                     { &cg_drawAttacker, "cg_drawAttacker", "1", CVAR_ARCHIVE  },
                                     { &cg_drawCrosshair, "cg_drawCrosshair", "4", CVAR_ARCHIVE },
                                     { &cg_drawCrosshairNames, "cg_drawCrosshairNames", "1", CVAR_ARCHIVE },
                                     { &cg_drawRewards, "cg_drawRewards", "1", CVAR_ARCHIVE },
                                     { &cg_crosshairSize, "cg_crosshairSize", "24", CVAR_ARCHIVE },
                                     { &cg_crosshairHealth, "cg_crosshairHealth", "1", CVAR_ARCHIVE },
                                     { &cg_crosshairX, "cg_crosshairX", "0", CVAR_ARCHIVE },
                                     { &cg_crosshairY, "cg_crosshairY", "0", CVAR_ARCHIVE },
                                     { &cg_brassTime, "cg_brassTime", "2500", CVAR_ARCHIVE },
                                     { &cg_simpleItems, "cg_simpleItems", "0", CVAR_ARCHIVE },
                                     { &cg_addMarks, "cg_marks", "1", CVAR_ARCHIVE },
                                     { &cg_lagometer, "cg_lagometer", "1", CVAR_ARCHIVE },
                                     { &cg_railTrailTime, "cg_railTrailTime", "400", CVAR_ARCHIVE  },
                                     { &cg_gun_x, "cg_gunX", "0", CVAR_CHEAT },
                                     { &cg_gun_y, "cg_gunY", "0", CVAR_CHEAT },
                                     { &cg_gun_z, "cg_gunZ", "0", CVAR_CHEAT },
                                     { &cg_centertime, "cg_centertime", "3", CVAR_CHEAT },
                                     { &cg_runpitch, "cg_runpitch", "0.002", CVAR_ARCHIVE},
                                     { &cg_runroll, "cg_runroll", "0.005", CVAR_ARCHIVE },
                                     { &cg_bobup , "cg_bobup", "0.005", CVAR_CHEAT },
                                     { &cg_bobpitch, "cg_bobpitch", "0.002", CVAR_ARCHIVE },
                                     { &cg_bobroll, "cg_bobroll", "0.002", CVAR_ARCHIVE },
                                     { &cg_swingSpeed, "cg_swingSpeed", "0.3", CVAR_CHEAT },
                                     { &cg_animSpeed, "cg_animspeed", "1", CVAR_CHEAT },
                                     { &cg_debugAnim, "cg_debuganim", "0", CVAR_CHEAT },
                                     { &cg_debugPosition, "cg_debugposition", "0", CVAR_CHEAT },
                                     { &cg_debugEvents, "cg_debugevents", "0", CVAR_CHEAT },
                                     { &cg_errorDecay, "cCom_Errordecay", "100", 0 },
                                     { &cg_nopredict, "cg_nopredict", "0", 0 },
                                     { &cg_noPlayerAnims, "cg_noplayeranims", "0", CVAR_CHEAT },
                                     { &cg_showmiss, "cg_showmiss", "0", 0 },
                                     { &cg_footsteps, "cg_footsteps", "1", CVAR_CHEAT },
                                     { &cg_tracerChance, "cg_tracerchance", "0.4", CVAR_CHEAT },
                                     { &cg_tracerWidth, "cg_tracerwidth", "1", CVAR_CHEAT },
                                     { &cg_tracerLength, "cg_tracerlength", "100", CVAR_CHEAT },
                                     { &cg_thirdPersonRange, "cg_thirdPersonRange", "40", CVAR_CHEAT },
                                     { &cg_thirdPersonAngle, "cg_thirdPersonAngle", "0", CVAR_CHEAT },
                                     { &cg_thirdPerson, "cg_thirdPerson", "0", 0 },
                                     { &cg_teamChatTime, "cg_teamChatTime", "3000", CVAR_ARCHIVE  },
                                     { &cg_teamChatHeight, "cg_teamChatHeight", "0", CVAR_ARCHIVE  },
                                     { &cg_forceModel, "cg_forceModel", "0", CVAR_ARCHIVE  },
                                     { &cg_predictItems, "cg_predictItems", "1", CVAR_ARCHIVE },
                                     { &cg_deferPlayers, "cg_deferPlayers", "1", CVAR_ARCHIVE },
                                     { &cg_drawTeamOverlay, "cg_drawTeamOverlay", "0", CVAR_ARCHIVE },
                                     { &cg_teamOverlayUserinfo, "teamoverlay", "0", CVAR_ROM | CVAR_USERINFO },
                                     { &cg_stats, "cg_stats", "0", 0 },
                                     { &cg_drawFriend, "cg_drawFriend", "1", CVAR_ARCHIVE },
                                     { &cg_teamChatsOnly, "cg_teamChatsOnly", "0", CVAR_ARCHIVE },
                                     { &cg_noVoiceChats, "cg_noVoiceChats", "0", CVAR_ARCHIVE },
                                     { &cg_noVoiceText, "cg_noVoiceText", "0", CVAR_ARCHIVE },
                                     // the following variables are created in other parts of the system,
                                     // but we also reference them here
                                     { &cg_buildScript, "com_buildScript", "0", 0 },	// force loading of all possible data amd error on failures
                                     { &cg_paused, "cl_paused", "0", CVAR_ROM },
                                     { &cg_blood, "com_blood", "1", CVAR_ARCHIVE },
                                     { &cg_synchronousClients, "g_synchronousClients", "0", 0 },	// communicated by systeminfo
                                     { &cg_cameraOrbit, "cg_cameraOrbit", "0", CVAR_CHEAT},
                                     { &cg_cameraOrbitDelay, "cg_cameraOrbitDelay", "50", CVAR_ARCHIVE},
                                     { &cg_timescaleFadeEnd, "cg_timescaleFadeEnd", "1", 0},
                                     { &cg_timescaleFadeSpeed, "cg_timescaleFadeSpeed", "0", 0},
                                     { &cg_timescale, "timescale", "1", 0},
                                     { &cg_scorePlum, "cg_scorePlums", "1", CVAR_USERINFO | CVAR_ARCHIVE},
                                     { &cg_smoothClients, "cg_smoothClients", "0", CVAR_USERINFO | CVAR_ARCHIVE},
                                     { &cg_cameraMode, "com_cameraMode", "0", CVAR_CHEAT},

                                     { &pmove_fixed, "pmove_fixed", "0", 0},
                                     { &pmove_msec, "pmove_msec", "8", 0},
                                     { &cg_noTaunt, "cg_noTaunt", "0", CVAR_ARCHIVE},
                                     { &cg_noProjectileTrail, "cg_noProjectileTrail", "0", CVAR_ARCHIVE},
                                     { &cg_smallFont, "ui_smallFont", "0.25", CVAR_ARCHIVE},
                                     { &cg_bigFont, "ui_bigFont", "0.4", CVAR_ARCHIVE},
                                     { &cg_oldRail, "cg_oldRail", "1", CVAR_ARCHIVE},
                                     { &cg_oldRocket, "cg_oldRocket", "1", CVAR_ARCHIVE},
                                     { &cg_oldPlasma, "cg_oldPlasma", "1", CVAR_ARCHIVE},
                                     { &cg_trueLightning, "cg_trueLightning", "0.0", CVAR_ARCHIVE}
                                     //	{ &cg_pmove_fixed, "cg_pmove_fixed", "0", CVAR_USERINFO | CVAR_ARCHIVE }
                                 };

static int  cvarTableSize = sizeof( cvarTable ) / sizeof( cvarTable[0] );

/*
=================
CG_RegisterCvars
=================
*/
void CG_RegisterCvars( void )
{
    int			i;
    cvarTable_t	*cv;
    char		var[MAX_TOKEN_CHARS];

    for ( i = 0, cv = cvarTable ; i < cvarTableSize ; i++, cv++ )
    {
        *cv->cvar = Cvar_Get(cv->name, cv->defaultString, cv->flags );
    }

    // see if we are also running the server on this machine
    Cvar_VariableStringBuffer( "sv_running", var, sizeof( var ) );
    cgs.localServer = atoi( var );

    forceModelModificationCount = cg_forceModel->modificationCount;

    Cvar_Get("model", DEFAULT_MODEL, CVAR_USERINFO | CVAR_ARCHIVE );
    Cvar_Get("headmodel", DEFAULT_MODEL, CVAR_USERINFO | CVAR_ARCHIVE );
    Cvar_Get("team_model", DEFAULT_TEAM_MODEL, CVAR_USERINFO | CVAR_ARCHIVE );
    Cvar_Get("team_headmodel", DEFAULT_TEAM_HEAD, CVAR_USERINFO | CVAR_ARCHIVE );
}

/*
===================
CG_ForceModelChange
===================
*/
static void CG_ForceModelChange( void )
{
    int		i;

    for (i=0 ; i<MAX_CLIENTS ; i++)
    {
        const char		*clientInfo;

        clientInfo = CG_ConfigString( CS_PLAYERS+i );
        if ( !clientInfo[0] )
        {
            continue;
        }
        CG_NewClientInfo( i );
    }
}

/*
=================
CG_UpdateCvars
=================
*/
void CG_UpdateCvars( void )
{
    // check for modications here

    // If team overlay is on, ask for updates from the server.  If its off,
    // let the server know so we don't receive it
    if ( drawTeamOverlayModificationCount != cg_drawTeamOverlay->modificationCount )
    {
        drawTeamOverlayModificationCount = cg_drawTeamOverlay->modificationCount;

        if ( cg_drawTeamOverlay->integer > 0 )
        {
            Cvar_Set( "teamoverlay", "1" );
        }
        else
        {
            Cvar_Set( "teamoverlay", "0" );
        }
        // FIXME E3 HACK
        Cvar_Set( "teamoverlay", "1" );
    }

    // if force model changed
    if ( forceModelModificationCount != cg_forceModel->modificationCount )
    {
        forceModelModificationCount = cg_forceModel->modificationCount;
        CG_ForceModelChange();
    }
}

int CG_CrosshairPlayer( void )
{
    if ( cg.time > ( cg.crosshairClientTime + 1000 ) )
    {
        return -1;
    }
    return cg.crosshairClientNum;
}

int CG_LastAttacker( void )
{
    if ( !cg.attackerTime )
    {
        return -1;
    }
    return cg.snap->ps.persistant[PERS_ATTACKER];
}

/*
================
CG_Argv
================
*/
const char *CG_Argv( int arg )
{
    static char	buffer[MAX_STRING_CHARS];

    Cmd_ArgvBuffer( arg, buffer, sizeof( buffer ) );

    return buffer;
}


//========================================================================

/*
=================
CG_RegisterItemSounds
 
The server says this item is used on this level
=================
*/
static void CG_RegisterItemSounds( int itemNum )
{
    gitem_t			*item;
    char			data[MAX_QPATH];
    char			*s, *start;
    int				len;

    item = &bg_itemlist[ itemNum ];

    if( item->pickup_sound )
    {
        S_RegisterSound( item->pickup_sound, qfalse );
    }

    // parse the space seperated precache string for other media
    s = item->sounds;
    if (!s || !s[0])
        return;

    while (*s)
    {
        start = s;
        while (*s && *s != ' ')
        {
            s++;
        }

        len = s-start;
        if (len >= MAX_QPATH || len < 5)
        {
            Com_Error( ERR_DROP,  "PrecacheItem: %s has bad precache string",
                      item->classname);
            return;
        }
        memcpy (data, start, len);
        data[len] = 0;
        if ( *s )
        {
            s++;
        }

        if ( !strcmp(data+len-3, "wav" ))
        {
            S_RegisterSound( data, qfalse );
        }
    }
}


/*
=================
CG_RegisterSounds
 
called during a precache command
=================
*/
static void CG_RegisterSounds( void )
{
    int		i;
    char	items[MAX_ITEMS+1];
    char	name[MAX_QPATH];
    const char	*soundName;

    // voice commands

    cgs.media.oneMinuteSound = S_RegisterSound( "sound/feedback/1_minute.wav", qtrue );
    cgs.media.fiveMinuteSound = S_RegisterSound( "sound/feedback/5_minute.wav", qtrue );
    cgs.media.suddenDeathSound = S_RegisterSound( "sound/feedback/sudden_death.wav", qtrue );
    cgs.media.oneFragSound = S_RegisterSound( "sound/feedback/1_frag.wav", qtrue );
    cgs.media.twoFragSound = S_RegisterSound( "sound/feedback/2_frags.wav", qtrue );
    cgs.media.threeFragSound = S_RegisterSound( "sound/feedback/3_frags.wav", qtrue );
    cgs.media.count3Sound = S_RegisterSound( "sound/feedback/three.wav", qtrue );
    cgs.media.count2Sound = S_RegisterSound( "sound/feedback/two.wav", qtrue );
    cgs.media.count1Sound = S_RegisterSound( "sound/feedback/one.wav", qtrue );
    cgs.media.countFightSound = S_RegisterSound( "sound/feedback/fight.wav", qtrue );
    cgs.media.countPrepareSound = S_RegisterSound( "sound/feedback/prepare.wav", qtrue );

    if ( cgs.gametype >= GT_TEAM || cg_buildScript->integer )
    {

        cgs.media.captureAwardSound = S_RegisterSound( "sound/teamplay/flagcapture_yourteam.wav", qtrue );
        cgs.media.redLeadsSound = S_RegisterSound( "sound/feedback/redleads.wav", qtrue );
        cgs.media.blueLeadsSound = S_RegisterSound( "sound/feedback/blueleads.wav", qtrue );
        cgs.media.teamsTiedSound = S_RegisterSound( "sound/feedback/teamstied.wav", qtrue );
        cgs.media.hitTeamSound = S_RegisterSound( "sound/feedback/hit_teammate.wav", qtrue );

        cgs.media.redScoredSound = S_RegisterSound( "sound/teamplay/voc_red_scores.wav", qtrue );
        cgs.media.blueScoredSound = S_RegisterSound( "sound/teamplay/voc_blue_scores.wav", qtrue );

        cgs.media.captureYourTeamSound = S_RegisterSound( "sound/teamplay/flagcapture_yourteam.wav", qtrue );
        cgs.media.captureOpponentSound = S_RegisterSound( "sound/teamplay/flagcapture_opponent.wav", qtrue );

        cgs.media.returnYourTeamSound = S_RegisterSound( "sound/teamplay/flagreturn_yourteam.wav", qtrue );
        cgs.media.returnOpponentSound = S_RegisterSound( "sound/teamplay/flagreturn_opponent.wav", qtrue );

        cgs.media.takenYourTeamSound = S_RegisterSound( "sound/teamplay/flagtaken_yourteam.wav", qtrue );
        cgs.media.takenOpponentSound = S_RegisterSound( "sound/teamplay/flagtaken_opponent.wav", qtrue );

        if ( cgs.gametype == GT_CTF || cg_buildScript->integer )
        {
            cgs.media.redFlagReturnedSound = S_RegisterSound( "sound/teamplay/voc_red_returned.wav", qtrue );
            cgs.media.blueFlagReturnedSound = S_RegisterSound( "sound/teamplay/voc_blue_returned.wav", qtrue );
            cgs.media.enemyTookYourFlagSound = S_RegisterSound( "sound/teamplay/voc_enemy_flag.wav", qtrue );
            cgs.media.yourTeamTookEnemyFlagSound = S_RegisterSound( "sound/teamplay/voc_team_flag.wav", qtrue );
        }

        cgs.media.youHaveFlagSound = S_RegisterSound( "sound/teamplay/voc_you_flag.wav", qtrue );
        cgs.media.holyShitSound = S_RegisterSound("sound/feedback/voc_holyshit.wav", qtrue);
        cgs.media.neutralFlagReturnedSound = S_RegisterSound( "sound/teamplay/flagreturn_opponent.wav", qtrue );
        cgs.media.yourTeamTookTheFlagSound = S_RegisterSound( "sound/teamplay/voc_team_1flag.wav", qtrue );
        cgs.media.enemyTookTheFlagSound = S_RegisterSound( "sound/teamplay/voc_enemy_1flag.wav", qtrue );
    }

    cgs.media.tracerSound = S_RegisterSound( "sound/weapons/machinegun/buletby1.wav", qfalse );
    cgs.media.selectSound = S_RegisterSound( "sound/weapons/change.wav", qfalse );
    cgs.media.wearOffSound = S_RegisterSound( "sound/items/wearoff.wav", qfalse );
    cgs.media.useNothingSound = S_RegisterSound( "sound/items/use_nothing.wav", qfalse );
    cgs.media.gibSound = S_RegisterSound( "sound/player/gibsplt1.wav", qfalse );
    cgs.media.gibBounce1Sound = S_RegisterSound( "sound/player/gibimp1.wav", qfalse );
    cgs.media.gibBounce2Sound = S_RegisterSound( "sound/player/gibimp2.wav", qfalse );
    cgs.media.gibBounce3Sound = S_RegisterSound( "sound/player/gibimp3.wav", qfalse );

    cgs.media.teleInSound = S_RegisterSound( "sound/world/telein.wav", qfalse );
    cgs.media.teleOutSound = S_RegisterSound( "sound/world/teleout.wav", qfalse );
    cgs.media.respawnSound = S_RegisterSound( "sound/items/respawn1.wav", qfalse );

    cgs.media.noAmmoSound = S_RegisterSound( "sound/weapons/noammo.wav", qfalse );

    cgs.media.talkSound = S_RegisterSound( "sound/player/talk.wav", qfalse );
    cgs.media.landSound = S_RegisterSound( "sound/player/land1.wav", qfalse);

    cgs.media.hitSound = S_RegisterSound( "sound/feedback/hit.wav", qfalse );

    cgs.media.impressiveSound = S_RegisterSound( "sound/feedback/impressive.wav", qtrue );
    cgs.media.excellentSound = S_RegisterSound( "sound/feedback/excellent.wav", qtrue );
    cgs.media.deniedSound = S_RegisterSound( "sound/feedback/denied.wav", qtrue );
    cgs.media.humiliationSound = S_RegisterSound( "sound/feedback/humiliation.wav", qtrue );
    cgs.media.assistSound = S_RegisterSound( "sound/feedback/assist.wav", qtrue );
    cgs.media.defendSound = S_RegisterSound( "sound/feedback/defense.wav", qtrue );

    cgs.media.takenLeadSound = S_RegisterSound( "sound/feedback/takenlead.wav", qtrue);
    cgs.media.tiedLeadSound = S_RegisterSound( "sound/feedback/tiedlead.wav", qtrue);
    cgs.media.lostLeadSound = S_RegisterSound( "sound/feedback/lostlead.wav", qtrue);

    cgs.media.watrInSound = S_RegisterSound( "sound/player/watr_in.wav", qfalse);
    cgs.media.watrOutSound = S_RegisterSound( "sound/player/watr_out.wav", qfalse);
    cgs.media.watrUnSound = S_RegisterSound( "sound/player/watr_un.wav", qfalse);

    cgs.media.jumpPadSound = S_RegisterSound ("sound/world/jumppad.wav", qfalse );

    for (i=0 ; i<4 ; i++)
    {
        Com_sprintf (name, sizeof(name), "sound/player/footsteps/step%i.wav", i+1);
        cgs.media.footsteps[FOOTSTEP_NORMAL][i] = S_RegisterSound (name, qfalse);

        Com_sprintf (name, sizeof(name), "sound/player/footsteps/boot%i.wav", i+1);
        cgs.media.footsteps[FOOTSTEP_BOOT][i] = S_RegisterSound (name, qfalse);

        Com_sprintf (name, sizeof(name), "sound/player/footsteps/flesh%i.wav", i+1);
        cgs.media.footsteps[FOOTSTEP_FLESH][i] = S_RegisterSound (name, qfalse);

        Com_sprintf (name, sizeof(name), "sound/player/footsteps/mech%i.wav", i+1);
        cgs.media.footsteps[FOOTSTEP_MECH][i] = S_RegisterSound (name, qfalse);

        Com_sprintf (name, sizeof(name), "sound/player/footsteps/energy%i.wav", i+1);
        cgs.media.footsteps[FOOTSTEP_ENERGY][i] = S_RegisterSound (name, qfalse);

        Com_sprintf (name, sizeof(name), "sound/player/footsteps/splash%i.wav", i+1);
        cgs.media.footsteps[FOOTSTEP_SPLASH][i] = S_RegisterSound (name, qfalse);

        Com_sprintf (name, sizeof(name), "sound/player/footsteps/clank%i.wav", i+1);
        cgs.media.footsteps[FOOTSTEP_METAL][i] = S_RegisterSound (name, qfalse);
    }

    // only register the items that the server says we need
    strcpy( items, CG_ConfigString( CS_ITEMS ) );

    for ( i = 1 ; i < bg_numItems ; i++ )
    {
//		if ( items[ i ] == '1' || cg_buildScript->integer ) {
        CG_RegisterItemSounds( i );
//		}
    }

    for ( i = 1 ; i < MAX_SOUNDS ; i++ )
    {
        soundName = CG_ConfigString( CS_SOUNDS+i );
        if ( !soundName[0] )
        {
            break;
        }
        if ( soundName[0] == '*' )
        {
            continue;	// custom sound
        }
        cgs.gameSounds[i] = S_RegisterSound( soundName, qfalse );
    }

    // FIXME: only needed with item
    cgs.media.flightSound = S_RegisterSound( "sound/items/flight.wav", qfalse );
    cgs.media.medkitSound = S_RegisterSound ("sound/items/use_medkit.wav", qfalse);
    cgs.media.quadSound = S_RegisterSound("sound/items/damage3.wav", qfalse);
    cgs.media.sfx_ric1 = S_RegisterSound ("sound/weapons/machinegun/ric1.wav", qfalse);
    cgs.media.sfx_ric2 = S_RegisterSound ("sound/weapons/machinegun/ric2.wav", qfalse);
    cgs.media.sfx_ric3 = S_RegisterSound ("sound/weapons/machinegun/ric3.wav", qfalse);
    cgs.media.sfx_railg = S_RegisterSound ("sound/weapons/railgun/railgf1a.wav", qfalse);
    cgs.media.sfx_rockexp = S_RegisterSound ("sound/weapons/rocket/rocklx1a.wav", qfalse);
    cgs.media.sfx_plasmaexp = S_RegisterSound ("sound/weapons/plasma/plasmx1a.wav", qfalse);

    cgs.media.regenSound = S_RegisterSound("sound/items/regen.wav", qfalse);
    cgs.media.protectSound = S_RegisterSound("sound/items/protect3.wav", qfalse);
    cgs.media.n_healthSound = S_RegisterSound("sound/items/n_health.wav", qfalse );
    cgs.media.hgrenb1aSound = S_RegisterSound("sound/weapons/grenade/hgrenb1a.wav", qfalse);
    cgs.media.hgrenb2aSound = S_RegisterSound("sound/weapons/grenade/hgrenb2a.wav", qfalse);
}


//===================================================================================


/*
=================
CG_RegisterGraphics
 
This function may execute for a couple of minutes with a slow disk.
=================
*/
static void CG_RegisterGraphics( void )
{
    int			i;
    char		items[MAX_ITEMS+1];
    static char		*sb_nums[11] = {
                                    "gfx/2d/numbers/big0",
                                    "gfx/2d/numbers/big1",
                                    "gfx/2d/numbers/big2",
                                    "gfx/2d/numbers/big3",
                                    "gfx/2d/numbers/big4",
                                    "gfx/2d/numbers/big5",
                                    "gfx/2d/numbers/big6",
                                    "gfx/2d/numbers/big7",
                                    "gfx/2d/numbers/big8",
                                    "gfx/2d/numbers/big9",
                                    "gfx/2d/numbers/bigminus",
                                };

    // clear any references to old media
    memset( &cg.refdef, 0, sizeof( cg.refdef ) );
    RE_ClearScene();

    CG_LoadingString( cgs.mapname );

    RE_LoadWorldMap( cgs.mapname );

    // precache status bar pics
    CG_LoadingString( "game media" );

    for ( i=0 ; i<11 ; i++)
    {
        cgs.media.numberShaders[i] = RE_RegisterShader( sb_nums[i] );
    }

    cgs.media.botSkillShaders[0] = RE_RegisterShader( "menu/art/skill1.tga" );
    cgs.media.botSkillShaders[1] = RE_RegisterShader( "menu/art/skill2.tga" );
    cgs.media.botSkillShaders[2] = RE_RegisterShader( "menu/art/skill3.tga" );
    cgs.media.botSkillShaders[3] = RE_RegisterShader( "menu/art/skill4.tga" );
    cgs.media.botSkillShaders[4] = RE_RegisterShader( "menu/art/skill5.tga" );

    cgs.media.viewBloodShader = RE_RegisterShader( "viewBloodBlend" );

    cgs.media.deferShader = RE_RegisterShaderNoMip( "gfx/2d/defer.tga" );

    cgs.media.scoreboardName = RE_RegisterShaderNoMip( "menu/tab/name.tga" );
    cgs.media.scoreboardPing = RE_RegisterShaderNoMip( "menu/tab/ping.tga" );
    cgs.media.scoreboardScore = RE_RegisterShaderNoMip( "menu/tab/score.tga" );
    cgs.media.scoreboardTime = RE_RegisterShaderNoMip( "menu/tab/time.tga" );

    cgs.media.smokePuffShader = RE_RegisterShader( "smokePuff" );
    cgs.media.smokePuffRageProShader = RE_RegisterShader( "smokePuffRagePro" );
    cgs.media.shotgunSmokePuffShader = RE_RegisterShader( "shotgunSmokePuff" );
    cgs.media.plasmaBallShader = RE_RegisterShader( "sprites/plasma1" );
    cgs.media.bloodTrailShader = RE_RegisterShader( "bloodTrail" );
    cgs.media.lagometerShader = RE_RegisterShader("lagometer" );
    cgs.media.connectionShader = RE_RegisterShader( "disconnected" );

    cgs.media.waterBubbleShader = RE_RegisterShader( "waterBubble" );

    cgs.media.tracerShader = RE_RegisterShader( "gfx/misc/tracer" );
    cgs.media.selectShader = RE_RegisterShader( "gfx/2d/select" );
    cgs.media.crosshairShader = RE_RegisterShader("gfx/2d/crosshair");

    cgs.media.backTileShader = RE_RegisterShader( "gfx/2d/backtile" );
    cgs.media.noammoShader = RE_RegisterShader( "icons/noammo" );

    // powerup shaders
    cgs.media.quadShader = RE_RegisterShader("powerups/quad" );
    cgs.media.quadWeaponShader = RE_RegisterShader("powerups/quadWeapon" );
    cgs.media.battleSuitShader = RE_RegisterShader("powerups/battleSuit" );
    cgs.media.battleWeaponShader = RE_RegisterShader("powerups/battleWeapon" );
    cgs.media.invisShader = RE_RegisterShader("powerups/invisibility" );
    cgs.media.regenShader = RE_RegisterShader("powerups/regen" );
    cgs.media.hastePuffShader = RE_RegisterShader("hasteSmokePuff" );

    if ( cgs.gametype == GT_CTF || cg_buildScript->integer )
    {
        cgs.media.redCubeModel = RE_RegisterModel( "models/powerups/orb/r_orb.md3" );
        cgs.media.blueCubeModel = RE_RegisterModel( "models/powerups/orb/b_orb.md3" );
        cgs.media.redCubeIcon = RE_RegisterShader( "icons/skull_red" );
        cgs.media.blueCubeIcon = RE_RegisterShader( "icons/skull_blue" );
    }

    if ( cgs.gametype == GT_CTF || cg_buildScript->integer )
    {
        cgs.media.redFlagModel = RE_RegisterModel( "models/flags/r_flag.md3" );
        cgs.media.blueFlagModel = RE_RegisterModel( "models/flags/b_flag.md3" );
        cgs.media.redFlagShader[0] = RE_RegisterShaderNoMip( "icons/iconf_red1" );
        cgs.media.redFlagShader[1] = RE_RegisterShaderNoMip( "icons/iconf_red2" );
        cgs.media.redFlagShader[2] = RE_RegisterShaderNoMip( "icons/iconf_red3" );
        cgs.media.blueFlagShader[0] = RE_RegisterShaderNoMip( "icons/iconf_blu1" );
        cgs.media.blueFlagShader[1] = RE_RegisterShaderNoMip( "icons/iconf_blu2" );
        cgs.media.blueFlagShader[2] = RE_RegisterShaderNoMip( "icons/iconf_blu3" );
    }

    if ( cgs.gametype >= GT_TEAM || cg_buildScript->integer )
    {
        cgs.media.friendShader = RE_RegisterShader( "sprites/foe" );
        cgs.media.redQuadShader = RE_RegisterShader("powerups/blueflag" );
        cgs.media.teamStatusBar = RE_RegisterShader( "gfx/2d/colorbar.tga" );
    }

    cgs.media.armorModel = RE_RegisterModel( "models/powerups/armor/armor_yel.md3" );
    cgs.media.armorIcon  = RE_RegisterShaderNoMip( "icons/iconr_yellow" );

    cgs.media.machinegunBrassModel = RE_RegisterModel( "models/weapons2/shells/m_shell.md3" );
    cgs.media.shotgunBrassModel = RE_RegisterModel( "models/weapons2/shells/s_shell.md3" );

    cgs.media.gibAbdomen = RE_RegisterModel( "models/gibs/abdomen.md3" );
    cgs.media.gibArm = RE_RegisterModel( "models/gibs/arm.md3" );
    cgs.media.gibChest = RE_RegisterModel( "models/gibs/chest.md3" );
    cgs.media.gibFist = RE_RegisterModel( "models/gibs/fist.md3" );
    cgs.media.gibFoot = RE_RegisterModel( "models/gibs/foot.md3" );
    cgs.media.gibForearm = RE_RegisterModel( "models/gibs/forearm.md3" );
    cgs.media.gibIntestine = RE_RegisterModel( "models/gibs/intestine.md3" );
    cgs.media.gibLeg = RE_RegisterModel( "models/gibs/leg.md3" );
    cgs.media.gibSkull = RE_RegisterModel( "models/gibs/skull.md3" );
    cgs.media.gibBrain = RE_RegisterModel( "models/gibs/brain.md3" );

    cgs.media.smoke2 = RE_RegisterModel( "models/weapons2/shells/s_shell.md3" );

    cgs.media.balloonShader = RE_RegisterShader( "sprites/balloon3" );

    cgs.media.bloodExplosionShader = RE_RegisterShader( "bloodExplosion" );

    cgs.media.bulletFlashModel = RE_RegisterModel("models/weaphits/bullet.md3");
    cgs.media.ringFlashModel = RE_RegisterModel("models/weaphits/ring02.md3");
    cgs.media.dishFlashModel = RE_RegisterModel("models/weaphits/boom01.md3");
    cgs.media.teleportEffectModel = RE_RegisterModel( "models/misc/telep.md3" );
    cgs.media.teleportEffectShader = RE_RegisterShader( "teleportEffect" );
    cgs.media.invulnerabilityPowerupModel = RE_RegisterModel( "models/powerups/shield/shield.md3" );
    cgs.media.medalImpressive = RE_RegisterShaderNoMip( "medal_impressive" );
    cgs.media.medalExcellent = RE_RegisterShaderNoMip( "medal_excellent" );
    cgs.media.medalGauntlet = RE_RegisterShaderNoMip( "medal_gauntlet" );
    cgs.media.medalDefend = RE_RegisterShaderNoMip( "medal_defend" );
    cgs.media.medalAssist = RE_RegisterShaderNoMip( "medal_assist" );
    cgs.media.medalCapture = RE_RegisterShaderNoMip( "medal_capture" );


    memset( cg_items, 0, sizeof( cg_items ) );
//    memset( cg_weapons, 0, sizeof( cg_weapons ) );

    // only register the items that the server says we need
    strcpy( items, CG_ConfigString( CS_ITEMS) );

    for ( i = 1 ; i < bg_numItems ; i++ )
    {
        if ( items[ i ] == '1' || cg_buildScript->integer )
        {
            CG_LoadingItem( i );
            CG_RegisterItemVisuals( i );
        }
    }

    // wall marks
    cgs.media.bulletMarkShader = RE_RegisterShader( "gfx/damage/bullet_mrk" );
    cgs.media.burnMarkShader = RE_RegisterShader( "gfx/damage/burn_med_mrk" );
    cgs.media.holeMarkShader = RE_RegisterShader( "gfx/damage/hole_lg_mrk" );
    cgs.media.energyMarkShader = RE_RegisterShader( "gfx/damage/plasma_mrk" );
    cgs.media.shadowMarkShader = RE_RegisterShader( "markShadow" );
    cgs.media.wakeMarkShader = RE_RegisterShader( "wake" );
    cgs.media.bloodMarkShader = RE_RegisterShader( "bloodMark" );

    // register the inline models
    cgs.numInlineModels = CM_NumInlineModels();
    for ( i = 1 ; i < cgs.numInlineModels ; i++ )
    {
        char	name[10];
        vec3_t			mins, maxs;
        int				j;

        Com_sprintf( name, sizeof(name), "*%i", i );
        cgs.inlineDrawModel[i] = RE_RegisterModel( name );
        R_ModelBounds( cgs.inlineDrawModel[i], mins, maxs );
        for ( j = 0 ; j < 3 ; j++ )
        {
            cgs.inlineModelMidpoints[i][j] = mins[j] + 0.5 * ( maxs[j] - mins[j] );
        }
    }

    // register all the server specified models
    for (i=1 ; i<MAX_MODELS ; i++)
    {
        const char		*modelName;

        modelName = CG_ConfigString( CS_MODELS+i );
        if ( !modelName[0] )
        {
            break;
        }
        cgs.gameModels[i] = RE_RegisterModel( modelName );
    }
    CG_ClearParticles ();
    /*
    	for (i=1; i<MAX_PARTICLES_AREAS; i++)
    	{
    		{
    			int rval;
     
    			rval = CG_NewParticleArea ( CS_PARTICLES + i);
    			if (!rval)
    				break;
    		}
    	}
    */
}



/*
=======================
CG_BuildSpectatorString
 
=======================
*/
void CG_BuildSpectatorString()
{
    int i;
    cg.spectatorList[0] = 0;
    for (i = 0; i < MAX_CLIENTS; i++)
    {
        if (cgs.clientinfo[i].infoValid && cgs.clientinfo[i].team == TEAM_SPECTATOR )
        {
            Q_strcat(cg.spectatorList, sizeof(cg.spectatorList), va("%s     ", cgs.clientinfo[i].name));
        }
    }
    i = strlen(cg.spectatorList);
    if (i != cg.spectatorLen)
    {
        cg.spectatorLen = i;
        cg.spectatorWidth = -1;
    }
}


/*
===================
CG_RegisterClients
===================
*/
static void CG_RegisterClients( void )
{
    int		i;

    CG_LoadingClient(cg.clientNum);
    CG_NewClientInfo(cg.clientNum);

    for (i=0 ; i<MAX_CLIENTS ; i++)
    {
        const char		*clientInfo;

        if (cg.clientNum == i)
        {
            continue;
        }

        clientInfo = CG_ConfigString( CS_PLAYERS+i );
        if ( !clientInfo[0])
        {
            continue;
        }
        CG_LoadingClient( i );
        CG_NewClientInfo( i );
    }
    CG_BuildSpectatorString();
}

//===========================================================================

/*
=================
CG_ConfigString
=================
*/
const char *CG_ConfigString( int index )
{
    if ( index < 0 || index >= MAX_CONFIGSTRINGS )
    {
        Com_Error( ERR_DROP,  "CG_ConfigString: bad index: %i", index );
    }
    return cgs.gameState.stringData + cgs.gameState.stringOffsets[ index ];
}

//==================================================================

/*
======================
CG_StartMusic
 
======================
*/
void CG_StartMusic( void )
{
    char	*s;
    char	parm1[MAX_QPATH], parm2[MAX_QPATH];

    // start the background music
    s = (char *)CG_ConfigString( CS_MUSIC );
    Q_strncpyz( parm1, COM_Parse( &s ), sizeof( parm1 ) );
    Q_strncpyz( parm2, COM_Parse( &s ), sizeof( parm2 ) );

    S_StartBackgroundTrack( parm1, parm2 );
}

/*
=================
CG_Init
 
Called after every level change or subsystem restart
Will perform callbacks to make the loading info screen update.
=================
*/
void CG_Init( int serverMessageNum, int serverCommandSequence, int clientNum )
{
    const char	*s;

    // clear everything
    memset( &cgs, 0, sizeof( cgs ) );
    memset( &cg, 0, sizeof( cg ) );
    memset( cg_entities, 0, sizeof(cg_entities) );
//    memset( cg_weapons, 0, sizeof(cg_weapons) );
    memset( cg_items, 0, sizeof(cg_items) );

    cg.clientNum = clientNum;

    cgs.processedSnapshotNum = serverMessageNum;
    cgs.serverCommandSequence = serverCommandSequence;

    // load a few needed things before we do any screen updates
    cgs.media.charsetShader		= RE_RegisterShader( "gfx/2d/bigchars" );
    cgs.media.whiteShader		= RE_RegisterShader( "white" );
    cgs.media.charsetProp		= RE_RegisterShaderNoMip( "menu/art/font1_prop.tga" );
    cgs.media.charsetPropGlow	= RE_RegisterShaderNoMip( "menu/art/font1_prop_glo.tga" );
    cgs.media.charsetPropB		= RE_RegisterShaderNoMip( "menu/art/font2_prop.tga" );

    CG_RegisterCvars();

    CG_InitConsoleCommands();

    cg.weaponSelect = WP_MELEE;

    cgs.redflag = cgs.blueflag = -1; // For compatibily, default to unset for
    cgs.flagStatus = -1;
    // old servers

    // get the rendering configuration from the client system
    CL_GetGlconfig( &cgs.glconfig );
    cgs.screenXScale = cgs.glconfig.vidWidth / 640.0;
    cgs.screenYScale = cgs.glconfig.vidHeight / 480.0;

    // get the gamestate from the client system
    CL_GetGameState( &cgs.gameState );

    // check version
    s = CG_ConfigString( CS_GAME_VERSION );
    if ( strcmp( s, GAME_VERSION ) )
    {
        Com_Error( ERR_DROP,  "Client/Server game mismatch: %s/%s", GAME_VERSION, s );
    }

    s = CG_ConfigString( CS_LEVEL_START_TIME );
    cgs.levelStartTime = atoi( s );

    CG_ParseServerinfo();

    // load the new map
    CG_LoadingString( "collision map" );

    CL_CM_LoadMap( cgs.mapname );

    cg.loading = qtrue;		// force players to load instead of defer

    CG_LoadingString( "sounds" );

    CG_RegisterSounds();

    CG_LoadingString( "graphics" );

    CG_RegisterGraphics();

    CG_LoadingString( "clients" );

    CG_RegisterClients();		// if low on memory, some clients will be deferred

    cg.loading = qfalse;	// future players will be deferred

    CG_InitLocalEntities();

    CG_InitMarkPolys();

    // remove the last loading update
    cg.infoScreenText[0] = 0;

    // Make sure we have update values (scores)
    CG_SetConfigValues();

    CG_StartMusic();

    CG_LoadingString( "" );

    CG_ShaderStateChanged();

    S_ClearLoopingSounds( qtrue );
}

/*
=================
CG_Shutdown
 
Called before every level change or subsystem restart
=================
*/
void CG_Shutdown( void )
{
    // some mods may need to do cleanup work here,
    // like closing files or archiving session data
}

/*
==================
CG_EventHandling
==================
 type 0 - no event handling
      1 - team menu
      2 - hud editor
 
*/
void CG_EventHandling(int type)
{}



void CG_KeyEvent(int key, qboolean down)
{}

void CG_MouseEvent(int x, int y)
{}

