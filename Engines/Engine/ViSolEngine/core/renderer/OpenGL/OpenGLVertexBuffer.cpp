#include "OpenGLVertexBuffer.h"

#include "core/renderer/renderer2D.h"
#include "core/resource/resourceManager.h"
#include "OpenGLFactory.h"
#include <glad/gl.h>

namespace ViSolEngine {
	DEFINE_RTTI(OpenGLVertexBuffer, VertexBuffer::runTimeType)

	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		Renderer::submit([this]() {
			glGenBuffers(1, &mID);
			glBindBuffer(GL_ARRAY_BUFFER, mID);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
			glEnableVertexAttribArray(2);

		});
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{

	}

	void OpenGLVertexBuffer::release() {
		Renderer::submit([this]() {
			glDeleteBuffers(1, &mID);
			ResourceManager::get().freeVertexBuffer(this);
		});
	}

	void OpenGLVertexBuffer::bind()
	{
		Renderer::submit([this]() {
			glBindBuffer(GL_ARRAY_BUFFER, mID);
		});
	}

	void OpenGLVertexBuffer::unbind()
	{
		Renderer::submit([this]() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		});
	}

	void OpenGLVertexBuffer::setData(void* data, uint32_t size, ERendererMode mode)
	{
		void* submitData = ResourceManager::get().allocatePerFrame(size, alignof(uint32_t));
		memcpy(submitData, data, size);
		Renderer::submit([submitData, size, mode, this]() {
			glBindBuffer(GL_ARRAY_BUFFER, mID);
			glBufferData(GL_ARRAY_BUFFER, size, submitData, OpenGLFactory::toOpenGLMode(mode));
		});
	}
}