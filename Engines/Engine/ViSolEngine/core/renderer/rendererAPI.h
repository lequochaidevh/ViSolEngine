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
}