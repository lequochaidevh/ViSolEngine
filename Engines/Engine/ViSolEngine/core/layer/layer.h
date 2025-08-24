
#pragma once
#include "pch.h"
#include "core/logger/logger.h"
#include "core/event/eventContext.h"
#include "core/time/time.h"

/*1 Declare LayerClass*/
namespace ViSolEngine {
	class VISOL_API Layer {
	public:
		Layer() {
			mID = getUUID();
            CORE_LOG_TRACE("Create layer ID: {}", mID);
		}
		virtual ~Layer() = default;
		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onProcessInput(const struct InputState&) {}
		virtual void onUpdate(Time deltaTime) {}
		virtual void onRender() {}

		/* 2 Reference Application Action: Event > Application > Layer */
		virtual bool onWindowResizedEvent(const WindowResizedEvent&) { return false; }
		virtual bool onKeyPressedEvent(const KeyPressedEvent&) { return false; }
		virtual bool onKeyHeldEvent(const KeyHeldEvent&) { return false; }
		virtual bool onKeyReleasedEvent(const KeyReleasedEvent&) { return false; }
		virtual bool onMouseMovedEvent(const MouseMovedEvent&) { return false; }
		virtual bool onMouseScrolledEvent(const MouseScrolledEvent&) { return false; }
		virtual bool onMouseButtonPressedEvent(const MouseButtonPressedEvent&) { return false; }
		virtual bool onMouseButtonHeldEvent(const MouseButtonHeldEvent&) { return false; }
		virtual bool onMouseButtonReleasedEvent(const MouseButtonReleasedEvent&) { return false; }
	private:
		UUID mID;
	};
}
