#pragma once
#define cheat_name "shibahook"
namespace NSDK {

	typedef unsigned char uint8_t;
	typedef unsigned long ULONG;

	enum CSWeaponType {
		WEAPONTYPE_KNIFE,
		WEAPONTYPE_PISTOL,
		WEAPONTYPE_SUBMACHINEGUN,
		WEAPONTYPE_RIFLE,
		WEAPONTYPE_SHOTGUN,
		WEAPONTYPE_SNIPER_RIFLE,
		WEAPONTYPE_MACHINEGUN,
		WEAPONTYPE_C4,
		WEAPONTYPE_GRENADE,
		WEAPONTYPE_UNKNOWN
	};

	enum HitboxEnum_t {
		HITBOX_HEAD,
		HITBOX_NECK,
		HITBOX_LOWER_NECK,
		HITBOX_PELVIS,
		HITBOX_STOMACH,
		HITBOX_UPPER_STOMACH,
		HITBOX_CHEST,
		HITBOX_UPPER_CHEST,
		HITBOX_LEFT_THIGH,
		HITBOX_RIGHT_THIGH,
		HITBOX_LEFT_SHIN,
		HITBOX_RIGHT_SHIN,
		HITBOX_LEFT_FOOT,
		HITBOX_RIGHT_FOOT,
		HITBOX_LEFT_HAND,
		HITBOX_RIGHT_HAND,
		HITBOX_LEFT_UPPER_ARM,
		HITBOX_LEFT_FOREARM,
		HITBOX_RIGHT_UPPER_ARM,
		HITBOX_RIGHT_FOREARM
	};

	enum class EntityFlags {
		FL_ONGROUND = (1 << 0),
		FL_DUCKING = (1 << 1),
		FL_WATERJUMP = (1 << 2),
		FL_ONTRAIN = (1 << 3),
		FL_INRAIN = (1 << 4),
		FL_FROZEN = (1 << 5),
		FL_ATCONTROLS = (1 << 6),
		FL_CLIENT = (1 << 7),
		FL_FAKECLIENT = (1 << 8),
		FL_GRENADE = (1 << 20)
	};

	enum MoveType_t
	{
		MOVETYPE_NONE = 0,	// never moves
		MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
		MOVETYPE_WALK,				// Player only - moving on the ground
		MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
		MOVETYPE_FLY,				// No gravity, but still collides with stuff
		MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
		MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
		MOVETYPE_PUSH,				// no clip to world, push and crush
		MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
		MOVETYPE_LADDER,			// Used by players only when going onto a ladder
		MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
		MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

									// should always be defined as the last item in the list
									MOVETYPE_LAST = MOVETYPE_CUSTOM,

									MOVETYPE_MAX_BITS = 4
	};

	enum class FontFlags {
		FONTFLAG_NONE,
		FONTFLAG_ITALIC = 0x001,
		FONTFLAG_UNDERLINE = 0x002,
		FONTFLAG_STRIKEOUT = 0x004,
		FONTFLAG_SYMBOL = 0x008,
		FONTFLAG_ANTIALIAS = 0x010,
		FONTFLAG_GAUSSIANBLUR = 0x020,
		FONTFLAG_ROTARY = 0x040,
		FONTFLAG_DROPSHADOW = 0x080,
		FONTFLAG_ADDITIVE = 0x100,
		FONTFLAG_OUTLINE = 0x200,
		FONTFLAG_CUSTOM = 0x400,
		FONTFLAG_BITMAP = 0x800,
	};

	enum class FontDrawType {
		FONT_DRAW_DEFAULT = 0,
		FONT_DRAW_NONADDITIVE,
		FONT_DRAW_ADDITIVE,
		FONT_DRAW_TYPE_COUNT = 2,
	};

	enum class ClientFrameStage_t {
		FRAME_UNDEFINED = -1,
		FRAME_START,
		FRAME_NET_UPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_END,
		FRAME_NET_UPDATE_END,
		FRAME_RENDER_START,
		FRAME_RENDER_END
	};

	enum EItemDefinitionIndex {
		weapon_deagle = 1,
		weapon_elite = 2,
		weapon_fiveseven = 3,
		weapon_glock = 4,
		weapon_ak47 = 7,
		weapon_aug = 8,
		weapon_awp = 9,
		weapon_famas = 10,
		weapon_g3sg1 = 11,
		weapon_galilar = 13,
		weapon_m249 = 14,
		weapon_m4a4 = 16,
		weapon_mac10 = 17,
		weapon_p90 = 19,
		weapon_ump = 24,
		weapon_xm1014 = 25,
		weapon_bizon = 26,
		weapon_mag7 = 27,
		weapon_negev = 28,
		weapon_sawedoff = 29,
		weapon_tec9 = 30,
		weapon_taser = 31,
		weapon_hkp2000 = 32,
		weapon_mp7 = 33,
		weapon_mp9 = 34,
		weapon_nova = 35,
		weapon_p250 = 36,
		weapon_scar20 = 38,
		weapon_sg556 = 39,
		weapon_ssg08 = 40,
		weapon_knife = 42,
		weapon_flashbang = 43,
		weapon_hegrenade = 44,
		weapon_smokegrenade = 45,
		weapon_molotov = 46,
		weapon_decoy = 47,
		weapon_incgrenade = 48,
		weapon_c4 = 49,
		weapon_knife_t = 59,
		weapon_m4a1_silencer = 60,
		weapon_usp_silencer = 61,
		weapon_cz75a = 63,
		weapon_revolver = 64,
		weapon_bayonet = 500,
		weapon_knife_flip = 505,
		weapon_knife_gut = 506,
		weapon_knife_karambit = 507,
		weapon_knife_m9_bayonet = 508,
		weapon_knife_tactical = 509,
		weapon_knife_falchion = 512,
		weapon_knife_survival_bowie = 514,
		weapon_knife_butterfly = 515,
		weapon_knife_push = 516
	};

