#pragma once
#include <Windows.h>
#include <winternl.h>
#include <iostream>
#include <fstream>
#include <string>

#include <dxgi1_5.h>
#include <d3d12.h>
#include <intrin.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "user32.lib")

#include "common/utils/hook.hpp"
#include "common/utils/hardware_breakpoint.hpp"

#include "structs.h"
#include "assets.h"
#include "functions.hpp"

#include "ini.h"
#include "json.hpp"

#pragma warning(disable:4996)
#pragma comment(lib, "Gdi32.lib")


struct menu_variables {
	bool bInitiateMenu;
	bool bMenuOpen;

};
extern menu_variables vars;

struct DvarPair
{
	const char* m_key;
	const char* m_value;
};
inline bool IsBadPointer(uintptr_t* ptr)
{
	__try
	{
		volatile auto result = *ptr;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return true;
	}
	return false;
}

struct DvarMap
{
	DvarPair m_pairs[10000];
};
extern int g_dvarmapcount;
extern DvarPair g_dvarmap[6821];

struct shaderOverride_t
{
	float scrollRateX;
	float scrollRateY;
	float scrollRateR;
	float tilingX;
	float tilingY;
	float rotation;
	float alpha;
	float emissive;
	float atlasTime;
};

struct GfxSceneHudOutlineInfo
{
	unsigned int color;
	float scopeStencil;
	bool drawOccludedPixels;
	bool drawNonOccludedPixels;
	bool fill;
	bool useAlternateColor;
	bool forSpectator;
	bool specialActive;
	unsigned __int8 renderMode;
	unsigned __int8 lineWidth;
	unsigned __int8 temperatureSet;
	unsigned int mapEntLookup;
	float temperatureBase;
	float temperatureScale;
	float characterEVOffset;
};

