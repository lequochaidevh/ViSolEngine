#pragma once

#include "pch.h"
#include "core/type/RTTI.h"
#include "core/application.h"
#include "renderCommandQueue.h"
namespace ViSolEngine {
	class VISOL_API Renderer {
	public:
		DECLARE_RTTI
	public:
		Renderer();
		~Renderer();

		void onInit(const ApplicationConfiguration&);
		bool beginScene();
		void render();
		void endScene();
		void onShutDown();
	public:
		static void submit(const RenderCallback&);
		static void clearColor(float r, float g, float b, float w = 1.0f);
	private:
		static RenderCommandQueue sRenderCommandQueue;
	};
}