	enum ECSPlayerBones {
		PELVIS = 0U,
		LEAN_ROOT = 1U,
		CAM_DRIVER = 2U,
		SPINE_0 = 3U,
		SPINE_1 = 4U,
		SPINE_2 = 5U,
		SPINE_3 = 6U,
		NECK_0 = 7U,
		HEAD_0 = 8U,
		CLAVICLE_L = 9U,
		ARM_UPPER_L = 10U,
		ARM_LOWER_L = 11U,
		HAND_L = 12U,
		FINGER_MIDDLE_META_L = 13U,
		FINGER_MIDDLE_0_L = 14U,
		FINGER_MIDDLE_1_L = 15U,
		FINGER_MIDDLE_2_L = 16U,
		FINGER_PINKY_META_L = 17U,
		FINGER_PINKY_0_L = 18U,
		FINGER_PINKY_1_L = 19U,
		FINGER_PINKY_2_L = 20U,
		FINGER_INDEX_META_L = 21U,
		FINGER_INDEX_0_L = 22U,
		FINGER_INDEX_1_L = 23U,
		FINGER_INDEX_2_L = 24U,
		FINGER_THUMB_0_L = 25U,
		FINGER_THUMB_1_L = 26U,
		FINGER_THUMB_2_L = 27U,
		FINGER_RING_META_L = 28U,
		FINGER_RING_0_L = 29U,
		FINGER_RING_1_L = 30U,
		FINGER_RING_2_L = 31U,
		WEAPON_HAND_L = 32U,
		ARM_LOWER_L_TWIST = 33U,
		ARM_LOWER_L_TWIST1 = 34U,
		ARM_UPPER_L_TWIST = 35U,
		ARM_UPPER_L_TWIST1 = 36U,
		CLAVICLE_R = 37U,
		ARM_UPPER_R = 38U,
		ARM_LOWER_R = 39U,
		HAND_R = 40U,
		FINGER_MIDDLE_META_R = 41U,
		FINGER_MIDDLE_0_R = 42U,
		FINGER_MIDDLE_1_R = 43U,
		FINGER_MIDDLE_2_R = 44U,
		FINGER_PINKY_META_R = 45U,
		FINGER_PINKY_0_R = 46U,
		FINGER_PINKY_1_R = 47U,
		FINGER_PINKY_2_R = 48U,
		FINGER_INDEX_META_R = 49U,
		FINGER_INDEX_0_R = 50U,
		FINGER_INDEX_1_R = 51U,
		FINGER_INDEX_2_R = 52U,
		FINGER_THUMB_0_R = 53U,
		FINGER_THUMB_1_R = 54U,
		FINGER_THUMB_2_R = 55U,
		FINGER_RING_META_R = 56U,
		FINGER_RING_0_R = 57U,
		FINGER_RING_1_R = 58U,
		FINGER_RING_2_R = 59U,
		WEAPON_HAND_R = 60U,
		ARM_LOWER_R_TWIST = 61U,
		ARM_LOWER_R_TWIST1 = 62U,
		ARM_UPPER_R_TWIST = 63U,
		ARM_UPPER_R_TWIST1 = 64U,
		LEG_UPPER_L = 65U,
		LEG_LOWER_L = 66U,
		ANKLE_L = 67U,
		BALL_L = 68U,
		LFOOT_LOCK = 69U,
		LEG_UPPER_L_TWIST = 70U,
		LEG_UPPER_L_TWIST1 = 71U,
		LEG_UPPER_R = 72U,
		LEG_LOWER_R = 73U,
		ANKLE_R = 74U,
		BALL_R = 75U,
		RFOOT_LOCK = 76U,
		LEG_UPPER_R_TWIST = 77U,
		LEG_UPPER_R_TWIST1 = 78U,
		FINGER_PINKY_L_END = 79U,
		FINGER_PINKY_R_END = 80U,
		VALVEBIPED_WEAPON_BONE = 81U,
		LH_IK_DRIVER = 82U,
		PRIMARY_JIGGLE_JNT = 83U,
	};

	enum MathThings{
		PITCH = 0,	// up / down
		YAW,		// left / right
		ROLL		// fall over
	};
}