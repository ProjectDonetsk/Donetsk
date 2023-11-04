#pragma once
#include "Main.hpp"

struct gentity_s;

struct CmdArgs;

union DvarValue
{
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	__int64 integer64;
	unsigned __int64 unsignedInt64;
	float value;
	float vector[4];
	const char* string;
	unsigned __int8 color[4];
};

struct BbConstUsageFlags
{
	bool initialized;
	DvarValue codeValue;
};

struct netadr_t;

struct dvar_t
{
	const char* name;
	unsigned int checksum;
	const char* description;
	unsigned int flags;
	char level[1];
	unsigned __int8 type;
	bool modified;
	unsigned __int16 hashNext;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	char domain[0x10];
	BbConstUsageFlags BbConstUsageFlags;
};

struct EncryptionHeader
{
	unsigned int isEncrypted;
	unsigned __int8 IV[16];
};

struct __declspec(align(8)) XFile
{
	unsigned __int64 size;
	unsigned __int64 preloadWalkSize;
	unsigned __int64 blockSize[11];
	EncryptionHeader encryption;
};

struct DB_FFHeader
{
	unsigned __int64 magic;
	unsigned int headerVersion;
	unsigned int xfileVersion;
	bool dashCompressBuild;
	bool dashEncryptBuild;
	unsigned __int8 transientFileType[1];
	unsigned int residentPartSize;
	unsigned int residentHash;
	unsigned int alwaysLoadedPartSize;
	XFile xfileHeader;
};

struct EncryptionInfo
{
	EncryptionHeader header;
	unsigned __int8 privateKey[32];
};

struct DBFileHandle
{
	unsigned __int8 fileID[4];
	unsigned __int64 dcacheFileID;
};

struct cmd_function_s
{
	cmd_function_s* next;
	const char* name;
	const char** autoCompleteList;
	unsigned int autoCompleteListCount;
	void(__fastcall* function)();
};

struct DBFile
{
	char name[64];
	DBFileHandle dbFileHandle;
	bool isSecured;
	EncryptionInfo encryption;
};

struct Weapon;
struct scrContext_t;

extern dvar_t* player_name;
extern dvar_t* sv_cheats;
extern dvar_t* spawn_br_gas;
extern dvar_t* show_watermark;
extern dvar_t* player_sustainammo;
extern dvar_t* print_debug;

extern cmd_function_s set_byte_f_VAR;
extern cmd_function_s set_short_f_VAR;
extern cmd_function_s set_int_f_VAR;
extern cmd_function_s set_float_f_VAR;
extern cmd_function_s set_pointer_f_VAR;
extern cmd_function_s quit_f_VAR;
extern cmd_function_s openmenu_f_VAR;
extern cmd_function_s addbot_f_VAR;
extern cmd_function_s addTestClient_f_VAR;
extern cmd_function_s ddldump_f_VAR;
extern cmd_function_s weapondefdump_f_VAR;
extern cmd_function_s view_vehicle_ents_f_VAR;
extern cmd_function_s loadout_save_f_VAR;
extern cmd_function_s FastRestart_f_VAR;
extern cmd_function_s MapRestart_f_VAR;
extern cmd_function_s omnvar_set_f_VAR;
extern cmd_function_s omnvar_dump_f_VAR;
extern cmd_function_s unlockall_f_VAR;
extern cmd_function_s dump_weapdefs_f_VAR;
extern cmd_function_s load_weapdef_f_VAR;
extern CmdArgs* cmd_args;

void* RtlAddVectoredExceptionHandler(LONG First, PVECTORED_EXCEPTION_HANDLER Handler);
NTSTATUS NtContinue(PCONTEXT threadContext, BOOLEAN raiseAlert);

bool isSubStr(std::string str, std::string subStr);
float strToFloat(const std::string& str);

#pragma region //game functions

extern const char* (*va)(const char* fmt, ...);

void Live_FakeUserSignIn(int controllerIndex, const char* gamertag);

void R_AddCmdDrawText(const char* text, int maxChars, void /* GfxFont */* font, int fontHeight, float x, float y, float xScale, float yScale, float rotation, const float* color, const void /* FontGlowStyle */* glowStyle, bool usePost);

bool CG_WorldPosToScreenPosReal(int localClientNum, const uintptr_t scrPlace, const float* worldPos, float* outScreenPos);

void CG_DrawRotatedPicPhysical(uintptr_t scrPlace, float x, float y, float width, float height, float angle, const float* color, uintptr_t material);

inline bool file_exists(const char* name) {
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}

uintptr_t FS_ReadFile(const char* qpath, const char** buffer);
const char* Dvar_GetStringSafe(const char* dvar);
bool Dvar_GetBoolSafe(const char* dvar);
int Dvar_GetIntSafe(const char* dvar);

