#include "addr_utils.hpp"
#include "g_cmds.h"
#include "game_inc.h"

void addCustomCmds()
{
	Cmd_AddCommandInternal("set_byte", set_byte_f, &set_byte_f_VAR);
	Cmd_AddCommandInternal("set_short", set_short_f, &set_short_f_VAR);
	Cmd_AddCommandInternal("set_int", set_int_f, &set_int_f_VAR);
	Cmd_AddCommandInternal("set_float", set_float_f, &set_float_f_VAR);
	Cmd_AddCommandInternal("set_pointer", set_pointer_f, &set_pointer_f_VAR);
	Cmd_AddCommandInternal("quit", Cmd_Quit_f, &quit_f_VAR);
	Cmd_AddCommandInternal("openmenu", Cmd_OpenMenu_f, &openmenu_f_VAR);
	Cmd_AddCommandInternal("addbot", Cmd_AddBot_f, &addbot_f_VAR);
	Cmd_AddCommandInternal("addtestclient", Cmd_AddTestClient_f, &addTestClient_f_VAR);
	Cmd_AddCommandInternal("ddldump", Cmd_DDLDump_f, &ddldump_f_VAR);
	// Cmd_AddCommandInternal("weapondefdump", Cmd_WeaponDefDump_f, &weapondefdump_f_VAR);
	//Cmd_AddCommandInternal("view_vehicle_ents", Cmd_ViewVehicleEnts_f, &view_vehicle_ents_f_VAR);
	// Cmd_AddCommandInternal("save_inventory", Cmd_LoadoutSave_f, &loadout_save_f_VAR);
	Cmd_AddCommandInternal("map_restart", SV_CmdsMP_MapRestart_f, &MapRestart_f_VAR);
	Cmd_AddCommandInternal("fast_restart", SV_CmdsMP_FastRestart_f, &FastRestart_f_VAR);
	Cmd_AddCommandInternal("setOmnvar", Cmd_Omnvar_Set_f, &omnvar_set_f_VAR);
	// Cmd_AddCommandInternal("dumpomnvars", Cmd_Omnvars_Dump_f, &omnvar_dump_f_VAR);
	Cmd_AddCommandInternal("unlockAll", Cmd_UnlockAll_f, &unlockall_f_VAR);
	Cmd_AddCommandInternal("dumpweapondef", Cmd_WeaponDefDump_f, &dump_weapdefs_f_VAR);
	Cmd_AddCommandInternal("loadweapondef", Cmd_WeaponDef_Load_f, &load_weapdef_f_VAR);
}

