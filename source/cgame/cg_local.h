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
#include "../game/q_shared.h"
#include "tr_types.h"
#include "../game/bg_public.h"
#include "cg_public.h"


// The entire cgame module is unloaded and reloaded on each level change,
// so there is NO persistant data between levels on the client side.
// If you absolutely need something stored, it can either be kept
// by the server in the server stored userinfos, or stashed in a cvar.

#ifdef MISSIONPACK
#define CG_FONT_THRESHOLD 0.1
#endif

#define	POWERUP_BLINKS		5

#define	POWERUP_BLINK_TIME	1000
#define	FADE_TIME			200
#define	PULSE_TIME			200
#define	DAMAGE_DEFLECT_TIME	100
#define	DAMAGE_RETURN_TIME	400
#define DAMAGE_TIME			500
#define	LAND_DEFLECT_TIME	150
#define	LAND_RETURN_TIME	300
#define	STEP_TIME			200
#define	DUCK_TIME			100
#define	PAIN_TWITCH_TIME	200
#define	WEAPON_SELECT_TIME	1400
#define	ITEM_SCALEUP_TIME	1000
#define	ZOOM_TIME			150
#define	ITEM_BLOB_TIME		200
#define	MUZZLE_FLASH_TIME	20
#define	SINK_TIME			1000		// time for fragments to sink into ground before going away
#define	ATTACKER_HEAD_TIME	10000
#define	REWARD_TIME			3000

#define	PULSE_SCALE			1.5			// amount to scale up the icons when activating

#define	MAX_STEP_CHANGE		32

#define	MAX_VERTS_ON_POLY	10
#define	MAX_MARK_POLYS		256

#define STAT_MINUS			10	// num frame for '-' stats digit

#define	ICON_SIZE			48
#define	CHAR_WIDTH			32
#define	CHAR_HEIGHT			48
#define	TEXT_ICON_SPACE		4

#define	TEAMCHAT_WIDTH		80
#define TEAMCHAT_HEIGHT		8

// very large characters
#define	GIANT_WIDTH			32
#define	GIANT_HEIGHT		48

#define	NUM_CROSSHAIRS		10

#define TEAM_OVERLAY_MAXNAME_WIDTH	12
#define TEAM_OVERLAY_MAXLOCATION_WIDTH	16

#define	DEFAULT_MODEL			"default"
#ifdef MISSIONPACK
#define	DEFAULT_TEAM_MODEL		"james"
#define	DEFAULT_TEAM_HEAD		"*james"
#else
#define	DEFAULT_TEAM_MODEL		"sarge"
#define	DEFAULT_TEAM_HEAD		"sarge"
#endif

#define DEFAULT_REDTEAM_NAME		"Stroggs"
#define DEFAULT_BLUETEAM_NAME		"Pagans"

typedef enum {
    FOOTSTEP_NORMAL,
    FOOTSTEP_BOOT,
    FOOTSTEP_FLESH,
    FOOTSTEP_MECH,
    FOOTSTEP_ENERGY,
    FOOTSTEP_METAL,
    FOOTSTEP_SPLASH,

    FOOTSTEP_TOTAL
} footstep_t;

typedef enum {
    IMPACTSOUND_DEFAULT,
    IMPACTSOUND_METAL,
    IMPACTSOUND_FLESH
} impactSound_t;

//=================================================

// player entities need to track more information
// than any other type of entity.

// note that not every player entity is a client entity,
// because corpses after respawn are outside the normal
// client numbering range

// when changing animation, set animationTime to frameTime + lerping time
// The current lerp will finish out, then it will lerp to the new animation
typedef struct
{
    int			oldFrame;
    int			oldFrameTime;		// time when ->oldFrame was exactly on

    int			frame;
    int			frameTime;			// time when ->frame will be exactly on

    float		backlerp;

    float		yawAngle;
    qboolean	yawing;
    float		pitchAngle;
    qboolean	pitching;

    int			animationNumber;	// may include ANIM_TOGGLEBIT
    animation_t	*animation;
    int			animationTime;		// time when the first frame of the animation will be exact
}
lerpFrame_t;


typedef struct
{
    lerpFrame_t		legs, torso, flag;
    int				painTime;
    int				painDirection;	// flip from 0 to 1
    int				lightningFiring;

    // railgun trail spawning
    vec3_t			railgunImpact;
    qboolean		railgunFlash;

    // machinegun spinning
    float			barrelAngle;
    int				barrelTime;
    qboolean		barrelSpinning;
}
playerEntity_t;

//=================================================



// centity_t have a direct corespondence with gentity_t in the game, but
// only the entityState_t is directly communicated to the cgame
typedef struct centity_s
{
    entityState_t	currentState;	// from cg.frame
    entityState_t	nextState;		// from cg.nextFrame, if available
    qboolean		interpolate;	// true if next is valid to interpolate to
    qboolean		currentValid;	// true if cg.frame holds this entity

    int				muzzleFlashTime;	// move to playerEntity?
    int				previousEvent;
    int				teleportFlag;

    int				trailTime;		// so missile trails can handle dropped initial packets
    int				dustTrailTime;
    int				miscTime;

    int				snapShotTime;	// last time this entity was found in a snapshot

    playerEntity_t	pe;

    int				errorTime;		// decay the error from this time
    vec3_t			errorOrigin;
    vec3_t			errorAngles;

    qboolean		extrapolated;	// false if origin / angles is an interpolation
    vec3_t			rawOrigin;
    vec3_t			rawAngles;

    vec3_t			beamEnd;

    // exact interpolated position of entity on this frame
    vec3_t			lerpOrigin;
    vec3_t			lerpAngles;
}
centity_t;


//======================================================================

// local entities are created as a result of events or predicted actions,
// and live independantly from all server transmitted entities

typedef struct markPoly_s
{
    struct markPoly_s	*prevMark, *nextMark;
    int			time;
    qhandle_t	markShader;
    qboolean	alphaFade;		// fade alpha instead of rgb
    float		color[4];
    poly_t		poly;
    polyVert_t	verts[MAX_VERTS_ON_POLY];
}
markPoly_t;


typedef enum {
    LE_MARK,
    LE_EXPLOSION,
    LE_SPRITE_EXPLOSION,
    LE_FRAGMENT,
    LE_MOVE_SCALE_FADE,
    LE_FALL_SCALE_FADE,
    LE_FADE_RGB,
    LE_SCALE_FADE,
    LE_SCOREPLUM,
#ifdef MISSIONPACK
    LE_KAMIKAZE,
    LE_INVULIMPACT,
    LE_INVULJUICED,
    LE_SHOWREFENTITY
#endif
} leType_t;

