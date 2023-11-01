#include "addr_utils.hpp"
#include "cmd.h"

void Cmd_Exec_Internal(bool isSuperUser)
{
	const char* cmdbuf;
	const char* file;
	auto DB_FindXAssetHeader = reinterpret_cast<uintptr_t(*)(XAssetType type, const char* givenName, int allowCreateDefault)>(0x1411AA890_g);
	auto DB_ReadRawFile = reinterpret_cast<const char* (*)(unsigned int a1, unsigned int a2, const char* a3, char a4)>(0x141297140_g);
	auto Core_strcpy_truncate = reinterpret_cast<bool(*)(char* dest, unsigned __int64 destsize, const char* src)>(0x142036A90_g);
	auto Com_DefaultExtension = reinterpret_cast<void(*)(char* path, int maxSize, const char* extension)>(0x1413F1AE0_g);
	char path[64];

	if (cmd_args->argc[cmd_args->nesting] == 2)
	{
		Core_strcpy_truncate(path, 64, *(cmd_args->argv[cmd_args->nesting] + 1));
		Com_DefaultExtension(path, 64, ".cfg");
		if (DB_FindXAssetHeader(ASSET_TYPE_RAWFILE, path, 0))
		{
			if (!DB_ReadRawFile(0, cmd_args->controllerIndex[cmd_args->nesting], path, isSuperUser))
			{
				if (cmd_args->argc[cmd_args->nesting] <= 1)
					file = "";
				else
					file = *(cmd_args->argv[cmd_args->nesting] + 1);
				printf("couldn't exec %s\n", file);
			}
		}
		else
		{
			FS_ReadFile(path, &cmdbuf);
			LUI_CoD_LuaCall_ExecNow(*reinterpret_cast<uintptr_t*>(0x151868880_g), cmdbuf);
		}
	}
	else
	{
		printf(0, "exec <filename> : execute a script file\n");
	}
}