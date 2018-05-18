#pragma once
#include "EntityStructs.h"
namespace RunCommand
{
	typedef void(__stdcall* RunCommand_t)(CBaseEntity*, NSDK::CUserCmd*, NSDK::IMoveHelper*);

	extern RunCommand_t g_fnOrigRunCommand;

	void __stdcall Hooked_RunCommand(CBaseEntity* pEntity, NSDK::CUserCmd* cmd, NSDK::IMoveHelper* moveHelper);
}