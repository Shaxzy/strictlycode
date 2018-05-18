#pragma once

#include "..\SDKHelper\Utilities.h"

namespace NSDK {
	class IVRenderView {
	public:
		void SetColorModulation(float const* blend){
			typedef void(__thiscall *OrigFn)(void*, float const*);
			CallVFunction<OrigFn>(this, 6)(this, blend);
		}
	};
}