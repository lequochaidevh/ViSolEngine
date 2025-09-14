#include"core/renderer/renderCommand.h"

#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>

namespace ViSolEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLRenderCommand)

	void OpenGLRenderCommand::clearColorImpl(float r, float g, float b, float w) {
		glClearColor(r, g, b, w);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}