typedef enum {
    LEF_PUFF_DONT_SCALE  = 0x0001,			// do not scale size over time
    LEF_TUMBLE			 = 0x0002,			// tumble over time, used for ejecting shells
    LEF_SOUND1			 = 0x0004,			// sound 1 for kamikaze
    LEF_SOUND2			 = 0x0008			// sound 2 for kamikaze
} leFlag_t;

typedef enum {
    LEMT_NONE,
    LEMT_BURN,
    LEMT_BLOOD
} leMarkType_t;			// fragment local entities can leave marks on walls

typedef enum {
    LEBS_NONE,
    LEBS_BLOOD,
    LEBS_BRASS
} leBounceSoundType_t;	// fragment local entities can make sounds on impacts

typedef struct localEntity_s
{
    struct localEntity_s	*prev, *next;
    leType_t		leType;
    int				leFlags;

    int				startTime;
    int				endTime;
    int				fadeInTime;

    float			lifeRate;			// 1.0 / (endTime - startTime)

    trajectory_t	pos;
    trajectory_t	angles;

    float			bounceFactor;		// 0.0 = no bounce, 1.0 = perfect

    float			color[4];

    float			radius;

    float			light;
    vec3_t			lightColor;

    leMarkType_t		leMarkType;		// mark to leave on fragment impact
    leBounceSoundType_t	leBounceSoundType;

    refEntity_t		refEntity;
}
localEntity_t;

//======================================================================


typedef struct
{
    int				client;
    int				score;
    int				ping;
    int				time;
    int				scoreFlags;
    int				powerUps;
    int				accuracy;
    int				impressiveCount;
    int				excellentCount;
    int				guantletCount;
    int				defendCount;
    int				assistCount;
    int				captures;
    qboolean	perfect;
    int				team;
}
score_t;

// each client has an associated clientInfo_t
// that contains media references necessary to present the
// client model and other color coded effects
// this is regenerated each time a client's configstring changes,
// usually as a result of a userinfo (name, model, etc) change
#define	MAX_CUSTOM_SOUNDS	32

typedef struct
{
    qboolean		infoValid;

    char			name[MAX_QPATH];
    team_t			team;

    int				botSkill;		// 0 = not bot, 1-5 = bot

    vec3_t			color1;
    vec3_t			color2;

    int				score;			// updated by score servercmds
    int				location;		// location index for team mode
    int				health;			// you only get this info about your teammates
    int				armor;
    int				curWeapon;

    int				handicap;
    int				wins, losses;	// in tourney mode

    int				teamTask;		// task in teamplay (offence/defence)
    qboolean		teamLeader;		// true when this is a team leader

    int				powerups;		// so can display quad/flag status

    int				medkitUsageTime;
    int				invulnerabilityStartTime;
    int				invulnerabilityStopTime;

    int				breathPuffTime;

    // when clientinfo is changed, the loading of models/skins/sounds
    // can be deferred until you are dead, to prevent hitches in
    // gameplay
    char			modelName[MAX_QPATH];
    char			skinName[MAX_QPATH];
    char			headModelName[MAX_QPATH];
    char			headSkinName[MAX_QPATH];
    char			redTeam[MAX_TEAMNAME];
    char			blueTeam[MAX_TEAMNAME];
    qboolean		deferred;

    qboolean		newAnims;		// true if using the new mission pack animations
    qboolean		fixedlegs;		// true if legs yaw is always the same as torso yaw
    qboolean		fixedtorso;		// true if torso never changes yaw

    vec3_t			headOffset;		// move head in icon views
    footstep_t		footsteps;
    gender_t		gender;			// from model

    qhandle_t		legsModel;
    qhandle_t		legsSkin;

    qhandle_t		torsoModel;
    qhandle_t		torsoSkin;

    qhandle_t		headModel;
    qhandle_t		headSkin;

    qhandle_t		modelIcon;

    animation_t		animations[MAX_TOTALANIMATIONS];

    sfxHandle_t		sounds[MAX_CUSTOM_SOUNDS];
}
clientInfo_t;

// each IT_* item has an associated itemInfo_t
// that constains media references necessary to present the
// item and its effects
typedef struct
{
    qboolean		registered;
    qhandle_t		models[MAX_ITEM_MODELS];
    qhandle_t		icon;
}
itemInfo_t;


typedef struct
{
    int				itemNum;
}
powerupInfo_t;


#define MAX_SKULLTRAIL		10

typedef struct
{
    vec3_t positions[MAX_SKULLTRAIL];
    int numpositions;
}
skulltrail_t;


#define MAX_REWARDSTACK		10
#define MAX_SOUNDBUFFER		20

//======================================================================

// all cg.stepTime, cg.duckTime, cg.landTime, etc are set to cg.time when the action
// occurs, and they will have visible effects for #define STEP_TIME or whatever msec after

#define MAX_PREDICTED_EVENTS	16

