#pragma once 

#include "pch.h"
#include "core/renderer/rendererAPI.h"

namespace ViSolEngine {
	class OpenGLFactory {
	public:
		static uint32_t toOpenGLMode(ERendererMode mode);
		static uint32_t toOpenGLPrimitive(ERendererPrimitive primitive);
	};
}