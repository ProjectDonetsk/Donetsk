#pragma once
#include "Main.hpp"

struct RumbleGraph;
struct RumbleInfo;
struct CameraDef;
struct GfxImage;
struct Material;
struct Bounds;
struct FxCombinedDef;

struct vec2_t
{
	float v[2];
};

struct vec3_t
{
	float v[3];
};

struct vec4_t
{
	float v[4];
};

typedef int scr_string_t;

struct Bounds
{
	vec3_t midPoint;
	vec3_t halfSize;
};

struct GfxDrawSurfFields
{
	unsigned __int64 indirectArgsOffset : 10;
	unsigned __int64 gpBatchIndex : 16;
	unsigned __int64 objectId : 24;
	unsigned __int64 hasGfxEntIndex : 1;
	unsigned __int64 lightmapIndex : 9;
	unsigned __int64 shadowcaster : 1;
	unsigned __int64 materialSortedIndex : 16;
	unsigned __int64 tessellation : 3;
	unsigned __int64 prepass : 2;
	unsigned __int64 viewModelRender : 1;
	unsigned __int64 lowResShading : 1;
	unsigned __int64 surfType : 4;
	unsigned __int64 primarySortKey : 6;
};

struct EffectDefMap {
	char name[64];
	char filename[256];
};

struct Packed128
{
	unsigned __int64 p0;
	unsigned __int64 p1;
};

union GfxDrawSurf
{
	GfxDrawSurfFields fields;
	Packed128 packed;
};

struct MaterialTextureDef
{
	unsigned __int8 index;
	GfxImage* image;
};

struct MaterialConstantDef
{
	unsigned __int8 index;
	vec4_t literal;
};

struct GfxDecalVolumeMaterial
{
	const char* name;
	GfxImage* channels[6];
	unsigned int flags;
	vec3_t colorTint;
	float alphaDissolveParms;
	float emissiveScale;
	unsigned int packedDisplacementScaleAndBias;
	float displacementCutoffDistance;
	float displacementCutoffFalloff;
	unsigned int packedTemperatureBaseAndScale;
	unsigned __int8 textureAtlasRowCount;
	unsigned __int8 textureAtlasColumnCount;
	unsigned __int8 padding[6];
};

struct PhysicsAssetUsageCounter
{
	int serverEnt;
	int clientEnt;
	int dynEnt;
};

struct __declspec(align(4)) PhysicsAsset
{
	const char* name;
	char* havokData;
	unsigned int havokDataSize;
	int useCategory;
	int numRigidBodies;
	int numConstraints;
	uintptr_t simulationCategories;
	unsigned int* bodyContents;
	int numSFXEventAssets;
	int numVFXEventAssets;
	uintptr_t sfxEventAssets;
	uintptr_t vfxEventAssets;
	PhysicsAssetUsageCounter usageCounter;
	bool containsDynamicBodies;
};

struct Material
{
	const char* name;
	unsigned int contents;
	unsigned int surfaceFlags;
	float maxDisplacement;
	int /*MaterialGeometryType*/ materialType;
	unsigned __int8 cameraRegion;
	unsigned __int8 sortKey;
	unsigned __int16 flags;
	unsigned __int8 textureCount;
	unsigned __int8 constantCount;
	unsigned __int8 constantBufferCount;
	unsigned __int8 layerCount;
	unsigned __int16 packedAtlasDataSize;
	unsigned __int8 textureAtlasRowCount;
	unsigned __int8 textureAtlasColumnCount;
	GfxDrawSurf drawSurf;
	unsigned __int8* packedAtlasData;
	void* /*MaterialTechniqueSet*/ techniqueSet;
	MaterialTextureDef* textureTable;
	MaterialConstantDef* constantTable;
	GfxDecalVolumeMaterial* decalVolumeMaterial;
	unsigned __int8* constantBufferIndex;
	void* /*MaterialConstantBufferDef*/ constantBufferTable;
	const char** subMaterials;
};

enum GfxTextureId : __int32
{
	NULLID = 0x0,
};

enum GfxPixelFormat : __int32
{
	GFX_PF_INVALID = 0x0,
	GFX_PF_R8 = 0x1,
	GFX_PF_A8 = 0x2,
	GFX_PF_L8 = 0x3,
	GFX_PF_R8G8 = 0x4,
	GFX_PF_L8A8 = 0x5,
	GFX_PF_R8G8B8A8 = 0x6,
	GFX_PF_R8G8B8A8_SRGB = 0x7,
	GFX_PF_R8_SNORM = 0x8,
	GFX_PF_R8G8_SNORM = 0x9,
	GFX_PF_R16 = 0xA,
	GFX_PF_R16G16 = 0xB,
	GFX_PF_R16G16B16A16 = 0xC,
	GFX_PF_R16_SNORM = 0xD,
	GFX_PF_R16F = 0xE,
	GFX_PF_R16G16F = 0xF,
	GFX_PF_R16G16B16A16F = 0x10,
	GFX_PF_R32F = 0x11,
	GFX_PF_R32G32F = 0x12,
	GFX_PF_R32G32B32A32F = 0x13,
	GFX_PF_D16 = 0x14,
	GFX_PF_D32F = 0x15,
	GFX_PF_D32F_S8 = 0x16,
	GFX_PF_R8_UINT = 0x17,
	GFX_PF_R16_UINT = 0x18,
	GFX_PF_R32_UINT = 0x19,
	GFX_PF_R32G32_UINT = 0x1A,
	GFX_PF_R32G32B32A32_UINT = 0x1B,
	GFX_PF_R10G10B10A2_UINT = 0x1C,
	GFX_PF_R5G6B5 = 0x1D,
	GFX_PF_R10G10B10A2 = 0x1E,
	GFX_PF_R9G9B9E5_SHAREDEXP = 0x1F,
	GFX_PF_R11G11B10F = 0x20,
	GFX_PF_BC1 = 0x21,
	GFX_PF_BC1_SRGB = 0x22,
	GFX_PF_BC2 = 0x23,
	GFX_PF_BC2_SRGB = 0x24,
	GFX_PF_BC3 = 0x25,
	GFX_PF_BC3_SRGB = 0x26,
	GFX_PF_BC4 = 0x27,
	GFX_PF_BC5 = 0x28,
	GFX_PF_BC5S = 0x29,
	GFX_PF_BC6H = 0x2A,
	GFX_PF_BC6HS = 0x2B,
	GFX_PF_BC7 = 0x2C,
	GFX_PF_BC7_SRGB = 0x2D,
	GFX_PF_R8G8B8A8_SNORM = 0x2E,
	GFX_PF_R1 = 0x2F,
	GFX_PF_R4G4 = 0x30,
	GFX_PF_R10G10B10A2_SNORM = 0x31,
	GFX_PF_COUNT = 0x32,
};

enum GfxImageFlags
{
	IMG_FLAG_NONE = 0x0,
	IMG_DISK_FLAG_NOPICMIP = 0x1,
	IMG_DISK_FLAG_NOMIPMAPS = 0x2,
	IMG_DISK_FLAG_UNUSED = 0x4,
	IMG_DISK_FLAG_NORMAL_OCCLUSON_GLOSS = 0x8,
	IMG_DISK_FLAG_CLAMP_U = 0x10,
	IMG_DISK_FLAG_CLAMP_V = 0x20,
	IMG_DISK_FLAG_STREAMED = 0x40,
	IMG_DISK_FLAG_USE_OODLE_COMPRESSION = 0x80,
	IMG_DISK_FLAG_GAMMA_SRGB = 0x100,
	IMG_DISK_FLAG_PACKED_ATLAS = 0x200,
	IMG_CREATE_FLAG_UNTILED = 0x400,
	IMG_CREATE_FLAG_CPU_READ = 0x800,
	IMG_CREATE_FLAG_CPU_WRITE = 0x1000,
	IMG_DISK_FLAG_AUTOMETALNESS = 0x2000,
	IMG_DISK_FLAG_AUTODISPLACEMENT = 0x4000,
	IMG_DISK_FLAG_MAPTYPE_2D = 0x0,
	IMG_DISK_FLAG_MAPTYPE_CUBE = 0x8000,
	IMG_DISK_FLAG_MAPTYPE_3D = 0x10000,
	IMG_DISK_FLAG_MAPTYPE_1D = 0x18000,
	IMG_DISK_FLAG_MAPTYPE_ARRAY = 0x20000,
	IMG_DISK_FLAG_MAPTYPE_CUBE_ARRAY = 0x28000,
	IMG_DISK_FLAG_INVERT_ALPHA = 0x40000,
	IMG_DISK_FLAG_PREMUL_ALPHA = 0x80000,
	IMG_DISK_FLAG_MIPGEN_ORIGINAL = 0x0,
	IMG_DISK_FLAG_MIPGEN_LANCZOS3 = 0x100000,
	IMG_DISK_FLAG_MIPGEN_CATMULL_ROM = 0x200000,
	IMG_DISK_FLAG_MIPGEN_CUBIC_BSPLINE = 0x300000,
	IMG_DISK_FLAG_MIPGEN_BOX = 0x400000,
	IMG_DISK_FLAG_MIPGEN_COVERAGE_PRESERVING = 0x500000,
	IMG_CREATE_FLAG_RW_VIEW = 0x800000,
	IMG_CREATE_FLAG_DYNAMIC = 0x1000000,
	IMG_DISK_FLAG_PREMUL_KEEP_ALPHA = 0x2000000,
	IMG_DISK_FLAG_RTT = 0x4000000,
	IMG_DISK_FLAG_EXTRACT_ALPHA = 0x8000000,
	IMG_DISK_FLAG_OCTAHEDRON = 0x10000000,
	IMG_CREATE_FLAG_STAGING = 0x20000000,
	IMG_CREATE_FLAG_VOLUMETRIC_LAYOUT_OVERRIDE = 0x40000000,
	IMG_CREATE_FLAG_TYPELESS = 0x80000000,
};

union GfxImageSemanticSpecific
{
	float atlasFps;
	unsigned int albedoMapScaleBias;
	unsigned int normalMapScaleBias;
	unsigned int maxMipMap;
};

struct GfxImageAtlasSize
{
	unsigned __int8 rowCount;
	unsigned __int8 colCount;
};

union GfxImageAtlasInfo
{
	GfxImageAtlasSize atlasSize;
	unsigned __int16 packedAtlasDataSize;
};

enum TextureSemantic : __int8
{
	TS_2D = 0x0,
	TS_FUNCTION = 0x1,
	TS_COLOR_MAP = 0x2,
	TS_GRAY_MAP = 0x3,
	TS_SIGNED_VELOCITY_MAP = 0x4,
	TS_NORMAL_MAP = 0x5,
	TS_METALNESS_MAP = 0x6,
	TS_NORMAL_OCCLUSION_GLOSS_MAP = 0x7,
	TS_SIGNED_DISTANCE_FIELD = 0x8,
	TS_CARD_IMPOSTER_NORMAL = 0x9,
	TS_COUNT = 0xA,
};

enum GfxImageCategory : __int8
{
	IMG_CATEGORY_UNKNOWN = 0x0,
	IMG_CATEGORY_AUTO_GENERATED = 0x1,
	IMG_CATEGORY_LIGHTMAP = 0x2,
	IMG_CATEGORY_LOAD_FROM_FILE = 0x3,
	IMG_CATEGORY_RAW = 0x4,
	IMG_CATEGORY_FIRST_UNMANAGED = 0x5,
	IMG_CATEGORY_RENDERTARGET = 0x5,
	IMG_CATEGORY_TEMP = 0x6,
};

struct XPakEntryInfo
{
	unsigned __int64 key;
	__int64 offset;
	unsigned __int64 size;
	unsigned __int64 xpakIndex : 8;
	unsigned __int64 compressed : 1;
	unsigned __int64 valid : 1;
	unsigned __int64 adjacentLeftType : 3;
	unsigned __int64 adjacentRightType : 3;
	unsigned __int64 adjacentLeft : 19;
	unsigned __int64 adjacentRight : 19;
	unsigned __int64 padding : 10;
};

enum GfxImageStreamLevelCountAndSize : __int32
{
};

struct GfxImageStreamData
{
	XPakEntryInfo xpakEntry;
	GfxImageStreamLevelCountAndSize levelCountAndSize;
	unsigned __int16 width;
	unsigned __int16 height;
};

struct streamer_handle_t
{
	unsigned __int64 data;
};

struct GfxImageFallback
{
	unsigned __int8* pixels;
	unsigned int size;
	unsigned __int16 width;
	unsigned __int16 height;
};

union GfxImagePixels
{
	streamer_handle_t streamedDataHandle;
	unsigned __int8* residentData;
};


struct GfxImage
{
	const char* name;
	unsigned __int8* packedAtlasData;
	GfxTextureId textureId;
	GfxPixelFormat format;
	GfxImageFlags flags;
	unsigned int totalSize;
	GfxImageSemanticSpecific semanticSpecific;
	unsigned __int16 width;
	unsigned __int16 height;
	unsigned __int16 depth;
	unsigned __int16 numElements;
	GfxImageAtlasInfo atlasInfo;
	TextureSemantic semantic;
	GfxImageCategory category;
	unsigned __int8 levelCount;
	unsigned __int8 streamedPartCount;
	unsigned __int8 decalAtlasIndex;
	char freqDomainMetricBias;
	GfxImageStreamData streams[4];
	GfxImageFallback* fallback;
	GfxImagePixels pixels;
};

struct AttachmentList
{
	unsigned int attachmentCount;
	void** /*WeaponAttachment*/ attachments;
};

struct __declspec(align(4)) SceneZoomSettings
{
	int adsZoomCount;
	float adsZoomFov[3];
	float adsReloadFov[3];
	int adsZoomFovTransitionTime[3];
	int /*AdsOffsetInterpolationType*/ adsZoomFovLerpType;
	float adsZoomInFrac;
	float adsZoomOutFrac;
	float adsFOVNVG;
	float adsReloadFovNVG;
	bool adsZoomLevelIndexResetOnToggle;
};

struct __declspec(align(4)) WeaponZoomSettings
{
	float adsZoomFov;
	int /*AdsOffsetInterpolationType*/ adsZoomFovLerpType;
	float adsZoomFovXOffset;
	float adsReloadZoomFov;
	float adsReloadZoomFovXOffset;
	float adsNVGZoomFov;
	float adsNVGZoomFovXOffset;
	float adsNVGReloadZoomFov;
	float adsNVGReloadZoomFovXOffset;
	float adsZoomInFrac;
	float adsZoomOutFrac;
	bool adsZoomFovXOffsetOverride;
	bool adsReloadFovXOffsetOverride;
};

struct ZoomSettings
{
	SceneZoomSettings scene;
	WeaponZoomSettings weapon;
};


struct WeaponEntityNotify
{
	int flags;
	float radius;
	float height;
	float minSpeed;
};



struct XModelPhysicsUsageCounter {
	int serverEnt;
	int clientEnt;
	int dynEnt;
};

struct DObjAnimMat {
	float quat[4];
	float trans[3];
	float transWeight;
};

struct XModel {
	const char* name;
	unsigned __int16 numsurfs;
	unsigned __int8 numLods;
	unsigned __int8 collLod;
	unsigned __int16 mdaoVolumeCount;
	unsigned __int8 shadowCutoffLod;
	int physicsUseCategory;
	char characterCollBoundsType;
	unsigned __int8 numAimAssistBones;
	unsigned __int8 impactType;
	unsigned __int8 mdaoType;
	unsigned __int8 numBones;
	unsigned __int8 numRootBones;
	unsigned __int16 numClientBones;
	unsigned __int8 numClothAssets;
	unsigned int flags;
	int contents;
	float scale;
	float radius;
	Bounds bounds;
	float edgeLength;
	unsigned int lgvData;
	XModelPhysicsUsageCounter physicsUsageCounter;
	unsigned int noScalePartBits[8];
	void* scriptableMoverDef;
	void* proceduralBones;
	void* dynamicBones;
	scr_string_t* aimAssistBones;
	scr_string_t* boneNames;
	unsigned __int8* parentList;
	__int16* quats;
	float* trans;
	unsigned __int8* partClassification;
	DObjAnimMat* baseMat;
	vec3_t* ikHingeAxis;
	uintptr_t reactiveMotionInfo;
	uintptr_t materialHandles;
};

struct WeaponAnimPackage
{
	const char* name;
	uintptr_t anims;
	uintptr_t timers;
	int meleeAnimPrimaryType;
	int meleeAnimPrimaryCount;
	unsigned __int8 meleeAnimPrimarySet;
	bool meleeRandomizeAnims;
	int meleeAnimAltType;
	int meleeAnimAltCount;
	unsigned __int8 meleeAnimAltSet;
	bool altMeleeRandomizeAnims;
	uintptr_t blendSpaces;
	uintptr_t footstep;
};

union XAnimIndices
{
	unsigned __int8* _1;
	unsigned __int16* _2;
	void* data;
};

struct XAnimParts
{
	const char* name;
	scr_string_t* names;
	unsigned __int8* dataByte;
	__int16* dataShort;
	int* dataInt;
	__int16* randomDataShort;
	unsigned __int8* randomDataByte;
	int* randomDataInt;
	XAnimIndices indices;
	uintptr_t notify;
	uintptr_t deltaPart;
	unsigned int randomDataShortCount;
	unsigned int randomDataByteCount;
	unsigned int indexCount;
	float framerate;
	float frequency;
	unsigned int dataByteCount;
	unsigned __int16 dataShortCount;
	unsigned __int16 dataIntCount;
	unsigned __int16 randomDataIntCount;
	unsigned __int16 numframes;
	unsigned __int8 flags;
	unsigned __int8 boneCount[10];
	unsigned __int8 notifyCount;
	unsigned __int8 assetType;
	unsigned __int8 ikType;
	unsigned __int8 fingerPoseType;
	unsigned __int16 blendShapeWeightCount;
	scr_string_t* blendShapeWeightNames;
	unsigned __int16* blendShapeWeights;
};

