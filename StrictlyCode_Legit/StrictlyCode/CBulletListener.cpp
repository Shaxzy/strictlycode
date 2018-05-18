#include "CBulletListener.h"
#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"

#include "EntityStructs.h"
#include "OptionsManager.h"
#include "Utilities.h"
#include "Utilities.h"
#include "DrawManager.h"
void CBulletListener::cbullet_tracer_info::OnRender()
{

	auto local = (CBaseEntity*)SSDK::I::EntityList()->GetClientEntity(SSDK::I::Engine()->GetLocalPlayer());

	if (!local)
		return;

	for (size_t i = 0; i < logs.size(); i++)
	{
		auto current = logs.at(i);
		SSDK::I::DebugOverlay()->AddLineOverlay(current.src, current.dst, 255, 0, 0, true, -1.f);
		if (fabs(SSDK::I::GlobalVars()->curtime - current.time) > 3.f)
			logs.erase(logs.begin() + i);
}

	void CBulletListener::cbullet_tracer_info::log(IGameEvent * event)
	{
		//if we receive bullet_impact event
		if (strstr(event->GetName(), "bullet_impact"))
		{
			//get the user who fired the bullet
			auto index = Interfaces::Engine()->GetPlayerForUserID(event->GetInt("userid"));

			//return if the userid is not valid or we werent the entity who was fireing
			if (index != Interfaces::Engine()->GetLocalPlayer())
				return;

			//get local player
			auto local = static_cast<C_BasePlayer*>(Interfaces::EntityList()->GetClientEntity(index));
			if (!local)
				return;

			//get the bullet impact's position
			SSDK::Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));

			SSDK::Ray_t ray;
			ray.Init(local->GetEyePosition(), position);

			//skip local player
			SSDK::CTraceFilter filter;
			filter.pSkip = local;

			//trace a ray
			SSDK::Trace_t tr;
			SSDK::I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

			//use different color when we hit a player
			auto color = (tr.m_pEnt && reinterpret_cast<C_BasePlayer*>(tr.m_pEnt)->IsPlayer()) ? Color(140, 29, 29, 220) : Color(255, 255, 0, 220);

			//push info to our vector
			logs.push_back(cbullet_tracer_info(local->GetEyePosition(), position, Interfaces::Globals()->curtime, color));

	}
