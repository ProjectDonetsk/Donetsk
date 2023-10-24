#pragma once
#include "Main.hpp"

inline utils::hook::detour net_outofbanddata;
bool NET_OutOfBandData_Detour(int sock, netadr_t* adr, const unsigned __int8* format, int len);