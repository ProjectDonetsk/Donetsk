#pragma once
#include "Main.hpp"

inline utils::hook::detour r_endframe;
void R_EndFrame_Detour();

const char* username_Detour();

inline utils::hook::detour gscr_spawnbrcircle;
void GScr_SpawnBrCircle_Detour(uintptr_t scrContext);

void patchGame();