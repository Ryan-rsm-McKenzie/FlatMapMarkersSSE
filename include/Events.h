#pragma once

#include "RE/Skyrim.h"


class MenuOpenCloseEventHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
{
public:
	static MenuOpenCloseEventHandler* GetSingleton();
	virtual	RE::EventResult	ReceiveEvent(RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;

private:
	MenuOpenCloseEventHandler() = default;
	MenuOpenCloseEventHandler(const MenuOpenCloseEventHandler&) = delete;
	MenuOpenCloseEventHandler(MenuOpenCloseEventHandler&&) = delete;
	virtual ~MenuOpenCloseEventHandler() = default;

	MenuOpenCloseEventHandler& operator=(const MenuOpenCloseEventHandler&) = delete;
	MenuOpenCloseEventHandler& operator=(MenuOpenCloseEventHandler&&) = delete;
};
