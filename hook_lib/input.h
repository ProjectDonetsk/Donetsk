#pragma once
#include "Main.hpp"

inline utils::hook::detour cl_keys_event;
void CL_Keys_Event_Detour(int localClientNum, int key, bool down, unsigned int time, int virtualKey, int controllerIndex);

inline utils::hook::detour cl_inputmp_execbinding;
void CL_InputMP_ExecBinding_Detour(int localClientNum, int kb, int key, int forceNotify);