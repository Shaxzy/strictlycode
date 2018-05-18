#pragma once
#include "NetvarManager.h"
#include "VTHooksManager.h"
#include "DrawManager.h"

#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"

#include "PT.h"
#include "DirectX.h"
#include "DM.h"
#include "DME.h"
#include "FSN.h"
#include "CHLCM.h"
#include "RView.h"
#include "OView.h"
#include "FireBulletsPostDataUpdate.h"

namespace Hooks {
	void Initialize();
	void RestoreAllTable();
}