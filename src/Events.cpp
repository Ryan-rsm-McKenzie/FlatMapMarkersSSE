#include "Events.h"

#include <memory>

#include "RE/Skyrim.h"

#include "Settings.h"


MenuOpenCloseEventHandler* MenuOpenCloseEventHandler::GetSingleton()
{
	static MenuOpenCloseEventHandler singleton;
	return std::addressof(singleton);
}


auto MenuOpenCloseEventHandler::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource)
-> EventResult
{
	auto intfcStr = RE::InterfaceStrings::GetSingleton();
	if (!a_event || !a_event->opening || a_event->menuName != intfcStr->mapMenu) {
		return EventResult::kContinue;
	}

	auto mm = RE::UI::GetSingleton();
	auto map = mm->GetMenu<RE::MapMenu>();
	auto worldSpace = map ? map->worldSpace : nullptr;
	if (!worldSpace) {
		return EventResult::kContinue;
	}

	auto it = Settings::worldSpaces.find(worldSpace->editorID.c_str());
	if (it != Settings::worldSpaces.end()) {
		Settings::enabled = it->second.first;
		Settings::markerHeight = it->second.second;
	} else {
		Settings::enabled = false;
	}

	return EventResult::kContinue;
}