typedef struct
{
    int			clientFrame;		// incremented each frame

    int			clientNum;

    qboolean	demoPlayback;
    qboolean	levelShot;			// taking a level menu screenshot
    int			deferredPlayerLoading;
    qboolean	loading;			// don't defer players at initial startup
    qboolean	intermissionStarted;	// don't play voice rewards, because game will end shortly

    // there are only one or two snapshot_t that are relevent at a time
    int			latestSnapshotNum;	// the number of snapshots the client system has received
    int			latestSnapshotTime;	// the time from latestSnapshotNum, so we don't need to read the snapshot yet

    snapshot_t	*snap;				// cg.snap->serverTime <= cg.time
    snapshot_t	*nextSnap;			// cg.nextSnap->serverTime > cg.time, or NULL
    snapshot_t	activeSnapshots[2];

    float		frameInterpolation;	// (float)( cg.time - cg.frame->serverTime ) / (cg.nextFrame->serverTime - cg.frame->serverTime)

    qboolean	thisFrameTeleport;
    qboolean	nextFrameTeleport;

    int			frametime;		// cg.time - cg.oldTime

    int			time;			// this is the time value that the client
    // is rendering at.
    int			oldTime;		// time at last frame, used for missile trails and prediction checking

    int			physicsTime;	// either cg.snap->time or cg.nextSnap->time

    int			timelimitWarnings;	// 5 min, 1 min, overtime
    int			fraglimitWarnings;

    qboolean	mapRestart;			// set on a map restart to set back the weapon

    qboolean	renderingThirdPerson;		// during deaths, chasecams, etc

    // prediction state
    qboolean	hyperspace;				// true if prediction has hit a trigger_teleport
    playerState_t	predictedPlayerState;
    centity_t		predictedPlayerEntity;
    qboolean	validPPS;				// clear until the first call to CG_PredictPlayerState
    int			predictedErrorTime;
    vec3_t		predictedError;

    int			eventSequence;
    int			predictableEvents[MAX_PREDICTED_EVENTS];

    float		stepChange;				// for stair up smoothing
    int			stepTime;

    float		duckChange;				// for duck viewheight smoothing
    int			duckTime;

    float		landChange;				// for landing hard
    int			landTime;

    // input state sent to server
    int			weaponSelect;

    // auto rotating items
    vec3_t		autoAngles;
    vec3_t		autoAxis[3];
    vec3_t		autoAnglesFast;
    vec3_t		autoAxisFast[3];

    // view rendering
    refdef_t	refdef;
    vec3_t		refdefViewAngles;		// will be converted to refdef.viewaxis

    // zoom key
    qboolean	zoomed;
    int			zoomTime;
    float		zoomSensitivity;

    // information screen text during loading
    char		infoScreenText[MAX_STRING_CHARS];

    // scoreboard
    int			scoresRequestTime;
    int			numScores;
    int			selectedScore;
    int			teamScores[2];
    score_t		scores[MAX_CLIENTS];
    qboolean	showScores;
    qboolean	scoreBoardShowing;
    int			scoreFadeTime;
    char		killerName[MAX_NAME_LENGTH];
    char			spectatorList[MAX_STRING_CHARS];		// list of names
    int				spectatorLen;												// length of list
    float			spectatorWidth;											// width in device units
    int				spectatorTime;											// next time to offset
    int				spectatorPaintX;										// current paint x
    int				spectatorPaintX2;										// current paint x
    int				spectatorOffset;										// current offset from start
    int				spectatorPaintLen; 									// current offset from start

    // skull trails
    skulltrail_t	skulltrails[MAX_CLIENTS];

    // centerprinting
    int			centerPrintTime;
    int			centerPrintCharWidth;
    int			centerPrintY;
    char		centerPrint[1024];
    int			centerPrintLines;

    // low ammo warning state
    int			lowAmmoWarning;		// 1 = low, 2 = empty

    // kill timers for carnage reward
    int			lastKillTime;

    // crosshair client ID
    int			crosshairClientNum;
    int			crosshairClientTime;

    // powerup active flashing
    int			powerupActive;
    int			powerupTime;

    // attacking player
    int			attackerTime;
    int			voiceTime;

    // reward medals
    int			rewardStack;
    int			rewardTime;
    int			rewardCount[MAX_REWARDSTACK];
    qhandle_t	rewardShader[MAX_REWARDSTACK];
    qhandle_t	rewardSound[MAX_REWARDSTACK];

    // sound buffer mainly for announcer sounds
    int			soundBufferIn;
    int			soundBufferOut;
    int			soundTime;
    qhandle_t	soundBuffer[MAX_SOUNDBUFFER];

    // for voice chat buffer
    int			voiceChatTime;
    int			voiceChatBufferIn;
    int			voiceChatBufferOut;

    // warmup countdown
    int			warmup;
    int			warmupCount;

    //==========================

    int			itemPickup;
    int			itemPickupTime;
    int			itemPickupBlendTime;	// the pulse around the crosshair is timed seperately

    int			weaponSelectTime;
    int			weaponAnimation;
    int			weaponAnimationTime;

    // blend blobs
    float		damageTime;
    float		damageX, damageY, damageValue;

    // status bar head
    float		headYaw;
    float		headEndPitch;
    float		headEndYaw;
    int			headEndTime;
    float		headStartPitch;
    float		headStartYaw;
    int			headStartTime;

    // view movement
    float		v_dmg_time;
    float		v_dmg_pitch;
    float		v_dmg_roll;

    vec3_t		kick_angles;	// weapon kicks
    vec3_t		kick_origin;

    // temp working variables for player view
    float		bobfracsin;
    int			bobcycle;
    float		xyspeed;
    int     nextOrbitTime;

    //qboolean cameraMode;		// if rendering from a loaded camera


    // development tool
    refEntity_t		testModelEntity;
    char			testModelName[MAX_QPATH];
    qboolean		testGun;

}
cg_t;


