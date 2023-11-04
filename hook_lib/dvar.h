#pragma once
#include "Main.hpp"

void addCustomDvars();

inline utils::hook::detour dvar_registerbool;
dvar_t* Dvar_RegisterBool_Detour(const char* dvarName, bool value, unsigned int flags, const char* description);

inline utils::hook::detour dvar_registerstring;
dvar_t* Dvar_RegisterString_Detour(const char* dvarName, const char* value, unsigned int flags, const char* description);

inline utils::hook::detour dvar_findvarbyname;
dvar_t* Dvar_FindVarByName_Detour(const char* dvarName);

bool CheatsEnabled();