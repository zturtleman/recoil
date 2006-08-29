/*
===========================================================================
Copyw_right(C)1999-2005 Id Software, Inc.
 
This file is part of Quake III Arena source code.
 
Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or(at your option)any later version.
 
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
// g_weapon.c
// perform the server side effects of a weapon firing

#include "g_local.h"

static	float	s_quadFactor;
vec3_t	w_forward, w_right, w_up;
static	vec3_t	muzzle;

/*
======================================================================
 
Generic
 
======================================================================
*/

void SnapVectorTowards(vec3_t v, vec3_t to)
{
    int		i;
    for(i = 0 ; i < 3 ; i++)
	{
		v[i] = (to[i] <= v[i]) ? (int)v[i] : (int)v[i] + 1;
	}
}

// Returns the number of players hit, cannot be more then numHits
#define MAX_UNLINKED_ENTS 32
static int Fire_HitScan(gentity_t *shooter, float spread, float range, int damage, int dflags, int mod, int numHits, gentity_t *(* lineEffect)(gentity_t *shooter, vec3_t start, trace_t *tr), gentity_t *(* hitEffect)(gentity_t *shooter, vec3_t start, trace_t *tr))
{
    trace_t		tr;
    vec3_t		end;
    gentity_t	*traceEnt, tracer;
	gentity_t	*unlinkedEntities[MAX_UNLINKED_ENTS];
    int			passent, hits, unlinked;
	float r, u;

    damage *= s_quadFactor;

	memset(&tracer, 0, sizeof(gentity_t));
    VectorCopy(w_forward, tracer.r.currentVelocity);
    VectorCopy(muzzle, tracer.r.currentOrigin);

    passent = shooter->s.number;
	unlinked = 0;
	hits = 0;
    while(unlinked < MAX_UNLINKED_ENTS && numHits && range > 1.0)
    {
	    VectorMA(tracer.r.currentOrigin, range, tracer.r.currentVelocity, end);

		if(spread)
		{
			r = random() * M_PI * 2.0f;
			u = sin(r) * crandom() * spread * 16;
			r = cos(r) * crandom() * spread * 16;
			VectorMA(end, r, w_right, end);
			VectorMA(end, u, w_up, end);
		}

        SV_Trace(&tr, tracer.r.currentOrigin, NULL, NULL, end, passent, MASK_SHOT | CONTENTS_TRIGGER, qfalse);
		range -= range * tr.fraction;

		traceEnt = &g_entities[tr.entityNum];
        if(traceEnt->takedamage)
		{
			hits += LogAccuracyHit(traceEnt, shooter) * 1;
			G_Damage(traceEnt, shooter, shooter, tracer.r.currentVelocity, tr.endpos, damage, dflags, mod);
		}

		if((traceEnt->r.contents & CONTENTS_TRIGGER) && traceEnt->touch)
		{
			if(traceEnt->s.eType == ET_TELEPORT_TRIGGER)
			{
				if(lineEffect)
					lineEffect(shooter, tracer.r.currentOrigin, &tr);

				VectorCopy(tr.endpos, tracer.r.currentOrigin);
				traceEnt->touch(traceEnt, &tracer, &tr);
				passent = ENTITYNUM_NONE; // you can hit yourself now
			}

			SV_UnlinkEntity(traceEnt);
			unlinkedEntities[unlinked++] = traceEnt;
			continue;
		}

        if(hitEffect)
			hitEffect(shooter, tracer.r.currentOrigin, &tr);

		if(tr.contents & CONTENTS_SOLID)
            break;

		if(numHits--)
		{
			SV_UnlinkEntity(traceEnt);
			unlinkedEntities[unlinked++] = traceEnt;
			continue;
		}

		break;
    }

	if(unlinked)
	{
		int i;
		for(i=0; i<unlinked; i++)
			SV_LinkEntity(unlinkedEntities[i]);
	}

	if(lineEffect)
		lineEffect(shooter, tracer.r.currentOrigin, &tr);

	return hits;
}

/*
======================================================================
 
GAUNTLET
 
======================================================================
*/

void Weapon_Gauntlet(gentity_t *ent)
{
}

