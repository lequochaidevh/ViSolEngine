#pragma once

#include "pch.h"
#include "core/type/RTTI.h"
#include "core/application.h"
#include "renderCommandQueue.h"
namespace ViSolEngine {
	class VISOL_API Renderer {
	public:
		~Renderer() = default;
	protected:
		Renderer() = default;
	public:
		static void onInit(const ApplicationConfiguration&);
		static bool beginScene();
		static void render();
		static void endScene();
		static void onShutDown();
		static void drawIndexed(uint32_t nums, ERendererPrimitive primitive = ERendererPrimitive::Triangles, uint32_t offset = 0);
	public:
		static void submit(const RenderCallback&);
		static void clearColor(float r, float g, float b, float w = 1.0f);
	private:
		static RenderCommandQueue sRenderCommandQueue;
	};
}