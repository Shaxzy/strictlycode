#pragma once

#include "Studio.h"

namespace NSDK {
	class IVModelInfo {
	public:
		int GetModelIndex(const char *name) 
		{
			typedef int(__thiscall *OrigFn)(void*, const char *);
			return CallVFunction<OrigFn>(this, 2)(this, name);
		}

		const char* GetModelName(const model_t *model) {
			typedef const char*(__thiscall *OrigFn)(void*, const model_t *);
			return CallVFunction<OrigFn>(this, 3)(this, model);
		}

		void GetModelMaterials(const model_t *model, int count, IMaterial** ppMaterials) {
			typedef void(__thiscall *OrigFn)(void*, const model_t *, int, IMaterial**);
			CallVFunction<OrigFn>(this, 17)(this, model, count, ppMaterials);
		}

		studiohdr_t* GetStudiomodel(const model_t *model) {
			typedef studiohdr_t*(__thiscall *OrigFn)(void*, const model_t *);
			return CallVFunction<OrigFn>(this, 32)(this, model);
		}
	};
}