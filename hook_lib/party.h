#pragma once
#include "Main.hpp"

inline utils::hook::detour partyhost_startprivateparty;
void PartyHost_StartPrivateParty_Detour(int localClientNum, int localControllerIndex, bool currentlyActive, int hostType);