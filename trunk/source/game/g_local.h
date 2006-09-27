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
// g_local.h -- local definitions for game module

//#include "q_shared.h"
#include "../engine/server.h"
//#include "bg_public.h"
//#include "g_public.h"

//==================================================================

// the "gameversion" client command will print this plus compile date
#define	GAMEVERSION	"baseq3"

#define BODY_QUEUE_SIZE		8

#define INFINITE			1000000

#define	FRAMETIME			100					// msec
#define	CARNAGE_REWARD_TIME	3000
#define REWARD_SPRITE_TIME	2000

#define	INTERMISSION_DELAY_TIME	1000
#define	SP_INTERMISSION_DELAY_TIME	5000

// gentity->flags
#define	FL_GODMODE				0x00000010
#define	FL_NOTARGET				0x00000020
#define	FL_TEAMSLAVE			0x00000400	// not the first on the team
#define FL_NO_KNOCKBACK			0x00000800
#define FL_DROPPED_ITEM			0x00001000
#define FL_NO_BOTS				0x00002000	// spawn point not for bot use
#define FL_NO_HUMANS			0x00004000	// spawn point just for bots
#define FL_FORCE_GESTURE		0x00008000	// force gesture on client

// movers are things like doors, plats, buttons, etc

#define SP_PODIUM_MODEL		"models/mapobjects/podium/podium4.md3"

//============================================================================

typedef struct gclient_s gclient_t;

typedef enum {
    CON_DISCONNECTED,
    CON_CONNECTING,
    CON_CONNECTED
} clientConnected_t;

typedef enum {
    SPECTATOR_NOT,
    SPECTATOR_FREE,
    SPECTATOR_FOLLOW,
    SPECTATOR_SCOREBOARD
} spectatorState_t;

typedef enum {
    TEAM_BEGIN,		// Beginning a team game, spawn at base
    TEAM_ACTIVE		// Now actively playing
} playerTeamStateState_t;

typedef struct
{
    playerTeamStateState_t	state;

    int			location;

    int			captures;
    int			basedefense;
    int			carrierdefense;
    int			flagrecovery;
    int			fragcarrier;
    int			assists;

    float		lasthurtcarrier;
    float		lastreturnedflag;
    float		flagsince;
    float		lastfraggedcarrier;
}
playerTeamState_t;

// the auto following clients don't follow a specific client
// number, but instead follow the first two active players
#define	FOLLOW_ACTIVE1	-1
#define	FOLLOW_ACTIVE2	-2

// client data that stays across multiple levels or tournament restarts
// this is achieved by writing all the data to cvar strings at game shutdown
// time and reading them back at connection time.  Anything added here
// MUST be dealt with in G_InitSessionData() / G_ReadSessionData() / G_WriteSessionData()
typedef struct
{
    team_t           sessionTeam;
    int              spectatorTime;		// for determining next-in-line to play
    spectatorState_t spectatorState;
    unsigned int     spectatorClient;	// for chasecam and follow mode
    int              wins, losses;		// tournament stats
    qboolean         teamLeader;			// true when this client is a team leader
}
clientSession_t;

//
#define MAX_NETNAME			36
#define	MAX_VOTE_COUNT		3

// client data that stays across multiple respawns, but is cleared
// on each level change or team change at ClientBegin()
typedef struct
{
    clientConnected_t	connected;
    usercmd_t	cmd;				// we would lose angles if not persistant
    qboolean	localClient;		// true if "ip" info key is "localhost"
    qboolean	initialSpawn;		// the first spawn should be at a cool location
    qboolean	predictItemPickup;	// based on cg_predictItems userinfo
    qboolean	pmoveFixed;			//
    char		netname[MAX_NETNAME];
    int			maxHealth;			// for handicapping
    int			enterTime;			// level.time the client entered the game
    playerTeamState_t teamState;	// status in teamplay games
    int			voteCount;			// to prevent people from constantly calling votes
    int			teamVoteCount;		// to prevent people from constantly calling votes
    qboolean	teamInfo;			// send team overlay updates?
}
clientPersistant_t;


