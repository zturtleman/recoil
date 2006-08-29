#include "g_local.h"
#include "../cgame/cg_local.h"

typedef enum
{
    AT_MA1,
    AT_MA2,
    AT_MT1,
    AT_MT2,
    AT_MD1,
    AT_MD2,
    AT_RA1,
    AT_RA2,
    AT_RT1,
    AT_RT2,
    AT_RD1,
    AT_RD2,
    AT_SA1,
    AT_SA2,
    AT_ST1,
    AT_ST2,
    AT_SD1,
    AT_SD2,
} attack_e;

typedef struct
{
    int damage, splashDamage;
    float splashRadius;
    int time;
    vec3_t min, max;
    vec3_t velAdd;
} attack_t;

attack_t attacks[] = 
{
    { // Thrust down
        30, 0, 0,
        1000,
        {-20, -20, -40}, {20, 20, 0},
        {0, 0, -200}
    },
    { // Kick
        30, 0, 0,
        800,
        {-20, -20, -40}, {20, 20, 0},
        {0, 0, -200}
    },
    { // Punch
        30, 0, 0,
        1000,
        {0, 0, 0}, {20, 40, 0},
        {0, 10, 0}
    },
    { // Run
        30, 0, 0,
        100,
        {0, 0, 0}, {20, 40, 0},
        {0, 20, 0}
    },
    { // Block
        30, 0, 0,
        600,
        {-40, 20, -40}, {40, 40, 40},
        {0, 0, 0}
    },
    { // Deflect
        30, 0, 0,
        600,
        {-40, 20, -40}, {40, 40, 40},
        {0, 0, 0}
    },
    {
        30, 0, 0,
        1000,
        {-20, -20, -40}, {20, 20, 0},
        {0, 0, -200}
    },
    {
        30, 0, 0,
        800,
        {-20, -20, -40}, {20, 20, 0},
        {0, 0, -200}
    },
    {
        30, 0, 0,
        1000,
        {0, 0, 0}, {20, 40, 0},
        {0, 10, 0}
    },
    {
        30, 0, 0,
        100,
        {0, 0, 0}, {20, 40, 0},
        {0, 20, 0}
    },
    {
        30, 0, 0,
        600,
        {-40, 20, -40}, {40, 40, 40},
        {0, 0, 0}
    },
    {
        30, 0, 0,
        600,
        {-40, 20, -40}, {40, 40, 40},
        {0, 0, 0}
    },
    {
        30, 0, 0,
        1000,
        {-20, -20, -40}, {20, 20, 0},
        {0, 0, -200}
    },
    {
        30, 0, 0,
        800,
        {-20, -20, -40}, {20, 20, 0},
        {0, 0, -200}
    },
    {
        30, 0, 0,
        1000,
        {0, 0, 0}, {20, 40, 0},
        {0, 10, 0}
    },
    {
        30, 0, 0,
        100,
        {0, 0, 0}, {20, 40, 0},
        {0, 20, 0}
    },
    {
        30, 0, 0,
        600,
        {-40, 20, -40}, {40, 40, 40},
        {0, 0, 0}
    },
    {
        30, 0, 0,
        600,
        {-40, 20, -40}, {40, 40, 40},
        {0, 0, 0}
    },
};

attack_t *getAttack(int weapon, qboolean a, qboolean d, qboolean alt)
{
    int index = (weapon==WP_MELEE) ? AT_MA1 : (weapon==WP_RANGE) ? AT_RA1 : AT_SA1;
    index += (a) ? 0 : (d) ? 4 : 2;
    return attacks + (index + ((alt) ? 1 : 0));
}

int Defualt_BG_GetAttackTime(int weapon, qboolean a, qboolean d, qboolean alt)
{
    return getAttack(weapon, a, d, alt)->time;
}

extern vec3_t w_forward;

void Defualt_SV_FireWeapon(gentity_t *ent, qboolean alt)
{
    vec3_t velAdd;
    attack_t *attack = getAttack(ent->s.weapon, ent->client->ps.groundEntityNum == ENTITYNUM_NONE, ent->client->ps.pm_flags & PMF_DUCKED, alt);

    VectorCopy(attack->min, ent->attack_min);
    VectorCopy(attack->max, ent->attack_max);
    VectorAdd(attack->velAdd, ent->client->ps.velocity, ent->client->ps.velocity);
}

void Defualt_CL_FireWeapon(centity_t *ent, qboolean alt)
{
/*    switch(ent->currentState.weapon)
    {
    case WP_MELEE:
        weapon_grenadelauncher_fire(ent);
        break;
    case WP_RANGE:
        weapon_railgun_fire(ent);
        break;
    case WP_SPECIAL:
        Weapon_RocketLauncher_Fire(ent);
        break;
    }*/
}

qhandle_t Defualt_CL_AmmoIcon(int weapon)
{
    switch(weapon)
    {
    case WP_MELEE:
        return RE_RegisterShader("icons/iconw_gauntlet");
    case WP_RANGE:
        return RE_RegisterShader("icons/iconw_machinegun");
    case WP_SPECIAL:
        return RE_RegisterShader("icons/iconw_grapple");
    }

    return 0;
}

qhandle_t Defualt_CL_AmmoModel(int weapon)
{
    switch(weapon)
    {
    case WP_MELEE:
        return RE_RegisterModel("models/weapons2/gauntlet/gauntlet.md3");
    case WP_RANGE:
        return RE_RegisterModel("models/weapons2/machinegun/machinegun.md3");
    case WP_SPECIAL:
        return RE_RegisterModel("models/weapons2/grapple/grapple.md3");
    }

    return 0;
}