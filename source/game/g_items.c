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

/*
 
  Items are any object that a player can touch to gain some effect.
 
  Pickup will return the number of seconds until they should respawn.
 
  all items should pop when dropped in lava or slime
 
  Respawnable items don't actually go away when picked up, they are
  just made invisible and untouchable.  This allows them to ride
  movers and respawn apropriately.
*/


#define	RESPAWN_ARMOR		25
#define	RESPAWN_HEALTH		35
#define	RESPAWN_AMMO		40
#define	RESPAWN_HOLDABLE	60
#define	RESPAWN_MEGAHEALTH	35//120
#define	RESPAWN_POWERUP		120


//======================================================================

int Pickup_Powerup( gentity_t *ent, gentity_t *other )
{
    int			quantity;
    int			i;
    gclient_t	*client;

    if ( !other->client->ps.powerups[ent->item->giTag] )
    {
        // round timing to seconds to make multiple powerup timers
        // count in sync
        other->client->ps.powerups[ent->item->giTag] =
            level.time - ( level.time % 1000 );
    }

    if ( ent->count )
    {
        quantity = ent->count;
    }
    else
    {
        quantity = ent->item->quantity;
    }

    other->client->ps.powerups[ent->item->giTag] += quantity * 1000;

    // give any nearby players a "denied" anti-reward
    for ( i = 0 ; i < level.maxclients ; i++ )
    {
        vec3_t		delta;
        float		len;
        vec3_t		forward;
        trace_t		tr;

        client = &level.clients[i];
        if ( client == other->client )
        {
            continue;
        }
        if ( client->pers.connected == CON_DISCONNECTED )
        {
            continue;
        }
        if ( client->ps.stats[STAT_HEALTH] <= 0 )
        {
            continue;
        }

        // if same team in team game, no sound
        // cannot use OnSameTeam as it expects to g_entities, not clients
        if ( g_gametype->integer >= GT_TEAM && other->client->sess.sessionTeam == client->sess.sessionTeam  )
        {
            continue;
        }

        // if too far away, no sound
        VectorSubtract( ent->s.pos.trBase, client->ps.origin, delta );
        len = VectorNormalize( delta );
        if ( len > 192 )
        {
            continue;
        }

        // if not facing, no sound
        AngleVectors( client->ps.viewangles, forward, NULL, NULL );
        if ( DotProduct( delta, forward ) < 0.4 )
        {
            continue;
        }

        // if not line of sight, no sound
        SV_Trace( &tr, client->ps.origin, NULL, NULL, ent->s.pos.trBase, ENTITYNUM_NONE, CONTENTS_SOLID, qfalse);
        if ( tr.fraction != 1.0 )
        {
            continue;
        }

        // anti-reward
        client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_DENIEDREWARD;
    }
    return RESPAWN_POWERUP;
}

//======================================================================

int Pickup_Holdable( gentity_t *ent, gentity_t *other )
{

    other->client->ps.stats[STAT_HOLDABLE_ITEM] = ent->item - bg_itemlist;

    if( ent->item->giTag == HI_KAMIKAZE )
    {
        other->client->ps.eFlags |= EF_KAMIKAZE;
    }

    return RESPAWN_HOLDABLE;
}


//======================================================================

void Add_Ammo (gentity_t *ent, int weapon, int count)
{
    ent->client->ps.weaponAmmo[weapon] += count;
    if ( ent->client->ps.weaponAmmo[weapon] > 200 )
    {
        ent->client->ps.weaponAmmo[weapon] = 200;
    }
}

int Pickup_Ammo (gentity_t *ent, gentity_t *other)
{
    int		quantity;

    if ( ent->count )
    {
        quantity = ent->count;
    }
    else
    {
        quantity = ent->item->quantity;
    }

    Add_Ammo (other, ent->item->giTag, quantity);

    return RESPAWN_AMMO;
}

//======================================================================

int Pickup_Health (gentity_t *ent, gentity_t *other)
{
    int			max;
    int			quantity;

    // small and mega healths will go over the max
    max = other->client->ps.stats[STAT_MAX_HEALTH] * (ent->item->quantity != 5 && ent->item->quantity != 100) ? 1 : 2;
    quantity = (ent->count) ? ent->count : ent->item->quantity;

    other->health -= quantity;

    if (other->health < 25)
        other->health = 25;

    other->client->ps.stats[STAT_HEALTH] = other->health;

    if ( ent->item->quantity == 100 )
    {		// mega health respawns slow
        return RESPAWN_MEGAHEALTH;
    }

    return RESPAWN_HEALTH;
}

