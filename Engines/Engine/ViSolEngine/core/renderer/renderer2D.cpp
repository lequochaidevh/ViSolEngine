#include "renderer2D.h"
#include "core/logger/logger.h"
#include "core/application.h"
#include "renderCommand.h"
namespace ViSolEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)

	Renderer::Renderer() {

	}

	Renderer::~Renderer() {

	}

	void Renderer::onInit(const ApplicationConfiguration& appConfig) {
		RenderCommand::onInit(appConfig.RendererSpec);
		CORE_LOG_TRACE("Renderer init success");
	}

	bool Renderer::beginScene() {
		return true;
	}

	void Renderer::render() {

	}

	void Renderer::endScene() {

	}

	void Renderer::onShutDown() {
		CORE_LOG_TRACE("Renderer is shutdown");
		RenderCommand::onShutdown();
	}
}