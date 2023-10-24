#pragma once
#include "Main.hpp"

inline bool initiatedevgui;

inline utils::hook::detour cl_createdevgui;
void CL_CreateDevGui_Detour(int fsMenuEntries, const char* modeCfg);