//======================================================================

int Pickup_Armor( gentity_t *ent, gentity_t *other )
{
    other->client->ps.stats[STAT_ARMOR] += ent->item->quantity;
    if ( other->client->ps.stats[STAT_ARMOR] > other->client->ps.stats[STAT_MAX_HEALTH] * 2 )
    {
        other->client->ps.stats[STAT_ARMOR] = other->client->ps.stats[STAT_MAX_HEALTH] * 2;
    }

    return RESPAWN_ARMOR;
}

//======================================================================

/*
===============
RespawnItem
===============
*/
void RespawnItem( gentity_t *ent )
{
    // randomly select from teamed entities
    if (ent->team)
    {
        gentity_t	*master;
        int	count;
        int choice;

        if ( !ent->teammaster )
        {
            Com_Error(ERR_DROP,  "RespawnItem: bad teammaster");
        }
        master = ent->teammaster;

        for (count = 0, ent = master; ent; ent = ent->teamchain, count++)
            ;

        choice = rand() % count;

        for (count = 0, ent = master; count < choice; ent = ent->teamchain, count++)
            ;
    }

    ent->r.contents = CONTENTS_TRIGGER;
    ent->s.eFlags &= ~EF_NODRAW;
    ent->r.svFlags &= ~SVF_NOCLIENT;
    SV_LinkEntity ((gentity_t *)ent);

    if ( ent->item->giType == IT_POWERUP )
    {
        // play powerup spawn sound to all clients
        gentity_t	*te;

        // if the powerup respawn sound should Not be global
        if (ent->speed)
        {
            te = G_TempEntity( ent->s.pos.trBase, EV_GENERAL_SOUND );
        }
        else
        {
            te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_SOUND );
        }
        te->s.eventParm = G_SoundIndex( "sound/items/poweruprespawn.wav" );
        te->r.svFlags |= SVF_BROADCAST;
    }

    if ( ent->item->giType == IT_HOLDABLE && ent->item->giTag == HI_KAMIKAZE )
    {
        // play powerup spawn sound to all clients
        gentity_t	*te;

        // if the powerup respawn sound should Not be global
        if (ent->speed)
        {
            te = G_TempEntity( ent->s.pos.trBase, EV_GENERAL_SOUND );
        }
        else
        {
            te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_SOUND );
        }
        te->s.eventParm = G_SoundIndex( "sound/items/kamikazerespawn.wav" );
        te->r.svFlags |= SVF_BROADCAST;
    }

    // play the normal respawn sound only to nearby clients
    G_AddEvent( ent, EV_ITEM_RESPAWN, 0 );

    ent->nextthink = 0;
}


