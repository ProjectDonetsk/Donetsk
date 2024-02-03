#include "Main.hpp"
#include "game_inc.h"
#include "debug_output.h"

#include "discord.h"
#include "addr_utils.hpp"

void entry_point()
{
	XUID xuid;
	xuid.RandomXUID();

	printf("%i\n", xuid.m_id);

	r_endframe.create(0x141966950_g, R_EndFrame_Detour);
	utils::hook::jump(0x141297580_g, Cmd_Exec_Internal);
	utils::hook::jump(0x1415E1340_g, CL_ScreenMP_DrawOverlay_Detour);
	utils::hook::jump(0x1413FD3A0_g, username_Detour);

	db_zones_performzoneload.create(0x140F677A0_g, DB_Zones_PerformZoneLoad_Detour);

	g_cmdsmp_clientcommand.create(0x14120B6A0_g, G_CmdsMP_ClientCommand_Detour);
	cl_inputmp_execbinding.create(0x1415E1AB0_g, CL_InputMP_ExecBinding_Detour);
	gscr_spawnbrcircle.create(0x141243AB0_g, GScr_SpawnBrCircle_Detour);

	utils::hook::jump(0x140D6B7D0_g, CL_TransientsCollisionMP_SetTransientMode_Detour);

	printf("hooked!\n");
}

extern "C" __declspec(dllexport) int DiscordCreate()
{
	CreateThread(0, 0xA0, (LPTHREAD_START_ROUTINE)entry_point, 0, 0, 0);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DiscordThread, 0, 0, 0);
	return 1;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD Reason, LPVOID lpVoid)
{
	initAddrUtils();
	utils::hook::set<char>(0x1403061A0_g, 0xC3); // Mystery function 1
	if (Reason == DLL_PROCESS_ATTACH) {
		AllocConsole();
		FILE* Dummy;
		freopen_s(&Dummy, "CONOUT$", "w", stdout);
		freopen_s(&Dummy, "CONIN$", "r", stdin);
		SetConsoleTitleA("Donetsk Client Console");

		utils::nt::library game{};
		utils::nt::library user32("user32.dll");
		utils::nt::library ntdll("ntdll.dll");
		utils::nt::library kernel32("kernel32.dll");

		va = (const char* (*)(const char*, ...))0x1413F3010_g; //j_va

		printf("Base Address: %p\n", 0_b);

		// prevents tact error E_REPAIR (28) from happening
		remove("Data/data/CASCRepair.mrk");

		debug_output_init(nullptr);
		addCustomCmds();
		patchGame();

		printf("Website: donetsk.live\n");

		cmd_args = (CmdArgs*)(0x14D20CBD0_g);

		clientUIActives = (clientUIActive_t*)(0x14EEF1280_g);
	}

	return TRUE;
}

menu_variables vars;
