#include "party.h"
#include "game_inc.h"

void PartyHost_StartPrivateParty_Detour(int localClientNum, int localControllerIndex, bool currentlyActive, int hostType)
{
	Cbuf_AddText("exec autoexec.cfg");

	partyhost_startprivateparty.stub<void>(localClientNum, localControllerIndex, currentlyActive, hostType);

	LoadInventory();

	Cbuf_AddText("set cl_textChatEnabled 1");
}