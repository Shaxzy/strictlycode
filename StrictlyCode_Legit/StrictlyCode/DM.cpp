#include "DM.h"
#include "OptionsManager.h"
namespace DM {

	DrawModel_t g_fnOriginalDrawModel;
	void __fastcall Hooked_DrawModel(void* thisptr, void* edx, NSDK::DrawModelResults_t *pResults, const NSDK::DrawModelInfo_t& info, NSDK::matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, const NSDK::Vector &modelOrigin, int flags)
	{
		const char *modelName = info.m_pStudioHdr->name;
		//csgosimple paster!!!
		bool IsArm = strstr(modelName, "arms") != nullptr;
		bool IsPlayer = strstr(modelName, "models/player") != nullptr;
		bool IsSleeve = strstr(modelName, "sleeve") != nullptr;
		bool IsWeapon = (strstr(modelName, "weapons/v_") != nullptr) || (strstr(modelName, "weapons/w_") != nullptr);
		g_fnOriginalDrawModel(thisptr, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, modelOrigin, flags);
		NSDK::I::StudioRender()->ForcedMaterialOverride(NULL);
	}


	void CreateVisibleVMT() {
		std::ifstream file(XorStr("csgo\\materials\\chams.vmt"));

		if (!file.good()) {
			std::string str =
				XorStr(R"###("VertexLitGeneric"
            {
                "$basetexture" "VGUI/white_additive"
                "$ignorez"     "0"
                "$nofog"       "1"
                "$model"       "1"
                "$nocull"      "1"
                "$halflambert" "1"
            })###");

			std::ofstream(XorStr("csgo\\materials\\chams.vmt")) << str;
		}
	}

	void CreateIgnoreZVMT() {
		std::ifstream file(XorStr("csgo\\materials\\chams_ignorez.vmt"));

		if (!file.good()) {
			std::string str =
				XorStr(R"###("VertexLitGeneric"
            {
                "$basetexture" "VGUI/white_additive"
                "$ignorez"     "1"
                "$nofog"       "1"
                "$model"       "1"
                "$nocull"      "1"
                "$halflambert" "1"
            })###");

			std::ofstream(XorStr("csgo\\materials\\chams_ignorez.vmt")) << str;
		}
	}

	void CreateVisibleWireVMT() {
		std::ifstream file(XorStr("csgo\\materials\\chams_wire.vmt"));

		if (!file.good()) {
			std::string str =
				XorStr(R"###("VertexLitGeneric"
            {
                "$basetexture" "VGUI/white_additive"
                "$ignorez"     "0"
                "$nofog"       "1"
                "$model"       "1"
                "$nocull"      "1"
                "$halflambert" "1"
				"$wireframe"   "1"
            })###");

			std::ofstream(XorStr("csgo\\materials\\chams_wire.vmt")) << str;
		}
	}

	void InitChams() {
		CreateVisibleVMT();
		CreateVisibleWireVMT();
		CreateIgnoreZVMT();
	}
}