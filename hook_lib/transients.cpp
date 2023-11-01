#include "addr_utils.hpp"
#include "transients.h"
#include "game_inc.h"

void CL_TransientsCollisionMP_SetTransientMode_Detour(int mode)
{
	if (strcmp(Dvar_GetStringSafe("NSQLTTMRMP"), "mp_donetsk") == 0)
	{
		*reinterpret_cast<int*>(0x145CC7534_g) = 1;
	}
	else {
		*reinterpret_cast<int*>(0x145CC7534_g) = mode;
	}
}

char CL_TransientsMP_ProcessLoadingQueue_Detour()
{
	return CL_TransientsMP_ProcessLoadingQueue.stub<char>();
}