struct WeaponDamageCommon
{
	int minDamage;
	int mid1Damage;
	int mid2Damage;
	int mid3Damage;
	int damage;
	float maxDamageRange;
	float mid1DamageRange;
	float mid2DamageRange;
	float mid3DamageRange;
	float minDamageRange;
};

struct WeaponDamageInfo
{
	WeaponDamageCommon damageData[3];
	int deathAnimDamageType;
	float terminateAtRange;
};

struct WeaponVFXPackage
{
	const char* name;
	uintptr_t vfx;
};

struct __declspec(align(4)) TriggerDisconnectSoundData
{
	float analogTriggerValue;
	bool enabledForFireType[6];
};

struct __declspec(align(8)) WeaponSFXPackage
{
	const char* name;
	uintptr_t sounds;
	WeaponSFXPackage* transientFallbackPackage;
	uintptr_t detailSoundBankNPC;
	uintptr_t detailSoundBankPlayer;
	unsigned __int8 rattleSoundType;
	const char* szAdsrBaseSetting;
	const char* szWeapSndReflectionClass;
	const char* szWeapSndReflFrontOverride;
	const char* szWeapSndReflDistantOverride;
	float weapSndFireVolumeShot1;
	float weapSndFireVolumeShot2;
	float weapSndFireVolumeShot3;
	float weapSndProneFireLFEVolume;
	float weapSndMediumRangeStart;
	float weapSndFarRangeStart;
	float weapSndDistantRangeStart;
	unsigned int projExplosionReflClass;
	int sfxImpactType;
	int sfxMeleeImpactType;
	int sfxMaterialType;
	const char* szMountEnterExitString;
	const char* szMountImpactString;
	unsigned int whizbyType;
	unsigned int adsContextType;
	unsigned int adsContextValue;
	float speedOfSoundMult;
	TriggerDisconnectSoundData triggerDisconnectSoundData;
};

struct __declspec(align(8)) ADSOverlay
{
	Material* shaderMat;
	Material* shaderLowResMat;
	Material* shaderEMPMat;
	Material* shaderEMPLowResMat;
	GfxImage* shaderImg;
	GfxImage* shaderLowResImg;
	GfxImage* shaderEMPImg;
	GfxImage* shaderEMPLowResImg;
	bool applyVisionSet;
	int reticle;
	float width;
	float height;
	float widthSplitscreen;
	float heightSplitscreen;
	const char* visionSetName;
	float visionSetADSFraction;
	int visionSetBlendInTimeMs;
	int visionSetBlendOutTimeMs;
};

struct CommonSwaySettings
{
	float maxAngle;
	float lerpSpeed;
	float pitchScale;
	float yawScale;
	float horizScale;
	float vertScale;
	float gunAngleScale;
};

struct HipSwaySettings
{
	CommonSwaySettings common;
	float maxAngleSteadyAim;
};

struct AdsSwaySettings
{
	CommonSwaySettings common;
	float swayTransitionLerpSpeed;
	float adsSwayScale[3];
};

struct AdvancedHipSwaySettings
{
	bool enabled;
	float torsoGoalSmoothSpeed;
	int torsoGoalViewSmoothDurationMs;
	vec2_t torsoGoalDeadzoneAdjustSpeed;
	RumbleGraph* torsoGoalViewSpeedToMaxDeadzone_graph;
	vec2_t torsoGoalViewSpeedToMaxDeadzone_viewspeed;
	vec2_t torsoGoalViewSpeedToMaxDeadzone_maxDeadzone;
	vec2_t torsoMass;
	vec2_t torsoSpring;
	vec2_t torsoDamper;
	int gunGoalViewSmoothDurationMs;
	RumbleGraph* gunGoalViewSpeedToOffset_graph;
	vec2_t gunGoalViewSpeedToOffset_viewspeed;
	vec2_t gunGoalViewSpeedToOffset_offset;
	vec2_t gunMass;
	vec2_t gunSpring;
	vec2_t gunDamper;
	vec3_t gunPivotPoint;
	float gunYawToRollScale;
	int fireDurationMs;
	int fireStartBlendDurationMs;
	int fireFinishBlendDurationMs;
	float fireTorsoGoalSmoothSpeed;
	float fireTorsoDeadzoneScale;
	float fireTorsoToGunDirScale;
};

struct __declspec(align(4)) SwaySettings
{
	HipSwaySettings hip;
	AdsSwaySettings ads;
	AdvancedHipSwaySettings adv;
	float shellShockScale;
	bool overrideHip;
	bool overrideAds;
};

struct WeaponOffsetCurveDescription
{
	float blendTime;
	float decayTime;
	float shotDecayFireTimeFrac;
	float holdTime;
	float adsFractionBegin;
	float adsFractionEnd;
	int interpType;
	int interpTypeOut;
};

struct WeaponOffsetPatternDescription
{
	bool active;
	scr_string_t patternKey;
	int curveType;
	int patternType;
	int transformType;
	float frequency;
	float blendTime;
	vec3_t magnitude;
	float hipScale;
	float rotationOffset;
	float bulletDirScale;
	float fullAutoScale;
	int fullAutoBullets;
	float fullAutoDecay;
	int referenceIndex;
	int kickOrSnapDecayIndex;
};

struct __declspec(align(4)) GestureWeaponSettings
{
	unsigned __int16 blendToStates;
	bool hideReticle;
	float fireDelay;
	float sprintDelay;
	bool useLeftIdleAkimbo;
	bool splitAnimsAkimbo;
	bool blendToDemeanorLoop;
	bool blendOutRaise;
	bool blendOutFingerPose;
	bool blendOutAdditiveADS;
};

struct __declspec(align(2)) GestureDirectionalSettings
{
	float maxAngle;
	float lerpAtMaxAngle;
	float widthCushionAngle;
	float lerpAtMinCushionAngle;
	float lerpAtMaxCushionAngle;
	float limitLeft;
	float limitRight;
	float limitUp;
	float limitDown;
	bool useTargetOffset;
	float targetOffsetX;
	float targetOffsetY;
	float targetOffsetZ;
	float targetOffsetYaw;
	float targetOffsetPitch;
	float targetOffsetRoll;
	bool ignoreViewPitchForTargetOffset;
	bool ignoreViewYawForTargetOffset;
	bool ignoreViewRollForTargetOffset;
};

struct __declspec(align(4)) FootstepTime
{
	float time;
	bool isLeft;
};

struct __declspec(align(4)) MovementTime
{
	float time;
	bool isLeadIn;
};

struct FootstepAnim
{
	int leftCount;
	FootstepTime step[32];
	MovementTime movement[32];
};

struct GestureLookAroundSettings
{
	float yawLerpIn;
	float yawLerpOut;
	unsigned __int16 walkTime;
	FootstepAnim walkFootStepAnim;
};

struct GestureIKTargetSettings
{
	scr_string_t targetEntityBoneName;
};

struct __declspec(align(8)) Gesture
{
	const char* name;
	int type;
	int priority;
	bool looping;
	uintptr_t anims;
	GestureWeaponSettings weaponSettings;
	GestureDirectionalSettings directionalSettings;
	GestureLookAroundSettings lookAroundSettings;
	GestureIKTargetSettings ikTargetSettings;
};

struct LaserSettings
{
	bool forceLaserOn;
	bool localPlayerADSLaserEnabled;
	bool localPlayerHipLaserEnabled;
	bool localPlayerNVGADSLaserEnabled;
	bool localPlayerNVGHipLaserEnabled;
	bool remotePlayerADSLaserEnabled;
	bool remotePlayerHipLaserEnabled;
	bool remotePlayerNVGADSLaserEnabled;
	bool remotePlayerNVGHipLaserEnabled;
	bool laserViewCenterInAds;
};

struct __declspec(align(4)) GrenadeRotationParams
{
	float initialPitch;
	float initialYaw;
	float initialRoll;
	int rotationPitchDir;
	int rotationPitchMin;
	int rotationPitchMax;
	int rotationYawDir;
	int rotationYawMin;
	int rotationYawMax;
	int rotationRollDir;
	int rotationRollMin;
	int rotationRollMax;
	bool rotate;
};

struct AnimOverride
{
	unsigned int numBindings;
	uintptr_t bindings;
	uintptr_t overrides;
	uintptr_t overridesAlt;
};

struct CarryAnimOverride
{
	int carryObjectType;
	WeaponAnimPackage* animPackage;
	WeaponAnimPackage* animPackageAlt;
};

struct SFXOverride
{
	unsigned int numBindings;
	uintptr_t bindings;
	uintptr_t overrides;
	uintptr_t overridesAlt;
};

struct VFXOverride
{
	unsigned int numBindings;
	uintptr_t bindings;
	uintptr_t overrides;
	uintptr_t overridesAlt;
};

struct WeaponOffsetPatternScaleInfo
{
	int numPatternScales;
	uintptr_t patternScales;
};

struct AdvancedIdleSettings
{
	bool useAdvancedIdleSettings;
	bool useRandomPointsAlgorithm;
	float breathGaspScaleOverride;
	float idleSwaySetting1_HipBulletDirScale;
	float idleSwaySetting1_HipIdleSpeed;
	float idleSwaySetting1_HipWeaponMagnitudeX;
	float idleSwaySetting1_HipWeaponMagnitudeY;
	float idleSwaySetting1_HipWeaponMagnitudeZ;
	float idleSwaySetting1_HipWeaponMagnitudeF;
	float idleSwaySetting1_HipWeaponRotationOffset;
	float idleSwaySetting1_HipViewMagnitudeX;
	float idleSwaySetting1_HipViewMagnitudeY;
	float idleSwaySetting1_AdsBulletDirScale;
	float idleSwaySetting1_AdsIdleSpeed;
	float idleSwaySetting1_AdsWeaponMagnitudeX;
	float idleSwaySetting1_AdsWeaponMagnitudeY;
	float idleSwaySetting1_AdsWeaponMagnitudeZ;
	float idleSwaySetting1_AdsWeaponMagnitudeF;
	float idleSwaySetting1_AdsWeaponRotationOffset;
	float idleSwaySetting1_AdsViewMagnitudeX;
	float idleSwaySetting1_AdsViewMagnitudeY;
	float idleSwaySetting2_HipBulletDirScale;
	float idleSwaySetting2_HipIdleSpeed;
	float idleSwaySetting2_HipWeaponMagnitudeX;
	float idleSwaySetting2_HipWeaponMagnitudeY;
	float idleSwaySetting2_HipWeaponMagnitudeZ;
	float idleSwaySetting2_HipWeaponMagnitudeF;
	float idleSwaySetting2_HipWeaponRotationOffset;
	float idleSwaySetting2_HipViewMagnitudeX;
	float idleSwaySetting2_HipViewMagnitudeY;
	float idleSwaySetting2_AdsBulletDirScale;
	float idleSwaySetting2_AdsIdleSpeed;
	float idleSwaySetting2_AdsWeaponMagnitudeX;
	float idleSwaySetting2_AdsWeaponMagnitudeY;
	float idleSwaySetting2_AdsWeaponMagnitudeZ;
	float idleSwaySetting2_AdsWeaponMagnitudeF;
	float idleSwaySetting2_AdsWeaponRotationOffset;
	float idleSwaySetting2_AdsViewMagnitudeX;
	float idleSwaySetting2_AdsViewMagnitudeY;
};

struct BallisticInfoCalculated
{
	float* distances;
	float zeroingAngle;
	int numDistanceEntries;
};

struct BallisticInfo
{
	float muzzleVelocity;
	float ballisticCoefficient;
	float diameter;
	float mass;
	float gravityFactor;
	float zeroingDistance;
	BallisticInfoCalculated* calculated;
	bool enableBallisticTrajectory;
	int lifeTimeMs;
};

struct FxCombinedDef
{
	const void* /*ParticleSystemDef*/ particleSystemDef;
};

struct TracerDef
{
	const char* name;
	FxCombinedDef effect;
	FxCombinedDef viewmodelEffect;
	unsigned int drawInterval;
	float speed;
	bool drawLegacyTracer;
	bool fadeOverTime;
	float fadeTime;
	Material* material;
	float beamLength;
	float beamWidth;
	float screwRadius;
	float screwDist;
	vec4_t colors[5];
};

struct LaserDef
{
	const char* name;
	Material* laserMaterial;
	Material* laserLightMaterial;
	bool ownerOnly;
	bool nightvisionOnly;
	float range;
	float radius;
	float endOffsetViewmodel;
	float endOffsetOther;
	float flarePct;
	FxCombinedDef beamEffect;
	FxCombinedDef laserEndEffect;
	bool clientCollision;
	vec4_t color;
	vec4_t hdrColorScale;
	bool laserLight;
	bool laserLightNvgOnly;
	float laserLightRadius;
	float laserLightBeginOffset;
	float laserLightEndOffset;
	float laserLightBodyTweak;
	vec4_t laserLightColor;
	vec4_t laserLightHdrColorScale;
	float range_alt;
	float radius_alt;
	float laserLightRadius_alt;
	float flarePct_alt;
};


struct SurfaceFxTable
{
	const char* name;
	void* /*SurfaceFxEntry*/ table;
	int numTableEntry;
	unsigned __int8* mapPoolBuffer;
	int mapPoolBufferSize;
};

struct RawFile
{
	const char* name;
	unsigned int compressedLen;
	unsigned int len;
	const char* buffer;
};

struct ScriptFile
{
	const char* name;
	int compressedLen;
	int len;
	int bytecodeLen;
	const char* buffer;
	unsigned __int8* bytecode;
};

struct ScriptDebugData
{
	const char* name;
	unsigned int nameCRC;
	unsigned int profileStringCount;
	void* /*ScriptDebugDataProfileString*/ profileStrings;
};

struct StringTable
{
	const char* name;
	int columnCount;
	int rowCount;
	int uniqueCellCount;
	unsigned __int16* cellIndices;
	int* hashes;
	const char** strings;
};

struct LeaderboardDef
{
	const char* name;
	int id;
	int sourceLbId;
	int sourceLbWidth;
	int columnCount;
	int xpColId;
	int prestigeColId;
	void* /*LbColumnDef*/ columns;
	int /*LbUpdateType*/ updateType;
	int trackTypes;
	int rankColIdX;
	int rankColIdY;
};

struct __declspec(align(8)) VirtualLeaderboardDef
{
	const char* name;
	const char* sourceName;
	int id;
	int sourceId;
	void* /*LbVrColumnDef*/ columns;
	int columnCount;
	int rankColIdX;
	int rankColIdY;
};

struct DDLFile
{
	char* name;
	struct DDLDef* ddlDef;
};

struct SndAliasLookup
{
	const char* name;
};

struct __declspec(align(8)) VehiclePhysicsSoundGroup
{
	SndAliasLookup alias;
	float threshold;
	float vmin;
	float vmax;
	float pmin;
	float pmax;
};

struct __declspec(align(8)) VehiclePhysicsVfxGroup
{
	void* /*FootstepVFX*/ surfaceEffects;
	float threshold;
	float range0;
	float range1;
};


