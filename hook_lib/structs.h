#pragma once
#include "Main.hpp"

#define ANGLE2SHORT(x) ((int)((x) * 65536 / 360) & 65535)

struct class_helper {
	uintptr_t at(int num) {
		return (uintptr_t)(this) + num;
	}

	template<typename T> T get(int num) {
		return *reinterpret_cast<T*>((uintptr_t)(this) + num);
	}

	template<typename T> void set(int num, T value) {
		*reinterpret_cast<T*>((uintptr_t)(this) + num) = value;
	}

	template<typename T> void inc(int num, T value) {
		*reinterpret_cast<T*>((uintptr_t)(this) + num) += value;
	}
};

struct CmdArgs
{
	int nesting;
	int localClientNum[8];
	int controllerIndex[8];
	int argc[8];
	const char** argv[8];
	char textPool[16384];
	const char* argvPool[512];
	int usedTextPool[8];
	int totalUsedArgvPool;
	int totalUsedTextPool;
};


struct Weapon
{
	unsigned __int16 weaponIdx;
	unsigned __int16 stickerIndices[4];
	unsigned __int16 weaponClientLoadout;
	unsigned __int16 weaponOthers;
	unsigned __int8 weaponAttachments[13];
	unsigned __int8 attachmentVariationIndices[29];
	unsigned __int8 weaponCamo;
	unsigned __int8 weaponLootId;
	unsigned __int8 scopeVariation;
	unsigned __int8 visualAttachmentHighAddr;
};

struct ScreenBlur
{
	int priority; //BlurPriority
	int time; //BlurTime
	int timeStart;
	int timeEnd;
	float start;
	float end;
	float radius;
};

struct netadr_t
{
	int type;
	unsigned __int8 ip[4];
	unsigned __int16 port;
	unsigned __int16 flags;
	int localNetID;
	int addrHandleIndex;
};

enum keyNum_t : int
{
	K_NONE = 0x0,
	K_BUTTON_A = 0x1,
	K_FIRST = 0x1,
	K_FIRSTGAMEPADBUTTON_RANGE_1 = 0x1,
	K_BUTTON_B = 0x2,
	K_BUTTON_X = 0x3,
	K_BUTTON_Y = 0x4,
	K_BUTTON_LSHLDR = 0x5,
	K_BUTTON_RSHLDR = 0x6,
	K_LASTGAMEPADBUTTON_RANGE_1 = 0x6,
	K_TAB = 0x9,
	K_ENTER = 0xD,
	K_BUTTON_START = 0xE,
	K_FIRSTGAMEPADBUTTON_RANGE_2 = 0xE,
	K_BUTTON_BACK = 0xF,
	K_BUTTON_LSTICK = 0x10,
	K_BUTTON_RSTICK = 0x11,
	K_BUTTON_LTRIG = 0x12,
	K_BUTTON_RTRIG = 0x13,
	K_DPAD_UP = 0x14,
	K_FIRSTDPAD = 0x14,
	K_DPAD_DOWN = 0x15,
	K_DPAD_LEFT = 0x16,
	K_DPAD_RIGHT = 0x17,
	K_LASTDPAD = 0x17,
	K_LASTGAMEPADBUTTON_RANGE_2 = 0x17,
	K_BUTTON_LSTICK_ALTIMAGE = 0x18,
	K_BUTTON_RSTICK_ALTIMAGE = 0x19,
	K_ESCAPE = 0x1B,
	K_APAD1_UP = 0x1C,
	K_FIRSTGAMEPADBUTTON_RANGE_3 = 0x1C,
	K_FIRSTAPAD = 0x1C,
	K_APAD1_DOWN = 0x1D,
	K_APAD1_LEFT = 0x1E,
	K_APAD1_RIGHT = 0x1F,
	K_LASTAPAD = 0x1F,
	K_LASTGAMEPADBUTTON_RANGE_3 = 0x1F,
	K_SPACE = 0x20,
	K_POUND = 0x23,
	K_APOSTROPHE = 0x27,
	K_COMMA = 0x2C,
	K_MINUS = 0x2D,
	K_PERIOD = 0x2E,
	K_SLASH = 0x2F,
	K_0 = 0x30,
	K_1 = 0x31,
	K_2 = 0x32,
	K_3 = 0x33,
	K_4 = 0x34,
	K_5 = 0x35,
	K_6 = 0x36,
	K_7 = 0x37,
	K_8 = 0x38,
	K_9 = 0x39,
	K_SEMICOLON = 0x3B,
	K_ISOB00 = 0x3C,
	K_EQUAL = 0x3D,
	K_LEFTBRACKET = 0x5B,
	K_BACKSLASH = 0x5C,
	K_RIGHTBRACKET = 0x5D,
	K_JIS_BACKSLASH = 0x5F,
	K_GRAVE = 0x60,
	K_A = 0x61,
	K_B = 0x62,
	K_C = 0x63,
	K_D = 0x64,
	K_E = 0x65,
	K_F = 0x66,
	K_G = 0x67,
	K_H = 0x68,
	K_I = 0x69,
	K_J = 0x6A,
	K_K = 0x6B,
	K_L = 0x6C,
	K_M = 0x6D,
	K_N = 0x6E,
	K_O = 0x6F,
	K_P = 0x70,
	K_Q = 0x71,
	K_R = 0x72,
	K_S = 0x73,
	K_T = 0x74,
	K_U = 0x75,
	K_V = 0x76,
	K_W = 0x77,
	K_X = 0x78,
	K_Y = 0x79,
	K_Z = 0x7A,
	K_JIS_YEN = 0x7C,
	K_BACKSPACE = 0x7F,
	K_CAPSLOCK = 0x80,
	K_PRINTSCREEN = 0x81,
	K_SCROLLLOCK = 0x82,
	K_PAUSE = 0x83,
	K_UPARROW = 0x84,
	K_DOWNARROW = 0x85,
	K_LEFTARROW = 0x86,
	K_RIGHTARROW = 0x87,
	K_LALT = 0x88,
	K_RALT = 0x89,
	K_LCTRL = 0x8A,
	K_RCTRL = 0x8B,
	K_LSHIFT = 0x8C,
	K_RSHIFT = 0x8D,
	K_LWIN = 0x8E,
	K_RWIN = 0x8F,
	K_MENU = 0x90,
	K_HIRAGANA = 0x91,
	K_HENKAN = 0x92,
	K_MUHENKAN = 0x93,
	K_INS = 0x94,
	K_DEL = 0x95,
	K_PGDN = 0x96,
	K_PGUP = 0x97,
	K_HOME = 0x98,
	K_END = 0x99,
	K_F1 = 0x9A,
	K_F2 = 0x9B,
	K_F3 = 0x9C,
	K_F4 = 0x9D,
	K_F5 = 0x9E,
	K_F6 = 0x9F,
	K_F7 = 0xA0,
	K_F8 = 0xA1,
	K_F9 = 0xA2,
	K_F10 = 0xA3,
	K_F11 = 0xA4,
	K_F12 = 0xA5,
	K_F13 = 0xA6,
	K_F14 = 0xA7,
	K_F15 = 0xA8,
	K_KP_HOME = 0xA9,
	K_KP_UPARROW = 0xAA,
	K_KP_PGUP = 0xAB,
	K_KP_LEFTARROW = 0xAC,
	K_KP_NUMPAD_5 = 0xAD,
	K_KP_RIGHTARROW = 0xAE,
	K_KP_END = 0xAF,
	K_KP_DOWNARROW = 0xB0,
	K_KP_PGDN = 0xB1,
	K_KP_ENTER = 0xB2,
	K_KP_INS = 0xB3,
	K_KP_DEL = 0xB4,
	K_KP_SLASH = 0xB5,
	K_KP_MINUS = 0xB6,
	K_KP_PLUS = 0xB7,
	K_KP_NUMLOCK = 0xB8,
	K_KP_STAR = 0xB9,
	K_KP_EQUALS = 0xBA,
	K_MOUSE1 = 0xBB,
	K_START_MOUSEBUTTON = 0xBB,
	K_START_MOUSE = 0xBB,
	K_MOUSE2 = 0xBC,
	K_MOUSE3 = 0xBD,
	K_MOUSE4 = 0xBE,
	K_MOUSE5 = 0xBF,
	K_LAST_MOUSEBUTTON = 0xBF,
	K_MWHEELDOWN = 0xC0,
	K_START_MOUSEWHEEL = 0xC0,
	K_MWHEELUP = 0xC1,
	K_MWHEELLEFT = 0xC2,
	K_MWHEELRIGHT = 0xC3,
	K_LAST_MOUSEWHEEL = 0xC3,
	K_LAST_MOUSE = 0xC3,
	K_BUTTON_BACK_LTRIG = 0xC4,
	K_BUTTON_BACK_LSHLDR = 0xC5,
	K_BUTTON_BACK_RTRIG = 0xC6,
	K_BUTTON_BACK_RSHLDR = 0xC7,
	K_BUTTON_BACK_A = 0xC8,
	K_BUTTON_BACK_B = 0xC9,
	K_BUTTON_BACK_X = 0xCA,
	K_BUTTON_BACK_Y = 0xCB,
	K_BUTTON_BACK_LSTICK = 0xCC,
	K_BUTTON_BACK_RSTICK = 0xCD,
	K_BUTTON_BACK_UP = 0xCE,
	K_BUTTON_BACK_DOWN = 0xCF,
	K_BUTTON_BACK_LEFT = 0xD0,
	K_BUTTON_BACK_RIGHT = 0xD1,
	K_BUTTON_VITA_L1 = 0xD2,
	K_BUTTON_VITA_R1 = 0xD3,
	K_BUTTON_VITA_L2 = 0xD4,
	K_BUTTON_VITA_R2 = 0xD5,
	K_BUTTON_VITA_L3 = 0xD6,
	K_BUTTON_VITA_R3 = 0xD7,
	K_BUTTON_VITA_TOUCHPAD = 0xD8,
	K_BUTTON_OPTIONS = 0xD9,
	K_APAD2_UP = 0xDA,
	K_FIRSTGAMEPADBUTTON_RANGE_4 = 0xDA,
	K_FIRSTBPAD = 0xDA,
	K_APAD2_DOWN = 0xDB,
	K_APAD2_LEFT = 0xDC,
	K_APAD2_RIGHT = 0xDD,
	K_LASTBPAD = 0xDD,
	K_LASTGAMEPADBUTTON_RANGE_4 = 0xDD,
	K_INHERIT = 0xDE,
	K_LAST_KEY = 0xDE,
};


