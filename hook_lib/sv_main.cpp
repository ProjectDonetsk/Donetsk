#include "addr_utils.hpp"
#include "sv_main.h"
#include "game_inc.h"

void SV_UpdateUserinfo_f(unsigned char* cl)
{
	auto SV_Cmd_Argv = reinterpret_cast<char* (*)(int)>(0x141298B10_g);
	auto Info_ValueForKey = reinterpret_cast<char* (*)(const char*, const char*)>(0x1413F2A10_g);
	// more checks can be added here (it's patched in current mw19, vanguard, and mwii, could probably find the actual fix there)
	if (!strlen(Info_ValueForKey(SV_Cmd_Argv(1), "platform")))
	{
		return;
	}
	sv_updateuserinfo_detour.stub<void>(cl);
}