struct VehiclePhysicsDef
{
	int physicsEnabled;
	int /*VehiclePhysicsNetcodeType*/ physics_netcodeType;
	char /*VehiclePhysicsGameProfile*/ physics_gameProfile;
	int /*VehiclePhysicsAnimProfile*/ physics_animProfile;
	int physics_numWheels;
	bool physics_axleRigidBodies;
	float physics_axleBodyPadding;
	int physics_axleBodySides;
	scr_string_t physics_wheelBones[12];
	float physics_wheelRadius;
	float physics_suspStiffness;
	float physics_suspDamping;
	float physics_suspNoiseAmp;
	float physics_frontalSuspension;
	float physics_ackermannRatio;
	vec3_t physics_hardPointOffset;
	vec3_t physics_comOffset;
	vec4_t physics_massFactorContact;
	vec4_t physics_inertiaDiagonal;
	float physics_extraGravityFactor;
	float physics_extraGravityFactorAir;
	float physics_camFovDelta;
	float physics_camPitchBase;
	float physics_camPitchDynamic;
	float physics_camRangeAdd;
	float physics_steeringFactor;
	float physics_steeringForce;
	float physics_steeringMaxYawSpeed;
	float physics_steeringOffsetPoint;
	float physics_steeringOffsetPointUp;
	float physics_steeringReturnSpeed;
	float physics_steeringChangeDirSpeed;
	float physics_steeringHandbrake;
	float physics_steeringSpeed;
	float physics_steeringSpeedIncrease;
	float physics_engineOffsetPoint;
	float physics_engineReductionOnHB;
	float physics_rollingFriction;
	float physics_lateralFriction;
	float physics_frictionBase;
	float physics_frictionRecoverSpeedTgt;
	float physics_frictionFwRedirect;
	float physics_frictionLost;
	float physics_frictionHandbrake;
	float physics_frictionSpeedToBlock;
	float physics_decel;
	float physics_minSpeed;
	bool physics_stabilizeRoll;
	bool physics_stabilizePitch;
	bool physics_contentsAsMissile;
	bool physics_pitchInversion;
	unsigned int physics_controlMode;
	float physics_timeAfterColl;
	int physics_cycleCamButton;
	int physics_boostButton;
	float physics_boostSpeed;
	float physics_rcpBoostAccel;
	float physics_rcpBoostDecel;
	bool physics_holdToBoost;
	SndAliasLookup physics_rcpBoostSound;
	vec3_t physics_rcpBoostShakeCam;
	bool physics_rcpUseChangeDirLogic;
	bool physics_rcpUseChangeDirLogicPitch;
	bool physics_rcpUseRollForYawSpeed;
	float physics_rcpOvershootProtection;
	float physics_rcpPitchTurnSpeed;
	float physics_rcpPitchChangeDirFactor;
	float physics_rcpPitchLerpSpeed;
	float physics_rcpPitchLerpSpeedChangeDir;
	float physics_rcpPitchLerpSpeedReturning;
	float physics_rcpPitchMaxAngle;
	float physics_rcpYawTurnSpeed;
	float physics_rcpYawChangeDirFactor;
	float physics_rcpYawLerpSpeed;
	float physics_rcpYawLerpSpeedChangeDir;
	float physics_rcpYawLerpSpeedReturning;
	float physics_rcpRollTurnSpeed;
	float physics_rcpRollLerpSpeedSteering;
	float physics_rcpRollLerpSpeedChangeDir;
	float physics_rcpRollLerpSpeedReturning;
	float physics_rcpRollMaxAngle;
	float physics_rcpAccelGoingDown;
	float physics_rcpDecelGoingUp;
	float physics_rcpTraceAhead;
	bool physics_rcpCam1stAttachToTagPlayer;
	vec2_t physics_rcpCam1stNoiseScale;
	float physics_rcpCam1stRollSpeed;
	float physics_rcpCam1stRollPercentage;
	float physics_comAdjustThreshold;
	float physics_comAdjustVertDisp;
	float physics_playersWeightFactor;
	float physics_timeToAcceptInputOnStart;
	float physics_viewDirectionHelp;
	float physics_stabilizePitchSpeed;
	float physics_stabilizeRollSpeed;
	int /*VehicleWheelSpinBoneType*/ spinWheelBones;
	float spinWheelAngleOffset;
	int treads_enabled;
	int treads_boneCount;
	scr_string_t treads_firstBones[2];
	float frictionBraking;
	float suspensionTravel;
	float maxSteeringAngle;
	float steeringLerp;
	float minSteeringScale;
	float minSteeringSpeed;
	int disableWheelsTurning;
	int disableWheelsSpinning;
	float minimumWheelCastFraction;
	float handbrakeThreshold;
	float minimumJoltForNotify;
	float pathConstraintStrengthFwd;
	float pathConstraintStrengthSide;
	float pathConstraintDampFwd;
	float pathConstraintDampSide;
	float crashPointOffsetFwd;
	float crashPointOffsetUp;
	float crashImpulseSide;
	float crashImpulseUp;
	float wreckedMassScale;
	VehiclePhysicsSoundGroup sndImpactHard;
	float sndImpactExp;
	VehiclePhysicsSoundGroup sndImpactLight;
	VehiclePhysicsSoundGroup sndDrivingFast;
	VehiclePhysicsSoundGroup sndDrivingSlow;
	VehiclePhysicsSoundGroup sndSuspension;
	VehiclePhysicsSoundGroup sndBrakingHard;
	VehiclePhysicsSoundGroup sndBrakingLight;
	VehiclePhysicsSoundGroup sndDrifting;
	VehiclePhysicsSoundGroup sndSkidding;
	VehiclePhysicsSoundGroup sndDlc1;
	VehiclePhysicsSoundGroup sndDlc2;
	VehiclePhysicsSoundGroup sndDlc3;
	VehiclePhysicsSoundGroup sndDlc4;
	VehiclePhysicsVfxGroup vfxImpactHard;
	VehiclePhysicsVfxGroup vfxImpactLight;
	VehiclePhysicsVfxGroup vfxDrivingFast;
	VehiclePhysicsVfxGroup vfxDrivingSlow;
	VehiclePhysicsVfxGroup vfxBrakingHard;
	VehiclePhysicsVfxGroup vfxBrakingLight;
	VehiclePhysicsVfxGroup vfxDrifting;
	VehiclePhysicsVfxGroup vfxSkidding;
	VehiclePhysicsVfxGroup vfxDrivingFlatFast;
	VehiclePhysicsVfxGroup vfxDrivingFlatSlow;
	VehiclePhysicsVfxGroup vfxDlc3;
	VehiclePhysicsVfxGroup vfxDlc4;
};

struct SpaceshipAnimParts
{
	void* /*XAnimParts*/ anim[2];
};

struct VehiclePhysicsRevModifier
{
	float skidSndContrib;
	float noiseAmpl;
	float sinewaveFreq;
	float sinewaveAmpl;
	float rpmMax;
	float rpmScale;
	float rpmSpeedEmaSamples;
	float inclinedThreshold;
	int gearCount;
	float inclContrib;
	float maxSpinSpeedRPMFw;
	float maxSpinSpeedRPMBw;
};

struct VehicleDef
{
	const char* name;
	char type;
	const char* useHintString;
	int health;
	int inputBindingSet;
	int hitClientScriptables;
	int hitRemoteControllers;
	int accurateShapeOverlap;
	int numDoors;
	float maxDoorAngle;
	scr_string_t doorBones[4];
	CameraDef* cameraDef;
	CameraDef* killCamDef;
	float texScrollScale;
	float topSpeed;
	float accel;
	float rotRate;
	float rotAccel;
	float maxBodyPitch;
	float maxBodyRoll;
	float rangeForBoneControllers;
	float fakeBodyAccelPitch;
	float fakeBodyAccelRoll;
	float fakeBodyVelPitch;
	float fakeBodyVelRoll;
	float fakeBodySideVelPitch;
	float fakeBodyPitchStrength;
	float fakeBodyRollStrength;
	float fakeBodyPitchDampening;
	float fakeBodyRollDampening;
	float fakeBodyBoatRockingAmplitude;
	float fakeBodyBoatRockingPeriod;
	float fakeBodyBoatRockingRotationPeriod;
	float fakeBodyBoatRockingFadeoutSpeed;
	float boatBouncingMinForce;
	float boatBouncingMaxForce;
	float boatBouncingRate;
	float boatBouncingFadeinSpeed;
	float boatBouncingFadeoutSteeringAngle;
	float collisionDamage;
	float collisionSpeed;
	bool collisionDamageIgnoresImpactAngle;
	vec3_t killcamOffset;
	int playerProtected;
	int bulletDamage;
	int armorPiercingDamage;
	int grenadeDamage;
	int projectileDamage;
	int projectileSplashDamage;
	int heavyExplosiveDamage;
	VehiclePhysicsDef vehiclePhysicsDef;
	int vehHelicopterLockAltitude;
	int vehHelicopterOffsetFromMesh;
	float vehHelicopterAltitudeOffset;
	float vehHelicopterPitchOffset;
	float vehHelicopterBoundsRadius;
	float vehHelicopterMaxSpeed;
	float vehHelicopterMaxSpeedVertical;
	float vehHelicopterMaxAccel;
	float vehHelicopterMaxAccelVertical;
	float vehHelicopterDecelerationFwd;
	float vehHelicopterDecelerationSide;
	float vehHelicopterDecelerationUp;
	float vehHelicopterMaxYawRate;
	float vehHelicopterMaxYawAccel;
	float vehHelicopterTiltFromVelocity;
	float vehHelicopterTiltFromControllerAxes;
	float vehHelicopterTiltFromAcceleration;
	float vehHelicopterTiltFromDeceleration;
	float vehHelicopterTiltFromFwdAndYaw_VelAtMaxTilt;
	float vehHelicopterTiltFromFwdAndYaw;
	float vehHelicopterTiltMomentum;
	float vehHelicopterTiltSpeed;
	float vehHelicopterMaxPitch;
	float vehHelicopterMaxRoll;
	float vehHelicopterHoverSpeedThreshold;
	float vehHelicopterJitterJerkyness;
	float vehHelicopterLookaheadTime;
	int vehHelicopterSoftCollisions;
	int vehHelicopterUseGroundFX;
	FxCombinedDef vehHelicopterGroundFx;
	FxCombinedDef vehHelicopterGroundWaterFx;
	float vehHelicopterGroundFxDefaultRepeatRate;
	float vehHelicopterGroundFxSlowestRepeatRate;
	float vehHelicopterGroundFxFastestRepeatRate;
	float vehHelicopterGroundFxMinGroundDist;
	float vehHelicopterGroundFxMaxGroundDist;
	float vehRotorMaxVelocity;
	float vehRotorMaxAccel;
	float vehRotorAccelTiltBlend;
	float vehRotorMaxVehicleSpin;
	float vehRotorMaxAngle;
	float vehRotorSpinSpeed;
	float vehRotorSpinVerticalSpeedThreshold;
	float vehRotorMaxSpinAddition;
	float ssWeaponSwitchDelaySeconds;
	float ssWeaponRaiseDelaySeconds;
	vec3_t ssFlyMaxSpeedMph;
	vec3_t ssFlyMaxAccelerationMphps;
	vec3_t ssFlyMaxCounterAccelerationMphps;
	vec3_t ssFlyFrictionMphps;
	vec3_t ssFlyJukeSpeedMph;
	vec3_t ssHoverMaxSpeedMph;
	vec3_t ssHoverMaxAccelerationMphps;
	vec3_t ssHoverMaxCounterAccelerationMphps;
	vec3_t ssHoverFrictionMphps;
	vec3_t ssHoverJukeSpeedMph;
	float ssFlyJukeRampTime;
	float ssHoverJukeRampTime;
	float ssBrakingFrictionMphps;
	float ssFlyRedirectVelocityScale;
	float ssFlySlowRedirectVelocityScale;
	float ssHoverRedirectVelocityScale;
	float ssFlyMinSpeedRatio;
	bool ssProjectVelocityDesiresToXY;
	bool ssEnforceMinGroundClearance;
	float ssMinGroundClearanceHeight;
	float ssMinGroundClearanceLiftForce;
	bool ssTerrainModeMovement;
	float ssTerrainModeGravity;
	float ssTerrainModeFlyTime;
	vec2_t ssAimOffsetClampDeg;
	vec2_t ssPitchUpSoftLimitDeg;
	vec2_t ssPitchDownSoftLimitDeg;
	float ssClutchPitchSpeedScale;
	vec2_t ssFlyAimSpeedDps;
	vec2_t ssFlySlowAimSpeedDps;
	vec2_t ssHoverAimSpeedDps;
	vec2_t ssFlyAimDriftScale;
	vec2_t ssFlySlowAimDriftScale;
	vec2_t ssHoverAimDriftScale;
	float ssMinSpringOscillation;
	float ssMaxSpringOscillation;
	float ssMinSpringStrength;
	float ssMaxSpringStrength;
	float ssMinSpringAngSpeed;
	float ssMaxSpringAngSpeed;
	float ssSpringControllerContribution;
	float ssTiltSpringOscillation;
	float ssTiltSpringStrength;
	float ssTiltSpringAngleContribution;
	int ssADSToLockOn;
	float ssLockOnMinAngle;
	float ssLockOnMaxAngle;
	float ssPilotAssistNoLockAimScale;
	float ssPilotAssistNoLockMinAngle;
	float ssPilotAssistNoLockMaxAngle;
	float ssPilotAssistAimScale;
	float ssPilotAssistMinAngle;
	float ssPilotAssistMaxAngle;
	vec2_t ssAutoLevelStrengthHover;
	vec2_t ssAutoLevelStrengthFly;
	bool ssIsRollRightStick;
	float ssRollMaxSpeedDps;
	float ssBoostSpeedScale;
	float ssBoostThrustScale;
	bool ssEnableBoostToFly;
	float ssBoostTime;
	float ssBoostRegenTime;
	float ssBoostRegenStallTime;
	float ssBoostMinThresholdRatio;
	float ssCollisionRadiusI;
	float ssCylinderHeightI;
	bool ssUseCylinder;
	bool ssUsePlayerClip;
	float ssCollisionOffsetI;
	float ssCollisionHardThresholdMph;
	float ssFOVFlyOffsetDeg;
	float ssFOVFlyBoostOffsetDeg;
	float ssFOVHoverOffsetDeg;
	float ssZoomBlendSpeedDps;
	float ssZoomMaxAngle;
	float ssZoomMinDistI;
	float ssZoomIdealDistI;
	float ssZoomMaxDistI;
	bool ssShowPilotViewmodel;
	float ssCameraAnimScale;
	vec2_t ssFlyTiltShipAngles;
	float ssFlyTiltCameraScale;
	vec2_t ssHoverTiltShipAngles;
	float ssHoverTiltCameraScale;
	float ssMotionIdleRateMinSpeed;
	float ssMotionIdleRateMaxSpeed;
	float ssMotionIdleMinRate;
	float ssMotionIdleMaxRate;
	scr_string_t ssAnimTree;
	SpaceshipAnimParts ssAnimParts[33];
	FxCombinedDef ssThrustFxLoop;
	FxCombinedDef ssJukeFx;
	RumbleInfo* ssIdleRumble;
	RumbleInfo* ssSmallRumble;
	RumbleInfo* ssMedRumble;
	RumbleInfo* ssLargeRumble;
	SndAliasLookup rattleLoop;
	float rattleLoopMinVolume;
	float rattleLoopMaxVolume;
	SndAliasLookup airLoop;
	float airLoopMinVolume;
	float airLoopMaxVolume;
	SndAliasLookup engineLoop;
	float engineLoopMinVolume;
	float engineLoopMaxVolume;
	float engineLoopMinPitch;
	float engineLoopMaxPitch;
	SndAliasLookup hoverLoop;
	float hoverLoopMinVolume;
	float hoverLoopMaxVolume;
	float hoverLoopMinPitch;
	float hoverLoopMaxPitch;
	SndAliasLookup boostLoop;
	float boostLoopMaxVolume;
	float boostLoopMaxPitch;
	SndAliasLookup ssThrustLoop;
	float ssThrustLoopMaxVolume;
	float ssThrustLoopMaxPitch;
	SndAliasLookup boostStart;
	SndAliasLookup boostStop;
	SndAliasLookup boostDepleted;
	SndAliasLookup boostUnavailable;
	SndAliasLookup jukeLeft;
	SndAliasLookup jukeRight;
	SndAliasLookup jukeUpDown;
	SndAliasLookup jukeBack;
	SndAliasLookup jukeFront;
	SndAliasLookup flightOn;
	SndAliasLookup flightOff;
	float flightOnTimer;
	float flightOffTimer;
	SndAliasLookup hardCollision;
	SndAliasLookup softCollision;
	int camLookEnabled;
	int camRelativeControl;
	int camRemoteDrive;
	float camLerp;
	float camHeight;
	float camRadius;
	float camPitchInfluence;
	float camYawInfluence;
	float camRollInfluence;
	float camFovIncrease;
	float camFovOffset;
	float camFovSpeed;
	float camReturnSpeed;
	float camReturnLerp;
	float camVehicleAnglePitchRate;
	float camVehicleAngleYawRate;
	float camVehicleAngleRollRate;
	int vehCam_UseGDT;
	float vehCam_anglesPitch;
	float vehCam_anglesYaw;
	float vehCam_anglesRoll;
	float vehCam_offsetX;
	float vehCam_offsetY;
	float vehCam_offsetZ;
	float vehCam_radius;
	float vehCam_speedInfluence;
	float vehCam_pitchTurnRate;
	float vehCam_pitchClamp;
	float vehCam_yawTurnRate;
	float vehCam_yawClamp;
	int /*VehCamZOffsetMode*/ vehCam_zOffsetMode;
	float vehCam_anglesPitch3P;
	float vehCam_anglesYaw3P;
	float vehCam_anglesRoll3P;
	float vehCam_offsetX3P;
	float vehCam_offsetY3P;
	float vehCam_offsetZ3P;
	float vehCam_radius3P;
	float vehCam_speedInfluence3P;
	float vehCam_pitchTurnRate3P;
	float vehCam_pitchClamp3P;
	float vehCam_yawTurnRate3P;
	float vehCam_yawClamp3P;
	int /*VehCamZOffsetMode*/ vehCam_zOffsetMode3P;
	const char* turretWeaponName;
	void* /*WeaponCompleteDef*/ turretWeapon;
	float turretHorizSpanLeft;
	float turretHorizSpanRight;
	float turretVertSpanUp;
	float turretVertSpanDown;
	float turretHorizResistLeft;
	float turretHorizResistRight;
	float turretVertResistUp;
	float turretVertResistDown;
	float turretRotRate;
	int /*VehicleTurretFireType*/ turretFireType;
	SndAliasLookup turretSpinSnd;
	SndAliasLookup turretStopSnd;
	int trophyEnabled;
	float trophyRadius;
	float trophyInactiveRadius;
	int trophyAmmoCount;
	float trophyReloadTime;
	scr_string_t trophyTags[4];
	FxCombinedDef trophyExplodeFx;
	FxCombinedDef trophyFlashFx;
	Material* compassFriendlyIcon;
	Material* compassEnemyIcon;
	Material* compassFriendlyAltIcon;
	Material* compassEnemyAltIcon;
	int compassIconWidth;
	int compassIconHeight;
	void* /*SndBankTransient*/ detailSoundBankNPC;
	void* /*SndBankTransient*/ detailSoundBankPlayer;
	SndAliasLookup idleLowSnd;
	SndAliasLookup idleHighSnd;
	SndAliasLookup engineLowSnd;
	SndAliasLookup engineHighSnd;
	SndAliasLookup fallbackIdleLowSnd;
	SndAliasLookup fallbackIdleHighSnd;
	SndAliasLookup fallbackEngineLowSnd;
	SndAliasLookup fallbackEngineHighSnd;
	float engineSndSpeed;
	scr_string_t audioOriginTag;
	SndAliasLookup mainRotorLowRpmSnd;
	SndAliasLookup mainRotorOperatingRpmSnd;
	SndAliasLookup mainRotorOperatingEffortSnd;
	SndAliasLookup tailRotorLowRpmSnd;
	SndAliasLookup tailRotorOperatingRpmSnd;
	SndAliasLookup tailRotorOperatingEffortSndLeft;
	SndAliasLookup tailRotorOperatingEffortSndRight;
	SndAliasLookup physicsHeliStartup;
	SndAliasLookup physicsHeliShutdown;
	SndAliasLookup turbineLowRpmSnd;
	SndAliasLookup turbineOperatingRpmSnd;
	bool useRevAudioSettings;
	SndAliasLookup revLowFidelityMod;
	SndAliasLookup revHighFidelityMod;
	float revPlayerPriority;
	VehiclePhysicsRevModifier revModifier;
	SndAliasLookup engineStartUpSnd;
	int engineStartUpLength;
	SndAliasLookup engineShutdownSnd;
	SndAliasLookup engineIdleSnd;
	SndAliasLookup engineSustainSnd;
	SndAliasLookup engineRampUpSnd;
	int engineRampUpLength;
	SndAliasLookup engineRampDownSnd;
	int engineRampDownLength;
	SndAliasLookup suspensionSoftSnd;
	float suspensionSoftCompression;
	SndAliasLookup suspensionHardSnd;
	float suspensionHardCompression;
	SndAliasLookup collisionSnd;
	float collisionBlendSpeed;
	SndAliasLookup speedSnd;
	float speedSndBlendSpeed;
	const char* surfaceSndName;
	float surfaceSndBlendSpeed;
	float slideVolume;
	float slideBlendSpeed;
	float inAirPitch;
	const char* soundTriggerOverrideZone;
	bool soundTriggerOverrideReverb;
	bool soundTriggerOverrideMix;
	bool soundTriggerOverrideFilter;
	bool soundTriggerOverrideOcclusion;
	bool soundTriggerOverrideAmbient;
	bool soundTriggerOverrideAmbientEvents;
	bool soundTriggerOverrideADSR;
	int visionBlendTime;
	const char* globalVisionSettings;
	const char* mapVisionSettings;
	const char* luiCrosshairWidget;
	float dlcFloat[8];
};

