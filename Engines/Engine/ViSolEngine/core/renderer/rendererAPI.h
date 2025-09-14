#pragma once

namespace ViSolEngine {
	enum class ERendererSpec {
		OpenGL,
		DirectX
        // Vulkhan ...
	};

	enum class ERendererMode {
		Static,
		Dynamic,
		Stream
	};

	enum class ERendererResource {
		VertexShader,
		FragmentShader,
		Shader
	};

	enum class ERendererPrimitive {
		Triangles,
		Points,
		Lines
	};

}