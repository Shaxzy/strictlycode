#include "CEnginePred.h"
#include "SqchSDK\SDKHelper\checksum_md5.hpp"
#include "EntityStructs.h"
#include "Utilities.h"

#define CLIENT_LIB "client.dll"
#define ENGINE_LIB "engine.dll"

#define PREDICTION_RANDOM_SEED "A3 ? ? ? ? 66 0F 6E 86"
#define SET_PREDICTION_PLAYER "89 35 ? ? ? ? F3 0F 10 48"
//~ ~ ~ ~  Engine Prediction  ~ ~ ~ ~//
/*
Credits:

Coded by: (c)Valve
Referenced: zbe
Reversed by: _xAE^, Flaw
with help from pre-existing reversed material

Summary:
Engine Prediction is the functionality of RunCommand reversed and used during Createmove to get higher accuracy while moving at high velocities.
It basically predicts our own next moves (as localplayer)

What does the code do:
-Back up m_fFlags
-Back up cmd->buttons
-Set m_pCurrentCommand to cmd
-Set SetHost to Localplayer
-Set PredictionRandomSeed to the MD5 of cmd->command_number & 0x7FFFFFFF
-Set PredictionPlayer to localplayer
-Set curtime to tickbase * interval_per_tick
-Set frametime to interval_per_tick
-Set m_nButtons |= (localplayer) + 0x3301
-Check for cmd->impulse and if true, set m_nImpulse to cmd->impulse
-Set C_MoveData.m_nButtons to cmd->buttons
-Create a new integer named buttonsChanged and set it to cmd->buttons ^(xor) (local) + 0x31E8
-Set (localplayer) + 0x31DC to (localplayer) + 0x31E8
-Set (localplayer) + 0x31E8 to cmd->buttons
-Set (localplayer) + 0x31E0 to cmd->buttons & buttonsChanged
-Set (localplayer) + 0x31E4 to buttonsChanged & ~cmd->buttons
-Create a static char to store movedata and use calloc or malloc and use the sizeof(CMoveData) for it's memory allocation
-Set StartTrackPredictionErrors to localplayer
-Back up Tickbase
-Set SetupMove to use the static char that we made earlier that allocates the memory of the SizeOf(CMoveData)
-Set ProcessMove to the same as SetupMove
-Set FinishMove to the same as SetupMove
-Override tickbase to saved tickbase
-Set FinishTrackPredictionErrors to localplayer
-Set m_pCurrentCommand to nullptr
-Set PredictionRandomSeed to -1
-Set PredictionPlayer to 0
-Set SetHost to 0
-Set m_fFlags to backup m_fFlags
-Set cmd->buttons to backup cmd->buttons

References:
https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/game/shared/baseplayer_shared.cpp#L753
zbe's TF2 Base

Special thanks to:
zbe		 - Notifying me of errors
friendly - Helping me with a signature (Was reading mov by accident)
*/

int iTickBaseBackup;
int iFlagsBackup;
int iButtonsBackup;
int* m_pPredictionRandomSeed;
int* m_pSetPredictionPlayer;
static char* cMoveData = nullptr;

void EnginePred::EnginePrediction(NSDK::CUserCmd* cmd)
{
	//Nullptr'ing is fun!
	//havent got interface for pred
	if (!NSDK::I::Prediction() || !cmd || !CBaseEntity::GetLocalPlayer())
		return;

	//We need to cast g_LocalPlayer to C_BasePlayer so we can use it in our code
	auto localplayer = CBaseEntity::GetLocalPlayer();
	NSDK::CMoveData C_MoveData;

	//Let's back things up for later use
	iFlagsBackup = *localplayer->GetFlags();
	iButtonsBackup = cmd->buttons;

	//Set m_pCurrentCommand to cmd. We'll set this to nullptr later.
	localplayer->m_pCurrentCommand() = cmd;

	//Let's get some signatures now
	if (!m_pPredictionRandomSeed || !m_pSetPredictionPlayer)
	{
		m_pPredictionRandomSeed = *reinterpret_cast<int**>(NSDK::O::FindSignature((CLIENT_LIB), PREDICTION_RANDOM_SEED) + 1);
		m_pSetPredictionPlayer = *reinterpret_cast<int**>(NSDK::O::FindSignature((CLIENT_LIB), SET_PREDICTION_PLAYER) + 2);
	}

	//We don't want to be calling this every tick, bad for framerate.
	//Thanks, zbe and Heep
	if (!cMoveData)
		cMoveData = (char*)(calloc(1, sizeof(NSDK::CMoveData)));
	
	//Let's set it up so that it predicts ourselves
	NSDK::O::MoveHelper()->SetHost(localplayer);
	*m_pPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;
	*m_pSetPredictionPlayer = uintptr_t(localplayer);

	//Let's set some global variables
	NSDK::I::GlobalVars()->curtime = *localplayer->GetTickBase() * NSDK::I::GlobalVars()->interval_per_tick;
	NSDK::I::GlobalVars()->frametime = NSDK::I::GlobalVars()->interval_per_tick;

	//Don't know is for exactly, but here's the relevant IDA picture of it. https://i.imgur.com/hT6caQV.png
	cmd->buttons |= *reinterpret_cast< uint8_t* >(uintptr_t(localplayer) + 0x3310);

	//This is for flashlights in older Source games, Thanks, friendly for the info
	if (cmd->impulse)
		*reinterpret_cast< uint8_t* >(uintptr_t(localplayer) + 0x31EC) = cmd->impulse;

	//Here we're doing CBasePlayer::UpdateButtonState
	C_MoveData.m_nButtons = cmd->buttons;
	int buttonsChanged = cmd->buttons ^ *reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31E8);
	*reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31DC) = (uintptr_t(localplayer) + 0x31E8);
	*reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31E8) = cmd->buttons;
	*reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31E0) = cmd->buttons & buttonsChanged;  //m_afButtonPressed ~ The changed ones still down are "pressed"
	*reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31E4) = buttonsChanged & ~cmd->buttons; //m_afButtonReleased ~ The ones not down are "released"

	NSDK::I::GameMovement()->StartTrackPredictionErrors(localplayer);

	iTickBaseBackup = *localplayer->GetTickBase();

	NSDK::I::Prediction()->SetupMove(localplayer, cmd, NSDK::O::MoveHelper(), reinterpret_cast< NSDK::CMoveData* >(cMoveData));
	NSDK::I::GameMovement()->ProcessMovement(localplayer, reinterpret_cast< NSDK::CMoveData* >(cMoveData));
	NSDK::I::Prediction()->FinishMove(localplayer, cmd, reinterpret_cast< NSDK::CMoveData* >(cMoveData));

	//Let's override our tickbase with the backed up tickbase
	*localplayer->GetTickBase() = iTickBaseBackup;

	NSDK::I::GameMovement()->FinishTrackPredictionErrors(localplayer);

	//Let's nullify these here
	localplayer->m_pCurrentCommand() = nullptr;
	*m_pPredictionRandomSeed = -1;
	*m_pSetPredictionPlayer = 0;
	
	NSDK::O::MoveHelper()->SetHost(0);

	//Last but not least, set these to their backups 
	*localplayer->GetFlags() = iFlagsBackup;
	cmd->buttons = iButtonsBackup;
}
