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
// g_misc.c

#include "g_local.h"


/*QUAKED func_group (0 0 0) ?
Used to group brushes together just for editor convenience.  They are turned into normal brushes by the utilities.
*/


/*QUAKED info_camp (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for calculations in the utilities (spotlights, etc), but removed during gameplay.
*/
void SP_info_camp( gentity_t *self )
{
    G_SetOrigin( self, self->s.origin );
}


/*QUAKED info_null (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for calculations in the utilities (spotlights, etc), but removed during gameplay.
*/
void SP_info_null( gentity_t *self )
{
    G_FreeEntity( self );
}


/*QUAKED info_notnull (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for in-game calculation, like jumppad targets.
target_position does the same thing
*/
void SP_info_notnull( gentity_t *self )
{
    G_SetOrigin( self, self->s.origin );
}


/*QUAKED light (0 1 0) (-8 -8 -8) (8 8 8) linear
Non-displayed light.
"light" overrides the default 300 intensity.
Linear checbox gives linear falloff instead of inverse square
Lights pointed at a target will be spotlights.
"radius" overrides the default 64 unit radius of a spotlight at the target point.
*/
void SP_light( gentity_t *self )
{
    G_FreeEntity( self );
}



/*
=================================================================================
 
TELEPORTERS
 
=================================================================================
*/

void TeleportPlayer( gentity_t *player, vec3_t origin, vec3_t angles )
{
    gentity_t	*tent;

    // use temp events at source and destination to prevent the effect
    // from getting dropped by a second player event
    if ( player->client->sess.sessionTeam != TEAM_SPECTATOR )
    {
        tent = G_TempEntity( player->client->ps.origin, EV_PLAYER_TELEPORT_OUT );
        tent->s.clientNum = player->s.clientNum;

        tent = G_TempEntity( origin, EV_PLAYER_TELEPORT_IN );
        tent->s.clientNum = player->s.clientNum;
    }

    // unlink to make sure it can't possibly interfere with G_KillBox
    SV_UnlinkEntity (player);

    VectorCopy ( origin, player->client->ps.origin );
    player->client->ps.origin[2] += 1;

    // spit the player out
    AngleVectors( angles, player->client->ps.velocity, NULL, NULL );
    VectorScale( player->client->ps.velocity, 400, player->client->ps.velocity );
    player->client->ps.pm_time = 160;		// hold time
    player->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;

    // toggle the teleport bit so the client knows to not lerp
    player->client->ps.eFlags ^= EF_TELEPORT_BIT;

    // set angles
    SetClientViewAngle( player, angles );

    // kill anything at the destination
    if ( player->client->sess.sessionTeam != TEAM_SPECTATOR )
    {
        G_KillBox (player);
    }

    // save results of pmove
    BG_PlayerStateToEntityState( &player->client->ps, &player->s, qtrue );

    // use the precise origin for linking
    VectorCopy( player->client->ps.origin, player->r.currentOrigin );

    if ( player->client->sess.sessionTeam != TEAM_SPECTATOR )
    {
        SV_LinkEntity (player);
    }
}

/*QUAKED misc_teleporter_dest (1 0 0) (-32 -32 -24) (32 32 -16)
Point teleporters at these.
Now that we don't have teleport destination pads, this is just
an info_notnull
*/
void SP_misc_teleporter_dest( gentity_t *ent )
{}


//===========================================================

/*QUAKED misc_model (1 0 0) (-16 -16 -16) (16 16 16)
"model"		arbitrary .md3 file to display
*/
void SP_misc_model( gentity_t *ent )
{

#if 0
    ent->s.modelindex = G_ModelIndex( ent->model );
    VectorSet (ent->mins, -16, -16, -16);
    VectorSet (ent->maxs, 16, 16, 16);
    SV_LinkEntity (ent);

    G_SetOrigin( ent, ent->s.origin );
    VectorCopy( ent->s.angles, ent->s.apos.trBase );
#else
    G_FreeEntity( ent );
#endif
}

//===========================================================

void locateCamera( gentity_t *ent )
{
    vec3_t		dir;
    gentity_t	*target;
    gentity_t	*dest;

    dest = G_PickTarget( ent->target );
    if ( !dest )
    {
        Com_Printf( "Couldn't find target for misc_partal_surface\n" );
        G_FreeEntity( ent );
        return;
    }

    ent->r.ownerNum = dest->s.number;

    if (ent->spawnflags & 1)
        ent->s.frame = 25;
    else if (dest->spawnflags & 2)
        ent->s.frame = 75;

    if ( ent->spawnflags & 4 )
        ent->s.powerups = 0;
    else
        ent->s.powerups = 1;

    ent->s.powerups = 0;

    VectorCopy(dest->s.origin, ent->s.origin2);

    target = G_PickTarget( dest->message );
    if(target)
    {
        VectorSubtract( target->s.origin, dest->s.origin, dir );
        VectorNormalize( dir );
    }
    else
        G_SetMovedir( dest->s.angles, dir );

    ent->s.eventParm = DirToByte( dir );

    vectoangles(dir, dir);
    dir[YAW] = 180 - dir[YAW];
    AnglesToAxis(dir, dest->staticAxis);
}

