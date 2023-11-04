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

	print_debug = Dvar_RegisterBool("print_debug", false, 0, "Print debug output to the external console");

	lui_cod_registerdvars.stub<void>();
}

int LuaShared_LuaCall_IsDemoBuild_Detour(uintptr_t luaVM)
{
	lua_pushboolean(luaVM, 1);
	return 1;
}

void LUI_CoD_LuaCall_EngineNotifyServer_Detour(uintptr_t luaVM) {
	static std::unordered_map<std::string, std::function<void()>> handlerMap{
		{"class_edit", SaveInventory},
		{"loadout_showcase_entered", SaveInventory}
	};
	if (lua_isstring(luaVM, 1)) {
		size_t strLen = 0;
		const char* rawStr = lua_tolstring(luaVM, 1, &strLen);
		std::string str(rawStr, strLen);
		if (handlerMap.find(str) != handlerMap.cend())
		{
			handlerMap.at(str)();
		}
	}
	lui_cod_luacall_enginenotifyserver_detour_impl.stub<void>(luaVM);
}