/*
===============
Touch_Item
===============
*/
void Touch_Item (gentity_t *ent, gentity_t *other, trace_t *trace)
{
    int			respawn;
    qboolean	predict;

    if (!other->client)
        return;
    if (other->health < 1)
        return;		// dead people can't pickup

    // the same pickup rules are used for client side and server side
    if ( !BG_CanItemBeGrabbed( g_gametype->integer, &ent->s, &other->client->ps ) )
    {
        return;
    }

    G_LogPrintf( "Item: %i %s\n", other->s.number, ent->item->classname );

    predict = other->client->pers.predictItemPickup;

    // call the item-specific pickup function
    switch( ent->item->giType )
    {
    case IT_AMMO:
        respawn = Pickup_Ammo(ent, other);
//		predict = qfalse;
        break;
    case IT_ARMOR:
        respawn = Pickup_Armor(ent, other);
        break;
    case IT_HEALTH:
        respawn = Pickup_Health(ent, other);
        break;
    case IT_POWERUP:
        respawn = Pickup_Powerup(ent, other);
        predict = qfalse;
        break;
    case IT_TEAM:
        respawn = Pickup_Team(ent, other);
        break;
    case IT_HOLDABLE:
        respawn = Pickup_Holdable(ent, other);
        break;
    default:
        return;
    }

    if ( !respawn )
    {
        return;
    }

    // play the normal pickup sound
    if (predict)
    {
        G_AddPredictableEvent( other, EV_ITEM_PICKUP, ent->s.modelindex );
    }
    else
    {
        G_AddEvent( other, EV_ITEM_PICKUP, ent->s.modelindex );
    }

    // powerup pickups are global broadcasts
    if ( ent->item->giType == IT_POWERUP || ent->item->giType == IT_TEAM)
    {
        // if we want the global sound to play
        if (!ent->speed)
        {
            gentity_t	*te;

            te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP );
            te->s.eventParm = ent->s.modelindex;
            te->r.svFlags |= SVF_BROADCAST;
        }
        else
        {
            gentity_t	*te;

            te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP );
            te->s.eventParm = ent->s.modelindex;
            // only send this temp entity to a single client
            te->r.svFlags |= SVF_SINGLECLIENT;
            te->r.singleClient = other->s.number;
        }
    }

    // fire item targets
    G_UseTargets (ent, other);

    // wait of -1 will not respawn
    if ( ent->wait == -1 )
    {
        ent->r.svFlags |= SVF_NOCLIENT;
        ent->s.eFlags |= EF_NODRAW;
        ent->r.contents = 0;
        ent->unlinkAfterEvent = qtrue;
        return;
    }

    // non zero wait overrides respawn time
    if ( ent->wait )
    {
        respawn = ent->wait;
    }

    // random can be used to vary the respawn time
    if ( ent->random )
    {
        respawn += crandom() * ent->random;
        if ( respawn < 1 )
        {
            respawn = 1;
        }
    }

    // dropped items will not respawn
    if ( ent->flags & FL_DROPPED_ITEM )
    {
        ent->freeAfterEvent = qtrue;
    }

    // picked up items still stay around, they just don't
    // draw anything.  This allows respawnable items
    // to be placed on movers.
    ent->r.svFlags |= SVF_NOCLIENT;
    ent->s.eFlags |= EF_NODRAW;
    ent->r.contents = 0;

    // ZOID
    // A negative respawn times means to never respawn this item (but don't
    // delete it).  This is used by items that are respawned by third party
    // events such as ctf flags
    if ( respawn <= 0 )
    {
        ent->nextthink = 0;
        ent->think = 0;
    }
    else
    {
        ent->nextthink = level.time + respawn * 1000;
        ent->think = RespawnItem;
    }
    SV_LinkEntity( ent );
}


//======================================================================

/*
================
LaunchItem
 
Spawns an item and tosses it forward
================
*/
gentity_t *LaunchItem( gitem_t *item, vec3_t origin, vec3_t velocity )
{
    gentity_t	*dropped;

    dropped = G_Spawn();

    dropped->s.eType = ET_ITEM;
    dropped->s.modelindex = item - bg_itemlist;	// store item number in modelindex
    dropped->s.modelindex2 = 1; // This is non-zero is it's a dropped item

    dropped->classname = item->classname;
    dropped->item = item;
    VectorSet (dropped->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS);
    VectorSet (dropped->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS);
    dropped->r.contents = CONTENTS_TRIGGER;

    dropped->touch = Touch_Item;

    G_SetOrigin( dropped, origin );
    dropped->s.pos.trType = TR_GRAVITY;
    dropped->s.pos.trTime = level.time;
    VectorCopy( velocity, dropped->s.pos.trDelta );

    dropped->s.eFlags |= EF_BOUNCE_HALF;
    if (g_gametype->integer == GT_CTF && item->giType == IT_TEAM)
    { // Special case for CTF flags
        dropped->think = Team_DroppedFlagThink;
        dropped->nextthink = level.time + 30000;
        Team_CheckDroppedItem( dropped );
    }
    else
    { // auto-remove after 30 seconds
        dropped->think = G_FreeEntity;
        dropped->nextthink = level.time + 30000;
    }

    dropped->flags = FL_DROPPED_ITEM;

    SV_LinkEntity (dropped);

    return dropped;
}

/*
================
Drop_Item
 
Spawns an item and tosses it forward
================
*/
gentity_t *Drop_Item( gentity_t *ent, gitem_t *item, float angle )
{
    vec3_t	velocity;
    vec3_t	angles;

    VectorCopy( ent->s.apos.trBase, angles );
    angles[YAW] += angle;
    angles[PITCH] = 0;	// always forward

    AngleVectors( angles, velocity, NULL, NULL );
    VectorScale( velocity, 150, velocity );
    velocity[2] += 200 + crandom() * 50;

    return LaunchItem( item, ent->s.pos.trBase, velocity );
}