struct MapTriggers
{
	unsigned int count;
	void* /*TriggerModel*/ models;
	unsigned int hullCount;
	void* /*TriggerHull*/ hulls;
	unsigned int slabCount;
	void* /*TriggerSlab*/ slabs;
	unsigned int windingCount;
	void* /*TriggerWinding*/ windings;
	unsigned int windingPointCount;
	void* /*TriggerWindingPoint*/ windingPoints;
};


struct AddonMapEnts
{
	const char* name;
	char* entityString;
	int numEntityChars;
	MapTriggers trigger;
	unsigned int numSubModels;
	void* /*cmodel_t*/ cmodels;
	void* /*GfxBrushModel*/ models;
};

struct NetConstStrings
{
	const char* name;
	int /*NetConstStringType*/ stringType;
	int /*NetConstStringSource*/ sourceType;
	unsigned int flags;
	unsigned int entryCount;
	const char** stringList;
};

struct LuaFile
{
	const char* name;
	int len;
	unsigned __int8 strippingType;
	const unsigned __int8* buffer;
};


struct __declspec(align(8)) ScriptableDef
{
	const char* name;
	ScriptableDef* nextScriptableDef;
	int flags;
	unsigned int numParts;
	void* /*ScriptablePartDef*/ parts;
	unsigned int maxNumDynEntsRequired;
	unsigned int partCount;
	unsigned int serverInstancedPartCount;
	unsigned int serverControlledPartCount;
	unsigned int maxNumDynEntPartsBase;
	unsigned int maxNumDynEntPartsForSpawning;
	unsigned __int16 eventStreamSizeRequiredServer;
	unsigned __int16 eventStreamSizeRequiredClient;
	unsigned int usablePartCount;
	unsigned int ffMemCost;
	scr_string_t animationTreeName;
	void* /*XAnim_s*/ animationTreeDef[2];
	float viewRadius;
	bool networkLODRangeOverride;
	float networkLODRangeOverrideDistance;
	unsigned int numXModels;
	XModel** models;
	char /*DynEntitySpatialActivationMode*/ spatialActivationMode;
};

struct EquipSoundSetMoveTypes
{
	void* /*EquipmentSoundSet*/ soundSets;
};

struct EquipmentSoundSet
{
	void* /*SndAliasList*/ soundPLR;
	void* /*SndAliasList*/ soundNPC;
};

struct EquipSoundSetMeleeWorld
{
	EquipmentSoundSet soundSets[8][3][2][4];
};

struct EquipmentSoundTable
{
	const char* szName;
	unsigned int numClothTypes;
	unsigned int numWeaponRattleTypes;
	unsigned int numMoveTypes;
	unsigned int numStanceTypes;
	void* /*EquipmentClothData*/ clothTypes;
	void* /*EquipmentWeaponRattleData*/ weaponRattleTypes;
	void* /*EquipmentChanceRattleTypes*/ chancesPLR;
	void* /*EquipmentChanceRattleTypes*/ chancesNPC;
	void* /*EquipSoundSetFootsteps*/ mvmtClothFootstepSoundSets;
	void* /*EquipSoundSetFootsteps*/ mvmtClothFootstepCeilingSoundSets;
	void* /*EquipSoundSetMoveLeadTypes*/ mvmtClothFoleySoundSets;
	void* /*EquipSoundSetMoveTypes*/ mvmtRattleSoundSets;
	EquipSoundSetMoveTypes mvmtAccentSoundSets;
	void* /*EquipSoundSetMantleTypes*/ mvmtMantleSoundSets;
	void* /*EquipSoundSetStanceTypes*/ mvmtStanceSoundSets;
	void* /*EquipSoundSetMeleeVM*/ meleeAttackVMSoundSets;
	void* /*EquipSoundSetMeleeWM*/ meleeAttackWMSoundSets;
	void* /*EquipSoundSetMeleeWM*/ meleeCharacterSoundSets;
	EquipSoundSetMeleeWorld meleeWorldSoundSets;
};

struct ExtentBounds
{
	vec3_t mins;
	vec3_t maxs;
};

struct VectorField
{
	const char* name;
	void* /*VectorSubField*/ subFields;
	ExtentBounds worldBounds;
	vec3_t localOrigin;
	unsigned int numSubFields;
	unsigned int pad[2];
};

struct FxParticleSimAnimationHeader
{
	float playbackRate;
	float duration;
	unsigned int frameCount;
	float minX;
	float minY;
	float minZ;
	float boundsXDelta;
	float boundsYDelta;
	float boundsZDelta;
	float maxWidth;
	float maxHeight;
	unsigned int colorTableSize;
	unsigned int particleDataCount;
	unsigned int maxActiveParticles;
	bool evalVisStatePerParticle;
	bool sortParticlesAtRuntime;
	bool hasOrientation3D;
	bool hasIndex;
};

struct FxParticleSimAnimation
{
	const char* name;
	Material* material;
	FxParticleSimAnimationHeader header;
	void* /*FxParticleSimAnimationParticleData*/ particleData;
	void* /*FxParticleSimAnimationParticleDataOrientation3D*/ particleDataOrientation3D;
	void* /*FxParticleSimAnimationParticleDataIndex*/ particleDataIndex;
	void* /*FxParticleSimAnimationFrame*/ frames;
	vec4_t* colorTable;
};

struct StreamingInfo {
	char __padding[0x48];
};

struct TTFDef
{
	const char* name;
	int fileLen;
	const char* file;
	void* ftFace;
};

struct SuitDef
{
	const char* name;
	float cam_minVelocityForFovIncrease;
	float cam_maxVelocityForFovIncrease;
	float cam_velocityToDecreaseFov;
	float cam_fovIncreaseAtMaxVelocity;
	float cam_oneOverFovEaseInTimeMs;
	float cam_oneOverFovEaseOutTimeMs;
	CameraDef* cam_helmetCam;
	bool cam_drawHelmet;
	vec3_t cam_camtoHelmetOffsetOrigin;
	vec3_t cam_camtoHelmetOffsetAngles;
	bool enableIKOverride;
	float player_globalAccelScale;
	float player_crouchSpeedScale;
	float player_proneSpeedScale;
	float player_lastStandCrawlSpeedScale;
	float player_sprintSpeedScale;
	bool player_sprintUnlimited;
	float player_viewBobScale;
	bool jump_slowdownEnable;
	float jump_height;
	float sprintLeap_height;
	float sprintLeap_forwardVelocityScale;
	int sprintLeap_minSprintTimeMs;
	float doubleJump_accel;
	float doubleJump_speed;
	float doubleJump_speedNoBoost;
	float doubleJump_frictionMin;
	float doubleJump_frictionMax;
	float doubleJump_initialUpBoostAccel;
	float doubleJump_standardUpBoostAccel;
	float doubleJump_energyNeededForInitialUpBoost;
	float doubleJump_energyNeededForStandardUpBoost;
	float doubleJump_maxUpwardsVelocity;
	bool doubleJump_enableMinZVelocity;
	float doubleJump_minZVelocity;
	float doubleJump_energyInitialCost;
	float doubleJump_boostUpEnergyUseRate;
	float doubleJump_energyUsePerButtonPress;
	bool doubleJump_hoverOnly;
	float doubleJump_maxViewPitchDip;
	float doubleJump_maxViewBackwardsPitchDip;
	float doubleJump_maxViewRoll;
	float doubleJump_oneOverEaseInTime;
	float doubleJump_oneOverEaseOutTimeMs;
	bool doubleJump_alwaysDipView;
	SndAliasLookup doubleJump_sound;
	SndAliasLookup doubleJump_soundPlayer;
	SndAliasLookup doubleJump_releaseSound;
	SndAliasLookup doubleJump_releaseSoundPlayer;
	float slide_strafe_speed_scale;
	int slide_sprint_penalty_ms;
	bool slide_allow_firing;
	bool slide_allow_ads;
	bool slide_allow_weapon_switch;
	float slide_jump_speed_scale;
	float slide_energy_cost_ratio;
	int slide_max_time_ms;
	int slide_max_time_reduced_ms;
	int slide_max_time_base_ms;
	int slide_inTimeMs;
	float slide_inMaxSpeedScale;
	float slide_inAcceleration;
	float slide_frictionScaleNormal;
	float slide_frictionScaleDownhill;
	float slide_frictionScaleUphill;
	float slide_frictionScaleBlocked;
	int slide_gestureOutTimeForJumpMs;
	int slide_sprintDelayMs;
	bool slide_disableProneTransition;
	int slide_proneDelayMs;
	int slide_proneButtonCheckTimeMs;
	int slide_outTimeMs;
	float slide_outFrictionScaleStart;
	float slide_outFrictionScaleFinish;
	float slide_outSpeedScaleStart;
	float slide_outSpeedScaleFinish;
	int slide_inAirTimeMs;
	float slide_inAirFrictionScaleStart;
	float slide_inAirFrictionScaleFinish;
	int slide_viewBlendInTimeMs;
	int slide_viewBlendOutTimeMs;
	float wallRun_minZVel;
	float wallRun_minTriggerSpeed;
	float wallRun_minMaintainSpeed;
	int wallRun_delayPeriodMs;
	float wallRun_minJumpHeight;
	int wallRun_maxTimeMs;
	int wallRun_fallStageTimeMs;
	float wallRun_maxHeight;
	float wallRun_jumpHeight;
	float wallRun_jumpVelocity;
	float wallRun_frictionScale;
	float wallRun_speedScale;
	float wallRun_speedScaleADS;
	float wallRun_energyInitialCost;
	float wallRun_energyChangePerSecond;
	float ladder_anchorOffset;
	float ladder_anchorOffsetWM;
	float ladder_handDistance;
	int /*SuitAnimType*/ suitAnimType;
	bool isMovementCameraIndependent;
	void* /*SuitAnimPackage*/ animPackage;
	void* /*SuitAnimPackage*/ animPackageL;
	void* /*SuitAnimPackage*/ animPackageR;
	void* /*SuitAnimPackage*/ animPackageRelaxed;
	void* /*SuitAnimPackage*/ animPackageSafe;
	void* /*ASM*/ asmAsset;
	void* /*Animset*/ animsetAsset;
	unsigned __int8 facialAnimType;
	int /*SuitBodyAnimType*/ bodyAnimType;
	ScriptableDef* scriptableDef;
	int viewheight_stand;
	int viewheight_crouch;
	int viewheight_prone;
	int viewheight_laststand;
	int viewheight_dead;
	int viewheight_swim;
	int viewheight_slide;
	int viewheight_sprint;
	int bounds_radius;
	int bounds_height_stand;
	int bounds_height_crouch;
	int bounds_height_prone;
	Bounds bounds_stand;
	Bounds bounds_crouch;
	Bounds bounds_prone;
	int radialMotionBlur_interpTimeIn;
	int radialMotionBlur_interpTimeOut;
	float radialMotionBlur_sprintMinRadius;
	float radialMotionBlur_sprintMaxRadius;
	float radialMotionBlur_sprintMinStrength;
	float radialMotionBlur_sprintMaxStrength;
	float radialMotionBlur_slideMinRadius;
	float radialMotionBlur_slideMaxRadius;
	float radialMotionBlur_slideMinStrength;
	float radialMotionBlur_slideMaxStrength;
	float radialMotionBlur_doubleJumpMinRadius;
	float radialMotionBlur_doubleJumpMaxRadius;
	float radialMotionBlur_doubleJumpMinStrength;
	float radialMotionBlur_doubleJumpMaxStrength;
	float radialMotionBlur_wallRunMinRadius;
	float radialMotionBlur_wallRunMaxRadius;
	float radialMotionBlur_wallRunMinStrength;
	float radialMotionBlur_wallRunMaxStrength;
	float radialMotionBlur_groundPoundMinRadius;
	float radialMotionBlur_groundPoundMaxRadius;
	float radialMotionBlur_groundPoundMinStrength;
	float radialMotionBlur_groundPoundMaxStrength;
	float radialMotionBlur_rewindMinRadius;
	float radialMotionBlur_rewindMaxRadius;
	float radialMotionBlur_rewindMinStrength;
	float radialMotionBlur_rewindMaxStrength;
	float radialMotionBlur_dodgeMinRadius;
	float radialMotionBlur_dodgeMaxRadius;
	float radialMotionBlur_dodgeMinStrength;
	float radialMotionBlur_dodgeMaxStrength;
	float radialMotionBlur_skydiveMinRadius;
	float radialMotionBlur_skydiveMaxRadius;
	float radialMotionBlur_skydiveMinStrength;
	float radialMotionBlur_skydiveMaxStrength;
	RumbleInfo* groundPound_activationRumble;
	SndAliasLookup groundPound_activationSound;
	SndAliasLookup groundPound_activationSoundPlayer;
	RumbleInfo* groundPound_landingRumble;
	SndAliasLookup groundPound_landingSound;
	SndAliasLookup groundPound_landingSoundPlayer;
	RumbleInfo* landing_rumbleLowHeight;
	RumbleInfo* landing_rumbleMediumHeight;
	RumbleInfo* landing_rumbleHighHeight;
	RumbleInfo* landing_rumbleExtremeHeight;
	float landing_speedScale;
	float footstep_shakeBroadcastRadiusInches;
	int footstep_shakeDurationMs;
	float footstep_shakeAmplitude;
	RumbleInfo* footstep_rumble;
	void* /*FootstepVFX*/ footstepvfx_slide;
	void* /*FootstepVFX*/ footstepvfx_creep_left;
	void* /*FootstepVFX*/ footstepvfx_creep_right;
	void* /*FootstepVFX*/ footstepvfx_walk_left;
	void* /*FootstepVFX*/ footstepvfx_walk_right;
	void* /*FootstepVFX*/ footstepvfx_run_left;
	void* /*FootstepVFX*/ footstepvfx_run_right;
	void* /*FootstepVFX*/ footstepvfx_sprint_left;
	void* /*FootstepVFX*/ footstepvfx_sprint_right;
	float skydive_mass;
	float skydive_gravitatationalAcceleration;
	XModel* skydive_parachuteViewModel;
	XModel* skydive_parachuteWorldModel;
	float skydive_baseJumpMinimumHeight;
	float skydive_baseJumpClearanceRadius;
	float skydive_baseJumpAutoDeployHeight;
	float skydive_baseJumpForceFreefallHeight;
	float skydive_freefallSuperDiveCameraPitch;
	float skydive_freefallSuperDiveStickInput;
	float skydive_freefallSuperDiveFovAdjustDegrees;
	int skydive_freefallSuperDiveFovAdjustInTime;
	int skydive_freefallSuperDiveFovAdjustOutTime;
	void* /*CinematicMotionDef*/ skydive_freefallCinematicMotion;
	float skydive_freefallThrottleTrackSpeed;
	float skydive_freefallAnimTrackSpeedThrottle;
	float skydive_freefallAnimTrackSpeedStrafe;
	float skydive_freefallAnimTrackSpeedYaw;
	float skydive_freefallAnimTrackSpeedPitch;
	float skydive_freefallAnimMinWeight;
	float skydive_freefallAnimMaxWeight;
	float skydive_freefallAnimMinPlayRate;
	float skydive_freefallAnimMaxPlayRate;
	float skydive_freefallAnimSpeedForMinWeight;
	float skydive_freefallAnimSpeedForMaxWeight;
	float skydive_freefallTopGroundSpeed;
	float skydive_freefallMinPitch;
	float skydive_freefallMaxPitch;
	float skydive_freefallPitchSpeed;
	float skydive_freefallYawSpeed;
	float skydive_freefallCrossSectionalArea;
	float skydive_freefallLookHorizForceMin;
	float skydive_freefallLookHorizForceMax;
	RumbleGraph* skydive_freefallLookHorizForceGraph;
	float skydive_freefallStickHorizForceMin;
	float skydive_freefallStickHorizForceMax;
	RumbleGraph* skydive_freefallStickHorizForceGraph;
	float skydive_freefallDragCoefHoriz;
	float skydive_freefallLookHorizDragCoeff;
	RumbleGraph* skydive_freefallLookHorizDragGraph;
	float skydive_freefallStickHorizDragCoeff;
	RumbleGraph* skydive_freefallStickHorizDragGraph;
	float skydive_freefallDragCoefVert;
	float skydive_freefallLookVertDragCoeff;
	RumbleGraph* skydive_freefallLookVertDragGraph;
	float skydive_freefallStickVertDragIncreasePerc;
	RumbleGraph* skydive_freefallStickVertDragIncreaseGraph;
	float skydive_freefallStickVertDragReductionPerc;
	RumbleGraph* skydive_freefallStickVertDragReductionGraph;
	float skydive_freefallStickSidewaysForce;
	float skydive_freefallMaxBrakeForce;
	float skydive_freefallMinTurnMultiplier;
	float skydive_freefallMaxTurnMultiplier;
	RumbleGraph* skydive_freefallTurnMultiplierGraph;
	float skydive_freefallTurnMultiplierMinScale;
	float skydive_freefallTurnMultiplierMaxScale;
	RumbleGraph* skydive_freefallTurnMultiplierPitchGraph;
	SndAliasLookup skydive_freefallAmbientSound;
	float skydive_freefallAmbientSoundGroundSpeedWeight;
	float skydive_freefallAmbientSoundMinVolume;
	float skydive_freefallAmbientSoundMaxVolume;
	float skydive_freefallAmbientSoundMinPitch;
	float skydive_freefallAmbientSoundMaxPitch;
	float skydive_freefallAmbientSoundMinGroundSpeed;
	float skydive_freefallAmbientSoundMaxGroundSpeed;
	float skydive_freefallAmbientSoundMinFallSpeed;
	float skydive_freefallAmbientSoundMaxFallSpeed;
	SndAliasLookup skydive_freefallHighSpeedSound;
	float skydive_freefallHighSpeedSoundGroundSpeedWeight;
	float skydive_freefallHighSpeedSoundMinVolume;
	float skydive_freefallHighSpeedSoundMaxVolume;
	float skydive_freefallHighSpeedSoundMinPitch;
	float skydive_freefallHighSpeedSoundMaxPitch;
	float skydive_freefallHighSpeedSoundMinGroundSpeed;
	float skydive_freefallHighSpeedSoundMaxGroundSpeed;
	float skydive_freefallHighSpeedSoundMinFallSpeed;
	float skydive_freefallHighSpeedSoundMaxFallSpeed;
	float skydive_deployHorizontalDrag;
	float skydive_deployVerticalDrag;
	void* /*CinematicMotionDef*/ skydive_canopyCinematicMotion;
	float skydive_canopyThrottleTrackSpeed;
	float skydive_canopyAnimTrackSpeedThrottle;
	float skydive_canopyAnimTrackSpeedStrafe;
	float skydive_canopyAnimTrackSpeedYaw;
	float skydive_canopyAnimTrackSpeedPitch;
	float skydive_canopyAnimMinWeight;
	float skydive_canopyAnimMaxWeight;
	float skydive_canopyAnimMinPlayRate;
	float skydive_canopyAnimMaxPlayRate;
	float skydive_canopyAnimSpeedForMinWeight;
	float skydive_canopyAnimSpeedForMaxWeight;
	float skydive_canopyTopGroundSpeed;
	float skydive_canopyMinPitch;
	float skydive_canopyMaxPitch;
	float skydive_canopyPitchSpeed;
	float skydive_canopyYawSpeed;
	float skydive_canopyCrossSectionalArea;
	float skydive_canopyLookHorizForceMin;
	float skydive_canopyLookHorizForceMax;
	RumbleGraph* skydive_canopyLookHorizForceGraph;
	float skydive_canopyStickHorizForceMin;
	float skydive_canopyStickHorizForceMax;
	RumbleGraph* skydive_canopyStickHorizForceGraph;
	float skydive_canopyDragCoefHoriz;
	float skydive_canopyLookHorizDragCoeff;
	RumbleGraph* skydive_canopyLookHorizDragGraph;
	float skydive_canopyStickHorizDragCoeff;
	RumbleGraph* skydive_canopyStickHorizDragGraph;
	float skydive_canopyDragCoefVert;
	float skydive_canopyLookVertDragCoeff;
	RumbleGraph* skydive_canopyLookVertDragGraph;
	float skydive_canopyStickVertDragIncreasePerc;
	RumbleGraph* skydive_canopyStickVertDragIncreaseGraph;
	float skydive_canopyStickVertDragReductionPerc;
	RumbleGraph* skydive_canopyStickVertDragReductionGraph;
	float skydive_canopyStickSidewaysForce;
	float skydive_canopyMaxBrakeForce;
	float skydive_canopyMinTurnMultiplier;
	float skydive_canopyMaxTurnMultiplier;
	RumbleGraph* skydive_canopyTurnMultiplierGraph;
	float skydive_canopyTurnMultiplierMinScale;
	float skydive_canopyTurnMultiplierMaxScale;
	RumbleGraph* skydive_canopyTurnMultiplierPitchGraph;
	SndAliasLookup skydive_canopyAmbientSound;
	float skydive_canopyAmbientSoundGroundSpeedWeight;
	float skydive_canopyAmbientSoundMinVolume;
	float skydive_canopyAmbientSoundMaxVolume;
	float skydive_canopyAmbientSoundMinPitch;
	float skydive_canopyAmbientSoundMaxPitch;
	float skydive_canopyAmbientSoundMinGroundSpeed;
	float skydive_canopyAmbientSoundMaxGroundSpeed;
	float skydive_canopyAmbientSoundMinFallSpeed;
	float skydive_canopyAmbientSoundMaxFallSpeed;
	SndAliasLookup skydive_canopyHighSpeedSound;
	float skydive_canopyHighSpeedSoundGroundSpeedWeight;
	float skydive_canopyHighSpeedSoundMinVolume;
	float skydive_canopyHighSpeedSoundMaxVolume;
	float skydive_canopyHighSpeedSoundMinPitch;
	float skydive_canopyHighSpeedSoundMaxPitch;
	float skydive_canopyHighSpeedSoundMinGroundSpeed;
	float skydive_canopyHighSpeedSoundMaxGroundSpeed;
	float skydive_canopyHighSpeedSoundMinFallSpeed;
	float skydive_canopyHighSpeedSoundMaxFallSpeed;
	float skydive_wmAnimFreefallPitchMin;
	float skydive_wmAnimFreefallPitchMax;
	float skydive_wmAnimFreefallPitchTrackSpeed;
	float skydive_wmAnimFreefallRollTrackSpeed;
	float skydive_wmAnimFreefallRollReturnSpeed;
	RumbleGraph* skydive_wmAnimFreefallLeftStickXToRollGraph;
	RumbleGraph* skydive_wmAnimFreefallRightStickXToRollGraph;
	float skydive_camFreefallHeightOffset;
	RumbleGraph* skydive_camFreefallPitchToDistanceGraph;
	RumbleGraph* skydive_camFreefallPitchToForwardOffsetGraph;
	float skydive_camParachuteHeightOffset;
	RumbleGraph* skydive_camParachutePitchToDistanceGraph;
	RumbleGraph* skydive_camParachutePitchToForwardOffsetGraph;
	RumbleGraph* skydive_camParachutePitchToModelPitchForwardOffsetGraph;
	RumbleGraph* skydive_camParachutePitchToModelRollSideOffsetGraph;
	RumbleGraph* skydive_camParachutePitchToModelRollUpOffsetGraph;
	float skydive_camParachuteBlendInTime;
	SndAliasLookup nvg_blindSound;
	float dlcFloat[8];
};