// all of the model, shader, and sound references that are
// loaded at gamestate time are stored in cgMedia_t
// Other media that can be tied to clients, weapons, or items are
// stored in the clientInfo_t, itemInfo_t, weaponInfo_t, and powerupInfo_t
typedef struct
{
    qhandle_t	charsetShader;
    qhandle_t	charsetProp;
    qhandle_t	charsetPropGlow;
    qhandle_t	charsetPropB;
    qhandle_t	whiteShader;

    qhandle_t	redCubeModel;
    qhandle_t	blueCubeModel;
    qhandle_t	redCubeIcon;
    qhandle_t	blueCubeIcon;
    qhandle_t	redFlagModel;
    qhandle_t	blueFlagModel;
    qhandle_t	neutralFlagModel;
    qhandle_t	redFlagShader[3];
    qhandle_t	blueFlagShader[3];
    qhandle_t	flagShader[4];

    qhandle_t	flagPoleModel;
    qhandle_t	flagFlapModel;

    qhandle_t	redFlagFlapSkin;
    qhandle_t	blueFlagFlapSkin;
    qhandle_t	neutralFlagFlapSkin;

    qhandle_t	redFlagBaseModel;
    qhandle_t	blueFlagBaseModel;
    qhandle_t	neutralFlagBaseModel;

#ifdef MISSIONPACK
    qhandle_t	overloadBaseModel;
    qhandle_t	overloadTargetModel;
    qhandle_t	overloadLightsModel;
    qhandle_t	overloadEnergyModel;

    qhandle_t	harvesterModel;
    qhandle_t	harvesterRedSkin;
    qhandle_t	harvesterBlueSkin;
    qhandle_t	harvesterNeutralModel;
#endif

    qhandle_t	armorModel;
    qhandle_t	armorIcon;

    qhandle_t	teamStatusBar;

    qhandle_t	deferShader;

    // gib explosions
    qhandle_t	gibAbdomen;
    qhandle_t	gibArm;
    qhandle_t	gibChest;
    qhandle_t	gibFist;
    qhandle_t	gibFoot;
    qhandle_t	gibForearm;
    qhandle_t	gibIntestine;
    qhandle_t	gibLeg;
    qhandle_t	gibSkull;
    qhandle_t	gibBrain;

    qhandle_t	smoke2;

    qhandle_t	machinegunBrassModel;
    qhandle_t	shotgunBrassModel;

    qhandle_t	railRingsShader;
    qhandle_t	railCoreShader;

    qhandle_t	lightningShader;

    qhandle_t	friendShader;

    qhandle_t	balloonShader;
    qhandle_t	connectionShader;

    qhandle_t	selectShader;
    qhandle_t	viewBloodShader;
    qhandle_t	tracerShader;
    qhandle_t	crosshairShader;
    qhandle_t	lagometerShader;
    qhandle_t	backTileShader;
    qhandle_t	noammoShader;

    qhandle_t	smokePuffShader;
    qhandle_t	smokePuffRageProShader;
    qhandle_t	shotgunSmokePuffShader;
    qhandle_t	plasmaBallShader;
    qhandle_t	waterBubbleShader;
    qhandle_t	bloodTrailShader;
#ifdef MISSIONPACK
    qhandle_t	nailPuffShader;
    qhandle_t	blueProxMine;
#endif

    qhandle_t	numberShaders[11];

    qhandle_t	shadowMarkShader;

    qhandle_t	botSkillShaders[5];

    // wall mark shaders
    qhandle_t	wakeMarkShader;
    qhandle_t	bloodMarkShader;
    qhandle_t	bulletMarkShader;
    qhandle_t	burnMarkShader;
    qhandle_t	holeMarkShader;
    qhandle_t	energyMarkShader;

    // powerup shaders
    qhandle_t	quadShader;
    qhandle_t	redQuadShader;
    qhandle_t	quadWeaponShader;
    qhandle_t	invisShader;
    qhandle_t	regenShader;
    qhandle_t	battleSuitShader;
    qhandle_t	battleWeaponShader;
    qhandle_t	hastePuffShader;
    qhandle_t	redKamikazeShader;
    qhandle_t	blueKamikazeShader;

    // weapon effect models
    qhandle_t	bulletFlashModel;
    qhandle_t	ringFlashModel;
    qhandle_t	dishFlashModel;
    qhandle_t	lightningExplosionModel;

    // weapon effect shaders
    qhandle_t	railExplosionShader;
    qhandle_t	plasmaExplosionShader;
    qhandle_t	bulletExplosionShader;
    qhandle_t	rocketExplosionShader;
    qhandle_t	grenadeExplosionShader;
    qhandle_t	bfgExplosionShader;
    qhandle_t	bloodExplosionShader;

    // special effects models
    qhandle_t	teleportEffectModel;
    qhandle_t	teleportEffectShader;
#ifdef MISSIONPACK
    qhandle_t	kamikazeEffectModel;
    qhandle_t	kamikazeShockWave;
    qhandle_t	kamikazeHeadModel;
    qhandle_t	kamikazeHeadTrail;
    qhandle_t	guardPowerupModel;
    qhandle_t	scoutPowerupModel;
    qhandle_t	doublerPowerupModel;
    qhandle_t	ammoRegenPowerupModel;
    qhandle_t	invulnerabilityImpactModel;
    qhandle_t	invulnerabilityJuicedModel;
    qhandle_t	medkitUsageModel;
    qhandle_t	dustPuffShader;
    qhandle_t	heartShader;
#endif
    qhandle_t	invulnerabilityPowerupModel;

    // scoreboard headers
    qhandle_t	scoreboardName;
    qhandle_t	scoreboardPing;
    qhandle_t	scoreboardScore;
    qhandle_t	scoreboardTime;

    // medals shown during gameplay
    qhandle_t	medalImpressive;
    qhandle_t	medalExcellent;
    qhandle_t	medalGauntlet;
    qhandle_t	medalDefend;
    qhandle_t	medalAssist;
    qhandle_t	medalCapture;

    // sounds
    sfxHandle_t	quadSound;
    sfxHandle_t	tracerSound;
    sfxHandle_t	selectSound;
    sfxHandle_t	useNothingSound;
    sfxHandle_t	wearOffSound;
    sfxHandle_t	footsteps[FOOTSTEP_TOTAL][4];
    sfxHandle_t	sfx_lghit1;
    sfxHandle_t	sfx_lghit2;
    sfxHandle_t	sfx_lghit3;
    sfxHandle_t	sfx_ric1;
    sfxHandle_t	sfx_ric2;
    sfxHandle_t	sfx_ric3;
    sfxHandle_t	sfx_railg;
    sfxHandle_t	sfx_rockexp;
    sfxHandle_t	sfx_plasmaexp;
#ifdef MISSIONPACK
    sfxHandle_t	sfx_proxexp;
    sfxHandle_t	sfx_nghit;
    sfxHandle_t	sfx_nghitflesh;
    sfxHandle_t	sfx_nghitmetal;
    sfxHandle_t	sfx_chghit;
    sfxHandle_t	sfx_chghitflesh;
    sfxHandle_t	sfx_chghitmetal;
    sfxHandle_t kamikazeExplodeSound;
    sfxHandle_t kamikazeImplodeSound;
    sfxHandle_t kamikazeFarSound;
    sfxHandle_t useInvulnerabilitySound;
    sfxHandle_t invulnerabilityImpactSound1;
    sfxHandle_t invulnerabilityImpactSound2;
    sfxHandle_t invulnerabilityImpactSound3;
    sfxHandle_t invulnerabilityJuicedSound;
    sfxHandle_t obeliskHitSound1;
    sfxHandle_t obeliskHitSound2;
    sfxHandle_t obeliskHitSound3;
    sfxHandle_t	obeliskRespawnSound;
    sfxHandle_t	winnerSound;
    sfxHandle_t	loserSound;
    sfxHandle_t	youSuckSound;
#endif
    sfxHandle_t	gibSound;
    sfxHandle_t	gibBounce1Sound;
    sfxHandle_t	gibBounce2Sound;
    sfxHandle_t	gibBounce3Sound;
    sfxHandle_t	teleInSound;
    sfxHandle_t	teleOutSound;
    sfxHandle_t	noAmmoSound;
    sfxHandle_t	respawnSound;
    sfxHandle_t talkSound;
    sfxHandle_t landSound;
    sfxHandle_t fallSound;
    sfxHandle_t jumpPadSound;

    sfxHandle_t oneMinuteSound;
    sfxHandle_t fiveMinuteSound;
    sfxHandle_t suddenDeathSound;

    sfxHandle_t threeFragSound;
    sfxHandle_t twoFragSound;
    sfxHandle_t oneFragSound;

    sfxHandle_t hitSound;
    sfxHandle_t hitSoundHighArmor;
    sfxHandle_t hitSoundLowArmor;
    sfxHandle_t hitTeamSound;
    sfxHandle_t impressiveSound;
    sfxHandle_t excellentSound;
    sfxHandle_t deniedSound;
    sfxHandle_t humiliationSound;
    sfxHandle_t assistSound;
    sfxHandle_t defendSound;
    sfxHandle_t firstImpressiveSound;
    sfxHandle_t firstExcellentSound;
    sfxHandle_t firstHumiliationSound;

    sfxHandle_t takenLeadSound;
    sfxHandle_t tiedLeadSound;
    sfxHandle_t lostLeadSound;

    sfxHandle_t voteNow;
    sfxHandle_t votePassed;
    sfxHandle_t voteFailed;

    sfxHandle_t watrInSound;
    sfxHandle_t watrOutSound;
    sfxHandle_t watrUnSound;

    sfxHandle_t flightSound;
    sfxHandle_t medkitSound;

    sfxHandle_t weaponHoverSound;

    // teamplay sounds
    sfxHandle_t captureAwardSound;
    sfxHandle_t redScoredSound;
    sfxHandle_t blueScoredSound;
    sfxHandle_t redLeadsSound;
    sfxHandle_t blueLeadsSound;
    sfxHandle_t teamsTiedSound;

    sfxHandle_t	captureYourTeamSound;
    sfxHandle_t	captureOpponentSound;
    sfxHandle_t	returnYourTeamSound;
    sfxHandle_t	returnOpponentSound;
    sfxHandle_t	takenYourTeamSound;
    sfxHandle_t	takenOpponentSound;

    sfxHandle_t redFlagReturnedSound;
    sfxHandle_t blueFlagReturnedSound;
    sfxHandle_t neutralFlagReturnedSound;
    sfxHandle_t	enemyTookYourFlagSound;
    sfxHandle_t	enemyTookTheFlagSound;
    sfxHandle_t yourTeamTookEnemyFlagSound;
    sfxHandle_t yourTeamTookTheFlagSound;
    sfxHandle_t	youHaveFlagSound;
    sfxHandle_t yourBaseIsUnderAttackSound;
    sfxHandle_t holyShitSound;

    // tournament sounds
    sfxHandle_t	count3Sound;
    sfxHandle_t	count2Sound;
    sfxHandle_t	count1Sound;
    sfxHandle_t	countFightSound;
    sfxHandle_t	countPrepareSound;

#ifdef MISSIONPACK
    // new stuff
    qhandle_t patrolShader;
    qhandle_t assaultShader;
    qhandle_t campShader;
    qhandle_t followShader;
    qhandle_t defendShader;
    qhandle_t teamLeaderShader;
    qhandle_t retrieveShader;
    qhandle_t escortShader;
    qhandle_t flagShaders[3];
    sfxHandle_t	countPrepareTeamSound;

    sfxHandle_t ammoregenSound;
    sfxHandle_t doublerSound;
    sfxHandle_t guardSound;
    sfxHandle_t scoutSound;
#endif
    qhandle_t cursor;
    qhandle_t selectCursor;
    qhandle_t sizeCursor;

    sfxHandle_t	regenSound;
    sfxHandle_t	protectSound;
    sfxHandle_t	n_healthSound;
    sfxHandle_t	hgrenb1aSound;
    sfxHandle_t	hgrenb2aSound;
    sfxHandle_t	wstbimplSound;
    sfxHandle_t	wstbimpmSound;
    sfxHandle_t	wstbimpdSound;
    sfxHandle_t	wstbactvSound;

}
cgMedia_t;


