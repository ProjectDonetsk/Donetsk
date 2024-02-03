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

		// skips Tutorial stuff
		Cbuf_AddText("setRankedPlayerData mpTutorialLevel -2147463171");
		Cbuf_AddText("setRankedPlayerData mpTutorialLevel2 28671");
		Cbuf_AddText("setRankedPlayerData mpTutorialLevel - 2147454979");
		Cbuf_AddText("setRankedPlayerData mpTutorialLevel2 61439");

		autoexec = true;
	}
}