struct SuitAnimPackage
{
	const char* name;
	void* /*SuitAnimPerWeapClass*/ animOverrides;
};

struct CameraFirstPersonProfileDef
{
	bool applyOffset;
	vec3_t offsetTranslation;
	bool disableFOVWeaponOffset;
	float cameraAnimationTransScale;
	float cameraAnimationRotScale;
	float handheldCameraTransScale;
	float handheldCameraRotScale;
	float handheldCameraImpulseTransScale;
	float handheldCameraImpulseRotScale;
};

struct CameraOrbitProfileDef
{
	float lerpSpeed;
	vec3_t pivotOffset;
	float initialAzimuth;
	float initialPolar;
	float polarMin;
	float polarMax;
	float range;
	float returnAzimuthSpeed;
	float returnPolarSpeed;
	float easeInFactor;
	float returnTimeTo;
	float turningSpeedPolar;
	float turningSpeedAzimuth;
	float traceCollRadius;
	float mouseInputMultiplier;
	float rollContrib;
	float pitchContrib;
	int buttonToggleReturn;
	int buttonCyclePerspective;
	int buttonRecenter;
	bool initialReturn;
	bool returnAzimuth;
	bool returnPolar;
	float alignToMovement;
	bool interpolateFocus;
	bool cameraReturnOnGas;
	float cameraReturnOnSpeed;
	float yawTurnAdjust;
};

struct CameraSentryDroneDef
{
	float range;
	float thresHitToSpeedUp;
	float speedUpFactor;
	float lerpSpeedEye;
	float lerpSpeedFocus;
	float lerpSpeedUp;
	float focusTraceLen;
	float eyeHeight;
	float horizontalOffset;
	float upOffsetFactorIncl;
};

struct CameraKillCamVehicleDef
{
	float lookAtRadius;
	float fov;
	float distBack;
	float distUp;
	float distBackRadiusMod;
	float distUpRadiusMod;
	float fovRadiusMod;
	float sideMag;
	float traceCollRad;
};

struct CameraTransitionDef
{
	bool active;
	float time;
	float timewaitEyepos;
	float timewaitAxis;
	int /*CameraTransitionCurve*/ curveEyepos;
	int /*CameraTransitionCurve*/ curveAxis;
};

struct CameraDef
{
	const char* name;
	int /*CameraProfile*/ profile;
	bool keepShakeCam;
	bool serverFeedback;
	bool behaveAsRemoteCont;
	bool interpolateViewTransition;
	bool overrideFOV;
	float FOV;
	int /*LensProfileMode*/ overrideLensProfile;
	float lensFocalLength;
	float lensFStop;
	float lensScale;
	float lensUVScale;
	bool overrideRadialBlur;
	float radialBlurRadius;
	float radialBlurStrength;
	bool overrideZPlanes;
	float zPlaneVMNear;
	float zPlaneSceneNear;
	CameraFirstPersonProfileDef firstPerson;
	CameraOrbitProfileDef orbit;
	CameraSentryDroneDef sentryDrone;
	CameraKillCamVehicleDef kcamVeh;
	CameraTransitionDef transitionIn;
	CameraTransitionDef transitionOut;
	vec3_t fpveh_offsetLs;
	float fpveh_offsetYaw;
	float fpveh_offsetPitch;
	float fpveh_rollContrib;
	float fpveh_rollMax;
	bool fpveh_freeLook;
	bool fpveh_freeLookReturn;
	bool dlcBool[1];
	bool fadeOutPlayerOnTransitionIn;
};

struct HudOutlineDef
{
	const char* name;
	unsigned __int8 outlineType;
	bool drawInStencil;
	bool drawNonOccludedPixels;
	bool drawOccludedPixels;
	bool drawFill;
	bool fadeOverTimeEnable;
	bool fadeOverTimeLooping;
	unsigned __int8 fadeOverTimeCurveType;
	float fadeOverTimeMinAlpha;
	float fadeOverTimeMaxAlphaTime;
	float fadeOverTimeMinAlphaTime;
	float fadeOverTimeInTime;
	float fadeOverTimeOutTime;
	bool distanceFadeEnable;
	float distanceFadeMinAlpha;
	float distanceFadeStartDistance;
	float distanceFadeEndDistance;
	unsigned int outlineColor;
	int outlineWidth;
	bool drawOnLocalPlayerCharacter;
	bool drawOnVehicleOccupants;
	bool drawOnLocalPlayerVehicleOccupants;
	bool drawOnLocalPlayerVehicle;
	bool dlcBool0;
	bool dlcBool1;
	bool dlcBool2;
	bool dlcBool3;
	bool dlcBool4;
	bool dlcBool5;
	float dlcFloat0;
	float dlcFloat1;
	float dlcFloat2;
	float dlcFloat3;
	float dlcFloat4;
	float dlcFloat5;
};

struct SpaceshipTargetDef
{
	const char* name;
	scr_string_t targetTag;
	float annotationOffsetX;
	float annotationOffsetY;
	float annotationOffsetZ;
	bool disableLeading;
	float lock_minDistance;
	float lock_maxDistance;
	float lock_cutoffDistance;
	float lock_minRate;
	float lock_maxRate;
	float lock_maxZoomFOV;
	float lock_followDistance;
	float lockCooldown_rate;
	float aa_closeDistance;
	float aa_farDistance;
	float aa_closeMinAngle;
	float aa_closeMaxAngle;
	float aa_closeBlendMax;
	float aa_farMinAngle;
	float aa_farMaxAngle;
	float aa_farBlendMax;
	float aaLocked_closeDistance;
	float aaLocked_farDistance;
	float aaLocked_closeMinAngle;
	float aaLocked_closeMaxAngle;
	float aaLocked_closeBlendMax;
	float aaLocked_farMinAngle;
	float aaLocked_farMaxAngle;
	float aaLocked_farBlendMax;
	float pilotAssistScale;
	float callout_maxDistance;
	float callout_maxAngle;
};

struct __declspec(align(8)) RumbleInfo
{
	const char* name;
	int duration;
	float range;
	RumbleGraph* highRumbleGraph;
	RumbleGraph* lowRumbleGraph;
	RumbleGraph* leftTriggerRumbleGraph;
	RumbleGraph* rightTriggerRumbleGraph;
	bool swapTriggerRumblesOnLefty;
	bool panTriggerRumbles;
	bool fadeWithDistance;
	bool broadcast;
};

struct __declspec(align(8)) RumbleGraph
{
	const char* name;
	vec2_t knots[16];
	unsigned __int16 knotCount;
};

struct LocalizeEntry
{
	const char* name;
	const char* value;
};

struct StaticModelCollisionInstance
{
	vec3_t origin;
	vec3_t angles;
	float scale;
};

struct XModelDetailCollision
{
	const char* name;
	unsigned int physicsLODDataSize;
	char* physicsLODData;
	unsigned int physicsLODDataNameCount;
	scr_string_t* physicsLODDataNames;
};

struct StaticModelCollisionModel
{
	scr_string_t name;
	PhysicsAsset* physicsAsset;
	XModelDetailCollision* detailCollision;
	unsigned int numInstances;
	StaticModelCollisionInstance* instances;
};

struct __declspec(align(8)) StaticModelCollisionModelList
{
	unsigned int numModels;
	StaticModelCollisionModel* models;
	unsigned int structureMemoryCost;
};

struct PhysicsCapacities
{
	int maxNumRigidBodiesServer;
	int maxNumDetailRigidBodiesServer;
	int maxNumConstraintsServer;
	int maxNumMotionsServer;
	int maxNumRigidBodiesClient;
	int maxNumDetailRigidBodiesClient;
	int maxNumConstraintsClient;
	int maxNumMotionsClient;
};

struct SpawnPointEntityRecord
{
	unsigned __int16 index;
	scr_string_t name;
	scr_string_t target;
	scr_string_t script_noteworthy;
	vec3_t origin;
	vec3_t angles;
};

struct SpawnPointRecordList
{
	unsigned __int16 spawnsCount;
	SpawnPointEntityRecord* spawns;
};

struct ClientMapTriggers
{
	unsigned int count;
	uintptr_t models;
	unsigned int hullCount;
	uintptr_t hulls;
	unsigned int slabCount;
	uintptr_t slabs;
};

struct ClientTriggers
{
	ClientMapTriggers trigger;
	unsigned int triggerStringLength;
	char* triggerString;
	__int16* visionSetTriggers;
	unsigned __int16* triggerType;
	vec3_t* origins;
	float* scriptDelay;
	float* priority;
	__int16* audioTriggers;
	__int16* blendLookup;
	__int16* npcTriggers;
	__int16* audioStateIds;
	uintptr_t detailSoundBank;
	uintptr_t audioRvbPanInfo;
	__int16* parent;
	uintptr_t linkTo;
	uintptr_t spatialTree;
};

struct ClientTriggerBlend
{
	unsigned __int16 numClientTriggerBlendNodes;
	uintptr_t blendNodes;
};

struct SplinePointEntityRecord
{
	int splineId;
	int splineNodeId;
	scr_string_t splineNodeLabel;
	scr_string_t targetname;
	scr_string_t target;
	scr_string_t string;
	float speed;
	float splineNodeTension;
	vec3_t origin;
	vec3_t angles;
	float throttle;
	vec2_t corridorDims;
	vec3_t tangent;
	float distToNextNode;
	vec3_t positionCubic[4];
	vec3_t tangentQuadratic[3];
};

