#pragma once
#include "Main.hpp"

inline utils::hook::detour cg_mainmp_init;
void CG_MainMP_Init_Detour(int localClientNum, int serverMessageNum, int serverCommandSequence, int clientNum, void* hunkUser);