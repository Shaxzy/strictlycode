#pragma once

#include "EntityStructs.h"

class VarMapEntry_t {
public:
	unsigned short type;
	unsigned short m_bNeedsToInterpolate;
	void *data;
	void *watcher;
};

struct VarMapping_t {
	VarMapping_t() {
		m_nInterpolatedEntries = 0;
	}

	VarMapEntry_t* m_Entries;
	int m_nInterpolatedEntries;
	float m_lastInterpolationTime;
};

class CLagcompensation {
	VarMapping_t* GetVarMap(void* pBaseEntity) {
		return reinterpret_cast<VarMapping_t*>((DWORD)pBaseEntity + 0x24); //0x4C );
	}

public:
	void anim_fix(NSDK::ClientFrameStage_t stage)
	{
		auto g_Local = CBaseEntity::GetLocalPlayer();

		if (!g_Local)
			return;

		if (!g_Local->IsAlive())
			return;

		static int userId[64];
		static NSDK::AnimationLayer
			backupLayersUpdate[64][15],
			backupLayersInterp[64][15];

		for (int i = 1; i < NSDK::I::Engine()->GetMaxClients(); i++)
		{
			CBaseEntity *player = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(i);

			if (!player ||
				player == g_Local ||
				*player->GetTeamNum() == *g_Local->GetTeamNum() ||
				!player->isValidPlayer())
				continue;

			NSDK::PlayerInfo player_info;
			NSDK::I::Engine()->GetPlayerInfo(i, &player_info);

			switch (stage)
			{
			case NSDK::ClientFrameStage_t::FRAME_NET_UPDATE_START: // Copy new, server layers to use when drawing.
				userId[i] = player_info.iSteamID;
				memcpy(&backupLayersUpdate[i], player->GetAnimOverlays(), (sizeof NSDK::AnimationLayer) * player->GetNumAnimOverlays());
				break;
			case NSDK::ClientFrameStage_t::FRAME_RENDER_START: // Render started, don't use inaccurately extrapolated layers but save them to not mess shit up either.
				if (userId[i] != player_info.iSteamID) continue;
				memcpy(&backupLayersInterp[i], player->GetAnimOverlays(), (sizeof NSDK::AnimationLayer) * player->GetNumAnimOverlays());
				memcpy(player->GetAnimOverlays(), &backupLayersUpdate[i], (sizeof NSDK::AnimationLayer) * player->GetNumAnimOverlays());
				break;
			case NSDK::ClientFrameStage_t::FRAME_RENDER_END: // Restore layers to keep being accurate when backtracking.
				if (userId[i] != player_info.iSteamID) continue;
				memcpy(player->GetAnimOverlays(), &backupLayersInterp[i], (sizeof NSDK::AnimationLayer) * player->GetNumAnimOverlays());
				break;
			default:
				return;
			}
		}
	}

	void disable_interp(CBaseEntity* m_entity) 
	{
		VarMapping_t* map = GetVarMap(m_entity);
		if (!map) return;
		for (int i = 0; i < map->m_nInterpolatedEntries; i++) {
			VarMapEntry_t *e = &map->m_Entries[i];
			e->m_bNeedsToInterpolate = false;
		}
	}
};
extern CLagcompensation lagcompensation;