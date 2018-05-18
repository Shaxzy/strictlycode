#pragma once

#include "Vector.h"

namespace NSDK {
	class ICollideable {
	public:
		const Vector& OBBMins() {
			typedef Vector&(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 1)(this);
		}
		const Vector& OBBMaxs() {
			typedef Vector&(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 2)(this);
		}
	};
}