void Axis_Invert(vec3_t _in[3], vec3_t out[3])
{
    vec3_t in[3];
    AxisCopy(_in, in);
    out[0][0] = (float)(in[0][0] * -1);
    out[0][1] = (float)(in[1][0] * -1);
    out[0][2] = (float)(in[2][0] * -1);
    out[1][0] = (float)(in[0][1] * -1);
    out[1][1] = (float)(in[1][1] * -1);
    out[1][2] = (float)(in[2][1] * -1);
    out[2][0] = (float)(in[0][2] * -1);
    out[2][1] = (float)(in[1][2] * -1);
    out[2][2] = (float)(in[2][2] * -1);
}

void Axis_Concat(vec3_t _in1[3], vec3_t _in2[3], vec3_t out[3])
{
    vec3_t in1[3], in2[3];
    AxisCopy(_in1, in1);
    AxisCopy(_in2, in2);
    out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] + in1[0][2] * in2[2][0];
    out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] + in1[0][2] * in2[2][1];
    out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] + in1[0][2] * in2[2][2];
    out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] + in1[1][2] * in2[2][0];
    out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] + in1[1][2] * in2[2][1];
    out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] + in1[1][2] * in2[2][2];
    out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] + in1[2][2] * in2[2][0];
    out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] + in1[2][2] * in2[2][1];
    out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] + in1[2][2] * in2[2][2];
}

void Axis_Transpose(vec3_t _in[3], vec3_t out[3])
{
    vec3_t in[3];
    AxisCopy(_in, in);
    out[0][0] = in[0][0];
    out[0][1] = in[1][0];
    out[0][2] = in[2][0];
    out[1][0] = in[0][1];
    out[1][1] = in[1][1];
    out[1][2] = in[2][1];
    out[2][0] = in[0][2];
    out[2][1] = in[1][2];
    out[2][2] = in[2][2];
}

void Portal_TransformDirection(vec3_t axis[3], vec3_t _in, vec3_t _out)
{
    vec3_t in;
    VectorCopy(_in, in);
    _out[0] = DotProduct(in, axis[0]);
    _out[1] = DotProduct(in, axis[1]);
    _out[2] = DotProduct(in, axis[2]);
}

void Portal_TransformAngle(vec3_t axis[3], vec3_t _in, vec3_t _out)
{
    vec3_t in, temp;
    AngleVectors(_in, in, NULL, NULL);
    temp[0] = DotProduct(in, axis[0]);
    temp[1] = DotProduct(in, axis[1]);
    temp[2] = DotProduct(in, axis[2]);
    vectoangles(temp, _out);
}

void Portal_TransformOrigin(vec3_t src, vec3_t dst, vec3_t _in, vec3_t _out)
{
    _out[0] = _in[0] - (src[0] - dst[0]);
    _out[1] = _in[1] - (src[1] - dst[1]);
    _out[2] = _in[2] - (src[2] - dst[2]);
}

void SP_misc_portal_surface_touch(gentity_t *self, gentity_t *other, trace_t *trace)
{
    gentity_t	*dest = G_PickTarget(self->target);
    qboolean isClient = (other->client) ? qtrue : qfalse;

    if (!dest)
    {
        Com_Printf("Couldn't find portal destination %s\n", self->target);
        return;
    }

    if(isClient)
    {
        gentity_t	*player = other;

        // if we are pass the portal finaly move the player
        if(DotProduct(player->client->ps.origin, self->staticAxis[0]) - DotProduct(self->s.origin, self->staticAxis[0]) < 0)
        {
            vec3_t		playerA, tAxis[3];

            Axis_Concat(dest->staticAxis, self->staticAxis, tAxis);
            Portal_TransformDirection(tAxis, player->client->ps.velocity, player->client->ps.velocity);
            Portal_TransformAngle(tAxis, player->client->ps.viewangles, playerA);
            Portal_TransformOrigin(self->s.origin, dest->s.origin, player->client->ps.origin, player->client->ps.origin);

            SetClientViewAngle(other, playerA);
            player->client->ps.eFlags ^= EF_TELEPORT_BIT;
            BG_PlayerStateToEntityState( &player->client->ps, &player->s, qtrue );
            VectorCopy(player->client->ps.origin, player->r.currentOrigin);
        }
    }
    else
    {
        vec3_t	tAxis[3];

        Axis_Concat(dest->staticAxis, self->staticAxis, tAxis);

        Portal_TransformAngle(tAxis, other->r.currentAngles, other->r.currentAngles);
        Portal_TransformDirection(tAxis, other->r.currentVelocity, other->r.currentVelocity);
        Portal_TransformOrigin(self->s.origin, dest->s.origin, other->r.currentOrigin, other->r.currentOrigin);
    }
}

