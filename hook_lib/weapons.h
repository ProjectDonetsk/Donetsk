#pragma once
#include "Main.hpp"

inline utils::hook::detour PM_WeaponUseAmmo;
void PM_WeaponUseAmmo_Detour(__int64 playerstate, Weapon* weapon, char a3, int a4, int hand);

inline utils::hook::detour cg_overrideimpacteffecttype;
void CG_OverrideImpactEffectType(uintptr_t localClientNum, unsigned int sourceEntityNum, int* fxImpactType);

TracerDef* GetTracerDef(const char* asset);

void Dump_WeaponDef();

void Load_WeaponDef();