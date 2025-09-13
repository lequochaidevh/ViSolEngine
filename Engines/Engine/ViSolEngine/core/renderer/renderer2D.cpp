#include"renderer2D.h"
#include"core/logger/logger.h"

namespace ViSolEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)

	Renderer::Renderer() {

	}

	Renderer::~Renderer() {

	}

	void Renderer::onInit() {
		CORE_LOG_TRACE("Renderer init success");
	}

	bool Renderer::beginScene() {
		return true;
	}

	void Renderer::render() {

	}

	void Renderer::endScene() {

	}

	void Renderer::shutDown() {
		CORE_LOG_TRACE("Renderer is shutdown");
	}
}