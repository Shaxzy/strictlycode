#include "SceneEnd.h"

namespace SceneEnd
{
	//chams
	static float vis_col[3] = { 107.f / 255.f, 169.f / 255.f, 233.f / 255.f };
	static float hid_col[3] = { 130.f / 255.f, 96.f / 255.f, 224.f / 255.f };
	static float gos_col[3] = { 1.f, 1.f, 1.f };

	//fake chams
	static float white_col[3] = { 1.f, 1.f, 1.f };
	static float black_col[3] = { 0.f, 0.f, 0.f };

	SceneEnd_t g_fnOriginalSceneEnd;
	void __stdcall Hooked_SceneEnd()
	{
		g_fnOriginalSceneEnd(NSDK::I::RenderView());

		auto local = CBaseEntity::GetLocalPlayer();

		NSDK::IMaterial *material;

		/*
		for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); ++i) 
		{
			auto ent = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);

			if (ent && ent->isValidPlayer())
			{
				material = NSDK::I::MatSystem()->FindMaterial( ("chams_ignorez"), TEXTURE_GROUP_MODEL);
				if (material)
				{
					NSDK::I::RenderView()->SetColorModulation(hid_col);
					NSDK::I::ModelRender()->ForcedMaterialOverride(material);
					ent->DrawModel(0x1, 255);
				}

				material = NSDK::I::MatSystem()->FindMaterial( ("chams"), TEXTURE_GROUP_MODEL);
				if (material)
				{
					NSDK::I::RenderView()->SetColorModulation(vis_col);
					NSDK::I::ModelRender()->ForcedMaterialOverride(material);
					ent->DrawModel(0x1, 255);
				}

				NSDK::I::ModelRender()->ForcedMaterialOverride(nullptr);
			}
		}
		*/
		if (local && local->IsAlive() && NSDK::I::Input()->m_fCameraInThirdPerson == true)
		{
			material = NSDK::I::MatSystem()->FindMaterial(("chams_ignorez"), TEXTURE_GROUP_MODEL);
			if (material)
			{
				auto g_Local = CBaseEntity::GetLocalPlayer();
				NSDK::Vector curOrigin = *local->GetOrigin();
				local->SetAbsOrigin(Local::fakePos);
				local->SetAngle(NSDK::Vector(0, Local::Fake, 0));

				NSDK::I::RenderView()->SetColorModulation(white_col);
				NSDK::I::ModelRender()->ForcedMaterialOverride(material);

				local->DrawModel(0x1, 255);

				local->SetAngle(NSDK::Vector(0, *CBaseEntity::GetLocalPlayer()->GetLowerBodyYaw(), 0));

				NSDK::I::RenderView()->SetColorModulation(black_col);
				NSDK::I::ModelRender()->ForcedMaterialOverride(material);

				local->DrawModel(0x1, 255);

				NSDK::I::ModelRender()->ForcedMaterialOverride(nullptr);
				local->SetAbsOrigin(curOrigin);
			}
		}
	}
}