/*
===============
CheckGauntletAttack
===============
*/
qboolean CheckGauntletAttack(gentity_t *ent)
{
    trace_t		tr;
    vec3_t		end;
    gentity_t	*tent;
    gentity_t	*traceEnt;

    // set aiming directions
    AngleVectors(ent->client->ps.viewangles, w_forward, w_right, w_up);

    CalcMuzzlePoint(ent, w_forward, w_right, w_up, muzzle);

    VectorMA(muzzle, 32, w_forward, end);

    SV_Trace(&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT, qfalse);
    if(tr.surfaceFlags & SURF_NOIMPACT)
        return qfalse;

    traceEnt = &g_entities[tr.entityNum];

    // send blood impact
    if(traceEnt->takedamage && traceEnt->client)
    {
        tent = G_TempEntity(tr.endpos, EV_MISSILE_HIT);
        tent->s.otherEntityNum = traceEnt->s.number;
        tent->s.eventParm = DirToByte(tr.plane.normal);
        tent->s.weapon = ent->s.weapon;
    }

    if(!traceEnt->takedamage)
        return qfalse;

    if(ent->client->ps.powerups[PW_QUAD])
    {
        G_AddEvent(ent, EV_POWERUP_QUAD, 0);
        s_quadFactor = g_quadfactor->value;
    }
    else
        s_quadFactor = 1;

    G_Damage(traceEnt, ent, ent, w_forward, tr.endpos, 50 * s_quadFactor, 0, MOD_GAUNTLET);

    return qtrue;
}

/*
======================================================================
 
MACHINEGUN
 
======================================================================
*/

/*
======================
SnapVectorTowards
 
Round a vector to integers for more efficient network
transmission, but make sure that it rounds towards a given point
rather than blindly truncating.  This prevents it from truncating 
into a wall.
======================
*/

#define MACHINEGUN_SPREAD	200
#define	MACHINEGUN_DAMAGE	7
#define	MACHINEGUN_TEAM_DAMAGE	5		// wimpier MG in teamplay

gentity_t *BulletHitEffect(gentity_t *shooter, vec3_t start, trace_t *tr)
{
    gentity_t *tent, *traceEnt;

	traceEnt = &g_entities[tr->entityNum];

	SnapVectorTowards(tr->endpos, start);

    tent = G_TempEntity(tr->endpos, (traceEnt->takedamage && traceEnt->client) ? EV_BULLET_HIT_FLESH : EV_BULLET_HIT_WALL);
    tent->s.eventParm = (traceEnt->takedamage && traceEnt->client) ? traceEnt->s.number : DirToByte(tr->plane.normal);
	tent->s.otherEntityNum = shooter->s.number;
	return tent;
}

void Bullet_Fire(gentity_t *ent, float spread, int damage)
{
	int hit;

	hit = Fire_HitScan(ent, spread, 8192*8, damage, 0, MOD_MACHINEGUN, 1, NULL, BulletHitEffect);
	if(hit)
		ent->client->accuracy_hits++;
}

/*
======================================================================
 
BFG
 
======================================================================
*/

void BFG_Fire(gentity_t *ent)
{
    gentity_t	*m;

    m = fire_bfg(ent, muzzle, w_forward);
    m->damage *= s_quadFactor;
    m->splashDamage *= s_quadFactor;

//	VectorAdd(m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta);	// "real" physics
}

/*
======================================================================
 
SHOTGUN
 
======================================================================
*/

// DEFAULT_SHOTGUN_SPREAD and DEFAULT_SHOTGUN_COUNT	are in bg_public.h, because
// client predicts same spreads
#define	DEFAULT_SHOTGUN_DAMAGE	10

// this should match CG_ShotgunPattern
void ShotgunPattern(vec3_t origin, vec3_t origin2, int seed, gentity_t *ent)
{
    int			i;
    float		r, u;
    vec3_t		end;
    vec3_t		_w_forward, _w_right, _w_up;
    int			oldScore, hits = 0;

    // derive the w_right and w_up vectors from the w_forward vector, because
    // the client won't have any other information
    VectorNormalize2(origin2, _w_forward);
    PerpendicularVector(_w_right, _w_forward);
    CrossProduct(_w_forward, _w_right, _w_up);

	VectorCopy(origin, muzzle);

    oldScore = ent->client->ps.persistant[PERS_SCORE];

    // generate the "random" spread pattern
    for(i = 0 ; i < DEFAULT_SHOTGUN_COUNT ; i++)
    {
        r = Q_crandom(&seed) * DEFAULT_SHOTGUN_SPREAD * 16;
        u = Q_crandom(&seed) * DEFAULT_SHOTGUN_SPREAD * 16;
        VectorMA(origin, 8192 * 16, _w_forward, end);
        VectorMA(end, r, _w_right, end);
        VectorMA(end, u, _w_up, end);

		VectorSubtract(end, origin, w_forward);
		VectorNormalize(w_forward);

		hits += Fire_HitScan(ent, 0, 8192 * 16, DEFAULT_SHOTGUN_DAMAGE, 0, MOD_SHOTGUN, 1, NULL, NULL);
    }

	ent->client->accuracy_hits += (hits) ? 1 : 0;
}