void G_CmdsMP_ClientCommand_Detour(int clientNum)
{
	g_entities = *reinterpret_cast<gentity_s**>(0x14BC20F00_g);

	uintptr_t client = g_entities[clientNum].get<uintptr_t>(0x150);

	char command[1024];
	SV_Cmd_ArgvBuffer(0, command, 1024);

	if (client) {
		if (strcmp(command, "noclip") == 0) {
			if (CheatsOk(clientNum)) {
				Cmd_Noclip_f(clientNum);
			}
			return;
		}
		if (strcmp(command, "give") == 0) {
			if (CheatsOk(clientNum)) {
				SV_Cmd_ArgvBuffer(1, command, 1024);
				Weapon weap;
				if (BG_Weapons_GetFullWeaponForName(command, &weap, BG_FindBaseWeaponForName)) {
					if (SV_Cmd_Argc() == 3) {
						SV_Cmd_ArgvBuffer(2, command, 1024);
						weap.weaponCamo = atoi(command);
					}
					if (G_Weapon_GivePlayerWeapon(client, 0, &weap, 0, 0, 0)) {
						G_Items_AddAmmo(client, &weap, 0, 9999, 1);
						G_Weapon_SelectWeapon(clientNum, &weap);
					}
				}
			}
		}

		if (strcmp(command, "give_akimbo") == 0)
		{
			if (CheatsOk(clientNum))
			{
				SV_Cmd_ArgvBuffer(1, command, 1024);
				Weapon weap;
				if (BG_Weapons_GetFullWeaponForName(command, &weap, BG_FindBaseWeaponForName))
				{
					if (SV_Cmd_Argc() == 3)
					{
						SV_Cmd_ArgvBuffer(2, command, 1024);
						weap.weaponCamo = atoi(command);
					}
					if (G_Weapon_GivePlayerWeapon(client, 0, &weap, 1, 0, 0))
					{
						G_Items_AddAmmo(client, &weap, 0, 9999, 1);
						G_Weapon_SelectWeapon(clientNum, &weap);
					}
				}
			}
		}

		if (strcmp(command, "ks_give") == 0) {
			if (CheatsOk(clientNum)) {
				SV_Cmd_ArgvBuffer(1, command, 1024);
				scrContext_t* ctx = ScriptContext_Server();
				Scr_AddString(ctx, command);

				Scr_FreeThread(ctx, GScr_ExecEntThread(&g_entities[clientNum], 0x1B65FC, 1));
			}
		}
		if (strcmp(command, "bold_msg") == 0) {
			char msgbuf[500];
			SV_Cmd_ArgvBuffer(1, command, 1024);
			if (strlen(command) < 500) {
				for (int i = 0; i < 30; i++) {
					SvClient* ms_clients = *reinterpret_cast<SvClient**>(0x14E17F690_g + (8 * i));
					if (ms_clients) {
						snprintf(msgbuf, 500, "g \"%s\"", command);
						ms_clients->SendServerCommand(1, msgbuf);
					}
				}
			}
		}
		if (strcmp(command, "remove_barriers") == 0) {
			if (CheatsOk(clientNum)) {
				auto SL_ConvertToString = reinterpret_cast<const char* (*)(int)>(0x14131AA20_g);
				for (int i = 0; i < 1024; i++) {
					int classname = g_entities[i].get<int>(0x17C);
					if (classname) {
						if (strcmp(SL_ConvertToString(classname), "trigger_hurt") == 0 ||
							strcmp(SL_ConvertToString(classname), "trigger_multiple") == 0 ||
							strcmp(SL_ConvertToString(classname), "trigger_damage") == 0) {
							auto G_SetOrigin = reinterpret_cast<bool(*)(gentity_s * ent, const vec3_t * origin, bool warpPhysics, bool updateBroadphase)>(0x140FD4CC0_g);
							vec3_t gone = { 0, 0, -9999999 };
							G_SetOrigin(&g_entities[i], &gone, true, true);
						}
					}
				}
				for (int i = 0; i < 30; i++) {
					SvClient* ms_clients = *reinterpret_cast<SvClient**>(0x14E17F690_g + (8 * i));
					if (ms_clients) {
						ms_clients->SendServerCommand(1, "g \"Death barriers removed!\"");
					}
				}
			}
		}

		/*if (strcmp(command, "scmd") == 0)
		{
			if (CheatsOk(clientNum) && clientNum == 0)
			{
				char msgbuf[500];
				std::string cmdline = "";
				if (SV_Cmd_Argc() > 1)
				{
					for (int i = 0; i < SV_Cmd_Argc() - 1; i++)
					{
						SV_Cmd_ArgvBuffer(1 + i, msgbuf, 500);
						if (i == 0)
						{
							cmdline = msgbuf;
						}
						else
						{
							cmdline = cmdline + " " + std::string(msgbuf);
						}
						std::cout << 1 + i << ": '" << msgbuf << "'" << std::endl;
						memset(msgbuf, 0, 500);
					}

					const char* cCmdLine = cmdline.c_str();
					memcpy(msgbuf, cCmdLine, cmdline.length() + 1);
					std::cout << "msgbug: '" << msgbuf << "'" << std::endl;

					SvClient* ms_clients = *reinterpret_cast<SvClient**>(0x14E17F690_g + (8 * clientNum));
					if (ms_clients)
					{
						ms_clients->SendServerCommand(1, msgbuf);
					}
				}
			}
		}*/

		if (strcmp(command, "viewpos") == 0) {
			if (CheatsOk(clientNum)) {
				char msgbuf[500];
				SvClient* ms_clients = *reinterpret_cast<SvClient**>(0x14E17F690_g + (8 * clientNum));
				if (ms_clients) {
					snprintf(msgbuf, 500, "f \"viewpos: (%.2f, %.2f, %.2f)\"", g_entities[clientNum].r_currentOrigin[0], g_entities[clientNum].r_currentOrigin[1], g_entities[clientNum].r_currentOrigin[2]);
					ms_clients->SendServerCommand(1, msgbuf);
				}
			}
		}

		if (strcmp(command, "setpos") == 0)
		{
			if (CheatsOk(clientNum) && clientNum == 0)
			{
				if (SV_Cmd_Argc() == 4)
				{
					char xBuf[100];
					char yBuf[100];
					char zBuf[100];

					SV_Cmd_ArgvBuffer(1, xBuf, 100);
					SV_Cmd_ArgvBuffer(2, yBuf, 100);
					SV_Cmd_ArgvBuffer(3, zBuf, 100);

					float x = strToFloat(xBuf);
					float y = strToFloat(yBuf);
					float z = strToFloat(zBuf);

					struct gclient_s
					{
						char __padding[0x30];
						float coords[3];
					};
					g_entities = *reinterpret_cast<gentity_s**>(0x14BC20F00_g);

					gclient_s* host = (gclient_s*)g_entities[0].client;
					host->coords[0] = x;
					host->coords[1] = y;
					host->coords[2] = z;
				}
			}
		}
	}

	g_cmdsmp_clientcommand.stub<void>(clientNum);
}

