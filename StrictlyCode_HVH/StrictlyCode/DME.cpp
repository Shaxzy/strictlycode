#include "DME.h"
#include "OptionsManager.h"
static bool bInit = false;
namespace DME 
{
	DrawModelExecute_t g_fnOriginalDrawModelExecute;
	void __fastcall Hooked_DrawModelExecute(void* thisptr, void* edx, NSDK::IMatRenderContext* ctx, const NSDK::DrawModelState_t& state, const NSDK::ModelRenderInfo_t& pInfo, NSDK::matrix3x4_t* pCustomBoneToWorld)
	{
		g_fnOriginalDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

		if (!bInit)
		{
			std::ofstream("csgo\\materials\\chams_material_XQZ.vmt") << R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";

			std::ofstream("csgo\\materials\\chams_material.vmt") << R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";
			bInit = true;
		}
		auto material = NSDK::I::MatSystem()->FindMaterial( ("chams_ignorez"), TEXTURE_GROUP_MODEL);

	}
}