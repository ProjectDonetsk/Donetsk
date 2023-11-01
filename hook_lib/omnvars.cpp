#include "addr_utils.hpp"
#include "omnvars.h"

int BG_Omnvar_GetType(OmnvarDef* ovDef)
{
	const char* type = (const char*)((char*)ovDef + 0x26);
	return *type;
}

void DumpOmnvars()
{
	auto G_Omnvar_GetData = reinterpret_cast<OmnvarData * (*)(unsigned int index, int clientNum, uintptr_t ps)>(0x140FC5110_g);
	auto BG_Omnvar_GetTypeString = reinterpret_cast<const char* (*)(OmnvarDef * omnvar)>(0x140CD5900_g);
	auto NetConstStrings_GetLuiStringIndex = reinterpret_cast<int(*)(const char* newValue, unsigned int*)>(0x1410F0F40_g);
	auto BG_Omnvar_GetValueString = reinterpret_cast<void(*)(OmnvarDef * ovDef, OmnvarData * ovData, char* retStr, unsigned int valueBufLen)>(0x140CD5980_g);

	g_entities = *reinterpret_cast<gentity_s**>(0x14BC20F00_g);

	uintptr_t psHost = ((uintptr_t)(g_entities + 0x150));

	int s_omnvarDefCount = *(int*)(0x145C48518_g);
	OmnvarDef* OmnvarDefs = (OmnvarDef*)(0x145C48580_g);
	for (int i = 0; i < s_omnvarDefCount; ++i)
	{
		OmnvarDef* omnvar = &OmnvarDefs[i];
		OmnvarData* data = G_Omnvar_GetData(i, 0, psHost);
		const char* typeStr = BG_Omnvar_GetTypeString(omnvar);
		int type = BG_Omnvar_GetType(omnvar);

		std::cout << "omnvar '" << omnvar->name << "' (" << typeStr << ") ";
		if (type == OMNVAR_TYPE_BOOL)
		{
			std::cout << "value(" << data->current.enabled << ") ";
		}
		else if (type == OMNVAR_TYPE_FLOAT)
		{
			std::cout << "value(" << data->current.value << ") ";
		}
		else if (type == OMNVAR_TYPE_INT)
		{
			std::cout << "value(" << data->current.integer << ") ";
		}
		else if (type == OMNVAR_TYPE_UINT || type == OMNVAR_TYPE_TIME)
		{
			std::cout << "value(" << data->current.unsignedInteger << ") ";
		}
		else if (type == OMNVAR_TYPE_NCS_LUI)
		{
			char currentStr[100] = { NULL };
			BG_Omnvar_GetValueString(omnvar, data, currentStr, 100);

			std::cout << "value'" << currentStr << "' ";
		}
		else
		{
			std::cout << "value(" << data->current.unsignedInteger << ") ";
		}

		std::cout << std::endl;
	}
}

void Cmd_Omnvar_Set_f()
{
	char ovName[100];
	char newValue[100];

	auto BG_Omnvar_GetIndexByName = reinterpret_cast<unsigned int(*)(const char* name)>(0x140CD5870_g);
	auto BG_Omnvar_GetDef = reinterpret_cast<OmnvarDef * (*)(int index)>(0x140CD5830_g);
	auto G_Omnvar_GetData = reinterpret_cast<OmnvarData * (*)(unsigned int index, int clientNum, uintptr_t ps)>(0x140FC5110_g);
	auto BG_Omnvar_GetTypeString = reinterpret_cast<const char* (*)(OmnvarDef * omnvar)>(0x140CD5900_g);
	auto G_Omnvar_MarkChanged = reinterpret_cast<void(*)(OmnvarData * omnvar)>(0x140FC51B0_g);
	auto NetConstStrings_GetLuiStringIndex = reinterpret_cast<int(*)(const char* newValue, unsigned int*)>(0x1410F0F40_g);

	g_entities = *reinterpret_cast<gentity_s**>(0x14BC20F00_g);

	if (Cmd_Argc() != 3)
	{
		printf("setOmnvar usage: setOmnvar <omnvar_name> <value>\n");
		return;
	}

	Cmd_ArgvBuffer(1, ovName, 100);
	Cmd_ArgvBuffer(2, newValue, 100);

	unsigned int omnvarIndex = BG_Omnvar_GetIndexByName(ovName);
	if (omnvarIndex == -1)
	{
		printf("Omnvar %s not found\n", ovName);
		return;
	}
	OmnvarDef* ovDef = BG_Omnvar_GetDef(omnvarIndex);
	uintptr_t psHost = ((uintptr_t)(g_entities + 0x150));
	OmnvarData* data = G_Omnvar_GetData(omnvarIndex, 0, psHost);
	const char* typeStr = BG_Omnvar_GetTypeString(ovDef);
	int type = BG_Omnvar_GetType(ovDef);

	if (type == OMNVAR_TYPE_BOOL)
	{
		char num = *newValue;
		if (num == '0' || num == '1')
		{
			(data->current).enabled = num == '1';
			G_Omnvar_MarkChanged(data);
		}
	}
	else if (type == OMNVAR_TYPE_FLOAT)
	{
		float value = strToFloat(newValue);
		(data->current).value = value;
		G_Omnvar_MarkChanged(data);
	}
	else if (type == OMNVAR_TYPE_INT)
	{
		int value = atoi(newValue);
		(data->current).integer = value;
		G_Omnvar_MarkChanged(data);
	}
	else if (type == OMNVAR_TYPE_UINT)
	{
		int value = atoi(newValue);
		if ((ovDef->maxvalue > value) && (value > ovDef->minvalue))
		{
			(data->current).unsignedInteger = value;
			G_Omnvar_MarkChanged(data);
		}
	}
	else if (type == OMNVAR_TYPE_TIME)
	{
		int value = atoi(newValue);
		if (value < 0)
		{
			printf("Expected positive value for time omnvar %s\n", ovDef->name);
			return;
		}
		(data->current).integer = value;
		G_Omnvar_MarkChanged(data);
	}
	else if (type == OMNVAR_TYPE_NCS_LUI)
	{
		int ret = NetConstStrings_GetLuiStringIndex(newValue, &(data->current).ncsString);
		if (ret == NULL)
		{
			printf("Invalid value '%s' for omnvar '%s'.\n", newValue, ovDef->name);
		}
		else
		{
			G_Omnvar_MarkChanged(data);
		}
	}
}

void Cmd_Omnvars_Dump_f()
{
	DumpOmnvars();
}

OmnvarDef* BG_Omnvar_GetDef(unsigned int index)
{
	auto BG_Omnvar_GetDef_func = reinterpret_cast<OmnvarDef * (*)(int index)>(0x140CD5830_g);
	return BG_Omnvar_GetDef_func(index);

	/*OmnvarDef* OmnvarDefs = (OmnvarDef*)(0x145C48580_g);
	return OmnvarDefs + index;*/
}