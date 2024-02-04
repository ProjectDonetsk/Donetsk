#include "addr_utils.hpp"
#include "script.h"
#include "game_inc.h"

void Load_ScriptFile_Detour(int streamStart)
{
	auto DB_PatchMem_PushAsset = reinterpret_cast<void(*)(size_t len, ScriptFile * script)>(0x140D8D860_g);
	auto Load_Stream = reinterpret_cast<void(*)(int streamStart, void* ptr, size_t size)>(0x1411B2A20_g);
	auto DB_PushStreamPos = reinterpret_cast<void(*)(int param_1)>(0x1411B2570_g);
	auto Load_XString = reinterpret_cast<void(*)(int param_1)>(0x140DD3400_g);
	auto DB_PopStreamPos = reinterpret_cast<void(*)(void)>(0x1411B24C0_g);
	auto DB_PatchMem_PopAsset = reinterpret_cast<void(*)(void)>(0x140D8D850_g);
	auto DB_ReadXFile = reinterpret_cast<void(*)(void* ptr, size_t size)>(0x1411A85D0_g);

	ScriptFile** varScriptFile = reinterpret_cast<ScriptFile**>(0x145D43670_g);
	char** varXString = reinterpret_cast<char**>(0x145D417C0_g);
	char** varConstChar = reinterpret_cast<char**>(0x145D417B0_g);
	char** varbyte = reinterpret_cast<char**>(0x145D415D8_g);
	char** g_streamPosGlob_pos = reinterpret_cast<char**>(0x14D120C00_g);

	char* backup;
	ScriptFile* scriptfile;

	DB_PatchMem_PushAsset(ASSET_TYPE_SCRIPTFILE, *varScriptFile);
	Load_Stream(streamStart, *varScriptFile, sizeof(ScriptFile));
	DB_PushStreamPos(5);

	char* xStringBackup = *varXString;
	*varXString = reinterpret_cast<char*>(*varScriptFile);
	Load_XString(1);
	*varXString = xStringBackup;
	DB_PushStreamPos(6);

	scriptfile = *varScriptFile;

	backup = *varConstChar;

	printf("Loading scriptfile '%s' into database\n", scriptfile->name);
	std::string filepath = "script.gscbin";
	bool scriptgscbin = false;

	if (!strcmp(scriptfile->name, "1892") && file_exists("script.gscbin"))
	{
		scriptgscbin = true;
	}
	else
	{
		std::string scriptname = scriptfile->name;
		if (isSubStr(scriptname, ".gsc"))
		{
			filepath = "donetsk/scripts/" + scriptname + "bin";
		}
		else // numbered scriptfiles like "1892"
		{
			filepath = "donetsk/scripts/" + scriptname + ".gscbin";
		}
	}

	if (file_exists(filepath.c_str()) || scriptgscbin)
	{
		std::ifstream script;
		script.open(filepath, std::ios::binary | std::ios::ate);
		int size = (int)script.tellg();
		script.seekg(0, std::ios::beg);

		char* customScript = new char[size];
		script.read(customScript, size);
		script.seekg(0, std::ios::beg);

		while (script.get() != '\0'); // read past the name
		int vars[3] = { 0 };
		script.read((char*)vars, sizeof(int) * 3); //read header info

		if (scriptfile->buffer != NULL)
		{
			*varConstChar = *g_streamPosGlob_pos;
			scriptfile->buffer = *varConstChar;

			char* dummyMem = new char[scriptfile->compressedLen];
			DB_ReadXFile(dummyMem, scriptfile->compressedLen);
			delete[scriptfile->compressedLen] dummyMem;

			memmove(*g_streamPosGlob_pos, customScript + (int)script.tellg(), vars[0]);

			*g_streamPosGlob_pos = *g_streamPosGlob_pos + vars[0];
			scriptfile->compressedLen = vars[0];
		}
		*varConstChar = backup;
		scriptfile->len = vars[1];

		DB_PopStreamPos();
		DB_PushStreamPos(6);

		scriptfile = *varScriptFile;
		backup = *varbyte;

		if (scriptfile->bytecode != NULL)
		{
			*varbyte = *g_streamPosGlob_pos;
			scriptfile->bytecode = (unsigned char*)*varbyte;

			char* dummyMem = new char[scriptfile->bytecodeLen];
			DB_ReadXFile(dummyMem, scriptfile->bytecodeLen);
			delete[scriptfile->bytecodeLen] dummyMem;

			memmove(*g_streamPosGlob_pos, customScript + vars[0] + (int)script.tellg(), vars[2]);

			*g_streamPosGlob_pos = *g_streamPosGlob_pos + vars[2];
			scriptfile->bytecodeLen = vars[2];
		}
		*varbyte = backup;

		delete[size] customScript;
		script.close();
	}
	else
	{
		if (scriptfile->buffer != NULL)
		{
			*varConstChar = *g_streamPosGlob_pos;
			scriptfile->buffer = *varConstChar;
			Load_Stream(0, *varConstChar, scriptfile->compressedLen);
		}
		*varConstChar = backup;

		DB_PopStreamPos();
		DB_PushStreamPos(6);

		scriptfile = *varScriptFile;
		backup = *varbyte;
		if (scriptfile->bytecode != NULL)
		{
			*varbyte = *g_streamPosGlob_pos;
			scriptfile->bytecode = (unsigned char*)*varbyte;
			Load_Stream(0, *varbyte, scriptfile->bytecodeLen);
		}
		*varbyte = backup;
	}

	DB_PopStreamPos();
	DB_PopStreamPos();
	DB_PatchMem_PopAsset();
}

void dump_gsc_script(std::ofstream& stream, ScriptFile* scriptfile)
{
	std::string buffer;
	buffer.append(scriptfile->name, strlen(scriptfile->name) + 1);

	buffer.append(reinterpret_cast<char*>(&scriptfile->compressedLen), 4);
	buffer.append(reinterpret_cast<char*>(&scriptfile->len), 4);
	buffer.append(reinterpret_cast<char*>(&scriptfile->bytecodeLen), 4);
	buffer.append(scriptfile->buffer, scriptfile->compressedLen);
	buffer.append((char*)scriptfile->bytecode, scriptfile->bytecodeLen);

	stream << buffer;
}


void ProcessScriptFile(void* scrContext, ScriptFile* scriptfile)
{
	/*if (scriptfile)
	{
		if (strcmp(scriptfile->name, "1892") == 0)
		{
			std::ofstream gscbin_file("1892.gscbin", std::ios::out | std::ios::binary);
			if (gscbin_file.is_open())
			{
				dump_gsc_script(gscbin_file, scriptfile);
				gscbin_file.close();
			}
		}
	}*/

	if (g_dumpScripts->current.enabled)
	{
		std::string scriptFileStr = "";
		if (isSubStr(scriptfile->name, ".gsc"))
		{
			scriptFileStr = "gsc_dump/" + std::string(scriptfile->name) + "bin";
		}
		else
		{
			scriptFileStr = "gsc_dump/" + std::string(scriptfile->name) + ".gscbin";
		}

		size_t lastSlash = scriptFileStr.find_last_of("/");
		if (lastSlash != std::string::npos && isSubStr(scriptfile->name, "/"))
		{
			std::string directory = scriptFileStr.substr(0, lastSlash);

			std::filesystem::create_directories(directory);
		}

		std::ofstream gscbin_file(scriptFileStr, std::ios::out | std::ios::binary);
		if (gscbin_file.is_open())
		{
			dump_gsc_script(gscbin_file, scriptfile);
			gscbin_file.close();
		}
	}

	process_script_file.stub<void>(scrContext, scriptfile);
}