// this structure is cleared on each ClientSpawn(),
// except for 'client->pers' and 'client->sess'
struct gclient_s
{
    // ps MUST be the first element, because the server expects it
    playerState_t	ps;				// communicated by server to clients

    // the rest of the structure is private to game
    clientPersistant_t	pers;
    clientSession_t		sess;

    qboolean	readyToExit;		// wishes to leave the intermission

    qboolean	noclip;

    int			lastCmdTime;		// level.time of last usercmd_t, for EF_CONNECTION
    // we can't just use pers.lastCommand.time, because
    // of the g_sycronousclients case
    int			buttons;
    int			oldbuttons;
    int			latched_buttons;

    vec3_t		oldOrigin;

    // sum up damage over an entire frame, so
    // shotgun blasts give a single big kick
    int			damage_armor;		// damage absorbed by armor
    int			damage_blood;		// damage taken out of health
    int			damage_knockback;	// impact damage
    vec3_t		damage_from;		// origin for vector calculation
    qboolean	damage_fromWorld;	// if true, don't use the damage_from vector

    int			accurateCount;		// for "impressive" reward sound

    int			accuracy_shots;		// total number of shots
    int			accuracy_hits;		// total number of hits

    //
    int			lastkilled_client;	// last client that this client killed
    gentity_t	*lasthurt_entity;	// last client that damaged this client
    int			lasthurt_mod;		// type of damage the client did

    // timers
    int			respawnTime;		// can respawn when time > this, force after g_forcerespwan
    int			inactivityTime;		// kick players when time > this
    qboolean	inactivityWarning;	// qtrue if the five seoond warning has been given
    int			rewardTime;			// clear the EF_AWARD_IMPRESSIVE, etc when time > this

    int			airOutTime;

    int			lastKillTime;		// for multiple kill rewards

    qboolean	fireHeld;			// used for hook
    gentity_t	*hook;				// grapple hook if out

    int			switchTeamTime;		// time the player switched teams

    // timeResidual is used to handle events that happen every second
    // like health / armor countdowns and regeneration
    int			timeResidual;

#ifdef MISSIONPACK
    gentity_t	*persistantPowerup;
    int			portalID;
    int			ammoTimes[WP_NUM_WEAPONS];
    int			invulnerabilityTime;
#endif

    char		*areabits;
};


//
// this structure is cleared as each map is entered
//
#define	MAX_SPAWN_VARS			64
#define	MAX_SPAWN_VARS_CHARS	4096