void weapon_sw_upershotgun_fire(gentity_t *ent)
{
    gentity_t		*tent;

    // send shotgun blast
    tent = G_TempEntity(muzzle, EV_SHOTGUN);
    VectorScale(w_forward, 4096, tent->s.origin2);
    SnapVector(tent->s.origin2);
    tent->s.eventParm = rand() & 255;		// seed for spread pattern
    tent->s.otherEntityNum = ent->s.number;

    ShotgunPattern(tent->s.pos.trBase, tent->s.origin2, tent->s.eventParm, ent);
}

/*
======================================================================
 
GRENADE LAUNCHER
 
======================================================================
*/

void weapon_grenadelauncher_fire(gentity_t *ent)
{
    gentity_t	*m;

    // extra vertical velocity
    w_forward[2] += 0.2f;
    VectorNormalize(w_forward);

    m = fire_grenade(ent, muzzle, w_forward);
    m->damage *= s_quadFactor;
    m->splashDamage *= s_quadFactor;

//	VectorAdd(m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta);	// "real" physics
}

/*
======================================================================
 
ROCKET
 
======================================================================
*/
void Weapon_RocketLauncher_Fire(gentity_t *ent)
{
    gentity_t	*m;

    m = fire_rocket(ent, muzzle, w_forward);
    m->damage *= s_quadFactor;
    m->splashDamage *= s_quadFactor;

//	VectorAdd(m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta);	// "real" physics
}

/*
======================================================================
 
PLASMA GUN
 
======================================================================
*/
void Weapon_Plasmagun_Fire(gentity_t *ent)
{
    gentity_t	*m;

    m = fire_plasma(ent, muzzle, w_forward);
    m->damage *= s_quadFactor;
    m->splashDamage *= s_quadFactor;

//	VectorAdd(m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta);	// "real" physics
}

/*
======================================================================
 
RAILGUN
 
======================================================================
*/
gentity_t *Fire_RailgunEffect(gentity_t *shooter, vec3_t start, trace_t *tr)
{
    gentity_t *tent;

	tent = G_TempEntity(tr->endpos, EV_RAILTRAIL);
    tent->s.clientNum = shooter->s.clientNum;
    tent->s.eventParm = (tr->surfaceFlags & SURF_NOIMPACT) ? 255 : DirToByte(tr->plane.normal);

    VectorCopy(start, tent->s.origin2);
	return tent;
}

void weapon_railgun_fire(gentity_t *ent)
{
	int hits;
	
	VectorMA(muzzle, 4, w_right, muzzle);
    VectorMA(muzzle, -1, w_up, muzzle);

	hits = Fire_HitScan(ent, 0, 8192, 100, 0, MOD_RAILGUN, 8, Fire_RailgunEffect, NULL);

	if(hits == 0)
        ent->client->accurateCount = 0;
    else
    {
        ent->client->accurateCount += hits;
        if(ent->client->accurateCount >= 2)
        {
            ent->client->accurateCount -= 2;
            ent->client->ps.persistant[PERS_IMPRESSIVE_COUNT]++;
            ent->client->ps.eFlags &= ~(EF_AWARD_IMPRESSIVE | EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP);
            ent->client->ps.eFlags |= EF_AWARD_IMPRESSIVE;
            ent->client->rewardTime = level.time + REWARD_SPRITE_TIME;
        }
        ent->client->accuracy_hits++;
    }
}

/*
======================================================================
 
GRAPPLING HOOK
 
======================================================================
*/

void Weapon_GrapplingHook_Fire(gentity_t *ent)
{
    if(!ent->client->fireHeld && !ent->client->hook)
        fire_grapple(ent, muzzle, w_forward);

    ent->client->fireHeld = qtrue;
}

void Weapon_HookFree(gentity_t *ent)
{
    ent->parent->client->hook = NULL;
    ent->parent->client->ps.pm_flags &= ~PMF_GRAPPLE_PULL;
    G_FreeEntity(ent);
}

