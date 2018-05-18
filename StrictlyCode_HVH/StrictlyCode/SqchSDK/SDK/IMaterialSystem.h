#pragma once

#include "AllDef.h"

#define TEXTURE_GROUP_MODEL							("Model textures")
#define TEXTURE_GROUP_PARTICLE						("Particle textures")
#define TEXTURE_GROUP_CLIENT_EFFECTS				("ClientEffect textures")
#define TEXTURE_GROUP_OTHER							("Other textures")
namespace NSDK {
	class IMaterialSystem {
	public:

		IMaterial* FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL) {
			typedef IMaterial*(__thiscall *OrigFn)(void*, char const*, const char*, bool, const char*);
			return CallVFunction<OrigFn>(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
		}
	private:
		int created = 0;
	};
}