/*
================
Use_Item
 
Respawn the item
================
*/
void Use_Item( gentity_t *ent, gentity_t *other, gentity_t *activator )
{
    RespawnItem( ent );
}

//======================================================================

/*
================
FinishSpawningItem
 
Traces down to find where an item should rest, instead of letting them
free fall from their spawn points
================
*/
void FinishSpawningItem( gentity_t *ent )
{
    trace_t		tr;
    vec3_t		dest;

    VectorSet( ent->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS );
    VectorSet( ent->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS );

    ent->s.eType = ET_ITEM;
    ent->s.modelindex = ent->item - bg_itemlist;		// store item number in modelindex
    ent->s.modelindex2 = 0; // zero indicates this isn't a dropped item

    ent->r.contents = CONTENTS_TRIGGER;
    ent->touch = Touch_Item;
    // useing an item causes it to respawn
    ent->use = Use_Item;

    if ( ent->spawnflags & 1 )
    {
        // suspended
        G_SetOrigin( ent, ent->s.origin );
    }
    else
    {
        // drop to floor
        VectorSet( dest, ent->s.origin[0], ent->s.origin[1], ent->s.origin[2] - 4096 );
        SV_Trace( &tr, ent->s.origin, ent->r.mins, ent->r.maxs, dest, ent->s.number, MASK_SOLID, qfalse);
        if ( tr.startsolid )
        {
            Com_Printf ("FinishSpawningItem: %s startsolid at %s\n", ent->classname, vtos(ent->s.origin));
            G_FreeEntity( ent );
            return;
        }

        // allow to ride movers
        ent->s.groundEntityNum = tr.entityNum;

        G_SetOrigin( ent, tr.endpos );
    }

    // team slaves and targeted items aren't present at start
    if ( ( ent->flags & FL_TEAMSLAVE ) || ent->targetname )
    {
        ent->s.eFlags |= EF_NODRAW;
        ent->r.contents = 0;
        return;
    }

    // powerups don't spawn in for a while
    if ( ent->item->giType == IT_POWERUP )
    {
        float	respawn;

        respawn = 45 + crandom() * 15;
        ent->s.eFlags |= EF_NODRAW;
        ent->r.contents = 0;
        ent->nextthink = level.time + respawn * 1000;
        ent->think = RespawnItem;
        return;
    }


    SV_LinkEntity (ent);
}


qboolean	itemRegistered[MAX_ITEMS];

/*
==================
G_CheckTeamItems
==================
*/
void G_CheckTeamItems( void )
{

    // Set up team stuff
    Team_InitGame();

    if( g_gametype->integer == GT_CTF )
    {
        gitem_t	*item;

        // check for the two flags
        item = BG_FindItem( "Red Flag" );
        if ( !item || !itemRegistered[ item - bg_itemlist ] )
        {
            Com_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_redflag in map" );
        }
        item = BG_FindItem( "Blue Flag" );
        if ( !item || !itemRegistered[ item - bg_itemlist ] )
        {
            Com_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_blueflag in map" );
        }
    }
}

/*
==============
ClearRegisteredItems
==============
*/
void ClearRegisteredItems( void )
{
    memset( itemRegistered, 0, sizeof( itemRegistered ) );

    // players always start with the base weapon
 //   RegisterItem( BG_FindItemForWeapon( WP_MACHINEGUN ) );
//    RegisterItem( BG_FindItemForWeapon( WP_GAUNTLET ) );
}

/*
===============
RegisterItem
 
The item will be added to the precache list
===============
*/
void RegisterItem( gitem_t *item )
{
    if ( !item )
    {
        Com_Error(ERR_DROP,  "RegisterItem: NULL" );
    }
    itemRegistered[ item - bg_itemlist ] = qtrue;
}


/*
===============
SaveRegisteredItems
 
Write the needed items to a config string
so the client will know which ones to precache
===============
*/
void SaveRegisteredItems( void )
{
    char	string[MAX_ITEMS+1];
    int		i;
    int		count;

    count = 0;
    for ( i = 0 ; i < bg_numItems ; i++ )
    {
        if ( itemRegistered[i] )
        {
            count++;
            string[i] = '1';
        }
        else
        {
            string[i] = '0';
        }
    }
    string[ bg_numItems ] = 0;

    Com_Printf( "%i items registered\n", count );
    SV_SetConfigstring(CS_ITEMS, string);
}