struct SplinePointRecordList
{
	unsigned __int16 splinePointCount;
	float splineLength;
	SplinePointEntityRecord* splinePoints;
};

struct SplineRecordList
{
	unsigned __int16 splineCount;
	SplinePointRecordList* splines;
};

struct __declspec(align(8)) cmodel_t
{
	Bounds bounds;
	float radius;
	uintptr_t physicsAsset;
	unsigned __int16 physicsShapeOverrideIdx;
	unsigned __int16 navObstacleIdx;
	unsigned int edgeFirstIndex;
	unsigned int edgeTotalCount;
};

struct MapEdgeList
{
	const char* name;
	vec3_t mins;
	vec3_t maxs;
	unsigned int transientIndex;
	unsigned int dynamicQueryTypes;
	unsigned int staticQueryTypes;
	unsigned int numDynamicEdges;
	unsigned int numStaticEdges;
	bool valid;
	unsigned int numEdges;
	vec4_t(*edges)[2];
	uintptr_t edgeMetadata;
	unsigned int numEdgeOctrees;
	uintptr_t edgeOctrees;
	unsigned int numEdgeOctreeNodeSet;
	uintptr_t edgeOctreeNodeSets;
	unsigned int numEdgeIndices;
	unsigned int* edgeIndices;
	unsigned int numEdgeAdjacencyMetadata;
	uintptr_t edgeAdjacencyMetadata;
	unsigned int numEdgeAdjacency;
	uintptr_t edgeAdjacency;
};

struct __declspec(align(4)) CM_ClientModel
{
	vec3_t spawnOrigin;
	vec3_t spawnAngles;
	const XModel* model;
	scr_string_t animationTreeName;
	XAnimParts* animation;
	scr_string_t name;
	bool noPhysics;
	bool noCloth;
};

struct __declspec(align(8)) MapEnts
{
	const char* name;
	char* entityString;
	int numEntityChars;
	unsigned __int8 field_14;
	unsigned __int8 field_15;
	unsigned __int8 field_16;
	unsigned __int8 field_17;
	MapTriggers trigger;
	ClientTriggers clientTrigger;
	ClientTriggerBlend clientTriggerBlend;
	SpawnPointRecordList spawnList;
	SplineRecordList splineList;
	unsigned int havokEntsShapeDataSize;
	unsigned __int8 field_14C;
	unsigned __int8 field_14D;
	unsigned __int8 field_14E;
	unsigned __int8 field_14F;
	char* havokEntsShapeData;
	int numSubModels;
	unsigned __int8 field_15C;
	unsigned __int8 field_15D;
	unsigned __int8 field_15E;
	unsigned __int8 field_15F;
	cmodel_t* cmodels;
	unsigned __int8 field_168;
	unsigned __int8 field_169;
	unsigned __int8 field_16A;
	unsigned __int8 field_16B;
	int numEdgeLists;
	MapEdgeList** edgeLists;
	uintptr_t edgeListSpatialTree;
	int numClientModels;
	unsigned __int8 field_184;
	unsigned __int8 field_185;
	unsigned __int8 field_186;
	unsigned __int8 field_187;
	CM_ClientModel* clientModels;
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
	int dynEntityListsCount[2];
	__declspec(align(8)) unsigned __int8 field_1A8;
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
	unsigned __int8 field_1B8;
	unsigned __int8 field_1B9;
	unsigned __int8 field_1BA;
	unsigned __int8 field_1BB;
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
	uintptr_t dynEntSpatialPopulation[2];
	uintptr_t dynEntSpatialTransientMap[2];
	unsigned __int8 field_1E8;
	unsigned __int8 field_1E9;
	unsigned __int8 field_1EA;
	unsigned __int8 field_1EB;
	int clientEntAnchorCount;
	uintptr_t clientEntAnchors;
	unsigned __int8 scriptableMapEnts;
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
	unsigned __int8 field_2C0;
	unsigned __int8 field_2C1;
	unsigned __int8 field_2C2;
	unsigned __int8 field_2C3;
	unsigned __int8 field_2C4;
	unsigned __int8 field_2C5;
	unsigned __int8 field_2C6;
	unsigned __int8 field_2C7;
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
};


struct CollisionHeatmapEntry
{
	int vertexCount;
	float vertexDensity;
	vec3_t minExtent;
	vec3_t maxExtent;
};

struct Stage
{
	const char* name;
	vec3_t origin;
	unsigned __int16 triggerIndex;
	unsigned __int8 sunPrimaryLightIndex;
	unsigned int entityUID;
	vec3_t skyRotationAngles;
};

struct __declspec(align(8)) clipMap_t
{
	const char* name;
	int isInUse;
	unsigned int numStaticModelCollisionModelLists;
	StaticModelCollisionModelList* staticModelCollisionModelLists;
	MapEnts* mapEnts;
	Stage* stages;
	unsigned __int8 stageCount;
	MapTriggers stageTrigger;
	vec3_t broadphaseMin;
	vec3_t broadphaseMax;
	PhysicsCapacities physicsCapacities;
	unsigned int havokWorldShapeDataSize;
	char* havokWorldShapeData;
	unsigned int numCollisionHeatmapEntries;
	CollisionHeatmapEntry* collisionHeatmap;
	unsigned int totalGlassInitPieceCount;
	unsigned int totalGlassPieceLimit;
	uintptr_t topDownMapData;
	const char* visionSetName;
	unsigned int checksum;
};

