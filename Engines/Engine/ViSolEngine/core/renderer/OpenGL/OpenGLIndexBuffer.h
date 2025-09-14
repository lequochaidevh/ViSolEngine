#pragma once

#include "core/resource/indexBuffer.h"

namespace ViSolEngine {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer();
		virtual void release() override;
		virtual void bind() override;
		virtual void unbind() override;
		VISOL_FORCE_INLINE virtual uint32_t getID() const override { return mID; }
		VISOL_FORCE_INLINE virtual uint32_t getSize() const override { return mSize; }
		VISOL_FORCE_INLINE virtual uint32_t getNums() const override { return mNums; }
		virtual void setData(void* data, uint32_t size, uint32_t nums, ERendererMode mode = ERendererMode::Static) override;
	private:
		uint32_t mID, mSize, mNums;
	};
}