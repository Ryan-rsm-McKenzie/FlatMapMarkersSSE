#include "Hooks.h"

#include "skse64_common/BranchTrampoline.h"  // g_branchTrampoline
#include "skse64_common/Relocation.h"  // RelocAddr
#include "skse64_common/Utilities.h"  // GetFnAddr

#include "Settings.h"  // Settings

#include "RE/Misc.h"  // WorldPtToScreenPt3
#include "RE/NiCamera.h"  // NiCamera
#include "RE/NiRect.h"  // NiRect
#include "RE/NiPoint3.h"  // NiPoint3


void Hook_WorldPtToScreenPt3(RE::NiCamera* a_camera, RE::NiPoint3& a_in, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance)
{
	if (Settings::enabled) {
		a_in.z = Settings::markerHeight;
	}
	RE::WorldPtToScreenPt3(a_camera->worldToCam, a_camera->port, a_in, a_xOut, a_yOut, a_zOut, a_zeroTolerance);
}


void InstallHooks()
{
	constexpr uintptr_t TARGET = 0x008E6330;
	RelocAddr<uintptr_t> targetCall(TARGET + 0x22F);
	g_branchTrampoline.Write5Call(targetCall.GetUIntPtr(), GetFnAddr(&Hook_WorldPtToScreenPt3));
	_DMESSAGE("[DEBUG] Hooked function call");
}
