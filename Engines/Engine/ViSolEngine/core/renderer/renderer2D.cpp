#include "renderer2D.h"
#include "core/logger/logger.h"
#include "core/application.h"
#include "renderCommand.h"
namespace ViSolEngine {
	// DEFINE_RTTI_NO_PARENT(Renderer)

	RenderCommandQueue Renderer::sRenderCommandQueue;

	void Renderer::submit(const RenderCallback& renderCallback) {
		if (Application::get().getPerFrameData().isCatchUpPhase) return; // Not submit frame when LAG FRAME.
		sRenderCommandQueue.enqueue(renderCallback);
	}

	void Renderer::clearColor(float r, float g, float b, float w) {
		submit([r, g, b, w]() {
			RenderCommand::clearColor(r, g, b, w);
		});
	}
	
	// void Renderer::drawIndexed(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) {
	// 	submit([nums, primitive, offset]() {
	// 		RenderCommand::drawIndexed(nums, primitive, offset);
	// 	});
	// }

	void Renderer::onInit(const ApplicationConfiguration& appConfig) {
		submit([rendererSpec = appConfig.eRendererSpec]() {
			RenderCommand::onInit(rendererSpec);
		});
		CORE_LOG_TRACE("Renderer init success");
	}

	bool Renderer::beginScene() {
		return true;
	}

	void Renderer::render() {
		sRenderCommandQueue.processAndRender();
	}

	void Renderer::endScene() {

	}

	void Renderer::onShutDown() {
		CORE_LOG_TRACE("Renderer is shutdown");
		submit([]() {
			RenderCommand::onShutdown();
		});
	}
}