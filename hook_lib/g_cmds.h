#pragma once
#include "Main.hpp"

void addCustomCmds();

inline utils::hook::detour g_cmdsmp_clientcommand;
void G_CmdsMP_ClientCommand_Detour(int clientNum);

void set_byte_f();

void set_short_f();

void set_int_f();

void set_float_f();

void set_pointer_f();

void Cmd_Quit_f();

void Cmd_OpenMenu_f();

void Cmd_AddBot_f();

void Cmd_AddTestClient_f();

void SV_CmdsMP_MapRestart_f();

void SV_CmdsMP_FastRestart_f();

void Cmd_DDLDump_f();

void Cmd_WeaponDefDump_f();

void Cmd_ViewVehicleEnts_f();

void Cmd_LoadoutSave_f();

void Cmd_UnlockAll_f();

void Cmd_WeaponDef_Load_f();