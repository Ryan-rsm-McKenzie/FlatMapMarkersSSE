#include "Events.h"

#include "FNV1A.h"  // hash_32_fnv1a
#include "Settings.h"  // worldSpaces

#include "RE/Skyrim.h"


MenuOpenCloseEventHandler* MenuOpenCloseEventHandler::GetSingleton()
{
	static MenuOpenCloseEventHandler singleton;
	return &singleton;
}


RE::EventResult	MenuOpenCloseEventHandler::ReceiveEvent(RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource)
{
	using RE::EventResult;

	RE::UIStringHolder* uiStrHolder = RE::UIStringHolder::GetSingleton();
	if (!a_event || !a_event->isOpening || a_event->menuName != uiStrHolder->mapMenu) {
		return EventResult::kContinue;
	}

	auto mm = RE::MenuManager::GetSingleton();
	auto map = mm->GetMenu<RE::MapMenu>(uiStrHolder->mapMenu);
	auto worldSpace = map ? map->worldSpace : 0;
	if (!worldSpace) {
		return EventResult::kContinue;
	}

	std::uint32_t hash = hash_32_fnv1a(worldSpace->editorID.c_str(), worldSpace->editorID.length());
	auto& it = Settings::worldSpaces.find(hash);
	if (it != Settings::worldSpaces.end()) {
		Settings::enabled = it->second.first;
		Settings::markerHeight = it->second.second;
	} else {
		Settings::enabled = false;
	}

	return EventResult::kContinue;
}