struct __declspec(align(8)) WeaponDef
{
	const char* szOverlayName;
	XModel* gunXModel;
	XModel* gunXModelLeftHand;
	XModel* gunXModelRightHand;
	XModel* defaultViewModel;
	XModel* defaultWorldModelLeftHand;
	XModel* defaultWorldModelRightHand;
	XModel* worldModel;
	XModel* worldXModelLeftHand;
	XModel* worldXModelRightHand;
	XModel* defaultWorldModel;
	XModel* censorshipWorldModel;
	XModel* censorshipWorldModelLeftHand;
	XModel* censorshipWorldModelRightHand;
	XModel* playerShadowModel;
	XModel* playerShadowModelLeftHand;
	XModel* playerShadowModelRightHand;
	XModel* handXModel;
	WeaponAnimPackage* szXAnims;
	WeaponAnimPackage* szXAnimsRightHanded;
	WeaponAnimPackage* szXAnimsLeftHanded;
	XAnimParts* turretRaiseAnim;
	XAnimParts* turretIdleAnim;
	XAnimParts* turretFireAnim;
	WeaponDamageInfo damageInfo;
	int iFireTime;
	int iFireDelay;
	int iFireTimeAkimbo;
	int iFireDelayAkimbo;
	float sprintOutTimerScale;
	const char* szModeName;
	scr_string_t* notetrackRumbleMapKeys;
	scr_string_t* notetrackRumbleMapValues;
	scr_string_t* notetrackFXMapKeys;
	FxCombinedDef* notetrackFXMapValues;
	scr_string_t* notetrackFXMapTagValues;
	int playerAnimType;
	int scriptedAnimEvent;
	int scriptedAnimType;
	int weapType;
	int weapClass;
	int penetrateType;
	int inventoryType;
	int fireType;
	int turretFireType;
	int burstCount;
	int targetAssistType;
	int targetAssistBehavior;
	float targetAssistRange;
	float targetAssistAngle;
	float targetAssistLosOffsetForward;
	float targetAssistLosOffsetRight;
	float targetAssistLosOffsetUp;
	bool targetAssistOnlyAvailableInAds;
	int reloadType;
	float burstFireCooldown;
	bool burstFireAuto;
	float viewPitchMaxSpeed;
	float viewYawMaxSpeed;
	bool alignBarrelWithTurretBody;
	bool keepOrientationOnExit;
	float kickBackForceMultiplier;
	bool autoAdjust;
	bool networkLODRangeOverride;
	float networkLODRangeOverrideDistance;
	int offhandClass;
	int stance;
	WeaponVFXPackage* vfxPackage;
	WeaponSFXPackage* sfxPackage;
	bool disableBreathOffhand;
	int reticleType;
	int hitmarkerType;
	Material* reticleCenter;
	Material* reticleSide;
	Material* reticleOnePiece;
	int iReticleCenterSize;
	int iReticleSideSize;
	int iReticleMinOfs;
	bool reticleCenterPulse;
	int iReticleShakeDuration;
	int iReticleSettleDuration;
	int iReticleNumBulletsToRapidFire;
	int activeReticleType;
	bool useTurretViewmodelAnims;
	bool useTurret3pIK;
	int turret3pAnimType;
	float turretFireAnimMinTime;
	vec3_t vStandOfs;
	vec3_t vStandOfsRot;
	vec3_t vStandOfsRotPivot;
	vec3_t vStandMove;
	vec3_t vStandRot;
	vec3_t strafeMove;
	vec3_t strafeRot;
	int hipOffsetLerpType;
	vec3_t vDuckedOfs;
	vec3_t vDuckedOfsRot;
	vec3_t vDuckedOfsRotPivot;
	vec3_t vDuckedMove;
	vec3_t vDuckedRot;
	vec3_t vProneOfs;
	vec3_t vProneMove;
	vec3_t vProneRot;
	float adsForwardOffset;
	float adsRoll;
	float fPosMoveRate;
	float fPosProneMoveRate;
	float fStandMoveMinSpeed;
	float fDuckedMoveMinSpeed;
	float fProneMoveMinSpeed;
	float fPosRotRate;
	float fPosProneRotRate;
	float fDuckedOfsRotRate;
	float fStandRotMinSpeed;
	float fDuckedRotMinSpeed;
	float fProneRotMinSpeed;
	float fReticleShakeMagnitude;
	float fReticleRapidFireMultiplier;
	XModel* worldClipModel;
	XModel* rocketModel;
	GfxImage* hudIcon;
	GfxImage* pickupIcon;
	GfxImage* dangerIconImg;
	GfxImage* throwBackIconImg;
	Material* dangerIconMat;
	Material* throwBackIconMat;
	bool hideWarningIcons;
	float warningIconsDelay;
	int ammoCounterClip;
	int iStartAmmo;
	int iPerkStartAmmo;
	int iPerkMaxAmmo;
	const char* szAmmoName;
	int iAmmoIndex;
	int iMaxAmmo;
	int shotCount;
	const char* szSharedAmmoCapName;
	int iSharedAmmoCapIndex;
	int iSharedAmmoCap;
	int iAmmoUsedPerShot;
	bool requireAmmoUsedPerShot;
	bool disableNoAmmoWarning;
	float lowAmmoWarningThreshold;
	int lowAmmoWarningCount;
	int iDamageType;
	int iMeleeDamage;
	int iMeleeCountToFinisher;
	bool hasMeleeFinisher;
	float autoAimRange;
	float aimAssistRange;
	float aimAssistRangeAds;
	float aimAssistPitchSlowdown;
	float aimAssistPitchSlowdownAds;
	float aimAssistYawSlowdown;
	float aimAssistYawSlowdownAds;
	float aimAssistLockonStrength;
	float aimPadding;
	float enemyCrosshairRange;
	float moveSpeedScale;
	float adsMoveSpeedScale;
	float sprintDurationScale;
	float sprintRestoreDelay;
	ADSOverlay overlay;
	int overlayInterface;
	float fAdsBobFactor;
	float fAdsViewBobMult;
	float fAdsGunBobPitchScale;
	float fAdsGunBobYawScale;
	float fAdsGunBobTiltPitchScale;
	float fAdsGunBobTiltYawScale;
	float fAdsGunBobTiltRollScale;
	float fAdsGunBobTiltBulletDirScale;
	float fAdsGunBobTiltOffset;
	float fAdsGunBobCrouchFactor;
	float adsCrouchViewKickFactor;
	float adsCrouchGunKickFactor;
	float adsProneViewKickFactor;
	float adsProneGunKickFactor;
	float fHipSpreadStandMin;
	float fHipSpreadDuckedMin;
	float fHipSpreadProneMin;
	float hipSpreadSprintMin;
	float hipSpreadInAirMin;
	float hipSpreadStandMax;
	float hipSpreadDuckedMax;
	float hipSpreadProneMax;
	float hipSpreadSprintMax;
	float hipSpreadInAirMax;
	float fHipSpreadDecayRate;
	float fHipSpreadFireAdd;
	float fHipSpreadTurnAdd;
	float fHipSpreadMoveAdd;
	float fHipSpreadDuckedDecay;
	float fHipSpreadProneDecay;
	float hipSpreadSprintDecay;
	float hipSpreadInAirDecay;
	float fHipReticleSidePos;
	float fAdsIdleAmount;
	float fHipIdleAmount;
	float adsIdleSpeed;
	float hipIdleSpeed;
	float fIdleCrouchFactor;
	float fIdleProneFactor;
	float fGunMaxPitch;
	float fGunMaxYaw;
	float fViewMaxPitch;
	float fViewMaxYaw;
	float adsIdleLerpStartTime;
	float adsIdleLerpTime;
	bool useUninterruptedAdsIdleMotion;
	bool disableInputDrivenViewReturnDampening;
	float slideSpreadMin;
	float slideSpreadMax;
	float slideSpreadDecayRate;
	float slideSpreadFireAdd;
	float slideSpreadTurnAdd;
	SwaySettings swaySettings;
	float adsFireRateScale;
	float adsDamageRangeScale;
	float adsFireAnimFrac;
	float fireTimerLerpToAdsScale;
	bool alwaysFireAtMaxRangeInAds;
	bool adsAlignEnabled;
	bool disableTagAlignX;
	vec3_t adsAlignOffset;
	int adsAlignOffsetLerpType;
	int adsAlignLerpType;
	float adsMovementAnimLerpStart;
	float adsMovementAnimLerpEnd;
	float dualWieldViewModelOffset;
	float fScopeDriftDelay;
	float fScopeDriftLerpInTime;
	float fScopeDriftSteadyTime;
	float fScopeDriftLerpOutTime;
	float fScopeDriftSteadyFactor;
	float fScopeDriftUnsteadyFactor;
	int killIconRatio;
	int iReloadAmmoAdd;
	int iReloadStartAdd;
	bool reloadTwoRound;
	int ammoDropStockMin;
	int ammoDropClipPercentMin;
	int ammoDropClipPercentMax;
	float cameraShakeScale;
	int cameraShakeDuration;
	float cameraShakeRadius;
	int iExplosionRadius;
	int iExplosionRadiusMin;
	int iExplosionForceRadius;
	int iExplosionInnerDamage;
	int iExplosionOuterDamage;
	float explosionForceScalar;
	float damageConeAngle;
	float bulletExplDmgMultMin;
	float bulletExplDmgMult;
	float bulletExplRadiusMult;
	int iProjectileSpeed;
	int iProjectileSpeedUp;
	int iProjectileSpeedForward;
	int iProjectileActivateDist;
	int iProjectileDetonationRadius;
	float projLifetime;
	float projLifetimeStdDeviation;
	float timeToAccelerate;
	float projectileCurvature;
	XModel* projectileModel;
	int projExplosion;
	FxCombinedDef projExplosionEffect;
	FxCombinedDef projDudEffect;
	FxCombinedDef projTimeoutEffect;
	int iExplosionSteppedRadiusInner;
	int iExplosionSteppedRadiusMid;
	int iExplosionSteppedRadiusOuter;
	int iExplosionSteppedDamageInner;
	int iExplosionSteppedDamageMid;
	int iExplosionSteppedDamageOuter;
	float* parallelBounce;
	float* perpendicularBounce;
	FxCombinedDef vmProjBodyEffect;
	FxCombinedDef projBodyEffect;
	FxCombinedDef projTrailEffect;
	FxCombinedDef projBeaconEffect;
	vec3_t vProjectileColor;
	int guidedMissileType;
	float maxSteeringAccel;
	int projIgnitionDelay;
	FxCombinedDef projIgnitionEffect;
	float fAdsAimPitch;
	float adsInCrosshairAlphaStart;
	float adsInCrosshairAlphaEnd;
	float adsOutCrosshairAlphaStart;
	float adsOutCrosshairAlphaEnd;
	bool adsShouldShowCrosshair;
	float fAdsGunKickPitchMin;
	float fAdsGunKickPitchMax;
	float fAdsGunKickYawMin;
	float fAdsGunKickYawMax;
	float fAdsGunKickMagMin;
	float fAdsGunKickAccel;
	float fAdsGunKickSpeedMax;
	float fAdsGunKickSpeedDecay;
	float fAdsGunKickStaticDecay;
	float fAdsViewKickPitchMin;
	float fAdsViewKickPitchMax;
	float fAdsViewKickYawMin;
	float fAdsViewKickYawMax;
	float fAdsViewKickMagMin;
	float fAdsViewScatterMin;
	float fAdsViewScatterMax;
	float fAdsSpread;
	float fAdsSpreadNVG;
	float adsSpreadStartFrac;
	float adsSpreadEndFrac;
	int iVisibilityAxis;
	float fVisibilityUpOffset;
	float fHipGunKickPitchMin;
	float fHipGunKickPitchMax;
	float fHipGunKickYawMin;
	float fHipGunKickYawMax;
	float fHipGunKickMagMin;
	float fHipGunKickAccel;
	float fHipGunKickSpeedMax;
	float fHipGunKickSpeedDecay;
	float fHipGunKickStaticDecay;
	float fHipViewKickPitchMin;
	float fHipViewKickPitchMax;
	float fHipViewKickYawMin;
	float fHipViewKickYawMax;
	float fHipViewKickMagMin;
	float fHipViewScatterMin;
	float fHipViewScatterMax;
	float multipleReloadClipPercentage;
	float hipStartingGunKickPercent;
	float hipStartingViewKickPercent;
	int adsStartingKickBullets;
	float adsStartingGunKickPercent;
	float adsStartingViewKickPercent;
	float hipEndingGunKickPercent;
	float hipEndingViewKickPercent;
	int adsEndingKickBullets;
	float adsEndingGunKickPercent;
	float adsEndingViewKickPercent;
	float kickAlignedInputScalar;
	float kickOpposedInputScalar;
	float viewKickMaintainFraction;
	float adsGunTiltPitchFactor;
	float adsGunTiltYawFactor;
	float adsGunTiltRollFactor;
	float adsGunTiltOffset;
	float hipGunTiltPitchFactor;
	float hipGunTiltYawFactor;
	float hipGunTiltRollFactor;
	float hipGunTiltOffset;
	bool useNewViewKick;
	bool useNewGunKick;
	bool useAngularViewKick;
	bool useAngularGunKick;
	float hipAngularViewKickDir[6];
	float hipAngularViewKickDev[6];
	float hipAngularViewKickStrengthMin[6];
	float hipAngularViewKickStrengthMax[6];
	float hipAngularViewKickPitchScale[6];
	float adsAngularViewKickDir[6];
	float adsAngularViewKickDev[6];
	float adsAngularViewKickStrengthMin[6];
	float adsAngularViewKickStrengthMax[6];
	float adsAngularViewKickPitchScale[6];
	int adsAngularViewKickBullet[6];
	bool adsAngularViewKickUseSet[6];
	float hipAngularGunKickDir[6];
	float hipAngularGunKickDev[6];
	float hipAngularGunKickStrengthMin[6];
	float hipAngularGunKickStrengthMax[6];
	float hipAngularGunKickPitchScale[6];
	float adsAngularGunKickDir[6];
	float adsAngularGunKickDev[6];
	float adsAngularGunKickStrengthMin[6];
	float adsAngularGunKickStrengthMax[6];
	float adsAngularGunKickPitchScale[6];
	int adsAngularGunKickBullet[6];
	bool adsAngularGunKickUseSet[6];
	float hipViewKickReturnAccelScale;
	float adsViewKickReturnAccelScale;
	float hipViewKickReturnSpeedCurveScale;
	float adsViewKickReturnSpeedCurveScale;
	float hipGunKickReturnAccelScale;
	float adsGunKickReturnAccelScale;
	float hipGunKickReturnSpeedCurveScale;
	float adsGunKickReturnSpeedCurveScale;
	float hipSpreadStandMoveMax;
	float hipSpreadDuckedMoveMax;
	float hipSpreadProneMoveMax;
	float hipSpreadSprintMoveMax;
	float hipSpreadInAirMoveMax;
	float slideSpreadMoveMax;
	WeaponOffsetCurveDescription weaponOffsetCurveHoldFireSlow;
	WeaponOffsetCurveDescription weaponOffsetCurveHoldFireFast;
	WeaponOffsetCurveDescription weaponOffsetCurveAds;
	WeaponOffsetCurveDescription weaponOffsetCurveAlwaysOn;
	WeaponOffsetCurveDescription weaponOffsetCurveKick;
	WeaponOffsetCurveDescription weaponOffsetCurveSnapDecay;
	int numWeaponOffsetPatterns;
	WeaponOffsetPatternDescription* weaponOffsetPatterns;
	int numWeaponOffsetPatternsKickOrSnapDecay;
	WeaponOffsetPatternDescription** weaponOffsetPatternsKickOrSnapDecay;
	float fightDist;
	float maxDist;
	const char* accuracyGraphName[2];
	vec2_t* originalAccuracyGraphKnots[2];
	unsigned __int16 originalAccuracyGraphKnotCount[2];
	int iPositionReloadTransTime;
	float leftArc;
	float rightArc;
	float topArc;
	float bottomArc;
	float visualPitchLimitTop;
	float visualPitchLimitBottom;
	bool softLeftRightArc;
	float accuracy;
	float aiSpread;
	float playerSpread;
	float minTurnSpeed[2];
	float maxTurnSpeed[2];
	float pitchConvergenceTime;
	float yawConvergenceTime;
	float suppressTime;
	float suppressTimeTargetKilled;
	float aiReturnToDefaultSpeed[2];
	float maxRange;
	float fAnimHorRotateInc;
	float fPlayerPositionDist;
	const char* szUseHintString;
	const char* dropHintString;
	unsigned int iUseHintStringIndex;
	unsigned int dropHintStringIndex;
	float horizViewJitter;
	float vertViewJitter;
	bool enableViewBounceFire;
	float viewBounceFireDecay;
	float viewBounceFireFrequency;
	float viewBounceFirePitchScale;
	float viewBounceFireRollScale;
	float scanSpeed;
	float scanAccel;
	int scanPauseTime;
	const char* szScript;
	float adsSpeedMs[2];
	float adsAccelSec[2];
	bool deferDamageToParentVehicle;
	bool useSteppedExplosionDamage;
	float destabilizationRateTime;
	float destabilizationCurvatureMax;
	int destabilizeDistance;
	float robotechMaxPitch;
	float robotechMaxYaw;
	float robotechFrequency;
	float robotechVariancePitch;
	float robotechVarianceYaw;
	float robotechVarianceFrequency;
	float* locationDamageMultipliers;
	unsigned __int8* hitLocPriorityMap;
	float unittypeMultipliers[7];
	RumbleInfo* fireRumble;
	RumbleInfo* meleeImpactRumble;
	float heatAccumulationPerShot;
	float heatDissipationPerSecond;
	float heatSmokeStartThreshold;
	float heatSmokeStopThreshold;
	bool heatIsOpenBolt;
	int tracerStyle;
	TracerDef* tracerType;
	TracerDef* overchargeTracerType;
	LaserDef* laserTypeViewModel;
	LaserDef* laserTypeViewModelAlt;
	LaserDef* laserTypeFriendly;
	LaserDef* laserTypeEnemy;
	bool turretADSEnabled;
	float turretADSTime;
	float turretFov;
	float turretFovADS;
	float turretScopeZoomRate;
	float turretScopeZoomMin;
	float turretScopeZoomMax;
	float turretOverheatPenalty;
	SndAliasLookup turretOverheatSound;
	FxCombinedDef turretOverheatEffect;
	RumbleInfo* turretBarrelSpinRumble;
	float turretBarrelSpinSpeed;
	float turretBarrelSpinUpTime;
	float turretBarrelSpinDownTime;
	SndAliasLookup turretBarrelSpinMaxSnd;
	SndAliasLookup turretBarrelSpinUpSnd[4];
	SndAliasLookup turretBarrelSpinDownSnd[4];
	SndAliasLookup missileConeSoundAlias;
	SndAliasLookup missileConeSoundAliasAtBase;
	float missileConeSoundRadiusAtTop;
	float missileConeSoundRadiusAtBase;
	float missileConeSoundHeight;
	float missileConeSoundOriginOffset;
	float missileConeSoundVolumescaleAtCore;
	float missileConeSoundVolumescaleAtEdge;
	float missileConeSoundVolumescaleCoreSize;
	float missileConeSoundPitchAtTop;
	float missileConeSoundPitchAtBottom;
	float missileConeSoundPitchTopSize;
	float missileConeSoundPitchBottomSize;
	float missileConeSoundCrossfadeTopSize;
	float missileConeSoundCrossfadeBottomSize;
	bool meleeOverrideValues;
	float aim_automelee_lerp;
	float aim_automelee_region_height;
	float aim_automelee_region_width;
	float aim_automelee_maxPitchMovement;
	float aim_automelee_maxYawMovement;
	float player_meleeHeight;
	float player_meleeWidth;
	float playerMeleeRangeStanding;
	float playerMeleeRangeCrouched;
	float playerMeleeRangeProne;
	float playerMeleeRangeChargeStanding;
	float playerMeleeRangeChargeCrouched;
	float playerMeleeChargeHeightTolerance;
	bool shieldAllowFiring;
	int shieldMaxSpeed;
	bool shieldAlwaysDisplay;
	Gesture* shieldDeployGesture;
	Gesture* shieldFireWeapGesture;
	Gesture* shieldDeployWhileFiring;
	Gesture* shieldRetractWhileFiring;
	Gesture* shieldBashGesture;
	FxCombinedDef shieldMeleeFx;
	float shieldMeleeFxDelay;
	float HitEarthquakeScale;
	float HitEarthquakeDuration;
	float HitEarthquakeRadius;
	RumbleInfo* shieldHitRumble;
	float MissEarthquakeScale;
	float MissEarthquakeDuration;
	float MissEarthquakeRadius;
	RumbleInfo* shieldMissRumble;
	int shieldDeployButton;
	bool shieldUsesEnergy;
	float shieldMaxEnergy;
	float shieldConsumptionRate;
	float shieldMeleeEnergyCost;
	float shieldMeleeHitEnergyCost;
	float reactiveMotionRadiusScale;
	float reactiveMotionFrequencyScale;
	float reactiveMotionAmplitudeScale;
	float reactiveMotionFalloff;
	float reactiveMotionLifetime;
	unsigned __int8 transientBaseViewFlags;
	unsigned __int8 transientBaseWorldFlags;
	bool hasAnyTransientModels;
	bool blendFireAnimations;
	bool sharedAmmo;
	bool lockonSupported;
	bool requireLockonToFire;
	bool isAirburstWeapon;
	bool bigExplosion;
	bool noAdsWhenMagEmpty;
	bool avoidDropCleanup;
	bool allowGrenadeSwitching;
	bool inheritsPerks;
	bool forceUse;
	bool ladderWeapon;
	bool executionVictimHiddenWeapon;
	bool crosshairColorChange;
	bool bRifleBullet;
	bool bEnergyBullet;
	bool bIncendiaryBullet;
	bool armorPiercing;
	bool impaling;
	bool bBoltAction;
	bool aimDownSight;
	bool canHoldBreath;
	bool meleeOnly;
	bool supportsAlternateMelee;
	bool bRechamberWhileAds;
	bool reloadWhileAds;
	bool bBulletExplosiveDamage;
	bool bCookOffHold;
	bool overCookIsNotLethal;
	bool reticleSpin45;
	bool bClipOnly;
	bool bDoesNotConsumeAmmo;
	bool bRemoveWeaponOnEmpty;
	bool noAmmoPickup;
	bool adsFireOnly;
	bool cancelAutoHolsterWhenEmpty;
	bool disableSwitchToWhenEmpty;
	bool suppressAmmoPrimaryDisplay;
	bool suppressAmmoReserveDisplay;
	LaserSettings laserSettings;
	bool markableViewmodel;
	bool isPredictedProjectile;
	int clientTrajectoryBlendOutTime;
	int serverTrajectoryBlendInTime;
	int dualWieldType;
	bool flipKillIcon;
	bool bNoPartialReload;
	bool reloadDisabled;
	bool blocksProne;
	bool silenced;
	bool doNotSuppressAI;
	bool isRollingGrenade;
	bool dropGrenadeHeldOnDeath;
	bool projExplosionEffectForceNormalUp;
	bool projExplosionEffectInheritParentDirection;
	bool bProjImpactExplode;
	bool spawnProjAtMuzzle;
	bool correctBulletTrajectory;
	float maxCorrectionAngle;
	bool disableProjectileCrumpleCheck;
	bool bProjTrajectoryEvents;
	bool bProjWhizByEnabled;
	bool stickToPlayers;
	bool stickToVehicles;
	bool stickToTurrets;
	bool stickToNonStick;
	bool projEnableMissileStickiness;
	bool enableMissileRicochet;
	bool thrownSideways;
	bool disableFiring;
	bool firesOnWeaponSwitch;
	bool disableHolding;
	bool timedDetonation;
	float missileRicochetMinAngleOfIncidence;
	float missileCrumpleMinSpeed;
	int detonateType;
	XModel* detonatorWorldModel;
	int explosiveDamageDelay;
	int fuseTime;
	int aiFuseTime;
	int maxHoldTime;
	GrenadeRotationParams rotationParams;
	bool holdButtonToThrow;
	bool autoHold;
	bool infiniteHold;
	bool freezeMovementWhenFiring;
	bool offhandAllowsSprint;
	bool thermalScope;
	bool thermalToggle;
	bool outlineEnemies;
	bool outlineDepthTest;
	bool outlineFill;
	float enemyOutlineR;
	float enemyOutlineG;
	float enemyOutlineB;
	float enemyOutlineA;
	float allyOutlineR;
	float allyOutlineG;
	float allyOutlineB;
	float allyOutlineA;
	bool depthScan;
	float depthScanThickness;
	float depthScanR;
	float depthScanG;
	float depthScanB;
	float depthScanA;
	float depthScanOutlineThickness;
	float depthScanOutlineR;
	float depthScanOutlineG;
	float depthScanOutlineB;
	float depthScanOutlineA;
	bool depthScanOverlay;
	float depthScanOverlayStrength;
	float depthScanOverlayXTiles;
	float depthScanOverlayYTiles;
	float depthScanOverlayXScroll;
	float depthScanOverlayYScroll;
	float blurSceneAdsInFraction;
	float blurSceneAdsOutFraction;
	bool altModeSameWeapon;
	bool playAltGesturesForOffhandWeapons;
	bool turretBarrelSpinEnabled;
	bool missileConeSoundEnabled;
	bool missileConeSoundPitchshiftEnabled;
	bool missileConeSoundCrossfadeEnabled;
	bool offhandHoldIsCancelable;
	bool doNotAllowAttachmentsToOverrideSpread;
	bool useScopeDrift;
	bool alwaysShatterGlassOnImpact;
	bool jumpSpread;
	bool noFullViewmodelAnimations;
	float killcamOffset;
	bool useDualFOV;
	bool showViewModelInDualFOV;
	bool syncedFOVInDualFOV;
	bool disableDrop;
	bool preferredDrop;
	Gesture* gestureAnimation;
	float gestureFireStateTime;
	Gesture* gesturePullback;
	Gesture* gesturePullbackAlt;
	float minPullbackTime;
	float minPullbackToThrowBlendTime;
	float maxPullbackToThrowBlendTime;
	Gesture* gestureThrow;
	Gesture* gestureThrowAlt;
	float gestureFireTime;
	Gesture* gestureDetonate;
	Gesture* gestureDetonateAlt;
	float gestureDetonationTime;
	bool gesturesDisablePrimary;
	FxCombinedDef cameraFireEffect;
	float cameraFireEffectDurationSec;
	float changedFireTime;
	float changedFireTimeAkimbo;
	int changedFireTimeNumBullets;
	int chargeType;
	float chargeGain;
	float chargeCostPerShot;
	float chargeLossWhenIdle;
	float chargeEmptyCooldown;
	float chargeFireAtMaxDamageMultiplier;
	int chargeMeterEffectBoneCount;
	FxCombinedDef chargeMeterEffect;
	SndAliasLookup chargeUpSound;
	SndAliasLookup chargeDownSound;
	SndAliasLookup chargeUpSoundPlayer;
	SndAliasLookup chargeDownSoundPlayer;
	SndAliasLookup chargeDownToUpSound;
	SndAliasLookup chargeDownToUpSoundPlayer;
	SndAliasLookup chargeUpToDownSound;
	SndAliasLookup chargeUpToDownSoundPlayer;
	SndAliasLookup chargeMaxSound;
	SndAliasLookup chargeMaxSoundPlayer;
	bool chargeHudReveal;
	RumbleInfo* chargeRumble;
	scr_string_t stowTag;
	XModel* stowOffsetModel;
	scr_string_t stowOffsetAttachTag;
	int slot;
	float maxTargetAngle;
	bool spaceshipSecondaryWeapon;
	float impulseFieldRadius;
	float impulseFieldInitialSpeed;
	float impulseFieldMaxSpeed;
	float impulseFieldAcceleration;
	float impulseFieldInAirImpulseMultiplier;
	float impulseFieldInAirImpulseMultiplierInterpTime;
	float impulseFieldSlideMultiplier;
	float impulseFieldSlideMultiplierInterpTime;
	bool impulseFieldIsPush;
	bool impulseFieldAffectsFriendlies;
	bool impulseFieldAffectsSelf;
	bool impulseFieldAffectsProne;
	bool regenerationEnabled;
	int regenerationTimeMs;
	int regenerationAddTimeMs;
	int regenerationAmount;
	bool regenerationConsumeStock;
	bool regenerationDisableWhileFiring;
	int deployType;
	bool deployRequireOnWalkableSurface;
	bool deployRequireOnNavmesh;
	bool deployRequireSkyAbove;
	bool deployRequireNoOverhang;
	bool deployAlwaysUpright;
	bool deployEdgeSnap;
	float deployCylinderRadius;
	float deployCylinderHeight;
	float deployMaxDistance;
	float deployMaxHeightAboveEye;
	float deployEffectHeightOffset;
	float deployMaxSlope;
	FxCombinedDef deployEffect;
	int deployValidGroupId;
	int deployIndoorGroupId;
	int deployInvalidGroupId;
	int deployOutOfRangeGroupId;
	int numAnimOverrides;
	AnimOverride* animOverrides;
	CarryAnimOverride carryAnimOverrides[5];
	int numSfxOverrides;
	SFXOverride* sfxOverrides;
	int numVfxOverrides;
	VFXOverride* vfxOverrides;
	float reactiveEmitterDelay;
	float grenadeDangerIconDistance;
	float bulletDirGunAngleModifierIdleHip;
	float bulletDirGunAngleModifierIdleAds;
	float bulletDirGunAngleModifierGunKickHip;
	float bulletDirGunAngleModifierGunKickAds;
	float bulletDirGunAngleModifierGunTiltHip;
	float bulletDirGunAngleModifierGunTiltAds;
	float viewClampPitchCatchUpTimeSec;
	float viewClampYawCatchUpTimeSec;
	bool mountTopEnable;
	bool mountTopYawClamp;
	float mountTopYawMax;
	float mountTopGunKickScale;
	float mountTopGunCenterScale;
	float mountTopViewKickScale;
	float mountTopViewCenterScale;
	float mountTopGunIdleMotionScale;
	float mountTopViewIdleMotionScale;
	int mountTopEnterDurationMs;
	int mountTopExitDurationMs;
	float mountTopEdgeToEyeDistanceForward;
	float mountTopEdgeToEyeDistanceAbove;
	bool mountSideEnable;
	bool mountSideTransitionEnable;
	float mountSideRoll;
	float mountSideRollStartFrac;
	float mountSideRollEndFrac;
	float mountSideGunKickScale;
	float mountSideGunCenterScale;
	float mountSideViewKickScale;
	float mountSideViewCenterScale;
	float mountSideGunIdleMotionScale;
	float mountSideViewIdleMotionScale;
	int mountSideEnterDurationMs;
	int mountSideExitDurationMs;
	float mountSideEdgeToEyeDistanceForward;
	float mountSideEdgeToEyeDistanceAbove;
	float mountViewmodelOffset;
	float mountFOVScale;
	RumbleInfo* mountRumble;
	WeaponOffsetPatternScaleInfo mountWeaponOffsetPatternScaleInfo;
	float adsFireMotionBlur;
	int adsFireMotionBlurDurationMs;
	float adsFireMotionBlurDecayExponent;
	float hipFireMotionBlur;
	int hipFireMotionBlurDurationMs;
	float hipFireMotionBlurDecayExponent;
	float adsCameraShakeRotationScale;
	float adsCameraShakeTranslationScale;
	AdvancedIdleSettings advancedIdleSettings;
	WeaponOffsetPatternScaleInfo crouchedWeaponOffsetPatternScaleInfo;
	WeaponOffsetPatternScaleInfo proneWeaponOffsetPatternScaleInfo;
	BallisticInfo ballisticInfo;
	WeaponEntityNotify* notifyTypes[2];
	float dlcFloat[6];
	bool dlcBool[3];
	bool enableWeaponInspect;
	bool stowedOcclusionTestEnabled;
	bool ignoreMinTracerSpawnDistance;
	bool tracerOverrideEnabled;
	bool boltActionReloadIncludesRechamber;
};


