#pragma once

#include "core/resource/vertexBuffer.h"

namespace ViSolEngine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer();

		virtual void release() override;
		virtual void bind() override;
		virtual void unbind() override;
 		VISOL_FORCE_INLINE virtual uint32_t getID() const override { return mID; }
		VISOL_FORCE_INLINE virtual uint32_t getSize() const override { return mSize; }

		// Mode static will be set on GPU and will be optimized by itseft.
		virtual void setData(void* data, uint32_t size, ERendererMode mode = ERendererMode::Static) override;
	private:
		uint32_t mID, mSize;
	};
}