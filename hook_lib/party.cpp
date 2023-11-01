#include "party.h"
#include "game_inc.h"

void PartyHost_StartPrivateParty_Detour(int localClientNum, int localControllerIndex, bool currentlyActive, int hostType)
{
	partyhost_startprivateparty.stub<void>(localClientNum, localControllerIndex, currentlyActive, hostType);

	static bool autoexec = false;
	if (!autoexec)
	{
		Cbuf_AddText("exec autoexec.cfg");
		LoadInventory();
	}
}