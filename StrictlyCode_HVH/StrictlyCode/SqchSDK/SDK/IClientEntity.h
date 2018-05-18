#pragma once

#include "IClientNetworkable.h"
#include "ICollideable.h"
#include "VMatrix.h"
#include "CHandle.h"

namespace NSDK {
	struct model_t;

	class IClientEntity { // 0x00 -> IClientUnknown, 0x04 IClientRenderable, 0x08 IClientNetworkable, ..
	public:
		const CBaseHandle& GetRefEHandle() {
			typedef const CBaseHandle&(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 2)(this);
		}

		ICollideable* GetCollideable() {
			typedef ICollideable*(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 3)(this);
		}

		const model_t* GetModel()
		{
			void *pRenderable = (void*)(this + 0x4);
			typedef const model_t*(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(pRenderable, 8)(pRenderable);
		}

		bool SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) {
			void *pRenderable = (void*)(this + 0x4);
			typedef bool(__thiscall *OrigFn)(void*, matrix3x4_t*, int, int, float);
			return CallVFunction<OrigFn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
		}

		ClientClass* GetClientClass() {
			void *pNetworked = (void*)(this + 0x8);
			typedef ClientClass*(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(pNetworked, 2)(pNetworked);
		}

		bool IsDormant() {
			void *pNetworked = (void*)(this + 0x8);
			typedef bool(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(pNetworked, 9)(pNetworked);
		}

		int EntIndex()
		{
			void *pNetworked = (void*)(this + 0x8);
			typedef int(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(pNetworked, 10)(pNetworked);
		}
	};
}