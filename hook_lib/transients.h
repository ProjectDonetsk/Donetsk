#pragma once
#include "Main.hpp"

void CL_TransientsCollisionMP_SetTransientMode_Detour(int mode);

inline utils::hook::detour CL_TransientsMP_ProcessLoadingQueue;
char CL_TransientsMP_ProcessLoadingQueue_Detour();