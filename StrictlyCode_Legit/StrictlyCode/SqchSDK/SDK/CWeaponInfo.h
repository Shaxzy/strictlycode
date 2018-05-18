#pragma once

namespace NSDK {
	/*class WeaponInfo_t
	{
	public:
		char pad_0x0000[99];	//0x0000
		char m_name[80];			//0x00
		char pad_0x0800[0x74D];	//0x0000 Updated (Structure)
		float m_flArmorRatio;		//0x07B0 
		float unkwn1;				//0x07B4 
		float unkwn2;				//0x07B8 
		__int32 unkwn3;				//0x07BC 
		__int32 unkwn4;				//0x07C0 
		float m_flPenetration;		//0x07C4 
		__int32 m_iDamage;			//0x07C8 
		float m_flRange;			//0x07CC 
		float m_flRangeModifier;	//0x07D0 
	};*/

	struct CHudTexture
	{
		char	szShortName[64];	//0x0000
		char	szTextureFile[64];	//0x0040
		bool	bRenderUsingFont;	//0x0080
		bool	bPrecached;			//0x0081
		char	cCharacterInFont;	//0x0082
		char    pad;		        //0x0083
		HFont	hFont;				//0x0084
		int		iTextureId;			//0x0088
		float	afTexCoords[4];		//0x008C
		int		iPosX[4];			//0x009C
	}; //Size=0x00AC

	class WeaponInfo_t
	{
	public:
		char		pad00[0xC8];
		int			iWeaponType;		// 0xC8
		char		padCC[0x20];
		int			iDamage;			// 0xEC
		float		flArmorRatio;		// 0xF0
		char		padF4[0x4];
		float		flPenetration;	// 0xF8
		char		padFC[0x8];
		float		flRange;			// 0x104
		float		flRangeModifier;	// 0x108
		char		pad10C[0x10];
		bool		m_HasSilencer;		// 0x11C
		char		pad_0x0119[3];			// 0x011D
		char*		pSilencerModel;			// 0x0120
		int			iCrosshairMinDistance;	// 0x0124
		int			iCrosshairDeltaDistance;// 0x0128 - iTeam?
		float		flMaxPlayerSpeed;		// 0x012C
		float		flMaxPlayerSpeedAlt;	// 0x0130
		float		flSpread;				// 0x0134
		float		flSpreadAlt;			// 0x0138
		float		flInaccuracyCrouch;		// 0x013C
		float		flInaccuracyCrouchAlt;	// 0x0140
		float		flInaccuracyStand;		// 0x0144
		float		flInaccuracyStandAlt;	// 0x0148
		float		flInaccuracyJumpInitial;// 0x014C
		float		flInaccuracyJump;		// 0x0150
		float		flInaccuracyJumpAlt;	// 0x0154
		float		flInaccuracyLand;		// 0x0158
		float		flInaccuracyLandAlt;	// 0x015C
		float		flInaccuracyLadder;		// 0x0160
		float		flInaccuracyLadderAlt;	// 0x0164
		float		flInaccuracyFire;		// 0x0168
		float		flInaccuracyFireAlt;	// 0x016C
		float		flInaccuracyMove;		// 0x0170
		float		flInaccuracyMoveAlt;	// 0x0174
		float		flInaccuracyReload;		// 0x0178
		int			iRecoilSeed;			// 0x017C
		float		flRecoilAngle;			// 0x0180
		float		flRecoilAngleAlt;		// 0x0184
		float		flRecoilAngleVariance;	// 0x0188
		float		flRecoilAngleVarianceAlt;	// 0x018C
		float		flRecoilMagnitude;		// 0x0190
		float		flRecoilMagnitudeAlt;	// 0x0194
		float		flRecoilMagnitudeVariance;	// 0x0198
		float		flRecoilMagnitudeVarianceAlt;	// 0x019C
		float		flRecoveryTimeCrouch;	// 0x01A0
		float		flRecoveryTimeStand;	// 0x01A4
		float		flRecoveryTimeCrouchFinal;	// 0x01A8
		float		flRecoveryTimeStandFinal;	// 0x01AC
		int			iRecoveryTransitionStartBullet;// 0x01B0 
		int			iRecoveryTransitionEndBullet;	// 0x01B4
		bool		bUnzoomAfterShot;		// 0x01B8
		bool		bHideViewModelZoomed;	// 0x01B9
		char		pad_0x01B5[2];			// 0x01BA
		char		iZoomLevels[3];			// 0x01BC
		int			iZoomFOV[2];			// 0x01C0
		float		fZoomTime[3];			// 0x01C4
		char*		szWeaponClass;			// 0x01D4
		float		flAddonScale;			// 0x01D8
		char		pad_0x01DC[4];			// 0x01DC
		char*		szEjectBrassEffect;		// 0x01E0
		char*		szTracerEffect;			// 0x01E4
		int			iTracerFrequency;		// 0x01E8
		int			iTracerFrequencyAlt;	// 0x01EC
		char*		szMuzzleFlashEffect_1stPerson; // 0x01F0
		char		pad_0x01F4[4];			 // 0x01F4
		char*		szMuzzleFlashEffect_3rdPerson; // 0x01F8
		char		pad_0x01FC[4];			// 0x01FC
		char*		szMuzzleSmokeEffect;	// 0x0200
		float		flHeatPerShot;			// 0x0204
		char*		szZoomInSound;			// 0x0208
		char*		szZoomOutSound;			// 0x020C
		float		flInaccuracyPitchShift;	// 0x0210
		float		flInaccuracySoundThreshold;	// 0x0214
		float		flBotAudibleRange;		// 0x0218
		BYTE		pad_0x0218[8];			// 0x0220
		char*		pWrongTeamMsg;			// 0x0224
		bool		bHasBurstMode;			// 0x0228
		BYTE		pad_0x0225[3];			// 0x0229
		bool		bIsRevolver;			// 0x022C
		bool		bCannotShootUnderwater;	// 0x0230



	};
}