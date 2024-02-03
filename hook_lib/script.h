#pragma once
#include "Main.hpp"

void Load_ScriptFile_Detour(int streamStart);

inline utils::hook::detour process_script_file;
void ProcessScriptFile(void* scrContext, ScriptFile* scriptfile);