#include "SceneEnd.h"

namespace SceneEnd
{
	static float vis_col[3] = { 107.f / 255.f, 169.f / 255.f, 233.f / 255.f };
	static float hid_col[3] = { 130.f / 255.f, 96.f / 255.f, 224.f / 255.f };
	static float gos_col[3] = { 1.f, 1.f, 1.f };

	SceneEnd_t g_fnOriginalSceneEnd;
	void __stdcall Hooked_SceneEnd()
	{
		g_fnOriginalSceneEnd(NSDK::I::RenderView());

		auto local = CBaseEntity::GetLocalPlayer();

		NSDK::IMaterial *material;

		for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); ++i) {
			auto ent = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);

			if (ent && ent->isValidPlayer())
			{
				material = NSDK::I::MatSystem()->FindMaterial(XorStr("chams_ignorez"), TEXTURE_GROUP_MODEL);
				if (material)
				{
					NSDK::I::RenderView()->SetColorModulation(hid_col);
					NSDK::I::ModelRender()->ForcedMaterialOverride(material);
					ent->DrawModel(0x1, 255);
					/*
					if (Options.bBacktracking)
					{
						//set abs origin then draw model again.
						auto& cur = Backtracking.ticks[0];
						NSDK::Vector orig = ent->GetAbsOrigin();
						ent->SetAbsOrigin(cur.records.front().origin);
						ent->DrawModel(0x1, 255);
						ent->SetAbsOrigin(orig);
					}
					*/
				}

				material = NSDK::I::MatSystem()->FindMaterial(XorStr("chams"), TEXTURE_GROUP_MODEL);
				if (material)
				{
					NSDK::I::RenderView()->SetColorModulation(vis_col);
					NSDK::I::ModelRender()->ForcedMaterialOverride(material);
					ent->DrawModel(0x1, 255);
					/*
					if (Options.bBacktracking)
					{
						//set abs origin then draw model again. cant figure out how to loop through ticks
						auto& cur = Backtracking.ticks[0];
						NSDK::Vector orig = ent->GetAbsOrigin();
						ent->SetAbsOrigin(cur.records.front().origin);
						ent->DrawModel(0x1, 255);
						ent->SetAbsOrigin(orig);
					}
					*/
				}

				NSDK::I::ModelRender()->ForcedMaterialOverride(nullptr);
			}
		}
	}
}