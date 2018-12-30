#pragma once

#include "RE/BSTEvent.h"  // BSTEventSink, EventResult, BSTEventSource

namespace RE
{
	class MenuOpenCloseEvent;
}


class MenuOpenCloseEventHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
{
public:
	virtual ~MenuOpenCloseEventHandler();
	virtual	RE::EventResult	ReceiveEvent(RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
};


extern MenuOpenCloseEventHandler g_menuOpenCloseEventHandler;
