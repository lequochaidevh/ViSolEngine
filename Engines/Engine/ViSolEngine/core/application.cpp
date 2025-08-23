#include "application.h"
#include <spdlog/spdlog.h>
#define GLAD_CL_IMPLEMENTATION

#include <glad/gl.h>
#include <GLFW/glfw3.h>

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

        while (!mNativeWindow->shouldClose())
        {
            mNativeWindow->swapbuffers();
			/*9_Browse LayerStack class, this have vector*/
			for (auto layer : *mLayerStack.get()) {
				layer->onProcessInput(*mInputState);
			}

			for (auto layer : *mLayerStack.get()) {
				layer->onUpdate(0.0f);
			}

			mNativeWindow->pollsEvent();
			for (auto layer : *mLayerStack.get()) {
				layer->onRender();
			}
        }

        onShutdownClient();
    }

    void Application::shutdown() {
		mNativeWindow->shutdown();
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
		// Example: mouse move event
		CORE_LOG_TRACE("Mouse position: {}, {}. Mouse relative: {}, {}", \
			eventContext.getPositionX(), \
			eventContext.getPositionY(), \
			eventContext.getOffsetX(), \
			eventContext.getOffsetY());
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
