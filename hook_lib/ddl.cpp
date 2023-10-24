#include "ddl.h"

bool DDL_SetUInt_Detour(const DDLState* state, DDLContext* ddlContext, unsigned int val)
{
	//ddlContext->obfuscated = false;
	//printf("%p - %p\n", state->offset, (uintptr_t)(ddlContext->buff) + state->offset);

	return ddl_setuint.stub<bool>(state, ddlContext, val);
}