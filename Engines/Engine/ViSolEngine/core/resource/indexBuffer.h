#pragma once

#include "pch.h"
#include "core/type/object.h"
#include "renderer/rendererAPI.h"

namespace ViSolEngine {
	class VISOL_API IndexBuffer : public Object {
	public:
		DECLARE_RTTI
	public:
		static IndexBuffer* create();
	public:
		virtual ~IndexBuffer() = default;
		virtual void release() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual uint32_t getID() const = 0;
		virtual uint32_t getSize() const = 0;
        virtual uint32_t getNums() const = 0;
		virtual void setData(void* data, uint32_t size, uint32_t nums, ERendererMode mode = ERendererMode::Static) = 0;
	protected:
		IndexBuffer() = default;

	};
}