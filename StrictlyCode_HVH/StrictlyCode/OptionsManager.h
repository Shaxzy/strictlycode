#pragma once

#include "EntityStructs.h"

class COptions
{
public:

	//menu stuff
	bool bShowMenu = false;
	bool vecPressedKeys[256] = {};

	//esp
	bool bFovring = true;
	bool bSkinchanger = true;
	bool bHealthBar = false;
	bool bBoxESP = false;
	bool bPlayerName = false;
	bool bBoneESP = false;
	bool bWeaponESP = false;
	bool bResolverESP = false;
	bool bInfoESP = false;

	//legitbot stuff
	bool bAimbot = false;
	int iHitbox = 0;
	float fAimbotFov = 0.f;
	float fSmoothing = 0.f;

	// etc
	bool bThirdperson = false;
	bool bChatSpam = false;
	bool bClantagchanger = false;
	int iConfig = 0;
	bool bBhop = false;
	float debugx = 0;
	float debugy = 0;
	int iLocalFov = 0;
	bool bTextSettings = 0;
	int iTracer = 1;
	bool bTrashTalk = false;

	//random hvh stuff
	int iAntiAim = 0;
	int iLBYType = 0;
	float fLBYDelta = 180;
	float fAwall = 5.0f;
	int iHitchance = 0;
	bool bAutoSlow = true;
	bool bHitscan = true;
	bool bAutoScope = true;
	bool bAutoShoot = true;
	bool bLBYBacktrack = true;
	bool bLBYUpdate = false;
	bool HitscanBoxes[20] = {
		true, true, true, true, true,
		true, true, true, true, true,
		true, true, true, true, true,
		true, true, true, true, true
	};
};

extern COptions Options;