/*QUAKED misc_portal_surface (0 0 1) (-8 -8 -8) (8 8 8)
The portal surface nearest this entity will show a view from the targeted misc_portal_camera, or a mirror view if untargeted.
This must be within 64 world units of the surface!
*/
void SP_misc_portal_surface(gentity_t *ent)
{
    VectorClear( ent->r.mins );
    VectorClear( ent->r.maxs );
    SV_LinkEntity (ent);

    ent->r.svFlags = SVF_PORTAL;
    ent->s.eType = ET_PORTAL;

    if ( !ent->target )
        VectorCopy( ent->s.origin, ent->s.origin2 );
    else
    {
        ent->think = locateCamera;
        ent->nextthink = level.time + 100;
    }

    ent->touch = SP_misc_portal_surface_touch;
}

/*QUAKED misc_portal_camera (0 0 1) (-8 -8 -8) (8 8 8) slowrotate fastrotate noswing
The target for a misc_portal_director.  You can set either angles or target another entity to determine the direction of view.
"roll" an angle modifier to orient the camera around the target vector;
*/
void SP_misc_portal_camera(gentity_t *ent)
{
    float	roll;

    VectorClear( ent->r.mins );
    VectorClear( ent->r.maxs );
    SV_LinkEntity (ent);

    G_SpawnFloat( "roll", "0", &roll );

    ent->s.clientNum = (int)(roll/360.0 * 256);
}

/*
======================================================================
 
  SHOOTERS
 
======================================================================
*/

void Use_Shooter( gentity_t *ent, gentity_t *other, gentity_t *activator )
{
    /*    vec3_t		dir;
        float		deg;
        vec3_t		up, right;

        // see if we have a target
        if ( ent->enemy )
        {
            VectorSubtract( ent->enemy->r.currentOrigin, ent->s.origin, dir );
            VectorNormalize( dir );
        }
        else
        {
            VectorCopy( ent->movedir, dir );
        }

        // randomize a bit
        PerpendicularVector( up, dir );
        CrossProduct( up, dir, right );

        deg = crandom() * ent->random;
        VectorMA( dir, deg, up, dir );

        deg = crandom() * ent->random;
        VectorMA( dir, deg, right, dir );

        VectorNormalize( dir );

        switch ( ent->s.weapon )
        {
        case WP_GRENADE_LAUNCHER:
            fire_grenade( ent, ent->s.origin, dir );
            break;
        case WP_ROCKET_LAUNCHER:
            fire_rocket( ent, ent->s.origin, dir );
            break;
        case WP_PLASMAGUN:
            fire_plasma( ent, ent->s.origin, dir );
            break;
        }

        G_AddEvent( ent, EV_FIRE_WEAPON, 0 );*/
}


static void InitShooter_Finish( gentity_t *ent )
{
    ent->enemy = G_PickTarget( ent->target );
    ent->think = 0;
    ent->nextthink = 0;
}

void InitShooter( gentity_t *ent, int weapon )
{
    ent->use = Use_Shooter;
    ent->s.weapon = weapon;

    //    RegisterItem( BG_FindItemForWeapon( weapon ) );

    G_SetMovedir( ent->s.angles, ent->movedir );

    if ( !ent->random )
    {
        ent->random = 1.0;
    }
    ent->random = sin( M_PI * ent->random / 180 );
    // target might be a moving object, so we can't set movedir for it
    if ( ent->target )
    {
        ent->think = InitShooter_Finish;
        ent->nextthink = level.time + 500;
    }
    SV_LinkEntity( ent );
}

/*QUAKED shooter_rocket (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" the number of degrees of deviance from the taget. (1.0 default)
*/
void SP_shooter_rocket( gentity_t *ent )
{
    //    InitShooter( ent, WP_ROCKET_LAUNCHER );
}

/*QUAKED shooter_plasma (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" is the number of degrees of deviance from the taget. (1.0 default)
*/
void SP_shooter_plasma( gentity_t *ent )
{
    //   InitShooter( ent, WP_PLASMAGUN);
}

/*QUAKED shooter_grenade (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" is the number of degrees of deviance from the taget. (1.0 default)
*/
void SP_shooter_grenade( gentity_t *ent )
{
    //    InitShooter( ent, WP_GRENADE_LAUNCHER);
}
