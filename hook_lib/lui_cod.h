#pragma once
#include "Main.hpp"

inline utils::hook::detour lui_cod_registerdvars;
void LUI_CoD_RegisterDvars_Detour();

int LuaShared_LuaCall_IsDemoBuild_Detour(uintptr_t luaVM);

inline utils::hook::detour lui_cod_luacall_getblueprintdata_impl;
int LUI_CoD_LuaCall_GetBlueprintData_impl_Detour(uintptr_t luaState);