typedef struct
{
    struct gclient_s *clients;		// [maxclients]

    struct gentity_s *gentities;
    unsigned         intgentitySize;
    unsigned int     num_entities;		// current number, <= MAX_GENTITIES

    int              warmupTime;			// restart match at this time

    fileHandle_t     logFile;

    // store latched cvars here that we want to get at often
    unsigned int     maxclients;

    int              framenum;
    int              time;					// in msec
    int              previousTime;			// so movers can back up when blocked

    int              startTime;				// level.time the map was started

    int              teamScores[TEAM_NUM_TEAMS];
    int              lastTeamLocationTime;		// last time of client team location update

    qboolean         newSession;				// don't use any old session data, because
    // we changed gametype

    qboolean         restarted;				// waiting for a map_restart to fire

    unsigned int     numConnectedClients;
    unsigned int     numNonSpectatorClients;	// includes connecting clients
    unsigned int     numPlayingClients;		// connected, non-spectators
    unsigned int     sortedClients[MAX_CLIENTS];		// sorted by score
    unsigned int     follow1, follow2;		// clientNums for auto-follow spectators

    int              snd_fry;				// sound index for standing in lava

    int              warmupModificationCount;	// for detecting if g_warmup is changed

    // voting state
    char		voteString[MAX_STRING_CHARS];
    char		voteDisplayString[MAX_STRING_CHARS];
    int			voteTime;				// level.time vote was called
    int			voteExecuteTime;		// time the vote is executed
    int			voteYes;
    int			voteNo;
    int			numVotingClients;		// set by CalculateRanks

    // team voting state
    char		teamVoteString[2][MAX_STRING_CHARS];
    int			teamVoteTime[2];		// level.time vote was called
    int			teamVoteYes[2];
    int			teamVoteNo[2];
    int			numteamVotingClients[2];// set by CalculateRanks

    // spawn variables
    qboolean	spawning;				// the G_Spawn*() functions are valid
    int			numSpawnVars;
    char		*spawnVars[MAX_SPAWN_VARS][2];	// key / value pairs
    int			numSpawnVarChars;
    char		spawnVarChars[MAX_SPAWN_VARS_CHARS];

    // intermission state
    int			intermissionQueued;		// intermission was qualified, but
    // wait INTERMISSION_DELAY_TIME before
    // actually going there so the last
    // frag can be watched.  Disable future
    // kills during this delay
    int			intermissiontime;		// time the intermission was started
    char		*changemap;
    qboolean	readyToExit;			// at least one client wants to exit
    int			exitTime;
    vec3_t		intermission_origin;	// also used for spectator spawns
    vec3_t		intermission_angle;

    qboolean	locationLinked;			// target_locations get linked
    gentity_t	*locationHead;			// head of the location list
    int			bodyQueIndex;			// dead bodies
    gentity_t	*bodyQue[BODY_QUEUE_SIZE];
#ifdef MISSIONPACK
    int			portalSequence;
#endif
}
level_locals_t;


//
// g_spawn.c
//
qboolean	G_SpawnString( const char *key, const char *defaultString, char **out );
// spawn string returns a temporary reference, you must CopyString() if you want to keep it
qboolean	G_SpawnFloat( const char *key, const char *defaultString, float *out );
qboolean	G_SpawnInt( const char *key, const char *defaultString, int *out );
qboolean	G_SpawnVector( const char *key, const char *defaultString, float *out );
void		G_SpawnEntitiesFromString( void );
char *G_NewString( const char *string );

//
// g_cmds.c
//
void Cmd_Score_f (gentity_t *ent);
void StopFollowing( gentity_t *ent );
void BroadcastTeamChange( gclient_t *client, int oldTeam );
void SetTeam( gentity_t *ent, char *s );
void Cmd_FollowCycle_f( gentity_t *ent, int dir );

//
// g_items.c
//
void G_CheckTeamItems( void );
void G_RunItem( gentity_t *ent );
void RespawnItem( gentity_t *ent );

void UseHoldableItem( gentity_t *ent );
void PrecacheItem (gitem_t *it);
gentity_t *Drop_Item( gentity_t *ent, gitem_t *item, float angle );
gentity_t *LaunchItem( gitem_t *item, vec3_t origin, vec3_t velocity );
void SetRespawn (gentity_t *ent, float delay);
void G_SpawnItem (gentity_t *ent, gitem_t *item);
void FinishSpawningItem( gentity_t *ent );
void Think_Weapon (gentity_t *ent);
int ArmorIndex (gentity_t *ent);
void	Add_Ammo (gentity_t *ent, int weapon, int count);
void Touch_Item (gentity_t *ent, gentity_t *other, trace_t *trace);

void ClearRegisteredItems( void );
void RegisterItem( gitem_t *item );
void SaveRegisteredItems( void );

//
// g_utils.c
//
int G_ModelIndex( char *name );
int		G_SoundIndex( char *name );
void	G_TeamCommand( team_t team, char *cmd );
void	G_KillBox (gentity_t *ent);
gentity_t *G_Find (gentity_t *from, int fieldofs, const char *match);
gentity_t *G_PickTarget (char *targetname);
void	G_UseTargets (gentity_t *ent, gentity_t *activator);
void	G_SetMovedir ( vec3_t angles, vec3_t movedir);

