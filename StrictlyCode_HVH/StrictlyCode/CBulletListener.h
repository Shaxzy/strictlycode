#pragma once

#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"

#include "EntityStructs.h"
#include "OptionsManager.h"
#include "Globals.h"

#include "Utilities.h"
#include "DrawManager.h"

class CBulletListener
{
	class BulletListener : IGameEventListener2
	{
	public:
		void start()
		{
			if (!NSDK::I::GameEvents()->AddListener(this, "bullet_impact", false))
			{
				NSDK::I::CVar()->ConsoleColorPrintf(NSDK::Color(255, 0, 0),  ("Failed to register bullet impact listener. \n"));
			}
		}
		void stop()
		{
			NSDK::I::GameEvents()->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent* event) override
		{
			CBulletListener::singleton()->OnFireEvent(event);
		}
		int GetEventDebugID(void) override
		{
			return EVENT_DEBUG_ID_INIT /*0x2A*/;
		}
	};
public:
	static CBulletListener* singleton()
	{
		static CBulletListener* instance = new CBulletListener();
		return instance;
	}

	void init()
	{
		_listener.start();
	}

	void OnFireEvent(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "bullet_impact"))
		{
			auto index = NSDK::I::Engine()->GetPlayerUserID(event->GetInt("userid"));

			if (index != NSDK::I::Engine()->GetLocalPlayer())
				return;

			auto local = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(index);

			if (!local)
				return;

			NSDK::Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));

			NSDK::Ray_t ray;
			ray.Init(local->GetEyePos(), position);

			NSDK::CTraceFilter filter;
			filter.pSkip = local;

			NSDK::Trace_t tr;
			NSDK::I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

			logs.push_back(cbullet_tracer_info(local->GetEyePos(), position, NSDK::I::GlobalVars()->curtime, NSDK::Color(204, 102, 255, 255)));
			if (Options.iTracer == 0)
			{
				OnStudioRender();
			}
		}
	}

	void OnStudioRender()
	{

		auto local = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(NSDK::I::Engine()->GetLocalPlayer());

		if (!local)
			return;

		if (Options.iTracer == 0)
		{
			for (size_t i = 0; i < logs.size(); i++)
			{
				auto current = logs.at(i);

				NSDK::I::DebugOverlay()->AddLineOverlay(current.src, current.dst, current.color.r(), current.color.g(), current.color.b(), true, 3);
				logs.erase(logs.begin() + i);
			}
		}

		if(Options.iTracer == 1)
		{
		for (size_t i = 0; i < logs.size(); i++)
		{
			auto current = logs.at(i);

			NSDK::BeamInfo_t beamInfo;
			beamInfo.m_nType = TE_BEAMPOINTS;
			beamInfo.m_pszModelName = "sprites/physbeam.vmt";
			beamInfo.m_nModelIndex = -1;
			beamInfo.m_flHaloScale = 0;
			beamInfo.m_flLife = 3; //duration of tracers
			beamInfo.m_flWidth = 1.5; //start width
			beamInfo.m_flEndWidth = 1.5; //end width
			beamInfo.m_flFadeLength = 0.0f;
			beamInfo.m_flAmplitude = 2.0f;
			beamInfo.m_flBrightness = 255.f;
			beamInfo.m_flSpeed = 0.2f;
			beamInfo.m_nStartFrame = 0;
			beamInfo.m_flFrameRate = 0.f;
			beamInfo.m_flRed = current.color.r();
			beamInfo.m_flGreen = current.color.g();
			beamInfo.m_flBlue = current.color.b();
			beamInfo.m_nSegments = 2;
			beamInfo.m_bRenderable = true;
			beamInfo.m_nFlags = NSDK::FBEAM_ONLYNOISEONCE | NSDK::FBEAM_NOTILE | NSDK::FBEAM_HALOBEAM;

			beamInfo.m_vecStart = current.src;
			beamInfo.m_vecEnd = current.dst;

			Beam_t* myBeam = NSDK::I::RenderBeams()->CreateBeamPoints(beamInfo);
			if (myBeam)
				NSDK::I::RenderBeams()->DrawBeam(myBeam);

			logs.erase(logs.begin() + i);
		}
		}

	}

private:
	BulletListener _listener;

	class cbullet_tracer_info
	{
	public:
		cbullet_tracer_info(NSDK::Vector src, NSDK::Vector dst, float time, NSDK::Color color)
		{
			this->src = src;
			this->dst = dst;
			this->time = time;
			this->color = color;
		}

		NSDK::Vector src, dst;
		float time;
		NSDK::Color color;
	};

	std::vector<cbullet_tracer_info> logs;
};