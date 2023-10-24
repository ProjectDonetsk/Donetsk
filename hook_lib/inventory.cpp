#include "inventory.h"
#include "game_inc.h"

void SaveInventory()
{
	auto DDL_MoveToPath = reinterpret_cast<bool(*)(const DDLState * fromState, DDLState * toState, int depth, const char** path)>(0x142052430_g);
	//auto Com_DDL_ConvertNavStringToHash = reinterpret_cast<int(*)(const char*)>(0x14129EE80_g);
	//auto LiveStorage_InitializeDDLStateForStatsGroup = reinterpret_cast<void(*)(const DDLDef * def, DDLState * state, int statsGroup)>(0x1410CAD70_g);
	auto Com_PlayerData_GetStatsBlob = reinterpret_cast<int(*)(int)>(0x1410CA7A0_g);
	auto DDL_GetType = reinterpret_cast<DDLType(*)(const DDLState*)>(0x142051DD0_g);
	auto DDL_GetString = reinterpret_cast<const char* (*)(const DDLState * state, const DDLContext * ddlContext)>(0x142051CD0_g);
	auto DDL_GetEnum = reinterpret_cast<const char* (*)(const DDLState * state, const DDLContext * ddlContext)>(0x1420519E0_g);
	auto DDL_GetInt = reinterpret_cast<int(*)(const DDLState * state, const DDLContext * ddlContext)>(0x142051BF0_g);
	auto DDL_GetRootState = reinterpret_cast<DDLState * (*)(DDLState * result, const DDLDef * ddlDef)>(0x142051C70_g);
	auto CL_PlayerData_GetDDLBuffer = reinterpret_cast<bool(*)(DDLContext * context, int controllerIndex, int statsSource, __int32 statsGroup)>(0x1415C7940_g);
	auto Com_DDL_LoadAsset = reinterpret_cast<const DDLDef * (*)(const char* fileName)>(0x14129F3B0_g);
	auto Com_ParseNavStrings = reinterpret_cast<bool(*)(const char* pStr, const char** navStrings, int navStringMax, int* navStringCount)>(0x1412A02E0_g);
	auto Com_DDL_CreateContext = reinterpret_cast<bool(*)(void* buffer, int len, const DDLDef * def, DDLContext* const ddlContext, uintptr_t a5, void* userData)>(0x14129EEC0_g);

	DDLContext context;
	DDLDef* ddlDef;
	DDLState state;
	char buffer[200];
	char* navStrings[32]{};
	int navStringCount;
	char path[MAX_PATH + 1];
	strcpy(path, Dvar_GetStringSafe("LOOQOTRNTN"));
	strcat(path, "\\players\\inventory.json");
	nlohmann::json inventoryJson;
	if (CL_PlayerData_GetDDLBuffer(&context, 0, STATS_OFFLINE, STATSGROUP_PRIVATELOADOUTS)) {
		ddlDef = (DDLDef*)context.def;
		// start of operator customization related
		for (int i = 0; i < ddlDef->enumCount; ++i)
		{
			if (!strcmp(ddlDef->enumList[i].name, "Operator")) {
				for (int j = 0; j < ddlDef->enumList[i].memberCount; ++j)
				{
					// get operator skins
					DDL_GetRootState(&state, ddlDef);
					sprintf_s(buffer, "customizationSetup.operatorCustomization.%s.skin", ddlDef->enumList[i].members[j]);
					Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
					if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
					{
						int OP_opSkin = DDL_GetInt(&state, &context);
						inventoryJson["Operator"]["OperatorSkin"][ddlDef->enumList[i].members[j]] = OP_opSkin;
					}
					// execution ids
					DDL_GetRootState(&state, ddlDef);
					sprintf_s(buffer, "customizationSetup.operatorCustomization.%s.execution", ddlDef->enumList[i].members[j]);
					Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
					if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
					{
						inventoryJson["Operator"]["OperatorExecution"][ddlDef->enumList[i].members[j]] = DDL_GetInt(&state, &context);
					}
				}
			}
		}
		// selected operator
		for (int i = 0; i < 2; ++i)
		{
			DDL_GetRootState(&state, ddlDef);
			sprintf_s(buffer, "customizationSetup.operators.%d", i);
			Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
			if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
			{
				inventoryJson["Operator"]["SelectedOperator"][i] = DDL_GetEnum(&state, &context);
			}
		}
		// operator Index
		DDL_GetRootState(&state, ddlDef);
		sprintf_s(buffer, "customizationSetup.selectedOperatorIndex");
		Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
		if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
		{
			inventoryJson["Operator"]["OperatorIndex"] = DDL_GetInt(&state, &context);
		}
		// operator watch
		DDL_GetRootState(&state, ddlDef);
		sprintf_s(buffer, "customizationSetup.operatorWatch");
		Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
		if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
		{
			inventoryJson["Operator"]["OperatorWatch"] = DDL_GetInt(&state, &context);
		}
		// end of operator customization related
		// start of weapon customization

		for (int i = 0; i < 10; ++i) {
			// get weapon
			DDL_GetRootState(&state, ddlDef);
			sprintf_s(buffer, "squadMembers.loadouts.%d.name", i);
			Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
			if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
			{
				// test by getting loadout names
				inventoryJson["Loadouts"][i] = { {"name", DDL_GetString(&state, &context)} };
			}
			for (int j = 0; j < 2; ++j) {
				// get camos
				DDL_GetRootState(&state, ddlDef);
				sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.camo", i, j);
				Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
				if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
				{
					inventoryJson["Loadouts"][i]["weaponSetup"][j] = { {"camo", DDL_GetEnum(&state, &context)} };
				}
				// get weapons
				DDL_GetRootState(&state, ddlDef);
				sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.weapon", i, j);
				Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
				if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
				{
					inventoryJson["Loadouts"][i]["weaponSetup"][j].push_back({ "weapon", DDL_GetEnum(&state, &context) });
				}
				// get variant ids
				DDL_GetRootState(&state, ddlDef);
				sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.variantID", i, j);
				Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
				if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
				{
					inventoryJson["Loadouts"][i]["weaponSetup"][j].push_back({ "variantId", DDL_GetInt(&state, &context) });
				}
				DDL_GetRootState(&state, ddlDef);
				sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.lootItemID", i, j);
				Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
				if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
				{
					inventoryJson["Loadouts"][i]["weaponSetup"][j].push_back({ "lootItemID", DDL_GetInt(&state, &context) });
				}
				for (int k = 0; k < 5; ++k) {
					// get attachments & variants
					std::string attachmentName;
					DDL_GetRootState(&state, ddlDef);
					sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.attachmentSetup.%d.attachment", i, j, k);
					Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
					if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
					{
						attachmentName = DDL_GetEnum(&state, &context);
					}

					DDL_GetRootState(&state, ddlDef);
					sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.attachmentSetup.%d.variantID", i, j, k);
					Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
					if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
					{
						inventoryJson["Loadouts"][i]["weaponSetup"][j]["attachments"][k] = { attachmentName.c_str(), DDL_GetInt(&state, &context) };
					}
				}
			}

		}
		// printf("Saved Inventory!\n");
	}
	else {
		Com_SetErrorMessage("[DLL ERROR] Couldn't get DDLBuffer, called before initialized?");
	}

	std::ofstream JsonOut(path);
	JsonOut << inventoryJson;

}

