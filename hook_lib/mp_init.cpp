#include "mp_init.h"
#include "game_inc.h"

void CG_MainMP_Init_Detour(int localClientNum, int serverMessageNum, int serverCommandSequence, int clientNum, void* hunkUser)
{
	cg_mainmp_init.stub<void>(localClientNum, serverMessageNum, serverCommandSequence, clientNum, hunkUser);

	Cbuf_AddText("set cl_textChatEnabled 1");
}