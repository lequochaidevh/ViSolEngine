#include"renderCommandQueue.h"
#include"core/application.h"
#include"core/logger/logger.h"

namespace ViSolEngine {
	RenderCommandQueue::RenderCommandQueue() : mRenderCommandCallbackQueue(), mMemoryManager() {

	}

	RenderCommandQueue::~RenderCommandQueue() {

	}

    // Allocate resource memory and push to CMD_QUEUE for callback function.
	void RenderCommandQueue::enqueue(const RenderCallback& renderCallback) {
		RenderCommandCallback* renderCommandCallback = \
            mMemoryManager.newPerFrame<RenderCommandCallback>(renderCallback);

		VISOL_ASSERT(renderCommandCallback != nullptr \
            && "Failed to allocate memory for render command");

		renderCommandCallback->setFrameIndex(Application::get().getPerFrameData().frameIndex);
		mRenderCommandCallbackQueue.push_back(renderCommandCallback);
        
		CORE_LOG_TRACE("RenderCommand at frame {0} is allocated at address {1}", \
            renderCommandCallback->getFrameIndex(), (void*)renderCommandCallback);
	}

	void RenderCommandQueue::processAndRender() {
		for (auto renderCommandCallback : mRenderCommandCallbackQueue) {
			renderCommandCallback->execute();
		}

		mRenderCommandCallbackQueue.clear();
	}
}