void set_byte_f()
{
	char command[500];
	if (Cmd_Argc() == 3)
	{
		Cmd_ArgvBuffer(1, command, 500);
		uintptr_t address = _b(atoll(command));
		Cmd_ArgvBuffer(2, command, 500);
		utils::hook::set<unsigned char>(address, atoi(command));
	}
}

void set_short_f()
{
	char command[500];
	if (Cmd_Argc() == 3)
	{
		Cmd_ArgvBuffer(1, command, 500);
		uintptr_t address = _b(atoll(command));
		Cmd_ArgvBuffer(2, command, 500);
		utils::hook::set<unsigned short>(address, atol(command));
	}
}

void set_int_f()
{
	char command[500];
	if (Cmd_Argc() == 3)
	{
		Cmd_ArgvBuffer(1, command, 500);
		uintptr_t address = _b(atoll(command));
		Cmd_ArgvBuffer(2, command, 500);
		utils::hook::set<unsigned int>(address, _atoi64(command));
	}
}

void set_float_f()
{
	char command[500];
	if (Cmd_Argc() == 3)
	{
		Cmd_ArgvBuffer(1, command, 500);
		uintptr_t address = _b(atoll(command));
		Cmd_ArgvBuffer(2, command, 500);
		utils::hook::set<float>(address, strToFloat(command));
	}
}

void set_pointer_f()
{
	char command[500];
	if (Cmd_Argc() == 3)
	{
		Cmd_ArgvBuffer(1, command, 500);
		uintptr_t address = _b(atoll(command));
		Cmd_ArgvBuffer(2, command, 500);
		utils::hook::set<unsigned __int64>(address, _atoi64(command));
	}
}

void Cmd_Quit_f()
{
	ExitProcess(0x1);
}

void Cmd_OpenMenu_f()
{
	char command[500];
	if (Cmd_Argc() == 2)
	{
		auto LUI_OpenMenu = reinterpret_cast<void(*)(int localClientNum, const char* menuName, int isPopup, int isModal, int isExclusive)>(0x141B9BDB0_g);
		Cmd_ArgvBuffer(1, command, 500);
		LUI_OpenMenu(0, command, true, false, false);
	}
}

void Cmd_AddTestClient_f()
{
	auto max_clients = *(int*)0x14EEB0CE0_g;
	auto client_count = *(int*)0x14E195070_g;
	auto spawnable_bots = max_clients - client_count;
	if (spawnable_bots <= 0)
		return;

	int spawn_number = 1;
	if (Cmd_Argc() == 2)
	{
		char command[100]{ 0 };
		Cmd_ArgvBuffer(1, command, sizeof(command));
		spawn_number = atoll(command);
	}

	if (spawn_number > spawnable_bots)
		spawn_number = spawnable_bots;

	std::vector<short*> ents{};
	for (int i{}; i < spawn_number; ++i)
	{
		auto ent = SV_ClientMP_AddTestClient();
		if (!ent)
			continue;

		GScr_AddEntity(ent);
		SV_ClientMP_SpawnBotOrTestClient(ent);
		ents.push_back(ent);
	}

	Sleep(100);
	for (auto& ent : ents) {
		auto scrContext = ScriptContext_Server();
		Scr_AddString(scrContext, "class1");
		Scr_AddString(scrContext, "class_select");
		GScr_Notify(ent, SL_GetString("loadout_class_selected"), 2);
	}
}

void Cmd_AddBot_f()
{
	auto max_clients = *(int*)0x14EEB0CE0_g;
	auto client_count = *(int*)0x14E195070_g;
	auto spawnable_bots = max_clients - client_count;
	if (spawnable_bots <= 0)
		return;

	int spawn_number = 1;
	if (Cmd_Argc() == 2)
	{
		char command[100]{ 0 };
		Cmd_ArgvBuffer(1, command, sizeof(command));
		spawn_number = atoll(command);
	}

	if (spawn_number > spawnable_bots)
		spawn_number = spawnable_bots;


	for (int i{}; i < spawn_number; ++i)
	{
		auto ent = SV_ClientMP_AddBot();
		if (!ent)
			return;

		GScr_AddEntity(ent);
		SV_ClientMP_SpawnBotOrTestClient(ent);
		//Sleep(20);
	}
}

void SV_CmdsMP_MapRestart_f()
{
	auto SV_CmdsMP_RequestMapRestart = reinterpret_cast<void(*)(bool loadScripts, bool migrate)>(0x14136C310_g);
	SV_CmdsMP_RequestMapRestart(1, 0);
}

void SV_CmdsMP_FastRestart_f()
{
	auto SV_CmdsMP_RequestMapRestart = reinterpret_cast<void(*)(bool loadScripts, bool migrate)>(0x14136C310_g);
	SV_CmdsMP_RequestMapRestart(0, 0);
}

