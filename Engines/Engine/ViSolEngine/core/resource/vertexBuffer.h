#pragma once

#include "core/type/object.h"
#include "renderer/rendererAPI.h"
#include <glm/glm.hpp>

namespace ViSolEngine {
	struct VISOL_API Vertex {
		glm::vec3 position;
		glm::vec2 texCoords;
		glm::vec4 color;
	};

	class VISOL_API VertexBuffer : public Object {
	public:
		DECLARE_RTTI
	public:
		static VertexBuffer* create();
	public:
		virtual ~VertexBuffer() = default;
		virtual void release() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual uint32_t getID() const = 0;
		virtual uint32_t getSize() const = 0;
		virtual void setData(void* data, uint32_t size, ERendererMode mode = ERendererMode::Static) = 0;
	protected:
		VertexBuffer() = default;
	};
}