struct MigrationPers
{
	bool stanceHeld;
	bool crouchToggle;
	bool crouchHoldReleased;
	int stance; //StanceState
	int stanceOnButtonDown; //StanceState
	int stanceTime;
	int cmdInputAccumTimeMs;
	Weapon cgameUserCmdWeapon;
	Weapon cgameUserCmdOffHand;
	int cgameUserCmdAlternate;
	Weapon weaponSelect;
	int weaponSelectInAlt;
	int weaponSelectTime;
	int weaponForcedSelectTime;
	Weapon weaponLatestPrimary;
	Weapon weaponPrevPrimary;
	int holdBreathTime;
	int holdBreathDelay;
	float holdBreathFrac;
	ScreenBlur blurPers;
};


struct __declspec(align(4)) clientUIActive_t
{
	bool active;
	bool isRunning;
	int keyCatchers;
	int connectionState; //connstate_t
	int nextScrollTime[2];
	int dpadNextTime;
	int dpadLatestKey;
	int holdKeyNextTime;
	int holdKeyLatest;
	unsigned char frontEndSceneState[1];
	bool cgameInitialized;
	bool cgameInitCalled;
	int lastInputType; //UIInputType
	int migrationState; //clientMigState_t
	MigrationPers migrationPers;
	int verboseMigrationState; //MigrationVerboseState
	int verboseMigrationNewHost;
	int verboseMigrationData;
	bool invited;
};

#pragma region //msg_t

struct msg_t
{
	int overflowed;
	int readOnly;
	unsigned __int8* data;
	unsigned __int8* splitData;
	int maxsize;
	int cursize;
	int splitSize;
	int readcount;
	int bit;
	int lastEntityRef;
	int targetLocalNetID;
	unsigned int compressionFlags;
};

unsigned __int64 MSG_ReadInt64(const msg_t* msg);
void MSG_WriteInt64(const msg_t* msg, const unsigned __int64 value);

#pragma endregion


#pragma region //XUID

struct XUID {
	unsigned __int64 m_id;
	void Deserialize(const msg_t * msg);
	void Serialize(const msg_t * msg);
	XUID* FromHexString(const char* xuidString);
	XUID* FromMsg(const msg_t* msg);
	XUID* FromString(const char* xuidString);
	XUID* FromUInt64(unsigned __int64 id);
	XUID* FromUniversalId(unsigned __int64 id);

	unsigned __int64 GetUniversalId();
	
	bool IsNull();
	bool IsValid();

	XUID* NullXUID();
	XUID* RandomXUID();

	const char* ToDevString();
	const char* ToHexString();
	const char* ToString();

	bool operator !=(const XUID * xuid);
	XUID* operator =(const XUID * xuid);
	bool operator ==(const XUID * xuid);

};

#pragma endregion


struct LightSample
{
	bool bValid;
	unsigned __int8 value;
};

struct UserCmdClientBits
{
	unsigned int data[7];
};

struct usercmd_s
{
	unsigned __int64 buttons;
	int stateFlags;
	int serverTime;
	int commandTime;
	int inputTime;
	int angles[3];
	Weapon weapon;
	Weapon offHand;
	char forwardmove;
	char rightmove;
	char pitchmove;
	char yawmove;
	unsigned __int16 meleeChargeEnt;
	unsigned __int8 packedControllerAim;
	char selectedLoc[2];
	char selectedAngle;
	char remoteControlAngles[2];
	char remoteControlMove[3];
	char mlgSelectedLoc[2];
	char mlgSelectedAngle;
	LightSample lightSample;
	__int16 avoidForward;
	__int16 avoidRight;
	unsigned __int8 upmove;
	unsigned __int8 downmove;
	bool inputFromGamepad;
	bool isAlternate;
	__int16 vehAngles[3];
	float vehOrgX;
	float vehOrgY;
	float vehOrgZ;
	float gunPitch;
	float gunYaw;
	float gunXOfs;
	float gunYOfs;
	float gunZOfs;
	float rollSensitivity;
	__int16 scriptedMeleeTarget;
	unsigned __int16 airburstMarkDistance;
	UserCmdClientBits sightedClientsMask;
	unsigned __int16 extrapolationMax;
	unsigned __int16 interpolationMax;
};


struct HeldStanceInputStack
{
	int heldStances[2];
	int stackIndex;
};

struct TurnRateCapInfo
{
	float maxPitchSpeed;
	float maxYawSpeed;
};

struct ClInputSequenceState
{
	int nextCommand;
	int prevTimeMs;
};

struct ClInputSequenceVirtualAxisKeyState
{
	float value;
	int downtime;
};

struct SecureCLViewangles
{
	float clViewangles[3];
};



enum DDLType : unsigned int
{
	DDL_INVALID_TYPE = 0xFFFFFFFF,
	DDL_BYTE_TYPE = 0x0,
	DDL_SHORT_TYPE = 0x1,
	DDL_UINT_TYPE = 0x2,
	DDL_INT_TYPE = 0x3,
	DDL_UINT64_TYPE = 0x4,
	DDL_HASH_TYPE = 0x5,
	DDL_FLOAT_TYPE = 0x6,
	DDL_FIXEDPOINT_TYPE = 0x7,
	DDL_STRING_TYPE = 0x8,
	DDL_STRUCT_TYPE = 0x9,
	DDL_ENUM_TYPE = 0xA,
	DDL_PAD_TYPE = 0xB,
};

struct DDLMember
{
	const char* name;
	int unkttt[2];
	const char* unkstr;
	int bitSize;
	int limitSize;
	int unkthing1;
	int type;
	int externalIndex;
	int rangeLimit;
	int unkthing;
	int arraySize;
	int enumIndex;
	int enumIndex1;
};


struct DDLHash
{
	unsigned int hash;
	int index;
};

struct DDLHashTable
{
	DDLHash* list;
	int count;
	int max;
};

struct DDLStruct
{
	const char* name;
	int bitSize;
	int memberCount;
	DDLMember* members;
	DDLHashTable hashTableUpper;
	DDLHashTable hashTableLower;
};

__inline const char* get_ddl_type(int type) {
	switch (type)
	{
	case DDL_INVALID_TYPE: return "invalid"; break;
	case DDL_BYTE_TYPE: return "byte"; break;
	case DDL_SHORT_TYPE: return "short"; break;
	case DDL_UINT_TYPE: return "uint32_t"; break;
	case DDL_INT_TYPE: return "int"; break;
	case DDL_UINT64_TYPE: return "uint64_t"; break;
	case DDL_HASH_TYPE: return "hash"; break;
	case DDL_FLOAT_TYPE: return "float"; break;
	case DDL_FIXEDPOINT_TYPE: return "fixedpoint"; break;
	case DDL_STRING_TYPE: return "const char*"; break;
	case DDL_STRUCT_TYPE: return "struct"; break;
	case DDL_ENUM_TYPE: return "enum"; break;
	case DDL_PAD_TYPE: return "pad"; break;
		default: return "unk"; break;
	}
}

struct DDLEnum
{
	const char* name;
	int memberCount;
	const char** members;
	DDLHashTable hashTable;
};

struct __declspec(align(8)) DDLDef
{
	char* name;
	unsigned __int16 version;
	unsigned __int64 guidSeed;
	unsigned __int64 guid;
	int bitSize;
	int byteSize;
	DDLStruct* structList;
	int structCount;
	DDLEnum* enumList;
	int enumCount;
	DDLDef* next;
	int headerBitSize;
	int headerByteSize;
	bool paddingUsed;
	bool minimalHeader;
};

struct DDLState
{
	bool isValid;
	int offset;
	int arrayIndex;
	DDLMember* member;
	const DDLDef* ddlDef;
};

struct DDLContext
{
	void* buff;
	int len;
	const DDLDef* def;
	void(__fastcall* accessCB)(const DDLContext*, unsigned int, unsigned int, int);
	void* userData;
	bool obfuscated;
	unsigned int randomInt;
};


