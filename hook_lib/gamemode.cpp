#include "gamemode.h"

bool Com_GameMode_SupportsFeature_Detour(unsigned int featureID)
{
	static dvar_t* com_timescale;
	static dvar_t* timescale;

	if (com_timescale == nullptr && featureID == 70)
	{
		com_timescale = Dvar_FindVarByName("LNOTRKNRPS");
		timescale = Dvar_FindVarByName("MSNTNLNQNM");
		// fixes slowmotion final killcam, but not in an ideal way
	}

	if (featureID == 70 && timescale->current.value != 1.0) // TIMESCALE_TWEAKING
	{
		return true;
	}

	if (featureID == 33) // GRAVITY_CHANGE_ALLOWED
	{
		return true;
	}

	return com_gamemode_supportsfeature.stub<bool>(featureID);
}