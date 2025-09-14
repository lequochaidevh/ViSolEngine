#pragma once

#include"pch.h"

namespace ViSolEngine {
	using RenderCallback = std::function<void()>;

	class RenderCommandCallback {
	public:
		RenderCommandCallback();
		RenderCommandCallback(const RenderCallback&);
		~RenderCommandCallback();

		void execute();

		VISOL_FORCE_INLINE uint32_t getFrameIndex() const { return mFrameIndex; }
		VISOL_FORCE_INLINE void setFrameIndex(uint32_t frameIndex) { mFrameIndex = frameIndex; }
	private:
		RenderCallback mCallback;
		uint32_t mFrameIndex;
	};
}