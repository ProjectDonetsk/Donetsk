#include "lui_cod.h"
#include "game_inc.h"

void LUI_CoD_RegisterDvars_Detour()
{
	printf("registering lui dvars\n");
	player_name = Dvar_RegisterString("player_name", "Player1", 0, "Sets the player name.");
	sv_cheats = Dvar_RegisterBool("sv_cheats", false, 0, "Enables cheats to be used on a server");
	spawn_br_gas = Dvar_RegisterBool("spawn_br_gas", true, 0, "Disables gas in battle royale maps");
	show_watermark = Dvar_RegisterBool("show_watermark", false, 0, "Shows the watermark for codUPLOADER");

	player_sustainammo = Dvar_RegisterBool("player_sustainAmmo", false, 0, "Firing weapon will not decrease clip ammo.");

	lui_cod_registerdvars.stub<void>();
}

int LuaShared_LuaCall_IsDemoBuild_Detour(uintptr_t luaVM)
{
	lua_pushboolean(luaVM, 1);
	return 1;
}

int LUI_CoD_LuaCall_GetBlueprintData_impl_Detour(uintptr_t luaState)
{
	SaveInventory();
	return 0;
}