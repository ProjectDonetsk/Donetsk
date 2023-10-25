#pragma once
#include "Main.hpp"

inline utils::hook::detour db_loadxfile;
int DB_LoadXFile_Detour(const char* zoneName, uintptr_t zoneMem, uintptr_t assetList, int zoneFlags, bool wasPaused, int failureMode, uintptr_t outSignature);

inline utils::hook::detour db_pollfastfilestate;
int DB_PollFastfileState_Detour(const char* zoneName);

inline utils::hook::detour db_checkxfileversion;
bool DB_CheckXFileVersion_Detour();