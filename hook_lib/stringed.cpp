#include "stringed.h"
#include "game_inc.h"

const char* SEH_StringEd_GetString_Detour(const char* pszReference)
{
	const char* ret = seh_stringed_getstring.stub<const char*>(pszReference);

	if (!pszReference[1])
	{
		if ((*pszReference & 0x80) != 0)
			return "t";
		return pszReference;
	}

	GamerProfile_SetDataByName(0, "acceptedEULA", 1);
	GamerProfile_SetDataByName(0, "hasEverPlayed_MainMenu", 1);

	// LUA_MENU/MAPNAME_ANIYAH // Aniyah Palace
	if (strstr(pszReference, "LUA_MENU/MAPNAME_ANIYAH"))
	{
		if (pszReference[23] == '\0')
		{
			return "^1no work";
		}
	}

	if (strstr(pszReference, "LUA_MENU/MAPNAME_DEADZONE") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_M_CAGE") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_CAVE_AM") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_CAVE") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_M_CARGO") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_CRASH2") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_M_OVERUNDER") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_EUPHRATES") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_RAID") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_M_SHOWERS") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_RUNNER_AM") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_RUNNER") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_HACKNEY_AM") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_HACKNEY_YARD") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_M_HILL") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_PICCADILLY") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_M_PINE") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_SPEAR_AM") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_SPEAR") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_PETROGRAD") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_M_STACK") ||
		strstr(pszReference, "LUA_MENU/MAPNAME_VACANT")) {
		return "^1no work";
	}

	if (strstr(pszReference, "MENU/CAMPAIGN"))
	{
		return "^3Campaign is not available in this build of the game.";
	}

	if (strstr(pszReference, "LUA_MENU/LOCAL_COOP_DESC"))
	{
		return "^3CO-OP is not available in this build of the game.";
	}

	if (strstr(pszReference, "LUA_MENU/LOCAL_MULTIPLAYER_CAPS"))
	{
		return "MULTIPLAYER";
	}

	if (strstr(pszReference, "MENU_SP/CAMPAIGN"))
	{
		return "^1CAMPAIGN";
	}

	if (strstr(pszReference, "LUA_MENU/LOCAL_COOP_CAPS"))
	{
		return "^1LOCAL CO-OP";
	}

	return ret;
}