void	G_InitGentity( gentity_t *e );
gentity_t	*G_Spawn (void);
gentity_t *G_TempEntity( vec3_t origin, int event );
void	G_Sound( gentity_t *ent, int channel, int soundIndex );
void	G_FreeEntity( gentity_t *e );
qboolean	G_EntitiesFree( void );

void	G_TouchTriggers (gentity_t *ent);
void	G_TouchSolids (gentity_t *ent);

float	*tv (float x, float y, float z);
char	*vtos( const vec3_t v );

float vectoyaw( const vec3_t vec );

void G_AddPredictableEvent( gentity_t *ent, int event, int eventParm );
void G_AddEvent( gentity_t *ent, int event, int eventParm );
void G_SetOrigin( gentity_t *ent, vec3_t origin );
void AddRemap(const char *oldShader, const char *newShader, float timeOffset);
const char *BuildShaderStateConfig(void);

//
// g_combat.c
//
qboolean CanDamage (gentity_t *targ, vec3_t origin);
void G_Damage (gentity_t *targ, gentity_t *inflictor, gentity_t *attacker, vec3_t dir, vec3_t point, int damage, int dflags, int mod);
qboolean G_RadiusDamage (vec3_t origin, gentity_t *attacker, float damage, float radius, gentity_t *ignore, int mod);
int G_InvulnerabilityEffect( gentity_t *targ, vec3_t dir, vec3_t point, vec3_t impactpoint, vec3_t bouncedir );
void body_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath );
void TossClientItems( gentity_t *self );
#ifdef MISSIONPACK
void TossClientPersistantPowerups( gentity_t *self );
#endif
void TossClientCubes( gentity_t *self );

// damage flags
#define DAMAGE_RADIUS				0x00000001	// damage was indirect
#define DAMAGE_NO_ARMOR				0x00000002	// armour does not protect from this damage
#define DAMAGE_NO_KNOCKBACK			0x00000004	// do not affect velocity, just view angles
#define DAMAGE_NO_PROTECTION		0x00000008  // armor, shields, invulnerability, and godmode have no effect
#ifdef MISSIONPACK
#define DAMAGE_NO_TEAM_PROTECTION	0x00000010  // armor, shields, invulnerability, and godmode have no effect
#endif

//
// g_missile.c
//
void G_RunMissile( gentity_t *ent );

gentity_t *fire_blaster (gentity_t *self, vec3_t start, vec3_t aimdir);
gentity_t *fire_plasma (gentity_t *self, vec3_t start, vec3_t aimdir);
gentity_t *fire_grenade (gentity_t *self, vec3_t start, vec3_t aimdir);
gentity_t *fire_rocket (gentity_t *self, vec3_t start, vec3_t dir);
gentity_t *fire_bfg (gentity_t *self, vec3_t start, vec3_t dir);
gentity_t *fire_grapple (gentity_t *self, vec3_t start, vec3_t dir);
#ifdef MISSIONPACK
gentity_t *fire_nail( gentity_t *self, vec3_t start, vec3_t forward, vec3_t right, vec3_t up );
gentity_t *fire_prox( gentity_t *self, vec3_t start, vec3_t aimdir );
#endif


//
// g_mover.c
//
void G_RunMover( gentity_t *ent );
void Touch_DoorTrigger( gentity_t *ent, gentity_t *other, trace_t *trace );

//
// g_trigger.c
//
void trigger_teleporter_touch (gentity_t *self, gentity_t *other, trace_t *trace );


//
// g_misc.c
//
void TeleportPlayer( gentity_t *player, vec3_t origin, vec3_t angles );
#ifdef MISSIONPACK
void DropPortalSource( gentity_t *ent );
void DropPortalDestination( gentity_t *ent );
#endif


//
// g_weapon.c
//
qboolean LogAccuracyHit( gentity_t *target, gentity_t *attacker );
void CalcMuzzlePoint ( gentity_t *ent, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint );
void SnapVectorTowards( vec3_t v, vec3_t to );
qboolean CheckGauntletAttack( gentity_t *ent );
void Weapon_HookFree (gentity_t *ent);
void Weapon_HookThink (gentity_t *ent);


