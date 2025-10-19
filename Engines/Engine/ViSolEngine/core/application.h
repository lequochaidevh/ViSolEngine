#pragma once
#include <pch.h>
#include "window/windowPlatform.h"
#include "core/event/eventDispatcher.h"
#include "core/layer/layerStack.h"
#include "core/time/time.h"
#include "renderer/rendererAPI.h"

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
		bool runState; // is_runstate
		ERendererSpec eRendererSpec;
	};
	struct VISOL_API PerFrameData {
		uint32_t frameIndex = 0;
		bool isCatchUpPhase = false;
	};

	class VISOL_API Application
	{
	public: // Singleton
		static Application& get();
	private:
		static Application* sInstance;
	public:
		virtual ~Application() = default;
		virtual bool init();
		virtual bool onInitClient() = 0;
		void run();
		virtual void onShutdownClient() = 0;
		virtual void shutdown();
	public:
		VISOL_FORCE_INLINE const PerFrameData& getPerFrameData() const { return mPerFrameData; }
		VISOL_FORCE_INLINE const ApplicationConfiguration& getConfig() const { return mConfig; }
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
		
	private:
		Time mTime;
	private:
		bool mIsRunning;
		PerFrameData mPerFrameData;
	};

	extern Application *createApplication();
}
