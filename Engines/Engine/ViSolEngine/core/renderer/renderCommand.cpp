#include"renderCommand.h"
#include"core/globalMemory.h"

namespace ViSolEngine {
	RenderCommand* RenderCommand::sInstance = nullptr;

	void RenderCommand::onInit(ERendererSpec rendererSpec) {
		switch (rendererSpec)
		{
		case ViSolEngine::ERendererSpec::OpenGL:
			sInstance = GlobalMemoryUsage::get().newOnStack<OpenGLRenderCommand>\
                (OpenGLRenderCommand::runTimeType.getTypeName());
			break;
		case ViSolEngine::ERendererSpec::DirectX:
			VISOL_ASSERT(false && "Currently not supported for DirectX");
			break;
		default:
			VISOL_ASSERT(false && "Unknow Renderer API");
			break;
		}
	}

	void RenderCommand::onShutdown() {

	}
}