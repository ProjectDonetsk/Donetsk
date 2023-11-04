#include "dvar.h"
#include "game_inc.h"

void addCustomDvars()
{
	
}

dvar_t* Dvar_RegisterBool_Detour(const char* dvarName, bool value, unsigned int flags, const char* description)
{
	if (strcmp(dvarName, "LSTQOKLTRN") == 0) {
		printf("dvar registered!\n");
		value = true;
	}
	if (strcmp(dvarName, "MPSSOTQQPM") == 0) {
		printf("dvar registered!\n");
		value = true;
	}
	dvar_t* ret = dvar_registerbool.stub<dvar_t*>(dvarName, value, flags, description);
	return ret;
}

dvar_t* Dvar_RegisterString_Detour(const char* dvarName, const char* value, unsigned int flags, const char* description)
{
	return dvar_registerstring.stub<dvar_t*>(dvarName, value, flags, description);
}

dvar_t* Dvar_FindVarByName_Detour(const char* dvarName)
{
	dvar_t* ret = dvar_findvarbyname.stub<dvar_t*>(dvarName);
	return ret;
}

bool CheatsEnabled()
{
	return sv_cheats->current.enabled;
}