#pragma once

#include "Studio.h"

namespace NSDK {


	struct DrawModelResults_t;
	struct studiohwdata_t;
	struct ColorMeshInfo_t;
	struct StudioDecalHandle_t { int unused; };

	enum LightType_t
	{
		MATERIAL_LIGHT_DISABLE = 0,
		MATERIAL_LIGHT_POINT,
		MATERIAL_LIGHT_DIRECTIONAL,
		MATERIAL_LIGHT_SPOT,
	};

	struct LightDesc_t
	{
		LightType_t m_Type;										//< MATERIAL_LIGHT_xxx
		Vector m_Color;											//< color+intensity 
		Vector m_Position;										//< light source center position
		Vector m_Direction;										//< for SPOT, direction it is pointing
		float  m_Range;											//< distance range for light.0=infinite
		float m_Falloff;										//< angular falloff exponent for spot lights
		float m_Attenuation0;									//< constant distance falloff term
		float m_Attenuation1;									//< linear term of falloff
		float m_Attenuation2;									//< quadatic term of falloff

																// NOTE: theta and phi are *half angles*
		float m_Theta;											//< inner cone angle. no angular falloff 
																//< within this cone
		float m_Phi;											//< outer cone angle

																// the values below are derived from the above settings for optimizations
																// These aren't used by DX8. . used for software lighting.

																// NOTE: These dots are cos( m_Theta ), cos( m_Phi )
		float m_ThetaDot;
		float m_PhiDot;
		float m_OneOverThetaDotMinusPhiDot;
		unsigned int m_Flags;
	protected:
		float m_RangeSquared;
	};


	struct MaterialLightingState_t
	{
		Vector			m_vecAmbientCube[6];		// ambient, and lights that aren't in locallight[]
		Vector			m_vecLightingOrigin;		// The position from which lighting state was computed
		int				m_nLocalLightCount;
		LightDesc_t		m_pLocalLightDesc[4];

	};

	struct DrawModelInfo_t
	{
		studiohdr_t		*m_pStudioHdr;
		studiohwdata_t	*m_pHardwareData;
		StudioDecalHandle_t m_Decals;
		int				m_Skin;
		int				m_Body;
		int				m_HitboxSet;
		void			*m_pClientEntity;
		int				m_Lod;
		ColorMeshInfo_t	*m_pColorMeshes;
		bool			m_bStaticLighting;
		MaterialLightingState_t	m_LightingState;
	};

	class IStudioRender {
	public:
		void SetColorModulation(float const* pColor) {
			typedef void(__thiscall *OrigFn)(void*, float const*);
			CallVFunction<OrigFn>(this, 28)(this, pColor);
		}

		void ForcedMaterialOverride(IMaterial *newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL, int unknown = NULL) {
			typedef void(__thiscall *OrigFn)(void*, IMaterial*, OverrideType_t, int);
			CallVFunction<OrigFn>(this, 33)(this, newMaterial, nOverrideType, unknown);
		}
	};
}