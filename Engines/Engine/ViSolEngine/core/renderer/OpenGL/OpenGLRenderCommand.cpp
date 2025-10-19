#include"core/renderer/renderCommand.h"
#include"OpenGLFactory.h"

#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>

namespace ViSolEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLRenderCommand)

	OpenGLRenderCommand::OpenGLRenderCommand() {
		glGenVertexArrays(1, &mVertexArrayID);
		glBindVertexArray(mVertexArrayID);
	}

	OpenGLRenderCommand::~OpenGLRenderCommand() {
		glDeleteVertexArrays(1, &mVertexArrayID);
	}

	void OpenGLRenderCommand::clearColorImpl(float r, float g, float b, float w) {
		glClearColor(r, g, b, w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderCommand::drawIndexedImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) {
		glDrawElements(OpenGLFactory::toOpenGLPrimitive(primitive), nums, GL_UNSIGNED_INT, (void*)offset);
	}
}