struct __declspec(align(8)) ClActiveClient
{
	void* __vftable;
	bool usingAds;
	bool holdingBreath;
	bool wasHoldingBreath;
	bool isRemoteControlling;
	bool autoForward;
	int mouseDx[2];
	int mouseDy[2];
	float weightedDx[8];
	float weightedDy[8];
	int mouseWheelDelta;
	float mouseWheelDeltaSustainTime;
	int mouseIndex;
	bool stanceHeld;
	bool crouchToggle;
	bool crouchHoldPressed;
	bool crouchHoldReleased;
	bool ignoreStanceInput;
	bool wasSprinting;
	bool requireSlideRelease;
	bool standToProne;
	HeldStanceInputStack heldInputs;
	bool weaponForwardHoldStartedInAds;
	int stance;
	int stanceOnButtonDown;
	int stanceTime;
	Weapon cgameUserCmdWeapon;
	Weapon cgameUserCmdOffHand;
	int cgameUserCmdAlternate;
	float cgameFOVSensitivityScale;
	unsigned __int64 cgameExtraButtons;
	int cgameMountRegisterTime;
	int cgameUserCmdStateFlags;
	TurnRateCapInfo turnRateCapInfos[5];
	ClInputSequenceState cmdSequenceState[7];
	ClInputSequenceVirtualAxisKeyState cmdSequenceAxisKeys[5];
	bool isDoubleAdsMountHeld;
	bool triggerSuperSprint;
	bool detonateOffhandPrimary;
	bool detonateOffhandSecondary;
	SecureCLViewangles clViewangles;
	int cmdInputAccumTimeMs;
	float mouseViewDelta[3];
	float accumulatedMouseDelta[2];
	int accumulatedInputTimer;
	usercmd_s cmds[128];
	int cmdNumber;


	template<typename T> T get(int num) {
		return *reinterpret_cast<T*>((uintptr_t)(this) + num);
	}

	template<typename T> T set(int num, T value) {
		*reinterpret_cast<T*>((uintptr_t)(this) + num) = value;
	}
};