// The client game static (cgs) structure hold everything
// loaded or calculated from the gamestate.  It will NOT
// be cleared when a tournement restart is done, allowing
// all clients to begin playing instantly
typedef struct
{
    gameState_t		gameState;			// gamestate from server
    glconfig_t		glconfig;			// rendering configuration
    float			screenXScale;		// derived from glconfig
    float			screenYScale;
    float			screenXBias;

    int				serverCommandSequence;	// reliable command stream counter
    int				processedSnapshotNum;// the number of snapshots cgame has requested

    qboolean		localServer;		// detected on startup by checking sv_running

    // parsed from serverinfo
    gametype_t		gametype;
    int				dmflags;
    int				teamflags;
    int				fraglimit;
    int				capturelimit;
    int				timelimit;
    int				maxclients;
    char			mapname[MAX_QPATH];
    char			redTeam[MAX_QPATH];
    char			blueTeam[MAX_QPATH];

    int				voteTime;
    int				voteYes;
    int				voteNo;
    qboolean		voteModified;			// beep whenever changed
    char			voteString[MAX_STRING_TOKENS];

    int				teamVoteTime[2];
    int				teamVoteYes[2];
    int				teamVoteNo[2];
    qboolean		teamVoteModified[2];	// beep whenever changed
    char			teamVoteString[2][MAX_STRING_TOKENS];

    int				levelStartTime;

    int				scores1, scores2;		// from configstrings
    int				redflag, blueflag;		// flag status from configstrings
    int				flagStatus;

    qboolean  newHud;

    //
    // locally derived information from gamestate
    //
    qhandle_t		gameModels[MAX_MODELS];
    sfxHandle_t		gameSounds[MAX_SOUNDS];

    int				numInlineModels;
    qhandle_t		inlineDrawModel[MAX_MODELS];
    vec3_t			inlineModelMidpoints[MAX_MODELS];

    clientInfo_t	clientinfo[MAX_CLIENTS];

    // teamchat width is *3 because of embedded color codes
    char			teamChatMsgs[TEAMCHAT_HEIGHT][TEAMCHAT_WIDTH*3+1];
    int				teamChatMsgTimes[TEAMCHAT_HEIGHT];
    int				teamChatPos;
    int				teamLastChatPos;

    int cursorX;
    int cursorY;
    qboolean eventHandling;
    qboolean mouseCaptured;
    qboolean sizingHud;
    void *capturedItem;
    qhandle_t activeCursor;

    // orders
    int currentOrder;
    qboolean orderPending;
    int orderTime;
    int currentVoiceClient;
    int acceptOrderTime;
    int acceptTask;
    int acceptLeader;
    char acceptVoice[MAX_NAME_LENGTH];

    // media
    cgMedia_t		media;

}
cgs_t;

