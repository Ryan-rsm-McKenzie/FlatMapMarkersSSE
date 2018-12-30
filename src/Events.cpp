#include "Events.h"

#include "FNV1A.h"  // hash_32_fnv1a
#include "Settings.h"  // worldSpaces

#include "RE/BSTEvent.h"  // EventResult, BSTEventSource
#include "RE/MapMenu.h"  // MapMenu
#include "RE/MenuManager.h"  // MenuManager
#include "RE/MenuOpenCloseEvent.h"  // MenuOpenCloseEvent
#include "RE/TESWorldSpace.h"  // TESWorldSpace
#include "RE/UIStringHolder.h"  // UIStringHolder


MenuOpenCloseEventHandler::~MenuOpenCloseEventHandler()
{}


RE::EventResult	MenuOpenCloseEventHandler::ReceiveEvent(RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource)
{
	using RE::EventResult;

	RE::UIStringHolder* uiStrHolder = RE::UIStringHolder::GetSingleton();
	if (!a_event || !a_event->isOpening || a_event->menuName != uiStrHolder->mapMenu) {
		return EventResult::kContinue;
	}

	RE::MenuManager* mm = RE::MenuManager::GetSingleton();
	RE::MapMenu* map = mm->GetMenu<RE::MapMenu>(uiStrHolder->mapMenu);
	RE::TESWorldSpace* worldSpace = map ? map->worldSpace : 0;
	if (!worldSpace) {
		return EventResult::kContinue;
	}

	std::uint32_t hash = hash_32_fnv1a(worldSpace->editorId.c_str(), worldSpace->editorId.length());
	auto& it = Settings::worldSpaces.find(hash);
	if (it != Settings::worldSpaces.end()) {
		Settings::enabled = it->second.first;
		Settings::markerHeight = it->second.second;
	} else {
		Settings::enabled = false;
	}

	return EventResult::kContinue;
}


MenuOpenCloseEventHandler g_menuOpenCloseEventHandler;