struct gentity_s : class_helper {
	__int16 s_number;
	unsigned __int8 field_2;
	unsigned __int8 field_3;
	unsigned __int8 field_4;
	unsigned __int8 field_5;
	unsigned __int8 field_6;
	unsigned __int8 field_7;
	unsigned __int8 field_8;
	unsigned __int8 field_9;
	unsigned __int8 field_A;
	unsigned __int8 field_B;
	unsigned __int8 field_C;
	unsigned __int8 field_D;
	unsigned __int8 field_E;
	unsigned __int8 field_F;
	unsigned __int8 field_10;
	unsigned __int8 field_11;
	unsigned __int8 field_12;
	unsigned __int8 field_13;
	unsigned __int8 field_14;
	unsigned __int8 field_15;
	unsigned __int8 field_16;
	unsigned __int8 field_17;
	unsigned __int8 field_18;
	unsigned __int8 field_19;
	unsigned __int8 field_1A;
	unsigned __int8 field_1B;
	unsigned __int8 field_1C;
	unsigned __int8 field_1D;
	unsigned __int8 field_1E;
	unsigned __int8 field_1F;
	unsigned __int8 field_20;
	unsigned __int8 field_21;
	unsigned __int8 field_22;
	unsigned __int8 field_23;
	unsigned __int8 field_24;
	unsigned __int8 field_25;
	unsigned __int8 field_26;
	unsigned __int8 field_27;
	unsigned __int8 field_28;
	unsigned __int8 field_29;
	unsigned __int8 field_2A;
	unsigned __int8 field_2B;
	unsigned __int8 field_2C;
	unsigned __int8 field_2D;
	unsigned __int8 field_2E;
	unsigned __int8 field_2F;
	unsigned __int8 field_30;
	unsigned __int8 field_31;
	unsigned __int8 field_32;
	unsigned __int8 field_33;
	unsigned __int8 field_34;
	unsigned __int8 field_35;
	unsigned __int8 field_36;
	unsigned __int8 field_37;
	unsigned __int8 field_38;
	unsigned __int8 field_39;
	unsigned __int8 field_3A;
	unsigned __int8 field_3B;
	unsigned __int8 field_3C;
	unsigned __int8 field_3D;
	unsigned __int8 field_3E;
	unsigned __int8 field_3F;
	unsigned __int8 field_40;
	unsigned __int8 field_41;
	unsigned __int8 field_42;
	unsigned __int8 field_43;
	unsigned __int8 field_44;
	unsigned __int8 field_45;
	unsigned __int8 field_46;
	unsigned __int8 field_47;
	unsigned __int8 field_48;
	unsigned __int8 field_49;
	unsigned __int8 field_4A;
	unsigned __int8 field_4B;
	unsigned __int8 field_4C;
	unsigned __int8 field_4D;
	unsigned __int8 field_4E;
	unsigned __int8 field_4F;
	unsigned __int8 field_50;
	unsigned __int8 field_51;
	unsigned __int8 field_52;
	unsigned __int8 field_53;
	unsigned __int8 field_54;
	unsigned __int8 field_55;
	unsigned __int8 field_56;
	unsigned __int8 field_57;
	unsigned __int8 field_58;
	unsigned __int8 field_59;
	unsigned __int8 field_5A;
	unsigned __int8 field_5B;
	unsigned __int8 field_5C;
	unsigned __int8 field_5D;
	unsigned __int8 field_5E;
	unsigned __int8 field_5F;
	unsigned __int8 field_60;
	unsigned __int8 field_61;
	unsigned __int8 field_62;
	unsigned __int8 field_63;
	unsigned __int8 field_64;
	unsigned __int8 field_65;
	unsigned __int8 field_66;
	unsigned __int8 field_67;
	unsigned __int8 field_68;
	unsigned __int8 field_69;
	unsigned __int8 field_6A;
	unsigned __int8 field_6B;
	unsigned __int8 field_6C;
	unsigned __int8 field_6D;
	unsigned __int8 field_6E;
	unsigned __int8 field_6F;
	unsigned __int8 field_70;
	unsigned __int8 field_71;
	unsigned __int8 field_72;
	unsigned __int8 field_73;
	unsigned __int8 field_74;
	unsigned __int8 field_75;
	unsigned __int8 field_76;
	unsigned __int8 field_77;
	unsigned __int8 field_78;
	unsigned __int8 field_79;
	unsigned __int8 field_7A;
	unsigned __int8 field_7B;
	unsigned __int8 field_7C;
	unsigned __int8 field_7D;
	unsigned __int8 field_7E;
	unsigned __int8 field_7F;
	unsigned __int8 field_80;
	unsigned __int8 field_81;
	unsigned __int8 field_82;
	unsigned __int8 field_83;
	unsigned __int8 field_84;
	unsigned __int8 field_85;
	unsigned __int8 field_86;
	unsigned __int8 field_87;
	unsigned __int8 field_88;
	unsigned __int8 field_89;
	unsigned __int8 field_8A;
	unsigned __int8 field_8B;
	unsigned __int8 field_8C;
	unsigned __int8 field_8D;
	unsigned __int8 field_8E;
	unsigned __int8 field_8F;
	__int16 s_clientNum;
	unsigned __int8 field_92;
	unsigned __int8 field_93;
	unsigned __int8 field_94;
	unsigned __int8 field_95;
	unsigned __int8 field_96;
	unsigned __int8 field_97;
	unsigned __int8 field_98;
	unsigned __int8 field_99;
	unsigned __int8 field_9A;
	unsigned __int8 field_9B;
	unsigned __int8 field_9C;
	unsigned __int8 field_9D;
	unsigned __int8 field_9E;
	unsigned __int8 field_9F;
	unsigned __int8 field_A0;
	unsigned __int8 field_A1;
	unsigned __int8 field_A2;
	unsigned __int8 field_A3;
	unsigned __int8 field_A4;
	unsigned __int8 field_A5;
	unsigned __int8 field_A6;
	unsigned __int8 field_A7;
	unsigned __int8 field_A8;
	unsigned __int8 field_A9;
	unsigned __int8 field_AA;
	unsigned __int8 field_AB;
	unsigned __int8 field_AC;
	unsigned __int8 field_AD;
	unsigned __int8 field_AE;
	unsigned __int8 field_AF;
	unsigned __int8 field_B0;
	unsigned __int8 field_B1;
	unsigned __int8 field_B2;
	unsigned __int8 field_B3;
	unsigned __int8 field_B4;
	unsigned __int8 field_B5;
	unsigned __int8 field_B6;
	unsigned __int8 field_B7;
	unsigned __int8 field_B8;
	unsigned __int8 field_B9;
	unsigned __int8 field_BA;
	unsigned __int8 field_BB;
	unsigned __int8 field_BC;
	unsigned __int8 field_BD;
	unsigned __int8 field_BE;
	unsigned __int8 field_BF;
	unsigned __int8 field_C0;
	unsigned __int8 field_C1;
	unsigned __int8 field_C2;
	unsigned __int8 field_C3;
	unsigned __int8 field_C4;
	unsigned __int8 field_C5;
	unsigned __int8 field_C6;
	unsigned __int8 field_C7;
	unsigned __int8 field_C8;
	unsigned __int8 field_C9;
	unsigned __int8 field_CA;
	unsigned __int8 field_CB;
	unsigned __int8 field_CC;
	unsigned __int8 field_CD;
	unsigned __int8 field_CE;
	unsigned __int8 field_CF;
	unsigned __int8 field_D0;
	unsigned __int8 field_D1;
	unsigned __int8 field_D2;
	unsigned __int8 field_D3;
	unsigned __int8 field_D4;
	unsigned __int8 field_D5;
	unsigned __int8 field_D6;
	unsigned __int8 field_D7;
	unsigned __int8 field_D8;
	unsigned __int8 field_D9;
	unsigned __int8 field_DA;
	unsigned __int8 field_DB;
	unsigned __int8 field_DC;
	unsigned __int8 field_DD;
	unsigned __int8 field_DE;
	unsigned __int8 field_DF;
	unsigned __int8 field_E0;
	unsigned __int8 field_E1;
	unsigned __int8 field_E2;
	unsigned __int8 field_E3;
	unsigned __int8 field_E4;
	unsigned __int8 field_E5;
	unsigned __int8 field_E6;
	unsigned __int8 field_E7;
	unsigned __int8 field_E8;
	unsigned __int8 field_E9;
	unsigned __int8 field_EA;
	unsigned __int8 field_EB;
	unsigned __int8 field_EC;
	unsigned __int8 field_ED;
	unsigned __int8 field_EE;
	unsigned __int8 field_EF;
	unsigned __int8 field_F0;
	unsigned __int8 field_F1;
	unsigned __int8 field_F2;
	unsigned __int8 field_F3;
	unsigned __int8 field_F4;
	unsigned __int8 field_F5;
	unsigned __int8 field_F6;
	unsigned __int8 field_F7;
	unsigned __int8 field_F8;
	unsigned __int8 field_F9;
	unsigned __int8 field_FA;
	unsigned __int8 field_FB;
	unsigned __int8 r_isInUse;
	unsigned __int8 field_FD;
	unsigned __int8 field_FE;
	unsigned __int8 field_FF;
	unsigned __int8 field_100;
	unsigned __int8 field_101;
	unsigned __int8 field_102;
	unsigned __int8 field_103;
	unsigned __int8 field_104;
	unsigned __int8 field_105;
	unsigned __int8 field_106;
	unsigned __int8 field_107;
	unsigned __int8 field_108;
	unsigned __int8 field_109;
	unsigned __int8 field_10A;
	unsigned __int8 field_10B;
	unsigned __int8 field_10C;
	unsigned __int8 field_10D;
	unsigned __int8 field_10E;
	unsigned __int8 field_10F;
	unsigned __int8 field_110;
	unsigned __int8 field_111;
	unsigned __int8 field_112;
	unsigned __int8 field_113;
	unsigned __int8 field_114;
	unsigned __int8 field_115;
	unsigned __int8 field_116;
	unsigned __int8 field_117;
	unsigned __int8 field_118;
	unsigned __int8 field_119;
	unsigned __int8 field_11A;
	unsigned __int8 field_11B;
	unsigned __int8 field_11C;
	unsigned __int8 field_11D;
	unsigned __int8 field_11E;
	unsigned __int8 field_11F;
	unsigned __int8 field_120;
	unsigned __int8 field_121;
	unsigned __int8 field_122;
	unsigned __int8 field_123;
	unsigned __int8 field_124;
	unsigned __int8 field_125;
	unsigned __int8 field_126;
	unsigned __int8 field_127;
	unsigned __int8 field_128;
	unsigned __int8 field_129;
	unsigned __int8 field_12A;
	unsigned __int8 field_12B;
	unsigned __int8 field_12C;
	unsigned __int8 field_12D;
	unsigned __int8 field_12E;
	unsigned __int8 field_12F;
	float r_currentOrigin[3];
	float r_currentAngles[3];
	unsigned __int8 field_148;
	unsigned __int8 field_149;
	unsigned __int8 field_14A;
	unsigned __int8 field_14B;
	unsigned __int8 field_14C;
	unsigned __int8 field_14D;
	unsigned __int8 field_14E;
	unsigned __int8 field_14F;
	uintptr_t client;
	unsigned __int8 field_158;
	unsigned __int8 field_159;
	unsigned __int8 field_15A;
	unsigned __int8 field_15B;
	unsigned __int8 field_15C;
	unsigned __int8 field_15D;
	unsigned __int8 field_15E;
	unsigned __int8 field_15F;
	unsigned __int8 field_160;
	unsigned __int8 field_161;
	unsigned __int8 field_162;
	unsigned __int8 field_163;
	unsigned __int8 field_164;
	unsigned __int8 field_165;
	unsigned __int8 field_166;
	unsigned __int8 field_167;
	uintptr_t agent;
	unsigned __int8 field_170;
	unsigned __int8 field_171;
	unsigned __int8 field_172;
	unsigned __int8 field_173;
	unsigned __int8 field_174;
	unsigned __int8 field_175;
	unsigned __int8 field_176;
	unsigned __int8 field_177;
	int turrentHandlem_objIndex;
	int classname;
	int script_classname;
	unsigned __int8 field_184;
	unsigned __int8 field_185;
	unsigned __int8 field_186;
	unsigned __int8 field_187;
	unsigned __int8 field_188;
	unsigned __int8 field_189;
	unsigned __int8 field_18A;
	unsigned __int8 field_18B;
	unsigned __int8 field_18C;
	unsigned __int8 field_18D;
	unsigned __int8 field_18E;
	unsigned __int8 field_18F;
	unsigned __int8 field_190;
	unsigned __int8 field_191;
	unsigned __int8 field_192;
	unsigned __int8 field_193;
	unsigned __int8 field_194;
	unsigned __int8 field_195;
	unsigned __int8 field_196;
	unsigned __int8 field_197;
	unsigned __int8 field_198;
	unsigned __int8 field_199;
	unsigned __int8 field_19A;
	unsigned __int8 field_19B;
	int spawnflags;
	unsigned int m_flags[2];
	unsigned __int8 field_1A8;
	unsigned __int8 field_1A9;
	unsigned __int8 field_1AA;
	unsigned __int8 field_1AB;
	unsigned __int8 field_1AC;
	unsigned __int8 field_1AD;
	unsigned __int8 field_1AE;
	unsigned __int8 field_1AF;
	unsigned __int8 field_1B0;
	unsigned __int8 field_1B1;
	unsigned __int8 field_1B2;
	unsigned __int8 field_1B3;
	unsigned __int8 field_1B4;
	unsigned __int8 field_1B5;
	unsigned __int8 field_1B6;
	unsigned __int8 field_1B7;
	int field_1B8;
	unsigned __int8 field_1BC;
	unsigned __int8 field_1BD;
	unsigned __int8 field_1BE;
	unsigned __int8 field_1BF;
	unsigned __int8 field_1C0;
	unsigned __int8 field_1C1;
	unsigned __int8 field_1C2;
	unsigned __int8 field_1C3;
	unsigned __int8 field_1C4;
	unsigned __int8 field_1C5;
	unsigned __int8 field_1C6;
	unsigned __int8 field_1C7;
	unsigned __int8 field_1C8;
	unsigned __int8 field_1C9;
	unsigned __int8 field_1CA;
	unsigned __int8 field_1CB;
	unsigned __int8 field_1CC;
	unsigned __int8 field_1CD;
	unsigned __int8 field_1CE;
	unsigned __int8 field_1CF;
	unsigned __int8 field_1D0;
	unsigned __int8 field_1D1;
	unsigned __int8 field_1D2;
	unsigned __int8 field_1D3;
	unsigned __int8 field_1D4;
	unsigned __int8 field_1D5;
	unsigned __int8 field_1D6;
	unsigned __int8 field_1D7;
	unsigned __int8 field_1D8;
	unsigned __int8 field_1D9;
	unsigned __int8 field_1DA;
	unsigned __int8 field_1DB;
	unsigned __int8 field_1DC;
	unsigned __int8 field_1DD;
	unsigned __int8 field_1DE;
	unsigned __int8 field_1DF;
	unsigned __int8 field_1E0;
	unsigned __int8 field_1E1;
	unsigned __int8 field_1E2;
	unsigned __int8 field_1E3;
	unsigned __int8 field_1E4;
	unsigned __int8 field_1E5;
	unsigned __int8 field_1E6;
	unsigned __int8 field_1E7;
	unsigned __int8 field_1E8;
	unsigned __int8 field_1E9;
	unsigned __int8 field_1EA;
	unsigned __int8 field_1EB;
	unsigned __int8 field_1EC;
	unsigned __int8 field_1ED;
	unsigned __int8 field_1EE;
	unsigned __int8 field_1EF;
	unsigned __int8 field_1F0;
	unsigned __int8 field_1F1;
	unsigned __int8 field_1F2;
	unsigned __int8 field_1F3;
	unsigned __int8 field_1F4;
	unsigned __int8 field_1F5;
	unsigned __int8 field_1F6;
	unsigned __int8 field_1F7;
	unsigned __int8 field_1F8;
	unsigned __int8 field_1F9;
	unsigned __int8 field_1FA;
	unsigned __int8 field_1FB;
	unsigned __int8 field_1FC;
	unsigned __int8 field_1FD;
	unsigned __int8 field_1FE;
	unsigned __int8 field_1FF;
	unsigned __int8 field_200;
	unsigned __int8 field_201;
	unsigned __int8 field_202;
	unsigned __int8 field_203;
	unsigned __int8 field_204;
	unsigned __int8 field_205;
	unsigned __int8 field_206;
	unsigned __int8 field_207;
	unsigned __int8 field_208;
	unsigned __int8 field_209;
	unsigned __int8 field_20A;
	unsigned __int8 field_20B;
	unsigned __int8 field_20C;
	unsigned __int8 field_20D;
	unsigned __int8 field_20E;
	unsigned __int8 field_20F;
	unsigned __int8 field_210;
	unsigned __int8 field_211;
	unsigned __int8 field_212;
	unsigned __int8 field_213;
	unsigned __int8 field_214;
	unsigned __int8 field_215;
	unsigned __int8 field_216;
	unsigned __int8 field_217;
	unsigned __int8 field_218;
	unsigned __int8 field_219;
	unsigned __int8 field_21A;
	unsigned __int8 field_21B;
	unsigned __int8 field_21C;
	unsigned __int8 field_21D;
	unsigned __int8 field_21E;
	unsigned __int8 field_21F;
	unsigned __int8 field_220;
	unsigned __int8 field_221;
	unsigned __int8 field_222;
	unsigned __int8 field_223;
	unsigned __int8 field_224;
	unsigned __int8 field_225;
	unsigned __int8 field_226;
	unsigned __int8 field_227;
	unsigned __int8 field_228;
	unsigned __int8 field_229;
	unsigned __int8 field_22A;
	unsigned __int8 field_22B;
	unsigned __int8 field_22C;
	unsigned __int8 field_22D;
	unsigned __int8 field_22E;
	unsigned __int8 field_22F;
	unsigned __int8 field_230;
	unsigned __int8 field_231;
	unsigned __int8 field_232;
	unsigned __int8 field_233;
	unsigned __int8 field_234;
	unsigned __int8 field_235;
	unsigned __int8 field_236;
	unsigned __int8 field_237;
	unsigned __int8 field_238;
	unsigned __int8 field_239;
	unsigned __int8 field_23A;
	unsigned __int8 field_23B;
	unsigned __int8 field_23C;
	unsigned __int8 field_23D;
	unsigned __int8 field_23E;
	unsigned __int8 field_23F;
	unsigned __int8 field_240;
	unsigned __int8 field_241;
	unsigned __int8 field_242;
	unsigned __int8 field_243;
	unsigned __int8 field_244;
	unsigned __int8 field_245;
	unsigned __int8 field_246;
	unsigned __int8 field_247;
	unsigned __int8 field_248;
	unsigned __int8 field_249;
	unsigned __int8 field_24A;
	unsigned __int8 field_24B;
	unsigned __int8 field_24C;
	unsigned __int8 field_24D;
	unsigned __int8 field_24E;
	unsigned __int8 field_24F;
	unsigned __int8 field_250;
	unsigned __int8 field_251;
	unsigned __int8 field_252;
	unsigned __int8 field_253;
	unsigned __int8 field_254;
	unsigned __int8 field_255;
	unsigned __int8 field_256;
	unsigned __int8 field_257;
	unsigned __int8 field_258;
	unsigned __int8 field_259;
	unsigned __int8 field_25A;
	unsigned __int8 field_25B;
	unsigned __int8 field_25C;
	unsigned __int8 field_25D;
	unsigned __int8 field_25E;
	unsigned __int8 field_25F;
	unsigned __int8 field_260;
	unsigned __int8 field_261;
	unsigned __int8 field_262;
	unsigned __int8 field_263;
	unsigned __int8 field_264;
	unsigned __int8 field_265;
	unsigned __int8 field_266;
	unsigned __int8 field_267;
	unsigned __int8 field_268;
	unsigned __int8 field_269;
	unsigned __int8 field_26A;
	unsigned __int8 field_26B;
	unsigned __int8 field_26C;
	unsigned __int8 field_26D;
	unsigned __int8 field_26E;
	unsigned __int8 field_26F;
	unsigned __int8 field_270;
	unsigned __int8 field_271;
	unsigned __int8 field_272;
	unsigned __int8 field_273;
	unsigned __int8 field_274;
	unsigned __int8 field_275;
	unsigned __int8 field_276;
	unsigned __int8 field_277;
	unsigned __int8 field_278;
	unsigned __int8 field_279;
	unsigned __int8 field_27A;
	unsigned __int8 field_27B;
	unsigned __int8 field_27C;
	unsigned __int8 field_27D;
	unsigned __int8 field_27E;
	unsigned __int8 field_27F;
	unsigned __int8 field_280;
	unsigned __int8 field_281;
	unsigned __int8 field_282;
	unsigned __int8 field_283;
	unsigned __int8 field_284;
	unsigned __int8 field_285;
	unsigned __int8 field_286;
	unsigned __int8 field_287;
	unsigned __int8 field_288;
	unsigned __int8 field_289;
	unsigned __int8 field_28A;
	unsigned __int8 field_28B;
	unsigned __int8 field_28C;
	unsigned __int8 field_28D;
	unsigned __int8 field_28E;
	unsigned __int8 field_28F;
	unsigned __int8 field_290;
	unsigned __int8 field_291;
	unsigned __int8 field_292;
	unsigned __int8 field_293;
	unsigned __int8 field_294;
	unsigned __int8 field_295;
	unsigned __int8 field_296;
	unsigned __int8 field_297;
	unsigned __int8 field_298;
	unsigned __int8 field_299;
	unsigned __int8 field_29A;
	unsigned __int8 field_29B;
	unsigned __int8 field_29C;
	unsigned __int8 field_29D;
	unsigned __int8 field_29E;
	unsigned __int8 field_29F;
	unsigned __int8 field_2A0;
	unsigned __int8 field_2A1;
	unsigned __int8 field_2A2;
	unsigned __int8 field_2A3;
	unsigned __int8 field_2A4;
	unsigned __int8 field_2A5;
	unsigned __int8 field_2A6;
	unsigned __int8 field_2A7;
	unsigned __int8 field_2A8;
	unsigned __int8 field_2A9;
	unsigned __int8 field_2AA;
	unsigned __int8 field_2AB;
	unsigned __int8 field_2AC;
	unsigned __int8 field_2AD;
	unsigned __int8 field_2AE;
	unsigned __int8 field_2AF;
	unsigned __int8 field_2B0;
	unsigned __int8 field_2B1;
	unsigned __int8 field_2B2;
	unsigned __int8 field_2B3;
	unsigned __int8 field_2B4;
	unsigned __int8 field_2B5;
	unsigned __int8 field_2B6;
	unsigned __int8 field_2B7;
	unsigned __int8 field_2B8;
	unsigned __int8 field_2B9;
	unsigned __int8 field_2BA;
	unsigned __int8 field_2BB;
	unsigned __int8 field_2BC;
	unsigned __int8 field_2BD;
	unsigned __int8 field_2BE;
	unsigned __int8 field_2BF;
	uintptr_t tagInfo;
	unsigned __int8 field_2C8;
	unsigned __int8 field_2C9;
	unsigned __int8 field_2CA;
	unsigned __int8 field_2CB;
	unsigned __int8 field_2CC;
	unsigned __int8 field_2CD;
	unsigned __int8 field_2CE;
	unsigned __int8 field_2CF;
	unsigned __int8 field_2D0;
	unsigned __int8 field_2D1;
	unsigned __int8 field_2D2;
	unsigned __int8 field_2D3;
	unsigned __int8 field_2D4;
	unsigned __int8 field_2D5;
	unsigned __int8 field_2D6;
	unsigned __int8 field_2D7;
	unsigned __int8 field_2D8;
	unsigned __int8 field_2D9;
	unsigned __int8 field_2DA;
	unsigned __int8 field_2DB;
	unsigned __int8 field_2DC;
	unsigned __int8 field_2DD;
	unsigned __int8 field_2DE;
	unsigned __int8 field_2DF;
	unsigned __int8 field_2E0;
	unsigned __int8 field_2E1;
	unsigned __int8 field_2E2;
	unsigned __int8 field_2E3;
	unsigned __int8 field_2E4;
	unsigned __int8 field_2E5;
	unsigned __int8 field_2E6;
	unsigned __int8 field_2E7;
	unsigned __int8 field_2E8;
	unsigned __int8 field_2E9;
	unsigned __int8 field_2EA;
	unsigned __int8 field_2EB;
	unsigned __int8 field_2EC;
	unsigned __int8 field_2ED;
	unsigned __int8 field_2EE;
	unsigned __int8 field_2EF;
	unsigned __int8 field_2F0;
	unsigned __int8 field_2F1;
	unsigned __int8 field_2F2;
	unsigned __int8 field_2F3;
	unsigned __int8 field_2F4;
	unsigned __int8 field_2F5;
	unsigned __int8 field_2F6;
	unsigned __int8 field_2F7;
	unsigned __int8 field_2F8;
	unsigned __int8 field_2F9;
	unsigned __int8 field_2FA;
	unsigned __int8 field_2FB;
	unsigned __int8 field_2FC;
	unsigned __int8 field_2FD;
	unsigned __int8 field_2FE;
	unsigned __int8 field_2FF;
	unsigned __int8 field_300;
	unsigned __int8 field_301;
	unsigned __int8 field_302;
	unsigned __int8 field_303;
	unsigned __int8 field_304;
	unsigned __int8 field_305;
	unsigned __int8 field_306;
	unsigned __int8 field_307;
	unsigned __int8 field_308;
	unsigned __int8 field_309;
	unsigned __int8 field_30A;
	unsigned __int8 field_30B;
	unsigned __int8 field_30C;
	unsigned __int8 field_30D;
	unsigned __int8 field_30E;
	unsigned __int8 field_30F;
	unsigned __int8 field_310;
	unsigned __int8 field_311;
	unsigned __int8 field_312;
	unsigned __int8 field_313;
	unsigned __int8 field_314;
	unsigned __int8 field_315;
	unsigned __int8 field_316;
	unsigned __int8 field_317;
	unsigned __int8 field_318;
	unsigned __int8 field_319;
	unsigned __int8 field_31A;
	unsigned __int8 field_31B;
	unsigned __int8 field_31C;
	unsigned __int8 field_31D;
	unsigned __int8 field_31E;
	unsigned __int8 field_31F;
	unsigned __int8 field_320;
	unsigned __int8 field_321;
	unsigned __int8 field_322;
	unsigned __int8 field_323;
	unsigned __int8 field_324;
	unsigned __int8 field_325;
	unsigned __int8 field_326;
	unsigned __int8 field_327;
	unsigned __int8 field_328;
	unsigned __int8 field_329;
	unsigned __int8 field_32A;
	unsigned __int8 field_32B;
	unsigned __int8 field_32C;
	unsigned __int8 field_32D;
	unsigned __int8 field_32E;
	unsigned __int8 field_32F;
	unsigned __int8 field_330;
	unsigned __int8 field_331;
	unsigned __int8 field_332;
	unsigned __int8 field_333;
	unsigned __int8 field_334;
	unsigned __int8 field_335;
	unsigned __int8 field_336;
	unsigned __int8 field_337;
	unsigned __int8 field_338;
	unsigned __int8 field_339;
	unsigned __int8 field_33A;
	unsigned __int8 field_33B;
	unsigned __int8 field_33C;
	unsigned __int8 field_33D;
	unsigned __int8 field_33E;
	unsigned __int8 field_33F;
	unsigned __int8 field_340;
	unsigned __int8 field_341;
	unsigned __int8 field_342;
	unsigned __int8 field_343;
	unsigned __int8 field_344;
	unsigned __int8 field_345;
	unsigned __int8 field_346;
	unsigned __int8 field_347;
	unsigned __int8 field_348;
	unsigned __int8 field_349;
	unsigned __int8 field_34A;
	unsigned __int8 field_34B;
	unsigned __int8 field_34C;
	unsigned __int8 field_34D;
	unsigned __int8 field_34E;
	unsigned __int8 field_34F;
	unsigned __int8 field_350;
	unsigned __int8 field_351;
	unsigned __int8 field_352;
	unsigned __int8 field_353;
	unsigned __int8 field_354;
	unsigned __int8 field_355;
	unsigned __int8 field_356;
	unsigned __int8 field_357;
	unsigned __int8 field_358;
	unsigned __int8 field_359;
	unsigned __int8 field_35A;
	unsigned __int8 field_35B;
	unsigned __int8 field_35C;
	unsigned __int8 field_35D;
	unsigned __int8 field_35E;
	unsigned __int8 field_35F;
	unsigned __int8 field_360;
	unsigned __int8 field_361;
	unsigned __int8 field_362;
	unsigned __int8 field_363;
	unsigned __int8 field_364;
	unsigned __int8 field_365;
	unsigned __int8 field_366;
	unsigned __int8 field_367;
	unsigned __int8 field_368;
	unsigned __int8 field_369;
	unsigned __int8 field_36A;
	unsigned __int8 field_36B;
	unsigned __int8 field_36C;
	unsigned __int8 field_36D;
	unsigned __int8 field_36E;
	unsigned __int8 field_36F;
	unsigned __int8 field_370;
	unsigned __int8 field_371;
	unsigned __int8 field_372;
	unsigned __int8 field_373;
	unsigned __int8 field_374;
	unsigned __int8 field_375;
	unsigned __int8 field_376;
	unsigned __int8 field_377;
	unsigned __int8 field_378;
	unsigned __int8 field_379;
	unsigned __int8 field_37A;
	unsigned __int8 field_37B;
	unsigned __int8 field_37C;
	unsigned __int8 field_37D;
	unsigned __int8 field_37E;
	unsigned __int8 field_37F;
	unsigned __int8 field_380;
	unsigned __int8 field_381;
	unsigned __int8 field_382;
	unsigned __int8 field_383;
	unsigned __int8 field_384;
	unsigned __int8 field_385;
	unsigned __int8 field_386;
	unsigned __int8 field_387;
	unsigned __int8 field_388;
	unsigned __int8 field_389;
	unsigned __int8 field_38A;
	unsigned __int8 field_38B;
	unsigned __int8 field_38C;
	unsigned __int8 field_38D;
	unsigned __int8 field_38E;
	unsigned __int8 field_38F;
	unsigned __int8 field_390;
	unsigned __int8 field_391;
	unsigned __int8 field_392;
	unsigned __int8 field_393;
	unsigned __int8 field_394;
	unsigned __int8 field_395;
	unsigned __int8 field_396;
	unsigned __int8 field_397;
	unsigned __int8 field_398;
	unsigned __int8 field_399;
	unsigned __int8 field_39A;
	unsigned __int8 field_39B;
	unsigned __int8 field_39C;
	unsigned __int8 field_39D;
	unsigned __int8 field_39E;
	unsigned __int8 field_39F;
	unsigned __int8 field_3A0;
	unsigned __int8 field_3A1;
	unsigned __int8 field_3A2;
	unsigned __int8 field_3A3;
	unsigned __int8 field_3A4;
	unsigned __int8 field_3A5;
	unsigned __int8 field_3A6;
	unsigned __int8 field_3A7;
	unsigned __int8 field_3A8;
	unsigned __int8 field_3A9;
	unsigned __int8 field_3AA;
	unsigned __int8 field_3AB;
	unsigned __int8 field_3AC;
	unsigned __int8 field_3AD;
	unsigned __int8 field_3AE;
	unsigned __int8 field_3AF;
	unsigned __int8 field_3B0;
	unsigned __int8 field_3B1;
	unsigned __int8 field_3B2;
	unsigned __int8 field_3B3;
	unsigned __int8 field_3B4;
	unsigned __int8 field_3B5;
	unsigned __int8 field_3B6;
	unsigned __int8 field_3B7;
	unsigned __int8 field_3B8;
	unsigned __int8 field_3B9;
	unsigned __int8 field_3BA;
	unsigned __int8 field_3BB;
	unsigned __int8 field_3BC;
	unsigned __int8 field_3BD;
	unsigned __int8 field_3BE;
	unsigned __int8 field_3BF;
	unsigned __int8 field_3C0;
	unsigned __int8 field_3C1;
	unsigned __int8 field_3C2;
	unsigned __int8 field_3C3;
	unsigned __int8 field_3C4;
	unsigned __int8 field_3C5;
	unsigned __int8 field_3C6;
	unsigned __int8 field_3C7;
	unsigned __int8 field_3C8;
	unsigned __int8 field_3C9;
	unsigned __int8 field_3CA;
	unsigned __int8 field_3CB;
	unsigned __int8 field_3CC;
	unsigned __int8 field_3CD;
	unsigned __int8 field_3CE;
	unsigned __int8 field_3CF;
	unsigned __int8 field_3D0;
	unsigned __int8 field_3D1;
	unsigned __int8 field_3D2;
	unsigned __int8 field_3D3;
	unsigned __int8 field_3D4;
	unsigned __int8 field_3D5;
	unsigned __int8 field_3D6;
	unsigned __int8 field_3D7;
	unsigned __int8 field_3D8;
	unsigned __int8 field_3D9;
	unsigned __int8 field_3DA;
	unsigned __int8 field_3DB;
	unsigned __int8 field_3DC;
	unsigned __int8 field_3DD;
	unsigned __int8 field_3DE;
	unsigned __int8 field_3DF;
	unsigned __int8 field_3E0;
	unsigned __int8 field_3E1;
	unsigned __int8 field_3E2;
	unsigned __int8 field_3E3;
	unsigned __int8 field_3E4;
	unsigned __int8 field_3E5;
	unsigned __int8 field_3E6;
	unsigned __int8 field_3E7;
	unsigned __int8 field_3E8;
	unsigned __int8 field_3E9;
	unsigned __int8 field_3EA;
	unsigned __int8 field_3EB;
	unsigned __int8 field_3EC;
	unsigned __int8 field_3ED;
	unsigned __int8 field_3EE;
	unsigned __int8 field_3EF;
	unsigned __int8 field_3F0;
	unsigned __int8 field_3F1;
	unsigned __int8 field_3F2;
	unsigned __int8 field_3F3;
	unsigned __int8 field_3F4;
	unsigned __int8 field_3F5;
	unsigned __int8 field_3F6;
	unsigned __int8 field_3F7;
	unsigned __int8 field_3F8;
	unsigned __int8 field_3F9;
	unsigned __int8 field_3FA;
	unsigned __int8 field_3FB;
	unsigned __int8 field_3FC;
	unsigned __int8 field_3FD;
	unsigned __int8 field_3FE;
	unsigned __int8 field_3FF;
	unsigned __int8 field_400;
	unsigned __int8 field_401;
	unsigned __int8 field_402;
	unsigned __int8 field_403;
	unsigned __int8 field_404;
	unsigned __int8 field_405;
	unsigned __int8 field_406;
	unsigned __int8 field_407;
	unsigned __int8 field_408;
	unsigned __int8 field_409;
	unsigned __int8 field_40A;
	unsigned __int8 field_40B;
	unsigned __int8 field_40C;
	unsigned __int8 field_40D;
	unsigned __int8 field_40E;
	unsigned __int8 field_40F;
	unsigned __int8 field_410;
	unsigned __int8 field_411;
	unsigned __int8 field_412;
	unsigned __int8 field_413;
	unsigned __int8 field_414;
	unsigned __int8 field_415;
	unsigned __int8 field_416;
	unsigned __int8 field_417;
	unsigned __int8 field_418;
	unsigned __int8 field_419;
	unsigned __int8 field_41A;
	unsigned __int8 field_41B;
	unsigned __int8 field_41C;
	unsigned __int8 field_41D;
	unsigned __int8 field_41E;
	unsigned __int8 field_41F;
	unsigned __int8 field_420;
	unsigned __int8 field_421;
	unsigned __int8 field_422;
	unsigned __int8 field_423;
	unsigned __int8 field_424;
	unsigned __int8 field_425;
	unsigned __int8 field_426;
	unsigned __int8 field_427;
	unsigned __int8 field_428;
	unsigned __int8 field_429;
	unsigned __int8 field_42A;
	unsigned __int8 field_42B;
	unsigned __int8 field_42C;
	unsigned __int8 field_42D;
	unsigned __int8 field_42E;
	unsigned __int8 field_42F;
	unsigned __int8 field_430;
	unsigned __int8 field_431;
	unsigned __int8 field_432;
	unsigned __int8 field_433;
	unsigned __int8 field_434;
	unsigned __int8 field_435;
	unsigned __int8 field_436;
	unsigned __int8 field_437;
	unsigned __int8 field_438;
	unsigned __int8 field_439;
	unsigned __int8 field_43A;
	unsigned __int8 field_43B;
	unsigned __int8 field_43C;
	unsigned __int8 field_43D;
	unsigned __int8 field_43E;
	unsigned __int8 field_43F;
	unsigned __int8 field_440;
	unsigned __int8 field_441;
	unsigned __int8 field_442;
	unsigned __int8 field_443;
	unsigned __int8 field_444;
	unsigned __int8 field_445;
	unsigned __int8 field_446;
	unsigned __int8 field_447;
	unsigned __int8 field_448;
	unsigned __int8 field_449;
	unsigned __int8 field_44A;
	unsigned __int8 field_44B;
	unsigned __int8 field_44C;
	unsigned __int8 field_44D;
	unsigned __int8 field_44E;
	unsigned __int8 field_44F;
	unsigned __int8 field_450;
	unsigned __int8 field_451;
	unsigned __int8 field_452;
	unsigned __int8 field_453;
	unsigned __int8 field_454;
	unsigned __int8 field_455;
	unsigned __int8 field_456;
	unsigned __int8 field_457;
	unsigned __int8 field_458;
	unsigned __int8 field_459;
	unsigned __int8 field_45A;
	unsigned __int8 field_45B;
	unsigned __int8 field_45C;
	unsigned __int8 field_45D;
	unsigned __int8 field_45E;
	unsigned __int8 field_45F;
	unsigned __int8 field_460;
	unsigned __int8 field_461;
	unsigned __int8 field_462;
	unsigned __int8 field_463;
	unsigned __int8 field_464;
	unsigned __int8 field_465;
	unsigned __int8 field_466;
	unsigned __int8 field_467;
	unsigned __int8 field_468;
	unsigned __int8 field_469;
	unsigned __int8 field_46A;
	unsigned __int8 field_46B;
	unsigned __int8 field_46C;
	unsigned __int8 field_46D;
	unsigned __int8 field_46E;
	unsigned __int8 field_46F;
	unsigned __int8 field_470;
	unsigned __int8 field_471;
	unsigned __int8 field_472;
	unsigned __int8 field_473;
	unsigned __int8 field_474;
	unsigned __int8 field_475;
	unsigned __int8 field_476;
	unsigned __int8 field_477;
	unsigned __int8 field_478;
	unsigned __int8 field_479;
	unsigned __int8 field_47A;
	unsigned __int8 field_47B;
	unsigned __int8 field_47C;
	unsigned __int8 field_47D;
	unsigned __int8 field_47E;
	unsigned __int8 field_47F;
	unsigned __int8 field_480;
	unsigned __int8 field_481;
	unsigned __int8 field_482;
	unsigned __int8 field_483;
	unsigned __int8 field_484;
	unsigned __int8 field_485;
	unsigned __int8 field_486;
	unsigned __int8 field_487;
	unsigned __int8 field_488;
	unsigned __int8 field_489;
	unsigned __int8 field_48A;
	unsigned __int8 field_48B;
	unsigned __int8 field_48C;
	unsigned __int8 field_48D;
	unsigned __int8 field_48E;
	unsigned __int8 field_48F;
	unsigned __int8 field_490;
	unsigned __int8 field_491;
	unsigned __int8 field_492;
	unsigned __int8 field_493;
	unsigned __int8 field_494;
	unsigned __int8 field_495;
	unsigned __int8 field_496;
	unsigned __int8 field_497;
	unsigned __int8 field_498;
	unsigned __int8 field_499;
	unsigned __int8 field_49A;
	unsigned __int8 field_49B;
	unsigned __int8 field_49C;
	unsigned __int8 field_49D;
	unsigned __int8 field_49E;
	unsigned __int8 field_49F;
	unsigned __int8 field_4A0;
	unsigned __int8 field_4A1;
	unsigned __int8 field_4A2;
	unsigned __int8 field_4A3;
	unsigned __int8 field_4A4;
	unsigned __int8 field_4A5;
	unsigned __int8 field_4A6;
	unsigned __int8 field_4A7;
	unsigned __int8 field_4A8;
	unsigned __int8 field_4A9;
	unsigned __int8 field_4AA;
	unsigned __int8 field_4AB;
	unsigned __int8 field_4AC;
	unsigned __int8 field_4AD;
	unsigned __int8 field_4AE;
	unsigned __int8 field_4AF;
	unsigned __int8 field_4B0;
	unsigned __int8 field_4B1;
	unsigned __int8 field_4B2;
	unsigned __int8 field_4B3;
	unsigned __int8 field_4B4;
	unsigned __int8 field_4B5;
	unsigned __int8 field_4B6;
	unsigned __int8 field_4B7;
	unsigned __int8 field_4B8;
	unsigned __int8 field_4B9;
	unsigned __int8 field_4BA;
	unsigned __int8 field_4BB;
	unsigned __int8 field_4BC;
	unsigned __int8 field_4BD;
	unsigned __int8 field_4BE;
	unsigned __int8 field_4BF;
	unsigned __int8 field_4C0;
	unsigned __int8 field_4C1;
	unsigned __int8 field_4C2;
	unsigned __int8 field_4C3;
	unsigned __int8 field_4C4;
	unsigned __int8 field_4C5;
	unsigned __int8 field_4C6;
	unsigned __int8 field_4C7;
	unsigned __int8 field_4C8;
	unsigned __int8 field_4C9;
	unsigned __int8 field_4CA;
	unsigned __int8 field_4CB;
	unsigned __int8 field_4CC;
	unsigned __int8 field_4CD;
	unsigned __int8 field_4CE;
	unsigned __int8 field_4CF;
	unsigned __int8 field_4D0;
	unsigned __int8 field_4D1;
	unsigned __int8 field_4D2;
	unsigned __int8 field_4D3;
	unsigned __int8 field_4D4;
	unsigned __int8 field_4D5;
	unsigned __int8 field_4D6;
	unsigned __int8 field_4D7;
	unsigned __int8 field_4D8;
	unsigned __int8 field_4D9;
	unsigned __int8 field_4DA;
	unsigned __int8 field_4DB;
	unsigned __int8 field_4DC;
	unsigned __int8 field_4DD;
	unsigned __int8 field_4DE;
	unsigned __int8 field_4DF;
	unsigned __int8 field_4E0;
	unsigned __int8 field_4E1;
	unsigned __int8 field_4E2;
	unsigned __int8 field_4E3;
	unsigned __int8 field_4E4;
	unsigned __int8 field_4E5;
	unsigned __int8 field_4E6;
	unsigned __int8 field_4E7;
	unsigned __int8 field_4E8;
	unsigned __int8 field_4E9;
	unsigned __int8 field_4EA;
	unsigned __int8 field_4EB;
	unsigned __int8 field_4EC;
	unsigned __int8 field_4ED;
	unsigned __int8 field_4EE;
	unsigned __int8 field_4EF;
	unsigned __int8 field_4F0;
	unsigned __int8 field_4F1;
	unsigned __int8 field_4F2;
	unsigned __int8 field_4F3;
	unsigned __int8 field_4F4;
	unsigned __int8 field_4F5;
	unsigned __int8 field_4F6;
	unsigned __int8 field_4F7;
	unsigned __int8 field_4F8;
	unsigned __int8 field_4F9;
	unsigned __int8 field_4FA;
	unsigned __int8 field_4FB;
	unsigned __int8 field_4FC;
	unsigned __int8 field_4FD;
	unsigned __int8 field_4FE;
	unsigned __int8 field_4FF;
	unsigned __int8 field_500;
	unsigned __int8 field_501;
	unsigned __int8 field_502;
	unsigned __int8 field_503;
	unsigned __int8 field_504;
	unsigned __int8 field_505;
	unsigned __int8 field_506;
	unsigned __int8 field_507;
	unsigned __int8 field_508;
	unsigned __int8 field_509;
	unsigned __int8 field_50A;
	unsigned __int8 field_50B;
	unsigned __int8 field_50C;
	unsigned __int8 field_50D;
	unsigned __int8 field_50E;
	unsigned __int8 field_50F;
	unsigned __int8 field_510;
	unsigned __int8 field_511;
	unsigned __int8 field_512;
	unsigned __int8 field_513;
	unsigned __int8 field_514;
	unsigned __int8 field_515;
	unsigned __int8 field_516;
	unsigned __int8 field_517;
	unsigned __int8 field_518;
	unsigned __int8 field_519;
	unsigned __int8 field_51A;
	unsigned __int8 field_51B;
	unsigned __int8 field_51C;
	unsigned __int8 field_51D;
	unsigned __int8 field_51E;
	unsigned __int8 field_51F;
	unsigned __int8 field_520;
	unsigned __int8 field_521;
	unsigned __int8 field_522;
	unsigned __int8 field_523;
	unsigned __int8 field_524;
	unsigned __int8 field_525;
	unsigned __int8 field_526;
	unsigned __int8 field_527;
	unsigned __int8 field_528;
	unsigned __int8 field_529;
	unsigned __int8 field_52A;
	unsigned __int8 field_52B;
	unsigned __int8 field_52C;
	unsigned __int8 field_52D;
	unsigned __int8 field_52E;
	unsigned __int8 field_52F;
	unsigned __int8 field_530;
	unsigned __int8 field_531;
	unsigned __int8 field_532;
	unsigned __int8 field_533;
	unsigned __int8 field_534;
	unsigned __int8 field_535;
	unsigned __int8 field_536;
	unsigned __int8 field_537;
	unsigned __int8 field_538;
	unsigned __int8 field_539;
	unsigned __int8 field_53A;
	unsigned __int8 field_53B;
	unsigned __int8 field_53C;
	unsigned __int8 field_53D;
	unsigned __int8 field_53E;
	unsigned __int8 field_53F;
	unsigned __int8 field_540;
	unsigned __int8 field_541;
	unsigned __int8 field_542;
	unsigned __int8 field_543;
	unsigned __int8 field_544;
	unsigned __int8 field_545;
	unsigned __int8 field_546;
	unsigned __int8 field_547;
	unsigned __int8 field_548;
	unsigned __int8 field_549;
	unsigned __int8 field_54A;
	unsigned __int8 field_54B;
	unsigned __int8 field_54C;
	unsigned __int8 field_54D;
	unsigned __int8 field_54E;
	unsigned __int8 field_54F;
	unsigned __int8 field_550;
	unsigned __int8 field_551;
	unsigned __int8 field_552;
	unsigned __int8 field_553;
	unsigned __int8 field_554;
	unsigned __int8 field_555;
	unsigned __int8 field_556;
	unsigned __int8 field_557;
	unsigned __int8 field_558;
	unsigned __int8 field_559;
	unsigned __int8 field_55A;
	unsigned __int8 field_55B;
	unsigned __int8 field_55C;
	unsigned __int8 field_55D;
	unsigned __int8 field_55E;
	unsigned __int8 field_55F;
	unsigned __int8 field_560;
	unsigned __int8 field_561;
	unsigned __int8 field_562;
	unsigned __int8 field_563;
	unsigned __int8 field_564;
	unsigned __int8 field_565;
	unsigned __int8 field_566;
	unsigned __int8 field_567;
	unsigned __int8 field_568;
	unsigned __int8 field_569;
	unsigned __int8 field_56A;
	unsigned __int8 field_56B;
	unsigned __int8 field_56C;
	unsigned __int8 field_56D;
	unsigned __int8 field_56E;
	unsigned __int8 field_56F;
	unsigned __int8 field_570;
	unsigned __int8 field_571;
	unsigned __int8 field_572;
	unsigned __int8 field_573;
	unsigned __int8 field_574;
	unsigned __int8 field_575;
	unsigned __int8 field_576;
	unsigned __int8 field_577;
	unsigned __int8 field_578;
	unsigned __int8 field_579;
	unsigned __int8 field_57A;
	unsigned __int8 field_57B;
	unsigned __int8 field_57C;
	unsigned __int8 field_57D;
	unsigned __int8 field_57E;
	unsigned __int8 field_57F;
	unsigned __int8 field_580;
	unsigned __int8 field_581;
	unsigned __int8 field_582;
	unsigned __int8 field_583;
	unsigned __int8 field_584;
	unsigned __int8 field_585;
	unsigned __int8 field_586;
	unsigned __int8 field_587;
	unsigned __int8 field_588;
	unsigned __int8 field_589;
	unsigned __int8 field_58A;
	unsigned __int8 field_58B;
	unsigned __int8 field_58C;
	unsigned __int8 field_58D;
	unsigned __int8 field_58E;
	unsigned __int8 field_58F;
	unsigned __int8 field_590;
	unsigned __int8 field_591;
	unsigned __int8 field_592;
	unsigned __int8 field_593;
	unsigned __int8 field_594;
	unsigned __int8 field_595;
	unsigned __int8 field_596;
	unsigned __int8 field_597;
	unsigned __int8 field_598;
	unsigned __int8 field_599;
	unsigned __int8 field_59A;
	unsigned __int8 field_59B;
	unsigned __int8 field_59C;
	unsigned __int8 field_59D;
	unsigned __int8 field_59E;
	unsigned __int8 field_59F;
};

