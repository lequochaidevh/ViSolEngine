#pragma once

/*Layer{5}: Add NEW: Layer*/
#include "core/application.h"

class UserPlayLayer : public ViSolEngine::Layer {
public:
	UserPlayLayer() {}
	~UserPlayLayer() {}
	virtual void onAttach() override {
		LOG_TRACE("UserPlayLayer is attached");
	}

	virtual void onDetach() override {
		LOG_TRACE("UserPlayLayer is detached");
	}

	virtual void onUpdate(ViSolEngine::Time time) override {
		LOG_TRACE("UserPlayLayer get time: {}", time.getDeltaTime());
	}

	virtual bool onKeyPressedEvent(const ViSolEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.getKey());
		if (eventContext.getKey() == (int32_t)ViSolEngine::EKeyCode::ESCAPE)
		{
			CORE_LOG_CRITICAL("EXIT");
		}
		
		return false;
	}

	virtual bool onMouseButtonPressedEvent(const ViSolEngine::MouseButtonPressedEvent& eventContext) override {
		if (eventContext.isButton(ViSolEngine::EMouseButton::BUTTON_LEFT)) {
			LOG_TRACE("UserPlayLayer Left mouse button is clicked");
			return true;
		}
		return false;
	}

};

// class UI_Layer : public ViSolEngine::Layer {
// public:
// 	UI_Layer() {}
// 	~UI_Layer() {}
// 	virtual void onAttach() override {
// 		LOG_INFO("UI_Layer is attached");
// 	}
// 	virtual void onDetach() override {
// 		LOG_INFO("UI_Layer is detached");
// 	}

// 	virtual bool onKeyPressedEvent(const ViSolEngine::KeyPressedEvent& eventContext) override {
// 		LOG_TRACE("Key {0} is pressed on UI_Layer", (char)eventContext.getKey());
// 		return false;
// 	}
// 	virtual bool onKeyHeldEvent(const ViSolEngine::KeyHeldEvent& eventContext) override {
// 		LOG_TRACE("Key {0} is held on UILayer", (char)eventContext.getKey());
// 		return true;
// 	}

// 	virtual bool onKeyReleasedEvent(const ViSolEngine::KeyReleasedEvent& eventContext) override {
// 		if (eventContext.isKey(ViSolEngine::EKeyCode::ESCAPE)) {
// 			LOG_TRACE("ESC key is released");
// 		}
// 		return true;
// 	}

// 	virtual bool onMouseButtonPressedEvent(const ViSolEngine::MouseButtonPressedEvent& eventContext) override {
// 		if (eventContext.isButton(ViSolEngine::EMouseButton::BUTTON_LEFT)) {
// 			LOG_TRACE("Left mouse button is clicked");
// 			return false;
// 		}
// 		return false;
// 	}

// };