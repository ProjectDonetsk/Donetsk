#pragma once
#include "Main.hpp"

inline utils::hook::detour com_gamemode_supportsfeature;
bool Com_GameMode_SupportsFeature_Detour(unsigned int featureID);