unsigned int* GetRandSeed();
unsigned __int64 Sys_Microseconds();
int I_irand(int min, int max);
unsigned __int64 I_atoui64_hex(const char* str);
unsigned __int64 I_atoui64(const char* str);
dvar_t* Dvar_FindVarByName(const char* dvarName);

void CL_DrawText(const uintptr_t scrPlace, const char* text, int maxChars, uintptr_t font, float x, float y, int horzAlign, int vertAlign, float xScale, float yScale, const float* color, int style);
dvar_t* Dvar_RegisterString(const char* dvarName, const char* value, unsigned int flags, const char* description);
dvar_t* Dvar_RegisterBool(const char* dvarName, bool value, unsigned int flags, const char* description);

void LUI_CoD_LuaCall_ExecNow(uintptr_t luaVM, const char* str);
bool LUI_LuaCall_Game_IsEntityAlive(uintptr_t luaVM, int entityNum);

void Cbuf_AddText(const char* cmd);

bool lua_toboolean(uintptr_t L, int idx);
const char* lua_tolstring(uintptr_t L, int idx, size_t* len);

void lua_pushboolean(uintptr_t L, int b);
void lua_remove(uintptr_t L, int idx);
void lua_call(uintptr_t L, int nargs, int nresults);
void lua_getfield(uintptr_t L, int idx, const char* k);
void lua_pushvalue(uintptr_t L, int idx);
void lua_pushstring(uintptr_t L, const char* str);
void lua_pushinteger(uintptr_t L, int n);
void lua_settop(uintptr_t L, int idx);

bool lua_isstring(uintptr_t L, int idx);

int LuaShared_PCall(uintptr_t luaVM, int nargs, int nresults);

bool CG_DObjGetWorldBoneMatrix(uintptr_t pose, uintptr_t obj, int boneIndex, uintptr_t outTagMat, float* outOrigin);

void CG_DrawLine(float X1, float Y1, float X2, float Y2, const float* color, float Width);
void CG_DrawBone(int entIndex, uintptr_t ent, int from, int to, const float* color);
void CG_DrawBones(int entIndex, uintptr_t ent, const float* color);

bool CheatsOk(int entNum);

void Cmd_Noclip_f(int entNum);

void Cmd_God_f(int entNum);

void SV_Cmd_ArgvBuffer(int arg, char* buffer, unsigned __int64 bufferLength);
void Cmd_ArgvBuffer(int arg, char* buffer, int bufferLength);
int Cmd_Argc();
int SV_Cmd_Argc();

void Cmd_AddCommandInternal(const char* cmdName, void(__fastcall* function)(), cmd_function_s* allocedCmd);

void AddReliableCommand(uintptr_t _this, const char* commandBuffer, const int reliableCmdSize, int type);
unsigned int MSG_WriteReliableCommandToBuffer(const char* pszCommand, char* pszBuffer, unsigned int iBufferSize);

void CL_Main_AddReliableCommand(const char* cmd);

bool BG_Weapons_GetFullWeaponForName(const char* name, Weapon* outWeapon, Weapon* (__fastcall* getWeaponFunc)(Weapon* result, const char*));

void Scr_AddString(scrContext_t* scrContext, const char* value);
unsigned int GScr_ExecEntThread(gentity_s* ent, int handle, unsigned int paramcount);
void Scr_FreeThread(scrContext_t* scrContext, unsigned int handle);

int G_Weapon_GivePlayerWeapon(uintptr_t ps, uintptr_t scrContext, Weapon* weapon, int dualWield, int startInAltMode, int usedBefore);
void G_Items_AddAmmo(uintptr_t ps, Weapon* weapon, bool isAlternate, int count, int fillClip);

void G_Weapon_SelectWeapon(int clientNum, Weapon* weapon);
Weapon* BG_FindBaseWeaponForName(Weapon* result, const char* name);

scrContext_t* ScriptContext_Server();

const char* SL_ConvertToString(int id);

union XAssetHeader DB_FindXAssetHeader(enum XAssetType type, const char* givenName, int allowCreateDefault);

void Com_SetErrorMessage(const char* errorMessage);

void GamerProfile_SetDataByName(unsigned int controllerIndex, const char* settingName, float settingValue);

short* SV_ClientMP_AddTestClient();
short* SV_ClientMP_AddBot();
void GScr_Notify(short* ent, unsigned int stringValue, unsigned int paramcount);
int SL_GetString(const char* value);

void GScr_AddEntity(short* entity);

void SV_ClientMP_SpawnBotOrTestClient(short* entity);

uintptr_t G_GetEntityPlayerState(gentity_s* ent);

int G_Main_GetTime();

const char* _va(const char* format, ...);

#pragma endregion
