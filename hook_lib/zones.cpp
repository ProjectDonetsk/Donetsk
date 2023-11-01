#include "addr_utils.hpp"
#include "zones.h"
#include "game_inc.h"

__int64 DB_Zones_PerformZoneLoad_Detour(bool processingPreloadedFiles, bool isBaseMap, bool wasPaused, int failureMode)
{
	failureMode = 1;

	return db_zones_performzoneload.stub<__int64>(processingPreloadedFiles, isBaseMap, wasPaused, failureMode);
}

XAssetHeader DB_FindXAssetHeader_Detour(XAssetType type, const char* givenName, int allowCreateDefault)
{
	XAssetHeader temp = db_findxassetheader.stub<XAssetHeader>(type, givenName, allowCreateDefault);

	//if (type == ASSET_TYPE_XMODEL) {
	//	if (strcmp(temp.model->name, "head_mp_western_ghost_1_1") == 0) {
	//		return db_findxassetheader.stub<XAssetHeader>(type, "head_opforce_juggernaut", allowCreateDefault);
	//	}
	//	if (strcmp(temp.model->name, "mp_western_vm_arms_ghost_1_1") == 0) {
	//		return db_findxassetheader.stub<XAssetHeader>(type, "viewhands_opforce_juggernaut", allowCreateDefault);
	//	}
	//	if (strcmp(temp.model->name, "body_mp_western_ghost_1_1_lod1") == 0) {
	//		return db_findxassetheader.stub<XAssetHeader>(type, "body_opforce_juggernaut_mp_lod1", allowCreateDefault);
	//	}
	//	if (strcmp(temp.model->name, "military_carepackage_01_friendly") == 0) {
	//		return db_findxassetheader.stub<XAssetHeader>(type, "opforce_juggernaut_prop_static", allowCreateDefault);
	//	}
	//	if (strstr(temp.model->name, "veh8_mil_air_")) {
	//		return db_findxassetheader.stub<XAssetHeader>(type, "veh8_mil_air_acharlie130", allowCreateDefault);
	//	}
	//}

	return temp;
}

const char* DB_GetRawBufferInflate_Detour(const char* file, char* buffer, int length)
{
	char path[MAX_PATH + 1];
	memset(path, 0, MAX_PATH + 1);
	std::string filecontents;
	std::string curline;
	snprintf(path, MAX_PATH + 1, "%s\\players\\raw\\%s", Dvar_GetStringSafe("LOOQOTRNTN"), file);
	if (file_exists(path))
	{
		printf("replacing file %s\n", file);
		std::ifstream myfile;
		myfile.open(path);
		filecontents = "";
		while (myfile)
		{
			std::getline(myfile, curline);
			filecontents += curline + "\n";
		}
		myfile.close();
		strcpy(buffer, filecontents.c_str());
		return filecontents.c_str();;
	}
	printf("loading %s\n", file);
	return db_getrawbufferinflate.stub<const char*>(file, buffer, length);
}

void Load_MapEntsAsset_Detour(XAssetHeader* mapEnts)
{
	auto Scr_AllocGlobalString = reinterpret_cast<scr_string_t(*)(const char*)>(0x14131B2C0_g);
	char path[MAX_PATH + 1];
	snprintf(path, MAX_PATH + 1, "%s\\players\\raw\\%s", Dvar_GetStringSafe("LOOQOTRNTN"), mapEnts->image->name);
	if (file_exists(path)) {
		printf("loading %s\n", path);
		HANDLE mapEntsFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		int numberOfBytesRead = GetFileSize(mapEntsFile, NULL);
		if (mapEntsFile != INVALID_HANDLE_VALUE)
		{
			memset(g_customEntityString, 0, 0xFFFFFFF);
			ReadFile(mapEntsFile, g_customEntityString, numberOfBytesRead, (LPDWORD)&numberOfBytesRead, 0);
			mapEnts->mapEnts->entityString = g_customEntityString;
			mapEnts->mapEnts->numEntityChars = strlen(g_customEntityString) + 1;
			CloseHandle(mapEntsFile);
			memset(path, 0, MAX_PATH + 1);
			snprintf(path, MAX_PATH + 1, "%s\\players\\raw\\%s.spawnlist", Dvar_GetStringSafe("LOOQOTRNTN"), mapEnts->image->name);
			if (!file_exists(path)) {
			}
			else {
				nlohmann::json json;
				std::ifstream file(path);
				file >> json;
				file.close();
				mapEnts->mapEnts->spawnList.spawnsCount = json["spawnList"]["spawnsCount"];
				for (int i = 0; i < mapEnts->mapEnts->spawnList.spawnsCount; i++) {
					mapEnts->mapEnts->spawnList.spawns[i].index = json["spawnList"][_va("spawns[%i]", i)]["index"];
					mapEnts->mapEnts->spawnList.spawns[i].name = Scr_AllocGlobalString(std::string(json["spawnList"][_va("spawns[%i]", i)]["name"]).c_str());
					mapEnts->mapEnts->spawnList.spawns[i].target = Scr_AllocGlobalString(std::string(json["spawnList"][_va("spawns[%i]", i)]["target"]).c_str());
					mapEnts->mapEnts->spawnList.spawns[i].script_noteworthy = Scr_AllocGlobalString(std::string(json["spawnList"][_va("spawns[%i]", i)]["script_noteworthy"]).c_str());

					mapEnts->mapEnts->spawnList.spawns[i].origin.v[0] = json["spawnList"][_va("spawns[%i]", i)]["origin"][0];
					mapEnts->mapEnts->spawnList.spawns[i].origin.v[1] = json["spawnList"][_va("spawns[%i]", i)]["origin"][1];
					mapEnts->mapEnts->spawnList.spawns[i].origin.v[2] = json["spawnList"][_va("spawns[%i]", i)]["origin"][2];

					mapEnts->mapEnts->spawnList.spawns[i].angles.v[0] = json["spawnList"][_va("spawns[%i]", i)]["angles"][0];
					mapEnts->mapEnts->spawnList.spawns[i].angles.v[1] = json["spawnList"][_va("spawns[%i]", i)]["angles"][1];
					mapEnts->mapEnts->spawnList.spawns[i].angles.v[2] = json["spawnList"][_va("spawns[%i]", i)]["angles"][2];
				}
			}
		}
	}

	printf("%s\n", mapEnts->mapEnts->clientTrigger.triggerString);

	load_mapentsasset.stub<void>(mapEnts);
}

void Load_ClipMapAsset_Detour(XAssetHeader* clipMap)
{
	load_clipmapasset.stub<void>(clipMap);
}

void DB_GetRawBuffer_Detour(const RawFile* rawfile, char* buf, int size)
{
	char path[MAX_PATH + 1];
	snprintf(path, MAX_PATH + 1, "%s\\players\\raw\\%s", Dvar_GetStringSafe("LOOQOTRNTN"), rawfile->name);
	if (file_exists(path)) {
		HANDLE mapEntsFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		int numberOfBytesRead = GetFileSize(mapEntsFile, NULL);
		if (mapEntsFile != INVALID_HANDLE_VALUE)
		{
			ReadFile(mapEntsFile, g_customBuffer, numberOfBytesRead, (LPDWORD)&numberOfBytesRead, 0);
			CloseHandle(mapEntsFile);
			strcpy(buf, g_customBuffer);
			printf("replacing %s\n", rawfile->name);
		}
		return;
	}

	db_getrawbuffer.stub<void>(rawfile, buf, size);
}

void Load_XModelAsset_Detour(XAssetHeader* model)
{
	load_xmodelasset.stub<void>(model);
}