#include "Events.h"
#include "Hooks.h"
#include "Settings.h"
#include "version.h"

#include "SKSE/API.h"
#include "RE/Skyrim.h"


namespace
{
	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case SKSE::MessagingInterface::kDataLoaded:
			{
				auto ui = RE::UI::GetSingleton();
				ui->AddEventSink(MenuOpenCloseEventHandler::GetSingleton());
				_MESSAGE("Registered menu open/close event handler");
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
		SKSE::Logger::UseLogStamp(true);
		SKSE::Logger::TrackTrampolineStats(true);

		_MESSAGE("FlatMapMarkersSSE v%s", FLTM_VERSION_VERSTRING);

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = "FlatMapMarkersSSE";
		a_info->version = FLTM_VERSION_MAJOR;

		if (a_skse->IsEditor()) {
			_FATALERROR("Loaded in editor, marking as incompatible!\n");
			return false;
		}

		auto ver = a_skse->RuntimeVersion();
		if (ver <= SKSE::RUNTIME_1_5_39) {
			_FATALERROR("Unsupported runtime version %s!", ver.GetString().c_str());
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
	{
		_MESSAGE("FlatMapMarkersSSE loaded");

		if (!SKSE::Init(a_skse)) {
			return false;
		}

		if (!Settings::LoadSettings()) {
			_FATALERROR("Settings failed to load!");
			return false;
		}

		if (!SKSE::AllocTrampoline(1 << 4)) {
			return false;
		}

		auto messaging = SKSE::GetMessagingInterface();
		if (!messaging->RegisterListener("SKSE", MessageHandler)) {
			return false;
		}

		Hooks::Install();

		return true;
	}
};
