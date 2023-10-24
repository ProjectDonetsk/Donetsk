#pragma once
#include "Main.hpp"

inline utils::hook::detour process_script_file;
void ProcessScriptFile(void* scrContext, ScriptFile* scriptfile);