//==============================================================================

extern	cgs_t			cgs;
extern	cg_t			cg;
extern	centity_t		cg_entities[MAX_GENTITIES];
extern	itemInfo_t		cg_items[MAX_ITEMS];
extern	markPoly_t		cg_markPolys[MAX_MARK_POLYS];

extern	cvar_t		*cg_centertime;
extern	cvar_t		*cg_runpitch;
extern	cvar_t		*cg_runroll;
extern	cvar_t		*cg_bobup;
extern	cvar_t		*cg_bobpitch;
extern	cvar_t		*cg_bobroll;
extern	cvar_t		*cg_swingSpeed;
extern	cvar_t		*cg_shadows;
extern	cvar_t		*cg_gibs;
extern	cvar_t		*cg_drawTimer;
extern	cvar_t		*cg_drawFPS;
extern	cvar_t		*cg_drawSnapshot;
extern	cvar_t		*cg_draw3dIcons;
extern	cvar_t		*cg_drawIcons;
extern	cvar_t		*cg_drawAmmoWarning;
extern	cvar_t		*cg_drawCrosshair;
extern	cvar_t		*cg_drawCrosshairNames;
extern	cvar_t		*cg_drawRewards;
extern	cvar_t		*cg_drawTeamOverlay;
extern	cvar_t		*cg_teamOverlayUserinfo;
extern	cvar_t		*cg_crosshairX;
extern	cvar_t		*cg_crosshairY;
extern	cvar_t		*cg_crosshairSize;
extern	cvar_t		*cg_crosshairHealth;
extern	cvar_t		*cg_drawStatus;
extern	cvar_t		*cg_draw2D;
extern	cvar_t		*cg_animSpeed;
extern	cvar_t		*cg_debugAnim;
extern	cvar_t		*cg_debugPosition;
extern	cvar_t		*cg_debugEvents;
extern	cvar_t		*cg_railTrailTime;
extern	cvar_t		*cg_errorDecay;
extern	cvar_t		*cg_nopredict;
extern	cvar_t		*cg_noPlayerAnims;
extern	cvar_t		*cg_showmiss;
extern	cvar_t		*cg_footsteps;
extern	cvar_t		*cg_addMarks;
extern	cvar_t		*cg_brassTime;
extern	cvar_t		*cg_gun_frame;
extern	cvar_t		*cg_gun_x;
extern	cvar_t		*cg_gun_y;
extern	cvar_t		*cg_gun_z;
extern	cvar_t		*cg_drawGun;
extern	cvar_t		*cg_viewsize;
extern	cvar_t		*cg_tracerChance;
extern	cvar_t		*cg_tracerWidth;
extern	cvar_t		*cg_tracerLength;
extern	cvar_t		*cg_autoswitch;
extern	cvar_t		*cg_ignore;
extern	cvar_t		*cg_simpleItems;
extern	cvar_t		*cg_fov;
extern	cvar_t		*cg_zoomFov;
extern	cvar_t		*cg_thirdPersonRange;
extern	cvar_t		*cg_thirdPersonAngle;
extern	cvar_t		*cg_thirdPerson;
extern	cvar_t		*cg_stereoSeparation;
extern	cvar_t		*cg_lagometer;
extern	cvar_t		*cg_drawAttacker;
extern	cvar_t		*cg_synchronousClients;
extern	cvar_t		*cg_teamChatTime;
extern	cvar_t		*cg_teamChatHeight;
extern	cvar_t		*cg_stats;
extern	cvar_t 		*cg_forceModel;
extern	cvar_t 		*cg_buildScript;
extern	cvar_t		*cg_paused;
extern	cvar_t		*cg_blood;
extern	cvar_t		*cg_predictItems;
extern	cvar_t		*cg_deferPlayers;
extern	cvar_t		*cg_drawFriend;
extern	cvar_t		*cg_teamChatsOnly;
extern	cvar_t		*cg_noVoiceChats;
extern	cvar_t		*cg_noVoiceText;
extern  cvar_t		*cg_scorePlum;
extern	cvar_t		*cg_smoothClients;
extern	cvar_t		*pmove_fixed;
extern	cvar_t		*pmove_msec;
//extern	cvar_t		*cg_pmove_fixed;
extern	cvar_t		*cg_cameraOrbit;
extern	cvar_t		*cg_cameraOrbitDelay;
extern	cvar_t		*cg_timescaleFadeEnd;
extern	cvar_t		*cg_timescaleFadeSpeed;
extern	cvar_t		*cg_timescale;
extern	cvar_t		*cg_cameraMode;
extern  cvar_t		*cg_smallFont;
extern  cvar_t		*cg_bigFont;
extern	cvar_t		*cg_noTaunt;
extern	cvar_t		*cg_noProjectileTrail;
extern	cvar_t		*cg_oldRail;
extern	cvar_t		*cg_oldRocket;
extern	cvar_t		*cg_oldPlasma;
extern	cvar_t		*cg_trueLightning;
#ifdef MISSIONPACK
extern	cvar_t		*cg_redTeamName;
extern	cvar_t		*cg_blueTeamName;
extern	cvar_t		*cg_currentSelectedPlayer;
extern	cvar_t		*cg_currentSelectedPlayerName;
extern	cvar_t		*cg_singlePlayer;
extern	cvar_t		*cg_enableDust;
extern	cvar_t		*cg_enableBreath;
extern	cvar_t		*cg_singlePlayerActive;
extern  cvar_t		*cg_recordSPDemo;
extern  cvar_t		*cg_recordSPDemoName;
extern	cvar_t		*cg_obeliskRespawnDelay;
#endif

//
// cg_main.c
//
const char *CG_ConfigString( int index );
const char *CG_Argv( int arg );

void QDECL CG_Printf( const char *msg, ... );
void QDECL CG_Error( const char *msg, ... );

void CG_StartMusic( void );

void CG_UpdateCvars( void );

int CG_CrosshairPlayer( void );
int CG_LastAttacker( void );
void CG_LoadMenus(const char *menuFile);
//void CG_KeyEvent(int key, qboolean down);
//void CG_MouseEvent(int x, int y);
void CG_EventHandling(int type);
void CG_RankRunFrame( void );
void CG_SetScoreSelection(void *menu);
score_t *CG_GetSelectedScore(void);
void CG_BuildSpectatorString(void);


