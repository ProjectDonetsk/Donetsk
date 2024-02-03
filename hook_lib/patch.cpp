#include "addr_utils.hpp"
#include "patch.h"
#include "game_inc.h"

int iTick = 0;
bool bFinished;
bool btoggle;

dvar_t* cl_textChatEnabled = reinterpret_cast<dvar_t*>(0x14EEB0738_g);

uintptr_t xuid_generated;
int collision_ticker;
void R_EndFrame_Detour()
{
	if (strcmp(Dvar_GetStringSafe("NSQLTTMRMP"), "mp_donetsk") == 0)
	{
		*reinterpret_cast<int*>(0x14E385A68_g) = 80;
		*reinterpret_cast<int*>(0x14E385A78_g) = 80;
		if (collision_ticker == 60) {
			btoggle = !btoggle;
			*reinterpret_cast<int*>(0x145CC7555_g) = btoggle; // s_transientsCollisionMP_LobbyToGameStart
		}
		collision_ticker++;
	}
	else {
		*reinterpret_cast<int*>(0x14E385A68_g) = 1000;
		*reinterpret_cast<int*>(0x14E385A78_g) = 1000;
	}

	if (!bFinished) {
		if (iTick == 500) {
			DWORD flOldProtect;
			XUID xuid;
			xuid.RandomXUID();
			utils::hook::set<int>(0x144622BE0_g, 1);

			utils::hook::set<uintptr_t>(0x14E5C07C0_g, 0x11CB1243B8D7C31E | xuid.m_id * xuid.m_id);
			utils::hook::set<uintptr_t>(0x14F05ACE8_g, 0x11CB1243B8D7C31E | xuid.m_id * xuid.m_id);

			utils::hook::set<uintptr_t>(0x14E5C07E8_g, 0x11CB1243B8D7C31E | (xuid.m_id * xuid.m_id) / 6); // s_presenceData

			utils::hook::set<int>(0x14E371231_g, 1);
			utils::hook::set<int>(0x144622910_g, 2);
			utils::hook::set<int>(0x144622BE0_g, 1);

			utils::hook::set<char>(*reinterpret_cast<uintptr_t*>(0x14EE560B0_g) + 0x28, 0);
			utils::hook::set(0x14E5C0730_g, 2);

			auto get_bnet_class = reinterpret_cast<uintptr_t(*)()>(0x141660280_g);
			uintptr_t bnet_class = get_bnet_class();
			*(DWORD*)(bnet_class + 0x2F4) = 0x795230F0;
			*(DWORD*)(bnet_class + 0x2FC) = 0;
			*(BYTE*)(bnet_class + 0x2F8) = 31;

			printf("LOADED!\n");
			bFinished = true;
		}
		else {
			iTick += 1;
		}
	}

	r_endframe.stub<void>();
}

const char* username_Detour()
{
	if (player_name) {
		return player_name->current.string;
	}
	else {
		return "Unknown Name";
	}
}

void GScr_SpawnBrCircle_Detour(uintptr_t scrContext)
{
	if (spawn_br_gas->current.enabled) {
		gscr_spawnbrcircle.stub<void>(scrContext);
	}
}

bool Live_IsUserSignedInToDemonware_Detour()
{
	return true;
}

int dwGetLogOnStatus_Detour()
{
	return 2;
}

int LiveStorage_GetActiveStatsSource_Detour()
{
	return 1;
}

bool ProfanityFilter_IsBadWord_Detour()
{
	return false;
}

