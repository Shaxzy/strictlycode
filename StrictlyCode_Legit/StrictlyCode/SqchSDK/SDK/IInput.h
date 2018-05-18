#pragma once

#include "../SDKHelper/Utilities.h"
#include "CInput.h"

namespace NSDK {
	class IInput: public CInput {
	public:
		CUserCmd *GetUserCmd(int nSlot, int sequence_number) {
			typedef CUserCmd*(__thiscall *OrigFn)(void*, int, int);
			return CallVFunction<OrigFn>(this, 8)(this, nSlot, sequence_number);
		}
	};
}