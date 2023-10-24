#pragma once
#include "Main.hpp"

inline utils::hook::detour db_zones_performzoneload;
__int64 DB_Zones_PerformZoneLoad_Detour(bool processingPreloadedFiles, bool isBaseMap, bool wasPaused, int failureMode);

inline utils::hook::detour db_findxassetheader;
XAssetHeader DB_FindXAssetHeader_Detour(XAssetType type, const char* givenName, int allowCreateDefault);

inline utils::hook::detour db_getrawbufferinflate;
const char* DB_GetRawBufferInflate_Detour(const char* file, char* buffer, int length);

inline SpawnPointEntityRecord* g_customSpawns;
inline char g_customEntityString[0xFFFFFFF];
inline utils::hook::detour load_mapentsasset;
void Load_MapEntsAsset_Detour(XAssetHeader* mapEnts);

inline utils::hook::detour load_clipmapasset;
void Load_ClipMapAsset_Detour(XAssetHeader* clipMap);

inline char g_customBuffer[0x18000];
inline utils::hook::detour db_getrawbuffer;
void DB_GetRawBuffer_Detour(const RawFile* rawfile, char* buf, int size);

inline utils::hook::detour load_xmodelasset;
void Load_XModelAsset_Detour(XAssetHeader* model);