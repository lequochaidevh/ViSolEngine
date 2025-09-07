#include "application.h"
#include <spdlog/spdlog.h>
#define GLAD_CL_IMPLEMENTATION

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "memory/memoryMonitor.h"

/*Define General function for iterator - rbegin to rend at class have vector*/
#define DISPATCH_LAYER_EVENT(eventType, eventContext) \
for (auto iter = mLayerStack->rbegin(); iter != mLayerStack->rend(); ++iter) {\
	if ((*iter)->on##eventType(eventContext)) {\
		break;\
	}\
}

namespace ViSolEngine
{
    Application::Application(const ApplicationConfiguration &config) : 
        mConfig(config) , mEventDispatcher()
    {
        mNativeWindow.reset(WindowPlatform::create(config.eWindowSpec));
		/*Layer{7} Add and Allocate Heap mLayerStack*/
		mLayerStack.reset(new LayerStack());
    }

    bool Application::init() {
		
		if (!mNativeWindow->init(mConfig, &mEventDispatcher)) {
			CORE_LOG_CRITICAL("Window spec created failed");
			return false;
		}

		mEventDispatcher.addEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(onWindowResizedEvent));
        /*set new heap --- Set value mInputState*/
        mInputState = mNativeWindow->getInputState();
		mEventDispatcher.addEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(onKeyPressedEvent));
        mEventDispatcher.addEventListener<KeyHeldEvent>(BIND_EVENT_FUNCTION(onKeyHeldEvent));
		mEventDispatcher.addEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(onKeyReleasedEvent));
		mEventDispatcher.addEventListener<MouseMovedEvent>(BIND_EVENT_FUNCTION(onMouseMovedEvent));
		mEventDispatcher.addEventListener<MouseScrolledEvent>(BIND_EVENT_FUNCTION(onMouseScrolledEvent));
		mEventDispatcher.addEventListener<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(onMouseButtonPressedEvent));
		mEventDispatcher.addEventListener<MouseButtonHeldEvent>(BIND_EVENT_FUNCTION(onMouseButtonHeldEvent));
		mEventDispatcher.addEventListener<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(onMouseButtonReleasedEvent));

		return true;
	}

    void Application::run()
    {
        CORE_LOG_INFO("App is running: {0} {1} {2} ", mConfig.width, mConfig.height, mConfig.title);
        onInitClient();

		const float MAX_DELTA_TIME = 0.05f;
		float minDeltaTime = 1.0f / mConfig.maxFPS;
		
        while (mConfig.runState && !mNativeWindow->shouldClose())
        {
			static float lastFrameTime = 0.0f;
			// 
			while (mNativeWindow->getRealTime() - lastFrameTime < minDeltaTime) {} // holding time

			MemoryMonitor::get().update(); // Singleton

			float currentFrameTime = mNativeWindow->getRealTime();
			mTime = Time(currentFrameTime - lastFrameTime); // explicit
			lastFrameTime = currentFrameTime;
			
			mNativeWindow->pollsEvent();
			
			for (auto layer : *mLayerStack.get()) {
				layer->onProcessInput(*mInputState);
			}
			
			while (mTime.getDeltaTime() > MAX_DELTA_TIME) {
				for (auto layer : *mLayerStack.get()) {
					layer->onUpdate(Time(MAX_DELTA_TIME));
				}
				mNativeWindow->swapbuffers();
				for (auto layer : *mLayerStack.get()) {
					layer->onRender();
				}
				mTime -= Time(MAX_DELTA_TIME);
			}
				
			
			for (auto layer : *mLayerStack.get()) {
				layer->onUpdate(mTime);
			}
			
			for (auto layer : *mLayerStack.get()) {
				layer->onRender();
			}

			mNativeWindow->swapbuffers();
        }
		
		
        onShutdownClient();
    }

    void Application::shutdown() {
		mNativeWindow->shutdown();
		MemoryMonitor::get().clear();
		MemoryMonitor::get().detectMemoryLeaks();
	}

	/*Add and Browse rend to rbegin class, this have vector*/
	bool Application::onWindowResizedEvent(const WindowResizedEvent& eventContext) {
		CORE_LOG_TRACE("Window resize --- width: {} --- height: {}",
               eventContext.getWidth(),
               eventContext.getHeight());
		DISPATCH_LAYER_EVENT(WindowResizedEvent, eventContext);
		return false;
	}

	bool Application::onKeyPressedEvent(const KeyPressedEvent& eventContext) {
		if (eventContext.isKey(EKeyCode::ESCAPE)) {
			LOG_DEBUG("-------------ESC was pressed - Exit application-------------");
			mConfig.runState = false;
			return true;
		}
		DISPATCH_LAYER_EVENT(KeyPressedEvent, eventContext);
		return false;
	}

	bool Application::onKeyHeldEvent(const KeyHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyHeldEvent, eventContext);
		return false;
	}

	bool Application::onKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyReleasedEvent, eventContext);
		return false;
	}

	bool Application::onMouseMovedEvent(const MouseMovedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseMovedEvent, eventContext);
		return false;
	}

	bool Application::onMouseScrolledEvent(const MouseScrolledEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseScrolledEvent, eventContext);
		return false;
	}

	bool Application::onMouseButtonPressedEvent(const MouseButtonPressedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonPressedEvent, eventContext);
		return false;
	}

	bool Application::onMouseButtonHeldEvent(const MouseButtonHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonHeldEvent, eventContext);
		return false;
	}

	bool Application::onMouseButtonReleasedEvent(const MouseButtonReleasedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonReleasedEvent, eventContext);
		return false;
	}
	/*Define func call to func of stackLayer from Application*/
	void Application::pushLayer(Layer* layer) {
		mLayerStack->push(layer);
		layer->onAttach();
	}

	void Application::pushOverlayLayer(Layer* layer) {
		mLayerStack->pushOverlay(layer);
		layer->onAttach();
	}

	void Application::popLayer(Layer* layer) {
		mLayerStack->pop(layer);
		layer->onDetach();
	}

	void Application::popOverlayLayer(Layer* layer) {
		mLayerStack->popOverlay(layer);
		layer->onDetach();
	}
}