void Weapon_HookThink(gentity_t *ent)
{
	if(!ent->parent->client->ps.weaponAmmo[2])
	{
		Weapon_HookFree(ent);
		return;
	}

    if(ent->enemy)
    {
        vec3_t v, oldorigin;

        VectorCopy(ent->r.currentOrigin, oldorigin);
        v[0] = ent->enemy->r.currentOrigin[0] + (ent->enemy->r.mins[0] + ent->enemy->r.maxs[0]) * 0.5;
        v[1] = ent->enemy->r.currentOrigin[1] + (ent->enemy->r.mins[1] + ent->enemy->r.maxs[1]) * 0.5;
        v[2] = ent->enemy->r.currentOrigin[2] + (ent->enemy->r.mins[2] + ent->enemy->r.maxs[2]) * 0.5;
        SnapVectorTowards(v, oldorigin);	// save net bandwidth

        G_SetOrigin(ent, v);
    }

    VectorCopy(ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);
}

/*
======================================================================
 
LIGHTNING GUN
 
======================================================================
*/

gentity_t *LightningHitEffect(gentity_t *shooter, vec3_t start, trace_t *tr)
{
    gentity_t *tent = NULL, *traceEnt;

	traceEnt = &g_entities[tr->entityNum];

    if(traceEnt->takedamage && traceEnt->client)
    {
        tent = G_TempEntity(tr->endpos, EV_MISSILE_HIT);
        tent->s.otherEntityNum = traceEnt->s.number;
        tent->s.eventParm = DirToByte(tr->plane.normal);
        tent->s.weapon = shooter->s.weapon;
    }
    else if(!(tr->surfaceFlags & SURF_NOIMPACT))
    {
        tent = G_TempEntity(tr->endpos, EV_MISSILE_MISS);
        tent->s.eventParm = DirToByte(tr->plane.normal);
    }

	return tent;
}

void Weapon_LightningFire(gentity_t *ent)
{
	if(Fire_HitScan(ent, 0, LIGHTNING_RANGE, 8, 0, MOD_LIGHTNING, 4, NULL, LightningHitEffect))
		ent->client->accuracy_hits++;
}

//======================================================================

/*
===============
LogAccuracyHit
===============
*/
qboolean LogAccuracyHit(gentity_t *target, gentity_t *attacker)
{
    if(!target->takedamage)
    {
        return qfalse;
    }

    if(target == attacker)
    {
        return qfalse;
    }

    if(!target->client)
    {
        return qfalse;
    }

    if(!attacker->client)
    {
        return qfalse;
    }

    if(target->client->ps.stats[STAT_HEALTH] <= 0)
    {
        return qfalse;
    }

    if(OnSameTeam(target, attacker))
    {
        return qfalse;
    }

    return qtrue;
}


/*
===============
CalcMuzzlePoint
 
set muzzle location relative to pivoting eye
===============
*/
void CalcMuzzlePoint(gentity_t *ent, vec3_t w_forward, vec3_t w_right, vec3_t w_up, vec3_t muzzlePoint)
{
    VectorCopy(ent->s.pos.trBase, muzzlePoint);
    muzzlePoint[2] += ent->client->ps.viewheight;
    VectorMA(muzzlePoint, 14, w_forward, muzzlePoint);
    // snap to integer coordinates for more efficient network bandwidth usage
    SnapVector(muzzlePoint);
}

/*
===============
CalcMuzzlePointOrigin
 
set muzzle location relative to pivoting eye
===============
*/
void CalcMuzzlePointOrigin(gentity_t *ent, vec3_t origin, vec3_t w_forward, vec3_t w_right, vec3_t w_up, vec3_t muzzlePoint)
{
    VectorCopy(ent->s.pos.trBase, muzzlePoint);
    muzzlePoint[2] += ent->client->ps.viewheight;
    VectorMA(muzzlePoint, 14, w_forward, muzzlePoint);
    // snap to integer coordinates for more efficient network bandwidth usage
    SnapVector(muzzlePoint);
}

/*
===============
FireWeapon
===============
*/
void svFireWeapon(gentity_t *ent, qboolean alt);
void FireWeapon(gentity_t *ent, qboolean alt)
{
    s_quadFactor = (ent->client->ps.powerups[PW_QUAD]) ? g_quadfactor->value : 1;

    // track shots taken for accuracy tracking.  Grapple is not a weapon and gauntet is just not tracked
    ent->client->accuracy_shots++;

    // set aiming directions
    AngleVectors(ent->client->ps.viewangles, w_forward, w_right, w_up);

    CalcMuzzlePointOrigin(ent, ent->client->oldOrigin, w_forward, w_right, w_up, muzzle);

    svFireWeapon(ent, alt);
}
