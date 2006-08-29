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

// g_public.h -- game module information visible to server

#include "bg_public.h"

// entity->svFlags
// the server does not know how to interpret most of the values
// in entityStates (level eType), so the game must explicitly flag
// special server behaviors
#define	SVF_NOCLIENT			0x00000001	// don't send entity to clients, even if it has effects

// TTimo
// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=551
#define SVF_CLIENTMASK 0x00000002

#define SVF_BOT					0x00000008	// set if the entity is a bot
#define	SVF_BROADCAST			0x00000020	// send to all connected clients
#define	SVF_PORTAL				0x00000040	// merge a second pvs at origin2 into snapshots
#define	SVF_USE_CURRENT_ORIGIN	0x00000080	// entity->r.currentOrigin instead of entity->s.origin
// for link position (missiles and movers)
#define SVF_SINGLECLIENT		0x00000100	// only send to a single client (entityShared_t->singleClient)
#define SVF_NOSERVERINFO		0x00000200	// don't send CS_SERVERINFO updates to this client
// so that it can be updated for ping tools without
// lagging clients
#define SVF_CAPSULE				0x00000400	// use capsule for collision detection instead of bbox
#define SVF_NOTSINGLECLIENT		0x00000800	// send entity to everyone but one client
// (entityShared_t->singleClient)



//===============================================================


typedef struct
{
    entityState_t	s;				// communicated by server to clients

    qboolean	linked;				// qfalse if not in any good cluster
    int			linkcount;

    int			svFlags;			// SVF_NOCLIENT, SVF_BROADCAST, etc

    // only send to this client when SVF_SINGLECLIENT is set
    // if SVF_CLIENTMASK is set, use bitmask for clients to send to (maxclients must be <= 32, up to the mod to enforce this)
    int			singleClient;

    qboolean	bmodel;				// if false, assume an explicit mins / maxs bounding box
    // only set by trap_SetBrushModel
    vec3_t		mins, maxs;
    int			contents;			// CONTENTS_TRIGGER, CONTENTS_SOLID, CONTENTS_BODY, etc
    // a non-solid entity should set to 0

    vec3_t		absmin, absmax;		// derived from mins/maxs and origin + rotation

    // currentOrigin will be used for all collision detection and world linking.
    // it will not necessarily be the same as the trajectory evaluation for the current
    // time, because each entity must be moved one at a time after time is advanced
    // to avoid simultanious collision issues
    vec3_t		currentOrigin;
    vec3_t		currentAngles;
    vec3_t		currentVelocity;

    // when a trace call is made and passEntityNum != ENTITYNUM_NONE,
    // an ent will be excluded from testing if:
    // ent->s.number == passEntityNum	(don't interact with self)
    // ent->s.ownerNum = passEntityNum	(don't interact with your own missiles)
    // entity[ent->s.ownerNum].ownerNum = passEntityNum	(don't interact with other missiles from owner)
    int			ownerNum;
}
entityShared_t;

typedef enum {
    MOVER_POS1,
    MOVER_POS2,
    MOVER_1TO2,
    MOVER_2TO1
} moverState_t;

// the server looks at a sharedEntity, which is the start of the game's gentity_t structure
typedef struct gentity_s gentity_t;

struct gentity_s
{
    entityState_t	s;				// communicated by server to clients
    entityShared_t	r;				// shared by both the server system and game

    // DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
    // EXPECTS THE FIELDS IN THAT ORDER!
    //================================

    struct gclient_s	*client;			// NULL if not a client

    qboolean	inuse;

    char		*classname;			// set in QuakeEd
    int			spawnflags;			// set in QuakeEd

    qboolean	neverFree;			// if true, FreeEntity will only unlink
    // bodyque uses this

    int			flags;				// FL_* variables

    char		*model;
    char		*model2;
    int			freetime;			// level.time when the object was freed

    int			eventTime;			// events will be cleared EVENT_VALID_MSEC after set
    qboolean	freeAfterEvent;
    qboolean	unlinkAfterEvent;

    qboolean	physicsObject;		// if true, it can be pushed by movers and fall off edges
    // all game items are physicsObjects,
    float		physicsBounce;		// 1.0 = continuous bounce, 0.0 = no bounce
    int			clipmask;			// brushes with this content value will be collided against
    // when moving.  items and corpses do not collide against
    // players, for instance

    // movers
    moverState_t moverState;
    int			soundPos1;
    int			sound1to2;
    int			sound2to1;
    int			soundPos2;
    int			soundLoop;
    gentity_t	*parent;
    gentity_t	*nextTrain;
    gentity_t	*prevTrain;
    vec3_t		pos1, pos2;

    char		*message;

    int			timestamp;		// body queue sinking, etc

    float		angle;			// set in editor, -1 = up, -2 = down
    char		*target;
    char		*targetname;
    char		*team;
    char		*targetShaderName;
    char		*targetShaderNewName;
    gentity_t	*target_ent;

    float		speed;
    vec3_t		movedir;

    int			nextthink;
    void		(*think)(gentity_t *self);
    void		(*reached)(gentity_t *self);	// movers call this when hitting endpoint
    void		(*blocked)(gentity_t *self, gentity_t *other);
    void		(*touch)(gentity_t *self, gentity_t *other, trace_t *trace);
    void		(*use)(gentity_t *self, gentity_t *other, gentity_t *activator);
    void		(*pain)(gentity_t *self, gentity_t *attacker, int damage);
    void		(*die)(gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod);

    int			pain_debounce_time;
    int			fly_sound_debounce_time;	// wind tunnel
    int			last_move_time;

    int			health;

    qboolean	takedamage;

    int			damage;
    int			splashDamage;	// quad will increase this without increasing radius
    int			splashRadius;
    int			methodOfDeath;
    int			splashMethodOfDeath;

    int			count;

    gentity_t	*chain;
    gentity_t	*enemy;
    gentity_t	*activator;
    gentity_t	*teamchain;		// next entity in team
    gentity_t	*teammaster;	// master of the team

    int			watertype;
    int			waterlevel;

    int			noise_index;

    // timing variables
    float		wait;
    float		random;

    gitem_t		*item;			// for bonus items

    // used for portal stuff
    vec3_t		staticOrigin;
    vec3_t		staticAngles;
    vec3_t		staticAxis[3];

    // attacks
    vec3_t      attack_min, attack_max;
};

//===============================================================

void G_RunFrame( int levelTime );
void SV_Trace( trace_t *results, const vec3_t start, vec3_t mins, vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask, int capsule );
int SV_PointContents( const vec3_t p, int passEntityNum );
int BotAIStartFrame( int time );
char *ClientConnect( int clientNum, qboolean firstTime, qboolean isBot );
void ClientBegin( int clientNum );
qboolean	ConsoleCommand( void );
void G_InitGame( int levelTime, int randomSeed, int restart );
void G_ShutdownGame( int restart );
void ClientThink( int clientNum );
void ClientCommand( int clientNum );
void ClientUserinfoChanged( int clientNum );
void ClientDisconnect( int clientNum );