//
// cg_view.c
//
void CG_TestModel_f (void);
void CG_TestGun_f (void);
void CG_TestModelNextFrame_f (void);
void CG_TestModelPrevFrame_f (void);
void CG_TestModelNextSkin_f (void);
void CG_TestModelPrevSkin_f (void);
void CG_ZoomDown_f( void );
void CG_ZoomUp_f( void );
void CG_AddBufferedSound( sfxHandle_t sfx);

void CG_DrawActiveFrame( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback );


//
// cg_drawtools.c
//
void CG_AdjustFrom640( float *x, float *y, float *w, float *h );
void CG_FillRect( float x, float y, float width, float height, const float *color );
void CG_DrawPic( float x, float y, float width, float height, qhandle_t hShader );
void CG_DrawString( float x, float y, const char *string,
                    float charWidth, float charHeight, const float *modulate );


void CG_DrawStringExt( int x, int y, const char *string, const float *setColor,
                       qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars );
void CG_DrawBigString( int x, int y, const char *s, float alpha );
void CG_DrawBigStringColor( int x, int y, const char *s, vec4_t color );
void CG_DrawSmallString( int x, int y, const char *s, float alpha );
void CG_DrawSmallStringColor( int x, int y, const char *s, vec4_t color );

int CG_DrawStrlen( const char *str );

float	*CG_FadeColor( int startMsec, int totalMsec );
float *CG_TeamColor( int team );
void CG_TileClear( void );
void CG_ColorForHealth( vec4_t hcolor );
void CG_GetColorForHealth( int health, int armor, vec4_t hcolor );

void UI_DrawProportionalString( int x, int y, const char* str, int style, vec4_t color );
void CG_DrawRect( float x, float y, float width, float height, float size, const float *color );
void CG_DrawSides(float x, float y, float w, float h, float size);
void CG_DrawTopBottom(float x, float y, float w, float h, float size);


//
// cg_draw.c, cg_newDraw.c
//
extern	int sortedTeamPlayers[TEAM_MAXOVERLAY];
extern	int	numSortedTeamPlayers;
extern	int drawTeamOverlayModificationCount;
extern  char systemChat[256];
extern  char teamChat1[256];
extern  char teamChat2[256];

void CG_AddLagometerFrameInfo( void );
void CG_AddLagometerSnapshotInfo( snapshot_t *snap );
void CG_CenterPrint( const char *str, int y, int charWidth );
void CG_DrawHead( float x, float y, float w, float h, int clientNum, vec3_t headAngles );
void CG_DrawActive( stereoFrame_t stereoView );
void CG_DrawFlagModel( float x, float y, float w, float h, int team, qboolean force2D );
void CG_DrawTeamBackground( int x, int y, int w, int h, float alpha, int team );
void CG_OwnerDraw(float x, float y, float w, float h, float text_x, float text_y, int ownerDraw, int ownerDrawFlags, int align, float special, float scale, vec4_t color, qhandle_t shader, int textStyle);
void CG_Text_Paint(float x, float y, float scale, vec4_t color, const char *text, float adjust, int limit, int style);
int CG_Text_Width(const char *text, float scale, int limit);
int CG_Text_Height(const char *text, float scale, int limit);
void CG_SelectPrevPlayer(void);
void CG_SelectNextPlayer(void);
float CG_GetValue(int ownerDraw);
qboolean CG_OwnerDrawVisible(int flags);
void CG_RunMenuScript(char **args);
void CG_ShowResponseHead(void);
void CG_SetPrintString(int type, const char *p);
void CG_InitTeamChat(void);
void CG_GetTeamColor(vec4_t *color);
const char *CG_GetGameStatusText(void);
const char *CG_GetKillerText(void);
void CG_Draw3DModel( float x, float y, float w, float h, qhandle_t model, qhandle_t skin, vec3_t origin, vec3_t angles );
void CG_Text_PaintChar(float x, float y, float width, float height, float scale, float s, float t, float s2, float t2, qhandle_t hShader);
void CG_CheckOrderPending(void);
const char *CG_GameTypeString(void);
qboolean CG_YourTeamHasFlag(void);
qboolean CG_OtherTeamHasFlag(void);
qhandle_t CG_StatusHandle(int task);



//
// cg_player.c
//
void CG_Player( centity_t *cent );
void CG_ResetPlayerEntity( centity_t *cent );
void CG_AddRefEntityWithPowerups( refEntity_t *ent, entityState_t *state, int team );
void CG_NewClientInfo( int clientNum );
sfxHandle_t	CG_CustomSound( int clientNum, const char *soundName );

//
// cg_predict.c
//
void CG_BuildSolidList( void );
int	CG_PointContents( const vec3_t point, int passEntityNum );
void CG_Trace( trace_t *result, const vec3_t start, vec3_t mins, vec3_t maxs, const vec3_t end,
               int skipNumber, int mask );
void CG_PredictPlayerState( void );
void CG_LoadDeferredPlayers( void );


//
// cg_events.c
//
void CG_CheckEvents( centity_t *cent );
const char	*CG_PlaceString( int rank );
void CG_EntityEvent( centity_t *cent, vec3_t position );
void CG_PainEvent( centity_t *cent, int health );


//
// cg_ents.c
//
void CG_SetEntitySoundPosition( centity_t *cent );
void CG_AddPacketEntities( void );
void CG_Beam( centity_t *cent );
void CG_AdjustPositionForMover( const vec3_t in, int moverNum, int fromTime, int toTime, vec3_t out );

void CG_PositionEntityOnTag( refEntity_t *entity, const refEntity_t *parent,
                             qhandle_t parentModel, char *tagName );
void CG_PositionRotatedEntityOnTag( refEntity_t *entity, const refEntity_t *parent,
                                    qhandle_t parentModel, char *tagName );



//
// cg_weapons.c
//
void CG_NextWeapon_f( void );
void CG_PrevWeapon_f( void );
//void CG_Weapon_f( void );

void CG_RegisterWeapon( int weaponNum );
void CG_RegisterItemVisuals( int itemNum );

void CG_FireWeapon( centity_t *cent );
void CG_MissileHitWall( int weapon, int clientNum, vec3_t origin, vec3_t dir, impactSound_t soundType );
void CG_MissileHitPlayer( int weapon, vec3_t origin, vec3_t dir, int entityNum );
void CG_ShotgunFire( entityState_t *es );
void CG_Bullet( vec3_t origin, int sourceEntityNum, vec3_t normal, qboolean flesh, int fleshEntityNum );

