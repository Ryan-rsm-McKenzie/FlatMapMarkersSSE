#include "skse64/PluginAPI.h"  // PluginHandle, SKSEInterface, PluginInfo
#include "skse64_common/BranchTrampoline.h"  // g_branchTrampoline
#include "skse64_common/skse_version.h"  // RUNTIME_VERSION

#include <ShlObj.h>  // CSIDL_MYDOCUMENTS

#include "Hooks.h"  // InstallHooks
#include "Settings.h"  // Settings
#include "version.h"  // FLATMAPMARKERSSSE_VERSION_VERSTRING, FLATMAPMARKERSSSE_VERSION_MAJOR


static PluginHandle g_pluginHandle = kPluginHandle_Invalid;


extern "C" {
	bool SKSEPlugin_Query(const SKSEInterface* a_skse, PluginInfo* a_info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\FlatMapMarkersSSE.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_DebugMessage);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		_MESSAGE("FlatMapMarkersSSE v%s", FLATMAPMARKERSSSE_VERSION_VERSTRING);

		a_info->infoVersion = PluginInfo::kInfoVersion;
		a_info->name = "FlatMapMarkersSSE";
		a_info->version = FLATMAPMARKERSSSE_VERSION_MAJOR;

		g_pluginHandle = a_skse->GetPluginHandle();

		if (a_skse->isEditor) {
			_FATALERROR("[FATAL ERROR] Loaded in editor, marking as incompatible!\n");
			return false;
		}

		if (a_skse->runtimeVersion != RUNTIME_VERSION_1_5_62) {
			_FATALERROR("[FATAL ERROR] Unsupported runtime version %08X!\n", a_skse->runtimeVersion);
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSEInterface* a_skse)
	{
		_MESSAGE("[MESSAGE] FlatMapMarkersSSE loaded");

		if (Settings::loadSettings()) {
			_MESSAGE("[MESSAGE] Settings successfully loaded");
		} else {
			_FATALERROR("[FATAL ERROR] Settings failed to load!\n");
			return false;
		}

		if (g_branchTrampoline.Create(1024 * 8)) {
			_MESSAGE("[MESSAGE] Branch trampoline creation successful");
		} else {
			_MESSAGE("[MESSAGE] Branch trampoline creation failed!\n");
			return false;
		}

		InstallHooks();
		_MESSAGE("[MESSAGE] Hooks installed");

		return true;
	}
};