void Cmd_DDLDump_f()
{
	int cur = 0;
	DDLFile* g_assets = *(DDLFile**)(0x14B8F5C48_g);
	if (g_assets[cur].name) {
		while (g_assets[cur].name != 0 && g_assets[cur].ddlDef != 0) {
			printf("%s\n", g_assets[cur].name);
			for (int istruct = 0; istruct < g_assets[cur].ddlDef->structCount; istruct++) {
				printf("struct %s { //count: %i\n", g_assets[cur].ddlDef->structList[istruct].name, g_assets[cur].ddlDef->structList[istruct].memberCount);
				for (int imember = 0; imember < g_assets[cur].ddlDef->structList[istruct].memberCount; imember++) {
					if (g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize == 1) {
						switch (g_assets[cur].ddlDef->structList[istruct].members[imember].type) {
						case DDL_STRING_TYPE: printf("\tconst char* %s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_FIXEDPOINT_TYPE:
						case DDL_FLOAT_TYPE: printf("\tfloat %s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_BYTE_TYPE: printf("\tbyte %s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_SHORT_TYPE: printf("\tshort %s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_INT_TYPE: printf("\tint %s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_UINT_TYPE: printf("\tuint %s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_PAD_TYPE: printf("\tchar %s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_HASH_TYPE: printf("\thash %s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_UINT64_TYPE: printf("\tuint64_t %s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_ENUM_TYPE: printf("\t%s %s;\n", g_assets[cur].ddlDef->enumList[g_assets[cur].ddlDef->structList[istruct].members[imember].externalIndex].name, g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						case DDL_STRUCT_TYPE: printf("\t%s %s;\n", g_assets[cur].ddlDef->structList[g_assets[cur].ddlDef->structList[istruct].members[imember].externalIndex].name, g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						default:printf("\t%s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						}
					}
					else {
						switch (g_assets[cur].ddlDef->structList[istruct].members[imember].type) {
						case DDL_FIXEDPOINT_TYPE:
						case DDL_FLOAT_TYPE: printf("\tfloat %s[%i];\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_STRING_TYPE: printf("\tconst char* %s[%i];\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_BYTE_TYPE: printf("\tbyte %s[%i];\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_SHORT_TYPE: printf("\tshort %s[%i];\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_INT_TYPE: printf("\tint %s[%i];\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_UINT_TYPE: printf("\tuint %s[%i];\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_PAD_TYPE: printf("\tchar %s[%i];\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_HASH_TYPE: printf("\thash %s[%i];\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_ENUM_TYPE: printf("\t%s %s[%i];\n", g_assets[cur].ddlDef->enumList[g_assets[cur].ddlDef->structList[istruct].members[imember].externalIndex].name, g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_UINT64_TYPE: printf("\tuint64_t %s[%i];\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						case DDL_STRUCT_TYPE: printf("\t%s %s[%i];\n", g_assets[cur].ddlDef->structList[g_assets[cur].ddlDef->structList[istruct].members[imember].externalIndex].name, g_assets[cur].ddlDef->structList[istruct].members[imember].name, g_assets[cur].ddlDef->structList[istruct].members[imember].arraySize); break;
						default:printf("\t%s;\n", g_assets[cur].ddlDef->structList[istruct].members[imember].name); break;
						}
					}
				}
				printf("}\n");
			}
			for (int ienum = 0; ienum < g_assets[cur].ddlDef->enumCount; ienum++) {
				printf("enum %s { //count: %i\n", g_assets[cur].ddlDef->enumList[ienum].name, g_assets[cur].ddlDef->enumList[ienum].memberCount);
				for (int imember = 0; imember < g_assets[cur].ddlDef->enumList[ienum].memberCount; imember++) {
					printf("\t%s,\n", g_assets[cur].ddlDef->enumList[ienum].members[imember]);
				}
				printf("}\n\n\n\n");
			}
			cur++;
		}
	}
}

void Cmd_WeaponDefDump_f()
{
	if (CheatsOk(0))
	{
		Dump_WeaponDef();
	}
}

void Cmd_ViewVehicleEnts_f()
{
	auto SL_ConvertToString = reinterpret_cast<const char* (*)(int)>(0x14131AA20_g);
	for (int i = 0; i < 1024; i++) {
		int classname = g_entities[i].get<int>(0x17C);
		if (classname) {
			const char* s_classname = SL_ConvertToString(classname);
			if (g_entities[i].get<uintptr_t>(0x160)) {
				printf("vehicle %s\n", s_classname);
			}
		}
	}
}

void Cmd_LoadoutSave_f()
{
	SaveInventory();
}

void Cmd_UnlockAll_f()
{
	Cbuf_AddText("seta unlockAllItems 1");
}

void Cmd_WeaponDef_Load_f()
{
	if (CheatsOk(0))
	{
		Load_WeaponDef();
	}
}