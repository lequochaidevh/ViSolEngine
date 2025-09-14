#pragma once

#include "renderCommandCallback.h"
#include "memory/memoryManager.h"

namespace ViSolEngine {
	class RenderCommandQueue {
	public:
		RenderCommandQueue();
		~RenderCommandQueue();

		void enqueue(const RenderCallback&);
		void processAndRender();
	private:
		std::vector<RenderCommandCallback*> mRenderCommandCallbackQueue;
		MemoryManager mMemoryManager;
	};
}