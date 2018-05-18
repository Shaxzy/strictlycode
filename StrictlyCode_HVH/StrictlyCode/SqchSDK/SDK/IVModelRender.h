#pragma once

#include "Vector.h"
#include "QAngle.h"
#include "VMatrix.h"
#include "IMaterial.h"

namespace NSDK {
	class IMatRenderContext;
	struct DrawModelState_t;
	struct model_t;
	typedef unsigned short ModelInstanceHandle_t;

	enum OverrideType_t
	{
		OVERRIDE_NORMAL = 0,
		OVERRIDE_BUILD_SHADOWS,
		OVERRIDE_DEPTH_WRITE,
	};

	struct ModelRenderInfo_t
	{
		Vector origin;
		QAngle angles;
		void *pRenderable;
		const model_t *pModel;
		const matrix3x4_t *pModelToWorld;
		const matrix3x4_t *pLightingOffset;
		const Vector *pLightingOrigin;
		int flags;
		int entity_index;
		int skin;
		int body;
		int hitboxset;
		ModelInstanceHandle_t instance;

		ModelRenderInfo_t()
		{
			pModelToWorld = NULL;
			pLightingOffset = NULL;
			pLightingOrigin = NULL;
		}
	};

	class IVModelRender {
	public:
		void ForcedMaterialOverride(IMaterial *newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL, int unknown = NULL) {
			typedef void(__thiscall *OrigFn)(void*, IMaterial*, OverrideType_t, int);
			CallVFunction<OrigFn>(this, 1)(this, newMaterial, nOverrideType, unknown);
		}
	};
}