void hooks()
{
	process_script_file.create(0x141322350_g, ProcessScriptFile);
	utils::hook::jump(0x140DFE370_g, Load_ScriptFile_Detour);

	//utils::hook::jump(0x141BD3360_g, sub_141BD3360_Detour);

	//sub_141BD3360.create(0x141BD3360_g, sub_141BD3360_Detour);

	// utils::hook::copy(0x1530AD525_g, data_buf, 0x12856B); // Splash screen data

	sv_updateuserinfo_detour.create(0x14136d0c0_g, SV_UpdateUserinfo_f);

	db_findxassetheader.create(0x1411AA890_g, DB_FindXAssetHeader_Detour);
	db_getrawbufferinflate.create(0x1412C2AE0_g, DB_GetRawBufferInflate_Detour);
	ddl_setuint.create(0x1420529C0_g, DDL_SetUInt_Detour);
	//db_pollfastfilestate.create(0x1411ADD00_g, DB_PollFastfileState_Detour);

	load_mapentsasset.create(0x140F61690_g, Load_MapEntsAsset_Detour);
	load_clipmapasset.create(0x140F60F40_g, Load_ClipMapAsset_Detour);
	load_xmodelasset.create(0x140F62290_g, Load_XModelAsset_Detour);
	//load_ttfasset.create(0x140F61F40_g, Load_TTFAsset_Detour);

	db_getrawbuffer.create(0x1412C29A0_g, DB_GetRawBuffer_Detour);

	utils::hook::jump(0x141528490_g, Live_IsUserSignedInToDemonware_Detour);
	utils::hook::jump(0x1417EC930_g, dwGetLogOnStatus_Detour);
	utils::hook::jump(0x1412A1EB0_g, LiveStorage_GetActiveStatsSource_Detour);
	utils::hook::jump(0x1419B96A0_g, LuaShared_LuaCall_IsDemoBuild_Detour);

	dvar_findvarbyname.create(0x1413E63A0_g, Dvar_FindVarByName_Detour);

	db_loadxfile.create(0x1411A79F0_g, DB_LoadXFile_Detour);
	CL_TransientsMP_ProcessLoadingQueue.create(0x1415F7BF0_g, CL_TransientsMP_ProcessLoadingQueue_Detour);

	lui_cod_registerdvars.create(0x1419D4500_g, LUI_CoD_RegisterDvars_Detour);
	net_outofbanddata.create(0x1412BB350_g, NET_OutOfBandData_Detour);
	cl_keys_event.create(0x1415BEB80_g, CL_Keys_Event_Detour);
	dvar_registerbool.create(0x1413E7670_g, Dvar_RegisterBool_Detour);
	dvar_registerstring.create(0x1413E7A70_g, Dvar_RegisterString_Detour);
	seh_stringed_getstring.create(0x1413CC2A0_g, SEH_StringEd_GetString_Detour);

	cl_createdevgui.create(0x1415B2080_g, CL_CreateDevGui_Detour);
	cg_mainmp_init.create(0x141792E60_g, CG_MainMP_Init_Detour);
	partyhost_startprivateparty.create(0x14119F0D0_g, PartyHost_StartPrivateParty_Detour);

	PM_WeaponUseAmmo.create(0x141155AF0_g, PM_WeaponUseAmmo_Detour);

	com_gamemode_supportsfeature.create(0x1410C8980_g, Com_GameMode_SupportsFeature_Detour);

	lui_cod_luacall_enginenotifyserver_detour_impl.create(0x1419F7160_g, LUI_CoD_LuaCall_EngineNotifyServer_Detour);

	utils::hook::jump(0x141609140_g, ProfanityFilter_IsBadWord_Detour);

	cg_overrideimpacteffecttype.create(0x141733CD0_g, CG_OverrideImpactEffectType_Detour);
	bg_getweapondismembermentenabled.create(0x141170C00_g, BG_GetWeaponDismembermentEnabled_Detour);

	// replacing Com_GameMode_GetActiveGameMode call with CheatsEnabled for jump_height dvar
	utils::hook::call(0x14110195A_g, CheatsEnabled);

	// remove FF Header version check
	// db_checkxfileversion.create(0x1411A7840_g, DB_CheckXFileVersion_Detour);
	// utils::hook::jump(0x1411A7840_g, DB_CheckXFileVersion_Detour);
}

void patchGame()
{
	hooks();

	// patch ui_maxclients limit
	utils::hook::nop(0x140F30210_g, 5);
	utils::hook::nop(0x14119E51D_g, 5);
	utils::hook::nop(0x14136B8F8_g, 5);
	utils::hook::nop(0x1416029F0_g, 5);
	utils::hook::nop(0x1419E19A3_g, 5);

	// patch party_maxplayers limit
	utils::hook::nop(0x140F252EE_g, 5);
	utils::hook::nop(0x14119D23F_g, 5);
	utils::hook::nop(0x1410769B9_g, 5);
	utils::hook::set(0x1410769B9_g, 0xC3);
	utils::hook::nop(0x140F24B4B_g, 5);
	utils::hook::set(0x140F24B4B_g, 0xC3);
	utils::hook::nop(0x1416029E2_g, 5);
	utils::hook::nop(0x14119E52B_g, 5);
	utils::hook::nop(0x140f252EE_g, 5);
	utils::hook::nop(0x14119F13A_g, 5);
	utils::hook::nop(0x1410D32E2_g, 5);

	// removes "Services aren't ready yet." print
	utils::hook::nop(0x141504374_g, 5);

	// enable tweaking of jump_slowdownEnable dvar
	utils::hook::nop(0x1411014F5_g, 2);
	utils::hook::nop(0x141101B12_g, 2);
	utils::hook::nop(0x141101C6C_g, 2);
	utils::hook::nop(0x141101D3C_g, 2);
	utils::hook::nop(0x141101EE5_g, 2);

	// fixes lost connection issue?
	utils::hook::nop(0x14165E97E_g, 5);
	utils::hook::nop(0x14165E660_g, 5);
	utils::hook::nop(0x141665289_g, 5);
	utils::hook::nop(0x14166567D_g, 5);

	// enable functionality for jump_height dvar
	utils::hook::set<byte>(0x141101946_g, 0xEB);

	// enable friction dvar
	utils::hook::set(0x14112141E_g, (int8_t)2);

	// remove FF Header version check
	// utils::hook::set<byte>(0x1411A776B_g, 0xEB);
}