//
// g_client.c
//
unsigned int TeamCount(unsigned int ignoreClientNum, team_t team );
unsigned int TeamLeader(team_t team);
team_t PickTeam(unsigned int ignoreClientNum);
void SetClientViewAngle( gentity_t *ent, vec3_t angle );
gentity_t *SelectSpawnPoint ( vec3_t avoidPoint, vec3_t origin, vec3_t angles );
void CopyToBodyQue( gentity_t *ent );
void respawn (gentity_t *ent);
void BeginIntermission (void);
void InitClientPersistant (gclient_t *client);
void InitClientResp (gclient_t *client);
void InitBodyQue (void);
void ClientSpawn( gentity_t *ent );
void player_die (gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod);
void AddScore( gentity_t *ent, vec3_t origin, int score );
void CalculateRanks( void );
qboolean SpotWouldTelefrag( gentity_t *spot );

//
// g_svcmds.c
//
qboolean	ConsoleCommand( void );
void G_ProcessIPBans(void);
qboolean G_FilterPacket (char *from);

//
// g_weapon.c
//
void FireWeapon( gentity_t *ent, qboolean alt);

//
// p_hud.c
//
void MoveClientToIntermission (gentity_t *client);
void G_SetStats (gentity_t *ent);
void DeathmatchScoreboardMessage (gentity_t *client);

//
// g_cmds.c
//

//
// g_pweapon.c
//


//
// g_main.c
//
void FindIntermissionPoint( void );
void SetLeader(int team, int client);
void CheckTeamLeader( int team );
void G_RunThink (gentity_t *ent);
void QDECL G_LogPrintf( const char *fmt, ... );
void SendScoreboardMessageToAllClients( void );
void QDECL G_Printf( const char *fmt, ... );
void QDECL G_Error( const char *fmt, ... );

//
// g_client.c
//
char *ClientConnect( unsigned int clientNum, qboolean firstTime, qboolean isBot );
void ClientUserinfoChanged( unsigned int clientNum );
void ClientDisconnect( unsigned int clientNum );
void ClientBegin( unsigned int clientNum );
void ClientCommand( unsigned int clientNum );

//
// g_active.c
//
void ClientThink(unsigned int clientNum );
void ClientEndFrame( gentity_t *ent );
void G_RunClient( gentity_t *ent );

//
// g_team.c
//
qboolean OnSameTeam( gentity_t *ent1, gentity_t *ent2 );
void Team_CheckDroppedItem( gentity_t *dropped );
qboolean CheckObeliskAttack( gentity_t *obelisk, gentity_t *attacker );

//
// g_mem.c
//
void *G_Alloc( int size );
void G_InitMemory( void );
void Svcmd_GameMem_f( void );

//
// g_session.c
//
void G_ReadSessionData( gclient_t *client );
void G_InitSessionData( gclient_t *client, char *userinfo );

void G_InitWorldSession( void );
void G_WriteSessionData( void );

//
// g_arenas.c
//
void UpdateTournamentInfo( void );
void SpawnModelsOnVictoryPads( void );
void Svcmd_AbortPodium_f( void );

//
// g_bot.c
//
void G_InitBots( qboolean restart );
char *G_GetBotInfoByNumber( int num );
char *G_GetBotInfoByName( const char *name );
void G_CheckBotSpawn( void );
void G_RemoveQueuedBotBegin( int clientNum );
qboolean G_BotConnect( int clientNum, qboolean restart );
void Svcmd_AddBot_f( void );
void Svcmd_BotList_f( void );
void BotInterbreedEndMatch( void );

// ai_main.c
#define MAX_FILEPATH			144

//bot settings
typedef struct bot_settings_s
{
    char characterfile[MAX_FILEPATH];
    float skill;
    char team[MAX_FILEPATH];
}
bot_settings_t;

int BotAISetup( int restart );
int BotAIShutdown( int restart );
int BotAILoadMap( int restart );
int BotAISetupClient(int client, struct bot_settings_s *settings, qboolean restart);
int BotAIShutdownClient( int client, qboolean restart );
int BotAIStartFrame( int time );
void BotTestAAS(vec3_t origin);

