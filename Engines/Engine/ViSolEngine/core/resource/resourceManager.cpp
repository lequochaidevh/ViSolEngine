#include "resourceManager.h"
#include "core/globalMemory.h"
#include "core/renderer/OpenGL/OpenGLResourceManager.h"

namespace ViSolEngine {
	ResourceManager* ResourceManager::sInstance = nullptr;

	ResourceManager& ResourceManager::get()
	{
		return *sInstance;
	}

	void ResourceManager::onInit(ERendererSpec rendererSpec)
	{
		switch (rendererSpec)
		{
		case ViSolEngine::ERendererSpec::OpenGL:
			sInstance = GlobalMemoryUsage::get().newOnStack<OpenGLResourceManager>\
                (OpenGLResourceManager::runTimeType.getTypeName());
			break;
		case ViSolEngine::ERendererSpec::DirectX:
			VISOL_ASSERT("Currently not supported for Direct X");
			break;
		default:
			VISOL_ASSERT("Unkown renderer spec!");
			break;
		}
	}

	void ResourceManager::onShutdown()
	{
		sInstance->onReset();
	}
}