typedef enum StatsSource {
	STATS_ONLINE = 0,
	STATS_OFFLINE = 1,
	STATS_COUNT = 2
} StatsSource;

typedef enum StatsGroup {
	STATSGROUP_FIRST = 0,
	STATSGROUP_RANKED = 0,
	STATSGROUP_COOP = 1,
	STATSGROUP_COMMON = 2,
	STATSGROUP_RANKEDLOADOUTS = 3,
	STATSGROUP_PRIVATELOADOUTS = 4,
	STATSGROUP_NONGAME = 5,
	STATSGROUP_COUNT = 6,
	STATSGROUP_IGNORE = 7
} StatsGroup;

typedef enum OmnvarType 
{
	OMNVAR_TYPE_BOOL = 0,
	OMNVAR_TYPE_FLOAT = 1,
	OMNVAR_TYPE_INT = 2,
	OMNVAR_TYPE_UINT = 3,
	OMNVAR_TYPE_TIME = 4,
	OMNVAR_TYPE_NCS_LUI = 5,
	OMNVAR_TYPE_COUNT = 6
} OmnvarType;

union OmnvarValue
{
	bool enabled;
	int integer;
	unsigned int unsignedInteger;
	float value;
	unsigned int ncsString;
};

struct OmnvarData
{
	unsigned int timeModified;
	OmnvarValue current;
};

struct __declspec(align(8)) OmnvarDef
{
	const char* name;
	const char* ncsString;
	int pmoveIndex;
	int minvalue;
	int maxvalue;
	OmnvarValue initial;
	char numbits;
	char flags;
	byte type[1];
	byte userType[1];
};

struct gameTypeInfo
{
	char gameTypeInternalName[12];
	char gameTypeName[32];
	char customizedGameTypeName[64];
	char customizedGameTypeDesc[64];
};

struct mapInfo
{
	char mapName[32];
	char mapLoadName[16];
	char mapDescription[32];
	char mapLoadImage[32];
	char mapVoteImage[32];
	char mapCamoTypes[2][16];
	char mapDefaultGameType[32];
	char mapGameTypes[1024];
	int isAliensMap;
	int mapPack;
};

struct scrContext_t :class_helper {

};

struct SvClient {
	virtual void unk();
	virtual void SendServerCommand(int type, const char* text);
};

ClActiveClient* GetClActiveClient();
int ClActiveClient_GetCmdNumber(ClActiveClient* activeClient);
usercmd_s* CL_GetUserCmd(int cmdNumber);

extern ClActiveClient* ms_activeClients;


extern clientUIActive_t* clientUIActives;

extern gentity_s* g_entities;
