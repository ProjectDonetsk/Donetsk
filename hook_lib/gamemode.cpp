#include "gamemode.h"

bool Com_GameMode_SupportsFeature_Detour(unsigned int featureID)
{
	if (featureID == 70) // TIMESCALE_TWEAKING
	{
		return true;
	}

	if (featureID == 33) // GRAVITY_CHANGE_ALLOWED
	{
		return true;
	}

	return com_gamemode_supportsfeature.stub<bool>(featureID);
}