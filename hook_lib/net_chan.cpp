#include "net_chan.h"
#include "game_inc.h"

bool NET_OutOfBandData_Detour(int sock, netadr_t* adr, const unsigned __int8* format, int len)
{
	return net_outofbanddata.stub<bool>(sock, adr, format, len);
}