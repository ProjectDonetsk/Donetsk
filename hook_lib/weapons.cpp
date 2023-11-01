#include "addr_utils.hpp"
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

TracerDef* GetTracerDef(const char* asset) {
	TracerDef* tracerDef = DB_FindXAssetHeader(ASSET_TYPE_TRACER, asset, 0).tracerDef;
	if (tracerDef) return tracerDef;
	return 0;
}

void Dump_WeaponDef() {
	char path[MAX_PATH + 1];
	strcpy(path, Dvar_GetStringSafe("LOOQOTRNTN"));
	strcat(path, "\\players\\weapondef.json");
	bool inFrontend = *(bool*)(0x1459D1750_g);
	if (!inFrontend) {
		nlohmann::json weaponDefJson;
		WeaponCompleteDef** bg_weaponCompleteDefs = (WeaponCompleteDef**)(0x14C6EC870_g);
		for (int i = 0; i < 550; i++) {
			WeaponCompleteDef* weap = bg_weaponCompleteDefs[i];
			if (!weap) continue;
			if (strstr(weap->szInternalName, "iw8") && !strstr(weap->szInternalName, "watch") && !strstr(weap->szInternalName, "execution") && !strstr(weap->szInternalName, "plyr")) {
				weaponDefJson[weap->szInternalName]["vfxImpactType"] = weap->vfxImpactType;
				weaponDefJson[weap->szInternalName]["ladderWeapon"] = weap->weapDef->ladderWeapon;
				weaponDefJson[weap->szInternalName]["canHoldBreath"] = weap->weapDef->canHoldBreath;
				weaponDefJson[weap->szInternalName]["iFireTime"] = weap->weapDef->iFireTime;
				weaponDefJson[weap->szInternalName]["bBoltAction"] = weap->weapDef->bBoltAction;
				weaponDefJson[weap->szInternalName]["fireType"] = weap->weapDef->fireType;
				weaponDefJson[weap->szInternalName]["iStartAmmo"] = weap->weapDef->iStartAmmo;
				weaponDefJson[weap->szInternalName]["iMaxAmmo"] = weap->weapDef->iMaxAmmo;
				if (weap->weapDef->tracerType)
					weaponDefJson[weap->szInternalName]["tracerType"] = weap->weapDef->tracerType->name;
			}
		}
		std::ofstream JsonOut(path);
		JsonOut << weaponDefJson;
	}
	else {
		Com_SetErrorMessage("[DLL ERROR] Must be in-game to dump WeaponDef.");
	}


}

void Load_WeaponDef() {
	char path[MAX_PATH + 1];
	strcpy(path, Dvar_GetStringSafe("LOOQOTRNTN"));
	strcat(path, "\\players\\weapondef.json");
	bool inFrontend = *(bool*)(0x1459D1750_g);
	if (!inFrontend) {
		if (file_exists(path)) {
			std::ifstream jsonPath(path);
			nlohmann::json weaponDefJson = nlohmann::json::parse(jsonPath);
			WeaponCompleteDef** bg_weaponCompleteDefs = (WeaponCompleteDef**)(0x14C6EC870_g);
			for (int i = 0; i < 550; i++) {
				WeaponCompleteDef* weap = bg_weaponCompleteDefs[i];
				if (!weap) continue;
				if (weaponDefJson.contains(weap->szInternalName)) {
					weap->vfxImpactType = weaponDefJson[weap->szInternalName]["vfxImpactType"];
					weap->weapDef->ladderWeapon = weaponDefJson[weap->szInternalName]["ladderWeapon"];
					weap->weapDef->canHoldBreath = weaponDefJson[weap->szInternalName]["canHoldBreath"];
					weap->weapDef->iFireTime = weaponDefJson[weap->szInternalName]["iFireTime"];
					weap->weapDef->bBoltAction = weaponDefJson[weap->szInternalName]["bBoltAction"];
					weap->weapDef->fireType = weaponDefJson[weap->szInternalName]["fireType"];
					weap->weapDef->iStartAmmo = weaponDefJson[weap->szInternalName]["iStartAmmo"];
					weap->weapDef->iMaxAmmo = weaponDefJson[weap->szInternalName]["iMaxAmmo"];

					if (weaponDefJson[weap->szInternalName].contains("tracerType")) {
						weap->weapDef->tracerType = GetTracerDef(weaponDefJson[weap->szInternalName]["tracerType"].get<std::string>().c_str());
					}
				}
			}
		}
		else {
			Com_SetErrorMessage("[DLL ERROR] weapondef JSON is not present in players directory.");
		}
	}
	else {
		Com_SetErrorMessage("[DLL ERROR] Must be in-game to load custom WeaponDef.");
	}
}