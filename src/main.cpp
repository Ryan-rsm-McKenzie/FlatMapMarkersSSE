#include "skse64_common/BranchTrampoline.h"  // g_branchTrampoline
#include "skse64_common/skse_version.h"  // RUNTIME_VERSION

#include "Events.h"  // g_menuOpenCloseEventHandler
#include "Hooks.h"  // InstallHooks
#include "Settings.h"  // Settings
#include "version.h"  // VERSION_VERSTRING, VERSION_MAJOR

#include "SKSE/API.h"
#include "RE/Skyrim.h"


namespace
{
	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case SKSE::MessagingInterface::kDataLoaded:
			{
				auto mm = RE::MenuManager::GetSingleton();
				mm->GetMenuOpenCloseEventSource()->AddEventSink(MenuOpenCloseEventHandler::GetSingleton());
				_MESSAGE("[MESSAGE] Registered menu open/close event handler");
			}
			break;
		}
	}
}


extern "C" {
	bool SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
	{
		SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\FlatMapMarkersSSE.log");
		SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kDebugMessage);

		_MESSAGE("FlatMapMarkersSSE v%s", FLTM_VERSION_VERSTRING);

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = "FlatMapMarkersSSE";
		a_info->version = FLTM_VERSION_MAJOR;

		if (a_skse->IsEditor()) {
			_FATALERROR("[FATAL ERROR] Loaded in editor, marking as incompatible!\n");
			return false;
		}

		switch (a_skse->RuntimeVersion()) {
		case RUNTIME_VERSION_1_5_73:
		case RUNTIME_VERSION_1_5_80:
			break;
		default:
			_FATALERROR("[FATAL ERROR] Unsupported runtime version %08X!\n", a_skse->RuntimeVersion());
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
	{
		_MESSAGE("[MESSAGE] FlatMapMarkersSSE loaded");

		if (!SKSE::Init(a_skse)) {
			return false;
		}

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

		auto messaging = SKSE::GetMessagingInterface();
		if (messaging->RegisterListener("SKSE", MessageHandler)) {
			_MESSAGE("[MESSAGE] Messaging interface registration successful");
		} else {
			_FATALERROR("[FATAL ERROR] Messaging interface registration failed!\n");
			return false;
		}

		InstallHooks();
		_MESSAGE("[MESSAGE] Hooks installed");

		return true;
	}
};
