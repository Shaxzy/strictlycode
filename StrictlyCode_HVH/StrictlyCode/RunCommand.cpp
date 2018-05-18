#include "RunCommand.h"

namespace RunCommand
{
	RunCommand_t g_fnOrigRunCommand;
	//lagfix memes here
	void __stdcall Hooked_RunCommand(CBaseEntity* pEntity, NSDK::CUserCmd* cmd, NSDK::IMoveHelper* moveHelper)
	{
		g_fnOrigRunCommand(pEntity, cmd, moveHelper);

	}
}