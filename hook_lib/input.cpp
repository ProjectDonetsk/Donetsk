#include "addr_utils.hpp"
#include "input.h"

void CL_Keys_Event_Detour(int localClientNum, int key, bool down, unsigned int time, int virtualKey, int controllerIndex)
{
	auto Con_ToggleConsole = reinterpret_cast<void(*)()>(0x1415B18C0_g);
	auto Con_ToggleConsoleOutput = reinterpret_cast<void(*)()>(0x1415B1930_g);
	auto DevGui_Toggle = reinterpret_cast<void(*)()>(0x1417E9DA0_g);
	auto Con_IsActive = reinterpret_cast<bool(*)(int localClientNum)>(0x1415b0EF0_g);

	if (down)
	{
		switch (key)
		{
		case K_GRAVE:

			if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			{
				if (Con_IsActive(localClientNum) == false)
				{
					Con_ToggleConsole();
				}
				Con_ToggleConsoleOutput();
			}
			else
			{
				Con_ToggleConsole();
			}
			return;
			break;
		case K_F1:
			DevGui_Toggle();
			return;
			break;
		}
	}

	cl_keys_event.stub<void>(localClientNum, key, down, time, virtualKey, controllerIndex);
}

void CL_InputMP_ExecBinding_Detour(int localClientNum, int kb, int key, int forceNotify)
{
	switch (key) {
	case K_N:
		CL_Main_AddReliableCommand("noclip");
		break;
	}

	cl_inputmp_execbinding.stub<void>(localClientNum, kb, key, forceNotify);
}