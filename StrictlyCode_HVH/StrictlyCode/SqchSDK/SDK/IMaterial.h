#pragma once

#define MAXSTUDIOSKINS 32

namespace NSDK {
	enum MaterialVarFlags_t
	{
		MATERIAL_VAR_DEBUG = (1 << 0),
		MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
		MATERIAL_VAR_NO_DRAW = (1 << 2),
		MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

		MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
		MATERIAL_VAR_VERTEXALPHA = (1 << 5),
		MATERIAL_VAR_SELFILLUM = (1 << 6),
		MATERIAL_VAR_ADDITIVE = (1 << 7),
		MATERIAL_VAR_ALPHATEST = (1 << 8),
		//	MATERIAL_VAR_UNUSED					  = (1 << 9),
		MATERIAL_VAR_ZNEARER = (1 << 10),
		MATERIAL_VAR_MODEL = (1 << 11),
		MATERIAL_VAR_FLAT = (1 << 12),
		MATERIAL_VAR_NOCULL = (1 << 13),
		MATERIAL_VAR_NOFOG = (1 << 14),
		MATERIAL_VAR_IGNOREZ = (1 << 15),
		MATERIAL_VAR_DECAL = (1 << 16),
		MATERIAL_VAR_ENVMAPSPHERE = (1 << 17), // OBSOLETE
											   //	MATERIAL_VAR_UNUSED					  = (1 << 18),
											   MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19), // OBSOLETE
											   MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
											   MATERIAL_VAR_TRANSLUCENT = (1 << 21),
											   MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
											   MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23), // OBSOLETE
											   MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
											   MATERIAL_VAR_ENVMAPMODE = (1 << 25), // OBSOLETE
											   MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
											   MATERIAL_VAR_HALFLAMBERT = (1 << 27),
											   MATERIAL_VAR_WIREFRAME = (1 << 28),
											   MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
											   MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
											   MATERIAL_VAR_VERTEXFOG = (1 << 31),

											   // NOTE: Only add flags here that either should be read from
											   // .vmts or can be set directly from client code. Other, internal
											   // flags should to into the flag enum in IMaterialInternal.h
	};

	class IMaterial {
	public:
		const char* GetName() {
			typedef const char*(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 0)(this);
		}

		void IncrementReferenceCount() {
			typedef void(__thiscall *OrigFn)(void*);
			CallVFunction<OrigFn>(this, 12)(this);
		}

		void AlphaModulate(float alpha) {
			typedef void(__thiscall *OrigFn)(void*, float);
			CallVFunction<OrigFn>(this, 27)(this, alpha);
		}

		void SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) {
			typedef void(__thiscall *OrigFn)(void*, MaterialVarFlags_t, bool);
			CallVFunction<OrigFn>(this, 29)(this, flag, on);
		}

		void SetShader(const char *pShaderName) {
			typedef void(__thiscall *OrigFn)(void*, const char*);
			CallVFunction<OrigFn>(this, 34)(this, pShaderName);
		}

		const char* GetShaderName() {
			typedef const char*(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 49)(this);
		}
	};
}