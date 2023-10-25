#include "Main.hpp"
#include "game_inc.h"

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
	return 1;
}

char buffer[0x5000];

BOOL WINAPI DllMain(HMODULE hModule, DWORD Reason, LPVOID lpVoid)
{
	g_Addrs.ModuleBase = (uintptr_t)(GetModuleHandle(0));
	utils::hook::set<char>(0x1403061A0_g, 0xC3); // Mystery function 1
	if (Reason == DLL_PROCESS_ATTACH) {
		AllocConsole();
		FILE* Dummy;
		freopen_s(&Dummy, "CONOUT$", "w", stdout);
		freopen_s(&Dummy, "CONIN$", "r", stdin);

		utils::nt::library game{};
		utils::nt::library user32("user32.dll");
		utils::nt::library ntdll("ntdll.dll");
		utils::nt::library kernel32("kernel32.dll");

		va = (const char* (*)(const char*, ...))0x1413F3010_g; //j_va

		printf("Base Address: %p\n", base);

		addCustomDvars();
		addCustomCmds();
		patchGame();

		printf("Discord: discord.gg/donetsk\n");

		cmd_args = (CmdArgs*)(0x14D20CBD0_g);

		clientUIActives = (clientUIActive_t*)(0x14EEF1280_g);
	}

	return TRUE;
}

uintptr_t find_pattern(const char* module_name, const char* pattern) {
	const auto get_module_size = [=](uintptr_t module_base)
		{
			return reinterpret_cast<PIMAGE_NT_HEADERS>(module_base + reinterpret_cast<PIMAGE_DOS_HEADER>(module_base)->e_lfanew)->OptionalHeader.SizeOfImage;
		};
	const auto module_start = (uintptr_t)GetModuleHandle(module_name);
	if (module_start != 0ULL)
	{
		const auto module_end = module_start + get_module_size(module_start);

		const char* pattern_current = pattern;
		uintptr_t current_match = NULL;

		MEMORY_BASIC_INFORMATION64 page_information = {};
		for (auto current_page = reinterpret_cast<unsigned char*>(module_start); current_page < reinterpret_cast<unsigned char*>(module_end); current_page = reinterpret_cast<unsigned char*>(page_information.BaseAddress + page_information.RegionSize))
		{
			VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));
			if (page_information.Protect == PAGE_NOACCESS)
				continue;

			if (page_information.State != MEM_COMMIT)
				continue;

			if (page_information.Protect & PAGE_GUARD)
				continue;

			for (auto current_address = reinterpret_cast<unsigned char*>(page_information.BaseAddress); current_address < reinterpret_cast<unsigned char*>(page_information.BaseAddress + page_information.RegionSize - 0x8); current_address++)
			{
				if (*current_address != GET_BYTE(pattern_current) && *pattern_current != '\?') {
					current_match = 0ULL;
					pattern_current = pattern;
					continue;
				}

				if (!current_match)
					current_match = reinterpret_cast<uintptr_t>(current_address);

				pattern_current += 3;
				if (pattern_current[-1] == NULL)
					return current_match;
			}
		}
	}

	return 0ULL;
}

uintptr_t find_pattern(uintptr_t start, const char* module_name, const char* pattern) {
	const auto get_module_size = [=](uintptr_t module_base)
		{
			return reinterpret_cast<PIMAGE_NT_HEADERS>(module_base + reinterpret_cast<PIMAGE_DOS_HEADER>(module_base)->e_lfanew)->OptionalHeader.SizeOfImage;
		};
	const auto module_start = start;
	if (module_start != 0ULL)
	{
		const auto module_end = module_start + get_module_size(module_start);

		const char* pattern_current = pattern;
		uintptr_t current_match = NULL;

		MEMORY_BASIC_INFORMATION64 page_information = {};
		for (auto current_page = reinterpret_cast<unsigned char*>(module_start); current_page < reinterpret_cast<unsigned char*>(module_end); current_page = reinterpret_cast<unsigned char*>(page_information.BaseAddress + page_information.RegionSize))
		{
			VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));
			if (page_information.Protect == PAGE_NOACCESS)
				continue;

			if (page_information.State != MEM_COMMIT)
				continue;

			if (page_information.Protect & PAGE_GUARD)
				continue;

			for (auto current_address = reinterpret_cast<unsigned char*>(page_information.BaseAddress); current_address < reinterpret_cast<unsigned char*>(page_information.BaseAddress + page_information.RegionSize - 0x8); current_address++)
			{
				if (*current_address != GET_BYTE(pattern_current) && *pattern_current != '\?') {
					current_match = 0ULL;
					pattern_current = pattern;
					continue;
				}

				if (!current_match)
					current_match = reinterpret_cast<uintptr_t>(current_address);

				pattern_current += 3;
				if (pattern_current[-1] == NULL)
					return current_match;
			}
		}
	}

	return 0ULL;
}
menu_variables vars;

size_t operator"" _b(const size_t val)
{
	return base + val;
}

size_t reverse_b(const size_t val)
{
	return val - base;
}

size_t reverse_b(const void* val)
{
	return reverse_b(reinterpret_cast<size_t>(val));
}

size_t operator"" _g(const size_t val)
{
	return base + (val - 0x140000000);
}

size_t reverse_g(const size_t val)
{
	return (val - base) + 0x140000000;
}

size_t reverse_g(const void* val)
{
	return reverse_g(reinterpret_cast<size_t>(val));
}