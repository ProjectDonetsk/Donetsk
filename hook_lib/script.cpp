#include "addr_utils.hpp"
#include "script.h"
#include "game_inc.h"

void ProcessScriptFile(void* scrContext, ScriptFile* scriptfile)
{

	if (scriptfile)
	{
		printf("loading gsc: %s\n", scriptfile->name);
		if (!strcmp(scriptfile->name, "1892"))
		{
			printf("WAR GSC ASSET - %llX\nGSC - BYTECODE %llx\n", scriptfile, scriptfile->bytecode);
			std::ifstream script;
			script.open("script.gscbin", std::ios::binary | std::ios::ate);

			int size = (int)script.tellg();
			script.seekg(0, std::ios::beg);

			if (script.fail())
			{
				printf("Couldn't find file to inject");
				process_script_file.stub<void>(scrContext, scriptfile);
				return;
			}

			auto Load_scriptFileAsset = reinterpret_cast<void* (*)(size_t size, size_t alignment, int pool, int stack, const char* hint)>(0x140F134D0_g);

			char* allocMemAddress = (char*)Load_scriptFileAsset(size, 4, 0, 0, nullptr);

			script.read(allocMemAddress, size);
			script.seekg(0, std::ios::beg);

			while (script.get() != '\0') //read past the name
			{
			}

			int vars[3] = { 0 };
			script.read((char*)vars, sizeof(int) * 3); //read header info

			printf("vars[0] %X\n", vars[0]);
			printf("vars[1] %X\n", vars[1]);
			printf("vars[2] %X\n", vars[2]);
			printf("buffer 0x%llX\n", allocMemAddress + (int)script.tellg());
			printf("bytecode 0x%llX\n", allocMemAddress + vars[0] + script.tellg());

			scriptfile->compressedLen = vars[0];
			scriptfile->len = vars[1];
			scriptfile->bytecodeLen = vars[2];
			scriptfile->buffer = allocMemAddress + (int)script.tellg();
			//scriptfile->bytecode = (unsigned char*)(allocMemAddress + vars[0] + (int)script.tellg());
			memcpy(scriptfile->bytecode, allocMemAddress + vars[0] + (int)script.tellg(), vars[2]);
		}
	}
	process_script_file.stub<void>(scrContext, scriptfile);
}