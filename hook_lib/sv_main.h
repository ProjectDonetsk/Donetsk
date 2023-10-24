#pragma once
#include "Main.hpp"

inline utils::hook::detour sv_updateuserinfo_detour;
void SV_UpdateUserinfo_f(unsigned char* cl);