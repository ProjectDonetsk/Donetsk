#include "addr_utils.hpp"
#include "devgui.h"

void CL_CreateDevGui_Detour(int fsMenuEntries, const char* modeCfg)
{
	auto DevGui_AddCommand = reinterpret_cast<void(*)(const char* path, const char* command)>(0x1417E58B0_g);
	auto DevGui_AddDvar = reinterpret_cast<void(*)(const char* path, uintptr_t dvar)>(0x1417E5940_g);

	cl_createdevgui.stub<void>(fsMenuEntries, modeCfg);
}