struct WeaponCompleteDef
{
	const char* szInternalName;
	WeaponDef weapDef;
	const char* szDisplayName;
	const char* szLootTable;
	scr_string_t* hideTags;
	AttachmentList attachments[14];
	unsigned int numLootVariants;
	unsigned int numNotetrackSoundMappings;
	scr_string_t* notetrackSoundMapKeys;
	scr_string_t* notetrackSoundMapValues;
	unsigned int numNotetrackOverrides;
	void* /*NoteTrackToSoundEntry*/ notetrackOverrides;
	unsigned int numNotetrackSuitEntries;
	void* /*NoteTrackToSuitSoundEntry*/ notetrackSuitEntries;
	ZoomSettings zoomSettings;
	int iAdsTransInTime;
	int iAdsTransOutTime;
	int iAdsTransInToOutTime;
	int iAdsTransOutToInTime;
	int iClipSize;
	int vfxImpactType;
	float penetrateMultiplier;
	float fAdsViewKickCenterSpeed;
	float fHipViewKickCenterSpeed;
	Material* killIconMat;
	Material* dpadIconMat;
	Material* dpadIconInactiveMat;
	GfxImage* killIconImg;
	GfxImage* dpadIconImg;
	GfxImage* dpadIconInactiveImg;
	int ammoDropStockMax;
	bool useSceneDof;
	float adsDofPhysicalFstop;
	float adsDofPhysicalFocusDistance;
	bool adsDofPhysicalFocalTag;
	float adsDofPhysicalReloadFstop;
	float adsDofPhysicalReloadFocusDistance;
	unsigned __int16 accuracyGraphKnotCount[2];
	vec2_t* accuracyGraphKnots[2];
	bool enhanced;
	bool dpadIconShowsAmmo;
	bool luiWeaponInfoWidgetUsesScopeStencil;
	const char* szAltModeInactiveName;
	const char* dynamicIconAnimationName;
	bool isUsingDynamicIcon;
	const char* szLUIWeaponInfoWidgetName;
	const char* szLUIWeaponInfoWidgetTag;
	const char* szLUICrosshairWidget;
};

union XAssetHeader
{
	//PhysicsLibrary* physicsLibrary;
	//PhysicsSFXEventAsset* physicsSFXEventAsset;
	//PhysicsVFXEventAsset* physicsVFXEventAsset;
	PhysicsAsset* physicsAsset;
	//PhysicsFXPipeline* physicsFXPipeline;
	//PhysicsFXShape* physicsFXShape;
	//PhysicsDebugData* physicsDebugData;
	//XAnimParts* parts;
	//XModelSurfs* modelSurfs;
	XModel* model;
	//MayhemData* mayhem;
	Material* material;
	//ComputeShader* computeShader;
	//MaterialSerializedShader* serializedShader;
	//MaterialTechniqueSet* techniqueSet;
	GfxImage* image;
	//SndGlobals* soundGlobals;
	//SndBankResident* soundBankResident;
	//SndBankTransient* soundBankTransient;
	clipMap_t* clipMap;
	//ComWorld* comWorld;
	//GlassWorld* glassWorld;
	//PathData* pathData;
	//NavMeshData* navMeshData;
	//TacticalGraphData* tacGraphData;
	MapEnts* mapEnts;
	//FxWorld* fxWorld;
	//GfxWorld* gfxWorld;
	//GfxWorldTransientZone* gfxWorldTransientZone;
	//GfxIESProfile* iesProfile;
	//GfxLightDef* lightDef;
	//GfxGradingClut* gradingClut;
	//GfxFogSpline* fogSpline;
	//AnimationClass* animClass;
	//PlayerAnimScript* playerAnim;
	Gesture* gesture;
	LocalizeEntry* localize;
	//WeaponAttachment* attachment;
	WeaponCompleteDef* weapon;
	//ParticleSystemDef* vfx;
	//FxImpactTable* impactFx;
	SurfaceFxTable* surfaceFx;
	RawFile* rawfile;
	ScriptFile* scriptfile;
	ScriptDebugData* scriptDebugData;
	StringTable* stringTable;
	LeaderboardDef* leaderboardDef;
	VirtualLeaderboardDef* virtualLeaderboardDef;
	DDLFile* ddlFile;
	TracerDef* tracerDef;
	VehicleDef* vehDef;
	AddonMapEnts* addonMapEnts;
	NetConstStrings* netConstStrings;
	LuaFile* luaFile;
	ScriptableDef* scriptable;
	EquipmentSoundTable* equipSndTable;
	VectorField* vectorField;
	FxParticleSimAnimation* particleSimAnimation;
	StreamingInfo* streamingInfo;
	LaserDef* laserDef;
	TTFDef* ttfDef;
	SuitDef* suitDef;
	SuitAnimPackage* suitAnimPackage;
	CameraDef* cameraDef;
	HudOutlineDef* hudOutlineDef;
	SpaceshipTargetDef* spaceshipTargetDef;
	RumbleInfo* rumble;
	RumbleGraph* rumbleGraph;
	//WeaponAnimPackage* weaponAnimPackage;
	//WeaponSFXPackage* weaponSFXPackage;
	//WeaponVFXPackage* weaponVFXPackage;
	//FootstepVFX* footstepVFX;
	//BehaviorTree* behaviorTree;
	//Animset* animset;
	//ASM* asmAsset;
	//XAnimProceduralBones* proceduralBones;
	//XAnimDynamicBones* dynamicBones;
	//ReticleDef* reticleDef;
	//XAnimCurve* xanimCurve;
	//CoverSelector* coverSelector;
	//EnemySelector* enemySelector;
	//ClientCharacter* clientCharacter;
	//ClothAsset* clothAsset;
	//CinematicMotionDef* cinematicMotion;
	//AccessoryDef* accessory;
	//LocDmgTable* locDmgTable;
	//BulletPenetration* bulletPenetration;
	//ScriptBundle* scriptBundle;
	//BlendSpace2DDef* blendSpace2DDef;
	//XCam* xcam;
	//Camo* camo;
	//XCompositeModelDef* compositeModel;
	//XModelDetailCollision* modelDetailCollision;
	//StreamKey* streamKey;
	//StreamTreeOverride* streamTreeOverride;
	//KeyValuePairs* keyValuePairs;
	//StTerrain* stTerrain;
	//NativeScriptPatchFile* nativeScriptPatch;
	//CollisionTile* collisionTile;
	//ExecutionDef* executionDef;
	//CarryObjectDef* carryObjectDef;
	//SoundBankListDef* soundBankListDef;
	//GfxDecalVolumeMaterial* decalVolumeMaterial;
	//GfxDecalVolumeMask* decalVolumeMask;
	//DynEntityList* dynEntityList;
	void* data;
	//FxWorldTransientZone* fxWorldTransientZone;
	//DLogSchema* dlogSchema;
	//MapEdgeList* mapEdgeList;
};

enum XAssetType
{
	ASSET_TYPE_PHYSICSLIBRARY = 0x0,
	ASSET_TYPE_PHYSICSSFXEVENTASSET = 0x1,
	ASSET_TYPE_PHYSICSVFXEVENTASSET = 0x2,
	ASSET_TYPE_PHYSICSASSET = 0x3,
	ASSET_TYPE_PHYSICSFXPIPELINE = 0x4,
	ASSET_TYPE_PHYSICSFXSHAPE = 0x5,
	ASSET_TYPE_PHYSICSDEBUGDATA = 0x6,
	ASSET_TYPE_XANIM = 0x7,
	ASSET_TYPE_XMODELSURFS = 0x8,
	ASSET_TYPE_XMODEL = 0x9,
	ASSET_TYPE_MAYHEM = 0xA,
	ASSET_TYPE_MATERIAL = 0xB,
	ASSET_TYPE_COMPUTESHADER = 0xC,
	ASSET_TYPE_LIBSHADER = 0xD,
	ASSET_TYPE_VERTEXSHADER = 0xE,
	ASSET_TYPE_HULLSHADER = 0xF,
	ASSET_TYPE_DOMAINSHADER = 0x10,
	ASSET_TYPE_PIXELSHADER = 0x11,
	ASSET_TYPE_TECHSET = 0x12,
	ASSET_TYPE_IMAGE = 0x13,
	ASSET_TYPE_SOUNDGLOBALS = 0x14,
	ASSET_TYPE_SOUNDBANK = 0x15,
	ASSET_TYPE_SOUNDBANKTRANSIENT = 0x16,
	ASSET_TYPE_COL_MAP = 0x17,
	ASSET_TYPE_COM_MAP = 0x18,
	ASSET_TYPE_GLASS_MAP = 0x19,
	ASSET_TYPE_AIPATHS = 0x1A,
	ASSET_TYPE_NAVMESH = 0x1B,
	ASSET_TYPE_TACGRAPH = 0x1C,
	ASSET_TYPE_MAP_ENTS = 0x1D,
	ASSET_TYPE_FX_MAP = 0x1E,
	ASSET_TYPE_GFX_MAP = 0x1F,
	ASSET_TYPE_GFX_MAP_TRZONE = 0x20,
	ASSET_TYPE_IESPROFILE = 0x21,
	ASSET_TYPE_LIGHTDEF = 0x22,
	ASSET_TYPE_GRADINGCLUT = 0x23,
	ASSET_TYPE_UI_MAP = 0x24,
	ASSET_TYPE_FOGSPLINE = 0x25,
	ASSET_TYPE_ANIMCLASS = 0x26,
	ASSET_TYPE_PLAYERANIM = 0x27,
	ASSET_TYPE_GESTURE = 0x28,
	ASSET_TYPE_LOCALIZE = 0x29,
	ASSET_TYPE_ATTACHMENT = 0x2A,
	ASSET_TYPE_WEAPON = 0x2B,
	ASSET_TYPE_VFX = 0x2C,
	ASSET_TYPE_IMPACTFX = 0x2D,
	ASSET_TYPE_SURFACEFX = 0x2E,
	ASSET_TYPE_AITYPE = 0x2F,
	ASSET_TYPE_MPTYPE = 0x30,
	ASSET_TYPE_CHARACTER = 0x31,
	ASSET_TYPE_XMODELALIAS = 0x32,
	ASSET_TYPE_RAWFILE = 0x33,
	ASSET_TYPE_SCRIPTFILE = 0x34,
	ASSET_TYPE_SCRIPTDEBUGDATA = 0x35,
	ASSET_TYPE_STRINGTABLE = 0x36,
	ASSET_TYPE_LEADERBOARDDEF = 0x37,
	ASSET_TYPE_VIRTUALLEADERBOARDDEF = 0x38,
	ASSET_TYPE_DDL = 0x39,
	ASSET_TYPE_TRACER = 0x3A,
	ASSET_TYPE_VEHICLE = 0x3B,
	ASSET_TYPE_ADDON_MAP_ENTS = 0x3C,
	ASSET_TYPE_NETCONSTSTRINGS = 0x3D,
	ASSET_TYPE_LUAFILE = 0x3E,
	ASSET_TYPE_SCRIPTABLE = 0x3F,
	ASSET_TYPE_EQUIPSNDTABLE = 0x40,
	ASSET_TYPE_VECTORFIELD = 0x41,
	ASSET_TYPE_PARTICLESIMANIMATION = 0x42,
	ASSET_TYPE_STREAMINGINFO = 0x43,
	ASSET_TYPE_LASER = 0x44,
	ASSET_TYPE_TTF = 0x45,
	ASSET_TYPE_SUIT = 0x46,
	ASSET_TYPE_SUITANIMPACKAGE = 0x47,
	ASSET_TYPE_CAMERA = 0x48,
	ASSET_TYPE_HUDOUTLINE = 0x49,
	ASSET_TYPE_SPACESHIPTARGET = 0x4A,
	ASSET_TYPE_RUMBLE = 0x4B,
	ASSET_TYPE_RUMBLEGRAPH = 0x4C,
	ASSET_TYPE_ANIMPKG = 0x4D,
	ASSET_TYPE_SFXPKG = 0x4E,
	ASSET_TYPE_VFXPKG = 0x4F,
	ASSET_TYPE_FOOTSTEPVFX = 0x50,
	ASSET_TYPE_BEHAVIORTREE = 0x51,
	ASSET_TYPE_AIANIMSET = 0x52,
	ASSET_TYPE_AIASM = 0x53,
	ASSET_TYPE_PROCEDURALBONES = 0x54,
	ASSET_TYPE_DYNAMICBONES = 0x55,
	ASSET_TYPE_RETICLE = 0x56,
	ASSET_TYPE_XANIMCURVE = 0x57,
	ASSET_TYPE_COVERSELECTOR = 0x58,
	ASSET_TYPE_ENEMYSELECTOR = 0x59,
	ASSET_TYPE_CLIENTCHARACTER = 0x5A,
	ASSET_TYPE_CLOTHASSET = 0x5B,
	ASSET_TYPE_CINEMATICMOTION = 0x5C,
	ASSET_TYPE_ACCESSORY = 0x5D,
	ASSET_TYPE_LOCDMGTABLE = 0x5E,
	ASSET_TYPE_BULLETPENETRATION = 0x5F,
	ASSET_TYPE_SCRIPTBUNDLE = 0x60,
	ASSET_TYPE_BLENDSPACE2D = 0x61,
	ASSET_TYPE_XCAM = 0x62,
	ASSET_TYPE_CAMO = 0x63,
	ASSET_TYPE_XCOMPOSITEMODEL = 0x64,
	ASSET_TYPE_XMODELDETAILCOLLISION = 0x65,
	ASSET_TYPE_STREAMKEY = 0x66,
	ASSET_TYPE_STREAMTREEOVERRIDE = 0x67,
	ASSET_TYPE_KEYVALUEPAIRS = 0x68,
	ASSET_TYPE_STTERRAIN = 0x69,
	ASSET_TYPE_NATIVESCRIPTPATCH = 0x6A,
	ASSET_TYPE_COLLISIONTILE = 0x6B,
	ASSET_TYPE_EXECUTION = 0x6C,
	ASSET_TYPE_CARRYOBJECT = 0x6D,
	ASSET_TYPE_SOUNDBANKLIST = 0x6E,
	ASSET_TYPE_DECALVOLUMEMATERIAL = 0x6F,
	ASSET_TYPE_DECALVOLUMEMASK = 0x70,
	ASSET_TYPE_DYNENTITYLIST = 0x71,
	ASSET_TYPE_FX_MAP_TRZONE = 0x72,
	ASSET_TYPE_DLOGSCHEMA = 0x73,
	ASSET_TYPE_EDGELIST = 0x74,
};

struct XAsset
{
	XAssetType type;
	XAssetHeader header;
};

struct ScriptStringList
{
	int count;
	bool loaded;
	const char** strings;
};

struct XAssetList
{
	ScriptStringList stringList;
	unsigned int assetCount;
	unsigned int assetReadPos;
	XAsset* assets;
};

