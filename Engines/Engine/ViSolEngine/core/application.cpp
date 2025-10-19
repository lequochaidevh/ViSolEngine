#include "application.h"

#include <spdlog/spdlog.h>
#include "logger/logger.h"

#define GLAD_CL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "memory/memoryMonitor.h"
#include "globalMemory.h"
#include "ECS/systemManager.h"
#include "ECS/coordinator.h"
#include "core/system/system.h"

#include "renderer/renderer2D.h"

#include "resource/resourceManager.h"

/*Define General function for iterator - rbegin to rend at class have vector*/
#define DISPATCH_LAYER_EVENT(eventType, eventContext) \
for (auto iter = mLayerStack->rbegin(); iter != mLayerStack->rend(); ++iter) {\
	if ((*iter)->on##eventType(eventContext)) {\
		break;\
	}\
}

namespace ViSolEngine
{
	Application* Application::sInstance = nullptr;

	Application& Application::get() {
		return *sInstance;
	}

    Application::Application(const ApplicationConfiguration &config) : 
        mConfig(config) , mEventDispatcher(), mPerFrameData(),
		mIsRunning(true), mInputState(nullptr), mTime()
    {
        mNativeWindow.reset(WindowPlatform::create(config.eWindowSpec));

		mLayerStack = GlobalMemoryUsage::get().newOnStack<LayerStack>\
			(LayerStack::runTimeType.getTypeName());

		mSystemManager = GlobalMemoryUsage::get().newOnStack<ECS::SystemManager>\
			(ECS::SystemManager::runTimeType.getTypeName());

		mCoordinator = GlobalMemoryUsage::get().newOnStack<ECS::Coordinator>\
			(ECS::Coordinator::runTimeType.getTypeName());

		sInstance = this;
    }

    bool Application::init() {
		
		if (!mNativeWindow->init(mConfig, &mEventDispatcher)) {
			CORE_LOG_CRITICAL("Window spec created failed");
			return false;
		}
        /*set new heap --- Set value mInputState*/
        mInputState = mNativeWindow->getInputState();

		mEventDispatcher.addEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(onWindowResizedEvent));
		mEventDispatcher.addEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(onKeyPressedEvent));
        mEventDispatcher.addEventListener<KeyHeldEvent>(BIND_EVENT_FUNCTION(onKeyHeldEvent));
		mEventDispatcher.addEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(onKeyReleasedEvent));
		mEventDispatcher.addEventListener<MouseMovedEvent>(BIND_EVENT_FUNCTION(onMouseMovedEvent));
		mEventDispatcher.addEventListener<MouseScrolledEvent>(BIND_EVENT_FUNCTION(onMouseScrolledEvent));
		mEventDispatcher.addEventListener<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(onMouseButtonPressedEvent));
		mEventDispatcher.addEventListener<MouseButtonHeldEvent>(BIND_EVENT_FUNCTION(onMouseButtonHeldEvent));
		mEventDispatcher.addEventListener<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(onMouseButtonReleasedEvent));

		// auto& collisionSystem = mSystemManager->addSystem<CollisionResolver>();
		// auto& animationSystem = mSystemManager->addSystem<AnimationSystem>();
		// auto& renderer2D = mSystemManager->addSystem<Renderer2D>();

		// mSystemManager->addSystemDependency(&animationSystem, &collisionSystem);
		// mSystemManager->addSystemDependency(&renderer2D, &collisionSystem, &animationSystem);

		// collisionSystem.setUpdateInterval(5.0f);

		mSystemManager->onInit();
		Renderer::onInit(mConfig);
		ResourceManager::onInit(mConfig.eRendererSpec);
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

			float currentFrameTime = mNativeWindow->getRealTime();
			mTime = Time(currentFrameTime - lastFrameTime); // explicit
			lastFrameTime = currentFrameTime;
			
			mNativeWindow->pollsEvent();
			
			for (auto layer : *mLayerStack) {
				layer->onProcessInput(*mInputState);
			}
			
			while (mTime.getDeltaTime() > MAX_DELTA_TIME) {
				mPerFrameData.isCatchUpPhase = true;
				for (auto layer : *mLayerStack) {
					layer->onUpdate(Time(MAX_DELTA_TIME));
				}
				mNativeWindow->swapbuffers();

				mSystemManager->onUpdate(Time(MAX_DELTA_TIME)); // Refactor

				mTime -= Time(MAX_DELTA_TIME);
			}
				mPerFrameData.isCatchUpPhase = false;
			
			for (auto layer : *mLayerStack) {
				layer->onUpdate(mTime);
			}

			mSystemManager->onUpdate(Time(MAX_DELTA_TIME));

			for (auto layer : *mLayerStack) {
				layer->onGUIRender();
			}

			if (Renderer::beginScene()) {
				Renderer::render();
				Renderer::endScene();
			}

			mNativeWindow->swapbuffers();

			MemoryMonitor::get().update(); // Singleton - Clear PerFrameAllocator
			mPerFrameData.frameIndex++;

        }

        onShutdownClient();
    }

    void Application::shutdown() {
		//GlobalMemoryUsage::get().freeOnStack(mLayerStack);
		Renderer::onShutDown();
		mSystemManager->onShutdown();
		mNativeWindow->shutdown();
		ResourceManager::onShutdown(); // TODO DECLARE
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
