#pragma once
#include <iostream>
#include <pch.h>
#include "spdlog/spdlog.h"
#include "logger/logger.h"
#include "window/window.h"
#include "window/windowPlatform.h"
#include "core/event/eventDispatcher.h"
#include "core/input/inputState.h"
#include "core/layer/layerStack.h"
#include "core/time/time.h"
#include "memory/memoryAllocator.h"

namespace ViSolEngine
{
	namespace ECS
	{
		class SystemManager;
		class Coordinator;
	}
	struct VISOL_API ApplicationConfiguration
	{
		uint16_t width, height;
		const char *title;
		EWindowPlatformSpec eWindowSpec;
		int32_t maxFPS;
		bool runState;
	};
	class VISOL_API Application
	{
	public:
		virtual ~Application() = default;
		virtual bool init();
		virtual bool onInitClient() = 0;
		void run();
		virtual void onShutdownClient() = 0;
		virtual void shutdown();

	protected:
		Application() = default;
		Application(const ApplicationConfiguration &);

	private:
		bool onWindowResizedEvent(const WindowResizedEvent &);
		bool onKeyPressedEvent(const KeyPressedEvent &);
		bool onKeyHeldEvent(const KeyHeldEvent &);
		bool onKeyReleasedEvent(const KeyReleasedEvent &);
		bool onMouseMovedEvent(const MouseMovedEvent &);
		bool onMouseScrolledEvent(const MouseScrolledEvent &);
		bool onMouseButtonPressedEvent(const MouseButtonPressedEvent &);
		bool onMouseButtonHeldEvent(const MouseButtonHeldEvent &);
		bool onMouseButtonReleasedEvent(const MouseButtonReleasedEvent &);

	protected:
		void pushLayer(Layer *);
		void pushOverlayLayer(Layer *);
		void popLayer(Layer *);
		void popOverlayLayer(Layer *);

	private:
		ApplicationConfiguration mConfig;
		Unique<NativeWindow> mNativeWindow;
		EventDispatcher mEventDispatcher;

	private:
		class InputState *mInputState;

	private:
		LayerStack* mLayerStack;
		ECS::SystemManager* mSystemManager;
		ECS::Coordinator* mCoordinator;
	private:
		Time mTime;
	};

	extern Application *createApplication();
}
