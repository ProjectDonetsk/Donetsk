#include "dvar.h"
#include "game_inc.h"

void addCustomDvars()
{
	Cmd_AddCommandInternal("set_byte", set_byte_f, &set_byte_f_VAR);
	Cmd_AddCommandInternal("set_short", set_short_f, &set_short_f_VAR);
	Cmd_AddCommandInternal("set_int", set_int_f, &set_int_f_VAR);
	Cmd_AddCommandInternal("set_float", set_float_f, &set_float_f_VAR);
	Cmd_AddCommandInternal("set_pointer", set_pointer_f, &set_pointer_f_VAR);
	Cmd_AddCommandInternal("quit", Cmd_Quit_f, &quit_f_VAR);
	Cmd_AddCommandInternal("openmenu", Cmd_OpenMenu_f, &openmenu_f_VAR);
	Cmd_AddCommandInternal("addbot", Cmd_AddBot_f, &addbot_f_VAR);
	Cmd_AddCommandInternal("ddldump", Cmd_DDLDump_f, &ddldump_f_VAR);
	Cmd_AddCommandInternal("weapondefdump", Cmd_WeaponDefDump_f, &weapondefdump_f_VAR);
	//Cmd_AddCommandInternal("view_vehicle_ents", Cmd_ViewVehicleEnts_f, &view_vehicle_ents_f_VAR);
	// Cmd_AddCommandInternal("save_inventory", Cmd_LoadoutSave_f, &loadout_save_f_VAR);
	Cmd_AddCommandInternal("map_restart", SV_CmdsMP_MapRestart_f, &MapRestart_f_VAR);
	Cmd_AddCommandInternal("fast_restart", SV_CmdsMP_FastRestart_f, &FastRestart_f_VAR);
	Cmd_AddCommandInternal("setOmnvar", Cmd_Omnvar_Set_f, &omnvar_set_f_VAR);
	// Cmd_AddCommandInternal("dumpomnvars", Cmd_Omnvars_Dump_f, &omnvar_dump_f_VAR);
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