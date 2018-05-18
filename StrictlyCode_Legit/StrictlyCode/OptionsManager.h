#pragma once

#include "EntityStructs.h"

class COptions
{
public:

	//menu stuff
	bool bShowMenu = false;
	bool vecPressedKeys[256] = {};

	//esp
	bool bSoundESP = false;
	bool bFovring = true;
	bool bSkinchanger = true;
	bool bHealthBar = false;
	bool bBoxESP = false;
	bool bPlayerName = false;
	bool bBoneESP = false;
	bool bWeaponESP = false;

	//legitbot stuff
	bool bAimbot = false;
	bool bBacktracking = false;
	bool bLuckShot = false;
	bool bSmoothing = false;
	int iHitbox = 0;
	int iLuckShotRate = 0;
	float fNormalFov = 0.f;
	float fSmoothing = 0.f;

	// etc
	bool bChatSpam = false;
	bool bClantagchanger = false;
	int iConfig = 0;
	bool bBhop = false;
	int debugx = 0;
	int debugy = 0;
	int iLocalFov = 0;

	//colors
	NSDK::Color fov_ring_color = NSDK::Color(255, 0, 0, 255);
	NSDK::Color box_enemy_color = NSDK::Color(255, 0, 0, 255);
	NSDK::Color box_team_color = NSDK::Color(0, 255, 0, 255);
	NSDK::Color player_name_team_color = NSDK::Color(255, 255, 255, 255);
	NSDK::Color player_name_enemy_color = NSDK::Color(255, 255, 255, 255);
	NSDK::Color weapon_team_color = NSDK::Color(255, 255, 255, 255);
	NSDK::Color weapon_enemy_color = NSDK::Color(255, 255, 255, 255);

	NSDK::Color logo_box_color = NSDK::Color(51, 153, 200, 35);
	NSDK::Color logo_text_color = NSDK::Color(105, 105, 105, 230);
};

extern COptions Options;