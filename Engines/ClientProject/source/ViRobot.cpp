#include "ViSolEngine/core/entry.h"
#include "ViSolEngine/core/logger/logger.h"

#include "ViSolEngine/window/window.h"
#include "UI_ViRobotLayer.h"
class ViRobot : public ViSolEngine::Application {
public:
	ViRobot(const ViSolEngine::ApplicationConfiguration& config) : ViSolEngine::Application(config) {
		LOG_INFO("ViRobot client constructor init");
	}

	virtual bool onInitClient() override {
		LOG_INFO("ViRobot is init");
		mLayer = new UserPlayLayer();
		// mUI = new UI_Layer();
		// pushOverlayLayer(mUI);
		pushLayer(mLayer);
		return true;
	}

	virtual void onShutdownClient() override {
		LOG_INFO("ViRobot is shutdown");
		popLayer(mLayer);
		// popOverlayLayer(mUI);
	}
private:
	ViSolEngine::Layer* mLayer, * mUI;
};

ViSolEngine::Application* ViSolEngine::createApplication() {
	std::cout << "----- Start CreateApplication -----" << std::endl;
	ViSolEngine::ApplicationConfiguration appConfig;
	appConfig.width = 800;
	appConfig.height = 600;
	appConfig.title = "ViSolEngine version 1.0.0";
	appConfig.eWindowSpec = ViSolEngine::EWindowPlatformSpec::GLFW;
	appConfig.maxFPS = 60;
	appConfig.runState = true;

	return new ViRobot(appConfig);
}