/*
============
G_ItemDisabled
============
*/
int G_ItemDisabled( gitem_t *item )
{

    char name[128];

    Com_sprintf(name, sizeof(name), "disable_%s", item->classname);
    return Cvar_VariableIntegerValue( name );
}

/*
============
G_SpawnItem
 
Sets the clipping size and plants the object on the floor.
 
Items can't be immediately dropped to floor, because they might
be on an entity that hasn't spawned yet.
============
*/
void G_SpawnItem (gentity_t *ent, gitem_t *item)
{
    G_SpawnFloat( "random", "0", &ent->random );
    G_SpawnFloat( "wait", "0", &ent->wait );

    RegisterItem( item );
    if ( G_ItemDisabled(item) )
        return;

    ent->item = item;
    // some movers spawn on the second frame, so delay item
    // spawns until the third frame so they can ride trains
    ent->nextthink = level.time + FRAMETIME * 2;
    ent->think = FinishSpawningItem;

    ent->physicsBounce = 0.50;		// items are bouncy

    if ( item->giType == IT_POWERUP )
    {
        G_SoundIndex( "sound/items/poweruprespawn.wav" );
        G_SpawnFloat( "noglobalsound", "0", &ent->speed);
    }
}


/*
================
G_BounceItem
 
================
*/
void G_BounceItem( gentity_t *ent, trace_t *trace )
{
    vec3_t	velocity;
    float	dot;
    int		hitTime;

    // reflect the velocity on the trace plane
    hitTime = level.previousTime + ( level.time - level.previousTime ) * trace->fraction;
    BG_EvaluateTrajectoryDelta( &ent->s.pos, hitTime, velocity );
    dot = DotProduct( velocity, trace->plane.normal );
    VectorMA( velocity, -2*dot, trace->plane.normal, ent->s.pos.trDelta );

    // cut the velocity to keep from bouncing forever
    VectorScale( ent->s.pos.trDelta, ent->physicsBounce, ent->s.pos.trDelta );

    // check for stop
    if ( trace->plane.normal[2] > 0 && ent->s.pos.trDelta[2] < 40 )
    {
        trace->endpos[2] += 1.0;	// make sure it is off ground
        SnapVector( trace->endpos );
        G_SetOrigin( ent, trace->endpos );
        ent->s.groundEntityNum = trace->entityNum;
        return;
    }

    VectorAdd( ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
    VectorCopy( ent->r.currentOrigin, ent->s.pos.trBase );
    ent->s.pos.trTime = level.time;
}


/*
================
G_RunItem
 
================
*/
void G_RunItem( gentity_t *ent )
{
    vec3_t		origin;
    trace_t		tr;
    int			contents;
    int			mask;

    // if groundentity has been set to -1, it may have been pushed off an edge
    if ( ent->s.groundEntityNum == -1 )
    {
        if ( ent->s.pos.trType != TR_GRAVITY )
        {
            ent->s.pos.trType = TR_GRAVITY;
            ent->s.pos.trTime = level.time;
        }
    }

    if ( ent->s.pos.trType == TR_STATIONARY )
    {
        // check think function
        G_RunThink( ent );
        return;
    }

    // get current position
    BG_EvaluateTrajectory( &ent->s.pos, level.time, origin );

    // trace a line from the previous position to the current position
    if ( ent->clipmask )
    {
        mask = ent->clipmask;
    }
    else
    {
        mask = MASK_PLAYERSOLID & ~CONTENTS_BODY;//MASK_SOLID;
    }
    SV_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, origin,
                ent->r.ownerNum, mask, qfalse);

    VectorCopy( tr.endpos, ent->r.currentOrigin );

    if ( tr.startsolid )
    {
        tr.fraction = 0;
    }

    SV_LinkEntity( ent );	// FIXME: avoid this for stationary?

    // check think function
    G_RunThink( ent );

    if ( tr.fraction == 1 )
    {
        return;
    }

    // if it is in a nodrop volume, remove it
    contents = SV_PointContents( ent->r.currentOrigin, -1 );
    if ( contents & CONTENTS_NODROP )
    {
        if (ent->item && ent->item->giType == IT_TEAM)
        {
            Team_FreeEntity(ent);
        }
        else
        {
            G_FreeEntity( ent );
        }
        return;
    }

    G_BounceItem( ent, &tr );
}
