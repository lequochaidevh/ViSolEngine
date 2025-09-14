#include "OpenGLIndexBuffer.h"

#include "renderer/renderer2D.h"
#include "resource/resourceManager.h"
#include "OpenGLFactory.h"

#include <glad/gl.h>

namespace ViSolEngine {
	DEFINE_RTTI(OpenGLIndexBuffer, IndexBuffer::runTimeType)

	OpenGLIndexBuffer::OpenGLIndexBuffer() {
		Renderer::submit([this]() {
			glGenBuffers(1, &mID);
		});
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
	}

	void OpenGLIndexBuffer::release()
	{
		Renderer::submit([this]() {
			glDeleteBuffers(1, &mID);
			ResourceManager::get().freeIndexBuffer(this);
		});
	}

	void OpenGLIndexBuffer::bind()
	{
		Renderer::submit([this]() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
		});
	}

	void OpenGLIndexBuffer::unbind()
	{
		Renderer::submit([]() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		});
	}

    // Send data to GPU
	void OpenGLIndexBuffer::setData(void* data, uint32_t size, uint32_t nums, ERendererMode mode)
	{
		mSize = size;
		mNums = nums;
		void* submitData = ResourceManager::get().allocatePerFrame(size, alignof(uint32_t));
		memcpy(submitData, data, size);

		Renderer::submit([submitData, mode, this]() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize, submitData, OpenGLFactory::toOpenGLMode(mode));
		});
	}
}