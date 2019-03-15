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
	// E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 58 00 00 00 BE 68 07 00 00 48 8B 3C C8 8B 1C 37 89 5C 24 70
	constexpr uintptr_t TARGET = 0x008E6140;	// 1_5_73
	RelocAddr<uintptr_t> targetCall(TARGET + 0x22F);
	g_branchTrampoline.Write5Call(targetCall.GetUIntPtr(), GetFnAddr(&Hook_WorldPtToScreenPt3));
	_DMESSAGE("[DEBUG] Hooked function call");
}
