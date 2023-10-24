#pragma once
#include "Main.hpp"

int BG_Omnvar_GetType(OmnvarDef* ovDef);

void DumpOmnvars();

void Cmd_Omnvar_Set_f();

void Cmd_Omnvars_Dump_f();

OmnvarDef* BG_Omnvar_GetDef(unsigned int index);