#include "weapons.h"
#include "game_inc.h"

void PM_WeaponUseAmmo_Detour(__int64 playerstate, Weapon* weapon, char a3, int a4, int hand)
{
	bool sv_cheats = Dvar_GetBoolSafe("NTPNRQTKNP");

	if (!(player_sustainammo->current.enabled && sv_cheats))
	{
		PM_WeaponUseAmmo.stub<void>(playerstate, weapon, a3, a4, hand);
	}
}

void CG_OverrideImpactEffectType(uintptr_t localClientNum, unsigned int sourceEntityNum, int* fxImpactType) // 0x141733CD0_g
{
	//33 = red, 34 = blue, 35 = pink, 36 = green
	fxImpactType[2] = 34;
	cg_overrideimpacteffecttype.stub<__int64>(localClientNum, sourceEntityNum, fxImpactType);
}