void CG_RailTrail( clientInfo_t *ci, vec3_t start, vec3_t end );
//void CG_GrappleTrail(centity_t *ent, const weaponInfo_t *wi );
void CG_AddViewWeapon (playerState_t *ps);
void CG_AddPlayerWeapon( refEntity_t *parent, playerState_t *ps, centity_t *cent, int team );
void CG_DrawWeaponSelect( void );

//void CG_OutOfAmmoChange( void );	// should this be in pmove?

//
// cg_marks.c
//
void	CG_InitMarkPolys( void );
void	CG_AddMarks( void );
void	CG_ImpactMark( qhandle_t markShader,
                    const vec3_t origin, const vec3_t dir,
                    float orientation,
                    float r, float g, float b, float a,
                    qboolean alphaFade,
                    float radius, qboolean temporary );

//
// cg_localents.c
//
void	CG_InitLocalEntities( void );
localEntity_t	*CG_AllocLocalEntity( void );
void	CG_AddLocalEntities( void );

//
// cg_effects.c
//
localEntity_t *CG_SmokePuff( const vec3_t p,
                             const vec3_t vel,
                             float radius,
                             float r, float g, float b, float a,
                             float duration,
                             int startTime,
                             int fadeInTime,
                             int leFlags,
                             qhandle_t hShader );
void CG_BubbleTrail( vec3_t start, vec3_t end, float spacing );
void CG_SpawnEffect( vec3_t org );
#ifdef MISSIONPACK
void CG_KamikazeEffect( vec3_t org );
void CG_ObeliskExplode( vec3_t org, int entityNum );
void CG_ObeliskPain( vec3_t org );
void CG_InvulnerabilityImpact( vec3_t org, vec3_t angles );
void CG_InvulnerabilityJuiced( vec3_t org );
void CG_LightningBoltBeam( vec3_t start, vec3_t end );
#endif
void CG_ScorePlum( int client, vec3_t org, int score );

void CG_GibPlayer( vec3_t playerOrigin );
void CG_BigExplode( vec3_t playerOrigin );

void CG_Bleed( vec3_t origin, int entityNum );

localEntity_t *CG_MakeExplosion( vec3_t origin, vec3_t dir,
                                 qhandle_t hModel, qhandle_t shader, int msec,
                                 qboolean isSprite );

//
// cg_snapshot.c
//
void CG_ProcessSnapshots( void );

//
// cg_info.c
//
void CG_LoadingString( const char *s );
void CG_LoadingItem( int itemNum );
void CG_LoadingClient( int clientNum );
void CG_DrawInformation( void );

//
// cg_scoreboard.c
//
qboolean CG_DrawOldScoreboard( void );
void CG_DrawOldTourneyScoreboard( void );

//
// cg_consolecmds.c
//
qboolean CG_ConsoleCommand( void );
void CG_InitConsoleCommands( void );

//
// cg_servercmds.c
//
void CG_ExecuteNewServerCommands( int latestSequence );
void CG_ParseServerinfo( void );
void CG_SetConfigValues( void );
void CG_LoadVoiceChats( void );
void CG_ShaderStateChanged(void);
void CG_VoiceChatLocal( int mode, qboolean voiceOnly, int clientNum, int color, const char *cmd );
void CG_PlayBufferedVoiceChats( void );

//
// cg_playerstate.c
//
void CG_Respawn( void );
void CG_TransitionPlayerState( playerState_t *ps, playerState_t *ops );
void CG_CheckChangedPredictableEvents( playerState_t *ps );


//===============================================

typedef enum {
    SYSTEM_PRINT,
    CHAT_PRINT,
    TEAMCHAT_PRINT
} q3print_t; // bk001201 - warning: useless keyword or type name in empty declaration

void	CG_ClearParticles (void);
void	CG_AddParticles (void);
void	CG_ParticleSnow (qhandle_t pshader, vec3_t origin, vec3_t origin2, int turb, float range, int snum);
void	CG_ParticleSmoke (qhandle_t pshader, centity_t *cent);
void	CG_AddParticleShrapnel (localEntity_t *le);
void	CG_ParticleSnowFlurry (qhandle_t pshader, centity_t *cent);
void	CG_ParticleBulletDebris (vec3_t	org, vec3_t vel, int duration);
void	CG_ParticleSparks (vec3_t org, vec3_t vel, int duration, float x, float y, float speed);
void	CG_ParticleDust (centity_t *cent, vec3_t origin, vec3_t dir);
void	CG_ParticleMisc (qhandle_t pshader, vec3_t origin, int size, int duration, float alpha);
void	CG_ParticleExplosion (char *animStr, vec3_t origin, vec3_t vel, int duration, int sizeStart, int sizeEnd);
extern qboolean		initparticles;
int CG_NewParticleArea ( int num );

void	Cmd_ArgvBuffer( unsigned int arg, char *buffer, unsigned int bufferLength );
void Cbuf_AddText( const char *text );
void Cvar_Set( const char *var_name, const char *value);
void CL_AddReliableCommand( const char *cmd );
void	Cmd_ArgsBuffer( char *buffer, unsigned int bufferLength );
void Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );
void CL_AddCgameCommand( const char *cmdName );
void RE_ClearScene( void );
void RE_AddRefEntityToScene( const refEntity_t *ent );
void RE_RenderScene( const refdef_t *fd );
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
void CL_GetGlconfig( glconfig_t *glconfig );
void S_ClearLoopingSounds( qboolean killall );
int R_MarkFragments(int numPoints, const vec3_t *points, const vec3_t projection, int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t *fragmentBuffer);
void RE_AddPolyToScene( qhandle_t hShader, int numVerts, const polyVert_t *verts, int numPolys );
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
unsigned int Cmd_Argc( void );
qboolean CL_GetServerCommand( int serverCommandNumber );
qboolean	CL_GetSnapshot( int snapshotNumber, snapshot_t *snapshot );
void	CL_GetCurrentSnapshotNumber( int *snapshotNumber, int *serverTime );
void S_Respatialize( unsigned int entityNum, const vec3_t head, vec3_t axis[3], int inwater );
void CL_SetUserCmdValue( int userCmdValue, float sensitivityScale );

void clFireWeapon(centity_t *ent, qboolean alt);
qhandle_t clAmmoIcon(centity_t *ent);
qhandle_t clAmmoModel(centity_t *ent);