void LoadInventory()
{
	auto Cmd_LocalControllerIndex = reinterpret_cast<int(*)()>(0x141298040_g);
	auto LiveStorage_GetActiveStatsSource = reinterpret_cast<int(*)(int)>(0x1412A1EB0_g);
	auto LiveStorage_CreateDDLContext = reinterpret_cast<bool(*)(const int controllerIndex, int statsGroup, int statsSource, DDLContext * context, uintptr_t a5, void* userData)>(0x1412A13C0_g);
	auto DDL_MoveToPath = reinterpret_cast<bool(*)(const DDLState * fromState, DDLState * toState, int depth, const char** path)>(0x142052430_g);
	//auto Com_DDL_ConvertNavStringToHash = reinterpret_cast<int(*)(const char*)>(0x14129EE80_g);
	//auto LiveStorage_InitializeDDLStateForStatsGroup = reinterpret_cast<void(*)(const DDLDef * def, DDLState * state, int statsGroup)>(0x1410CAD70_g);
	auto Com_PlayerData_GetStatsBlob = reinterpret_cast<int(*)(int)>(0x1410CA7A0_g);
	auto DDL_GetType = reinterpret_cast<DDLType(*)(const DDLState*)>(0x142051DD0_g);
	auto DDL_GetString = reinterpret_cast<const char* (*)(const DDLState * state, const DDLContext * ddlContext)>(0x142051CD0_g);
	auto DDL_GetEnum = reinterpret_cast<const char* (*)(const DDLState * state, const DDLContext * ddlContext)>(0x1420519E0_g);
	auto DDL_GetInt = reinterpret_cast<int(*)(const DDLState * state, const DDLContext * ddlContext)>(0x142051BF0_g);
	auto DDL_GetRootState = reinterpret_cast<DDLState * (*)(DDLState * result, const DDLDef * ddlDef)>(0x142051C70_g);
	auto CL_PlayerData_GetDDLBuffer = reinterpret_cast<bool(*)(DDLContext * context, int controllerIndex, int statsSource, __int32 statsGroup)>(0x1415C7940_g);
	auto Com_DDL_LoadAsset = reinterpret_cast<const DDLDef * (*)(const char* fileName)>(0x14129F3B0_g);
	auto Com_ParseNavStrings = reinterpret_cast<bool(*)(const char* pStr, const char** navStrings, int navStringMax, int* navStringCount)>(0x1412A02E0_g);
	auto Com_DDL_CreateContext = reinterpret_cast<bool(*)(void* buffer, int len, const DDLDef * def, DDLContext* const ddlContext, uintptr_t a5, void* userData)>(0x14129EEC0_g);
	auto StringTable_GetColumnValueForRow = reinterpret_cast<const char* (*)(StringTable*, int, int)>(0x1413E2B40_g);
	auto DDL_SetInt = reinterpret_cast<void (*)(DDLState * param_1, DDLContext * param_2, int param_3)>(0x142052820_g);
	auto DDL_SetEnum = reinterpret_cast<bool(*)(DDLState * param_1, DDLContext * param_2, const char* param_3)>(0x142052710_g);
	auto DDL_SetString = reinterpret_cast<bool(*)(DDLState * param_1, DDLContext * param_2, const char* param_3)>(0x1420528D0_g);

	DDLContext context;
	DDLDef* ddlDef;
	DDLState state;
	char buffer[200];
	char* navStrings[32]{};
	int navStringCount;
	char path[MAX_PATH + 1];
	strcpy(path, Dvar_GetStringSafe("LOOQOTRNTN"));
	strcat(path, "\\players\\inventory.json");
	if (file_exists(path)) {
		std::ifstream jsonPath(path);
		nlohmann::json inventoryJson = nlohmann::json::parse(jsonPath);
		if (CL_PlayerData_GetDDLBuffer(&context, 0, STATS_OFFLINE, STATSGROUP_PRIVATELOADOUTS)) {
			ddlDef = (DDLDef*)context.def;
			for (int i = 0; i < ddlDef->enumCount; ++i)
			{
				if (!strcmp(ddlDef->enumList[i].name, "Operator")) {
					for (int j = 0; j < ddlDef->enumList[i].memberCount; ++j)
					{
						DDL_GetRootState(&state, ddlDef);
						sprintf_s(buffer, "customizationSetup.operatorCustomization.%s.skin", ddlDef->enumList[i].members[j]);
						Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
						if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
						{
							DDL_SetInt(&state, &context, inventoryJson["Operator"]["OperatorSkin"][ddlDef->enumList[i].members[j]]);
						}
						// execution ids
						DDL_GetRootState(&state, ddlDef);
						sprintf_s(buffer, "customizationSetup.operatorCustomization.%s.execution", ddlDef->enumList[i].members[j]);
						Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
						if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
						{
							DDL_SetInt(&state, &context, inventoryJson["Operator"]["OperatorExecution"][ddlDef->enumList[i].members[j]]);
						}

					}
				}
			}
			for (int i = 0; i < 2; ++i)
			{
				DDL_GetRootState(&state, ddlDef);
				sprintf_s(buffer, "customizationSetup.operators.%d", i);
				Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
				if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
				{
					DDL_SetEnum(&state, &context, inventoryJson["Operator"]["SelectedOperator"][i].get<std::string>().c_str());
				}
			}
			// operator Index
			DDL_GetRootState(&state, ddlDef);
			sprintf_s(buffer, "customizationSetup.selectedOperatorIndex");
			Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
			if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
			{
				DDL_SetInt(&state, &context, inventoryJson["Operator"]["OperatorIndex"]);
			}

			// operator watch
			DDL_GetRootState(&state, ddlDef);
			sprintf_s(buffer, "customizationSetup.operatorWatch");
			Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
			if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
			{
				DDL_SetInt(&state, &context, inventoryJson["Operator"]["OperatorWatch"]);
			}
			// start of weapon customization
			for (int i = 0; i < 10; ++i) {
				DDL_GetRootState(&state, ddlDef);
				sprintf_s(buffer, "squadMembers.loadouts.%d.name", i);
				Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
				if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
				{
					DDL_SetString(&state, &context, inventoryJson["Loadouts"][i]["name"].get<std::string>().c_str());
				}
				for (int j = 0; j < 2; ++j) {
					// set camo
					DDL_GetRootState(&state, ddlDef);
					sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.camo", i, j);
					Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
					if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
					{
						DDL_SetEnum(&state, &context, inventoryJson["Loadouts"][i]["weaponSetup"][j]["camo"].get<std::string>().c_str());
					}
					// set weapon
					DDL_GetRootState(&state, ddlDef);
					sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.weapon", i, j);
					Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
					if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
					{
						DDL_SetEnum(&state, &context, inventoryJson["Loadouts"][i]["weaponSetup"][j]["weapon"].get<std::string>().c_str());
					}
					// set variantid
					DDL_GetRootState(&state, ddlDef);
					sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.variantID", i, j);
					Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
					if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
					{
						DDL_SetInt(&state, &context, inventoryJson["Loadouts"][i]["weaponSetup"][j]["variantId"]);
					}
					// set lootItemId
					DDL_GetRootState(&state, ddlDef);
					sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.lootItemID", i, j);
					Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
					if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
					{
						DDL_SetInt(&state, &context, inventoryJson["Loadouts"][i]["weaponSetup"][j]["lootItemID"]);
					}
					for (int k = 0; k < 5; ++k) {
						DDL_GetRootState(&state, ddlDef);
						sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.attachmentSetup.%d.attachment", i, j, k);
						Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
						if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
						{
							DDL_SetEnum(&state, &context, inventoryJson["Loadouts"][i]["weaponSetup"][j]["attachments"][k][0].get<std::string>().c_str());
						}

						DDL_GetRootState(&state, ddlDef);
						sprintf_s(buffer, "squadMembers.loadouts.%d.weaponSetups.%d.attachmentSetup.%d.variantID", i, j, k);
						Com_ParseNavStrings(buffer, (const char**)navStrings, 32, &navStringCount);
						if (DDL_MoveToPath(&state, &state, navStringCount, (const char**)navStrings))
						{
							DDL_SetInt(&state, &context, inventoryJson["Loadouts"][i]["weaponSetup"][j]["attachments"][k][1]);
						}
					}
				}
			}

		}
		else {
			Com_SetErrorMessage("[DLL ERROR] Couldn't get DDLBuffer, called before initialized?");
		}
		printf("Loaded Inventory!\n");
	}
	else {
		// Com_SetErrorMessage("[DLL ERROR] Attempted to load inventory from \"players/inventory.json\" but file does not exist. Use 'saveinv' to save your inventory.");
		printf("Attempted to load inventory from \"players/inventory.json\" but file does not exist\n");
	}
}