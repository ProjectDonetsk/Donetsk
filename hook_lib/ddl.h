#pragma once
#include "Main.hpp"

inline utils::hook::detour ddl_setuint;
bool DDL_SetUInt_Detour(const DDLState* state, DDLContext* ddlContext, unsigned int val);