#include "g_team.h" // teamplay specific stuff


extern	level_locals_t	level;
extern	gentity_t		g_entities[MAX_GENTITIES];

#define	FOFS(x) ((int)&(((gentity_t *)0)->x))

extern	cvar_t	*g_gametype;
extern	cvar_t	*g_dedicated;
extern	cvar_t	*g_cheats;
extern	cvar_t	*g_maxclients;			// allow this many total, including spectators
extern	cvar_t	*g_maxGameClients;		// allow this many active
extern	cvar_t	*g_restarted;

extern	cvar_t	*g_dmflags;
extern	cvar_t	*g_fraglimit;
extern	cvar_t	*g_timelimit;
extern	cvar_t	*g_capturelimit;
extern	cvar_t	*g_friendlyFire;
extern	cvar_t	*g_password;
extern	cvar_t	*g_needpass;
extern	cvar_t	*g_gravity;
extern	cvar_t	*g_speed;
extern	cvar_t	*g_knockback;
extern	cvar_t	*g_quadfactor;
extern	cvar_t	*g_forcerespawn;
extern	cvar_t	*g_inactivity;
extern	cvar_t	*g_debugMove;
extern	cvar_t	*g_debugAlloc;
extern	cvar_t	*g_debugDamage;
extern	cvar_t	*g_weaponRespawn;
extern	cvar_t	*g_weaponTeamRespawn;
extern	cvar_t	*g_synchronousClients;
extern	cvar_t	*g_motd;
extern	cvar_t	*g_warmup;
extern	cvar_t	*g_doWarmup;
extern	cvar_t	*g_blood;
extern	cvar_t	*g_allowVote;
extern	cvar_t	*g_teamAutoJoin;
extern	cvar_t	*g_teamForceBalance;
extern	cvar_t	*g_banIPs;
extern	cvar_t	*g_filterBan;
extern	cvar_t	*g_obeliskHealth;
extern	cvar_t	*g_obeliskRegenPeriod;
extern	cvar_t	*g_obeliskRegenAmount;
extern	cvar_t	*g_obeliskRespawnDelay;
extern	cvar_t	*g_cubeTimeout;
extern	cvar_t	*g_redteam;
extern	cvar_t	*g_blueteam;
extern	cvar_t	*g_smoothClients;
extern	cvar_t	*pmove_fixed;
extern	cvar_t	*pmove_msec;
extern	cvar_t	*g_rankings;
extern	cvar_t	*g_enableDust;
extern	cvar_t	*g_enableBreath;
extern	cvar_t	*g_singlePlayer;
extern	cvar_t	*g_proxMineTimeout;

void	Cmd_ArgvBuffer(unsigned int arg, char *buffer, unsigned int bufferLength );
void Cbuf_AddText( const char *text );
void Cvar_Set( const char *var_name, const char *value);
void CL_AddReliableCommand( const char *cmd );
void	Cmd_ArgsBuffer( char *buffer, unsigned int bufferLength );
void Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );
void CL_AddCgameCommand( const char *cmdName );
void RE_ClearScene( void );
void R_ModelBounds( qhandle_t handle, vec3_t mins, vec3_t maxs );
void	RE_SetColor( const float *rgba );
int Sys_Milliseconds (void);
qhandle_t RE_RegisterShader(const char *name);
void S_StartLocalSound( sfxHandle_t sfxHandle, int channelNum );
int CL_GetCurrentCmdNumber( void );
qboolean CL_GetUserCmd( int cmdNumber, usercmd_t *ucmd );
void RE_StretchPic ( float x, float y, float w, float h,
                     float s1, float t1, float s2, float t2, qhandle_t hShader );
int CM_PointContents( const vec3_t p, clipHandle_t model );
int R_LerpTag( orientation_t *tag, qhandle_t handle, int startFrame, int endFrame,
               float frac, const char *tagName );
