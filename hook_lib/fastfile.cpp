#include "fastfile.h"
#include "game_inc.h"

int DB_LoadXFile_Detour(const char* zoneName, uintptr_t zoneMem, uintptr_t assetList, int zoneFlags, bool wasPaused, int failureMode, uintptr_t outSignature)
{
	return db_loadxfile.stub<int>(zoneName, zoneMem, assetList, zoneFlags, wasPaused, failureMode, outSignature);
}

int DB_PollFastfileState_Detour(const char* zoneName)
{
	if (strcmp(zoneName, "mp_donetsk_cg_ls_tr") == 0)
	{
		return 2;
	}

	//printf("%s\n", zoneName);

	return db_pollfastfilestate.stub<int>(zoneName);
}

bool DB_CheckXFileVersion_Detour()
{
	return true;
}