void S_UpdateEntityPosition( int entityNum, const vec3_t origin );
void S_AddLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfxHandle );
void S_AddRealLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfxHandle );
void RE_AddLightToScene( const vec3_t org, float intensity, float r, float g, float b );
void S_StartSound(vec3_t origin, int entityNum, int entchannel, sfxHandle_t sfxHandle );
sfxHandle_t	S_RegisterSound( const char *name, qboolean compressed );
void S_StopLoopingSound(int entityNum);
void SCR_UpdateScreen( void );
qhandle_t RE_RegisterShaderNoMip(const char *name);
void RE_LoadWorldMap( const char *name );
qhandle_t RE_RegisterModel( const char *name );
int		CM_NumInlineModels( void );
void S_StartBackgroundTrack( const char *intro, const char *loop );
qboolean CL_GetUserCmd( int cmdNumber, usercmd_t *ucmd );
void CL_GetGameState( gameState_t *gs );
void CL_CM_LoadMap( const char *mapname );
void S_ClearLoopingSounds( qboolean killall );
int R_MarkFragments(int numPoints, const vec3_t *points, const vec3_t projection, int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t *fragmentBuffer);
int		FS_FOpenFileByMode( const char *qpath, fileHandle_t *f, fsMode_t mode );
int FS_Read2( void *buffer, int len, fileHandle_t f );
void FS_FCloseFile( fileHandle_t f );
qhandle_t RE_RegisterSkin( const char *name );
int	Hunk_MemoryRemaining( void );
void CM_BoxTrace(trace_t *results, const vec3_t start, const vec3_t end, vec3_t mins, vec3_t maxs, clipHandle_t model, int brushmask, int capsule);
int R_LightForPoint( vec3_t point, vec3_t ambientLight, vec3_t directedLight, vec3_t lightDir );
clipHandle_t	CM_InlineModel( int index );
clipHandle_t CM_TempBoxModel( const vec3_t mins, const vec3_t maxs, int capsule );
void CM_TransformedBoxTrace(trace_t *results, const vec3_t start, const vec3_t end, vec3_t mins, vec3_t maxs, clipHandle_t model, int brushmask, const vec3_t origin, const vec3_t angles, int capsule);
int	CM_TransformedPointContents( const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles);
void R_RemapShader(const char *shaderName, const char *newShaderName, const char *timeOffset);
unsigned int		Cmd_Argc( void );
qboolean CL_GetServerCommand( int serverCommandNumber );
void	CL_GetCurrentSnapshotNumber( int *snapshotNumber, int *serverTime );
void S_Respatialize(unsigned int entityNum, const vec3_t head, vec3_t axis[3], int inwater );
void CL_SetUserCmdValue( int userCmdValue, float sensitivityScale );
int Cvar_VariableIntegerValue( const char *var_name );
void SV_SetConfigstring (int index, const char *val);
void SV_GetServerinfo( char *buffer, int bufferSize );
int SV_PointContents( const vec3_t p, int passEntityNum );
void SV_GetUserinfo( int index, char *buffer, int bufferSize );
int SV_BotGetSnapshotEntity(unsigned int client, unsigned int sequence );
int SV_BotGetConsoleMessage(unsigned int client, char *buf, unsigned int size );
void SV_ClientThink (client_t *cl, usercmd_t *cmd);
void SV_AdjustAreaPortalState( gentity_t *ent, qboolean open );
void SV_SetBrushModel( gentity_t *ent, const char *name );
qboolean	SV_EntityContact( vec3_t mins, vec3_t maxs, const gentity_t *gEnt, int capsule );
void SV_GameDropClient( int clientNum, const char *reason );
void SV_GameSendServerCommand( int clientNum, const char *text );
void Cbuf_AddText( const char *text );
void SV_GetUsercmd( int clientNum, usercmd_t *cmd );
void SV_LocateGameData( gentity_t *gEnts, int numGEntities, playerState_t *clients, int sizeofGameClient );
qboolean GetEntityToken(char *buffer, int buffersize);
