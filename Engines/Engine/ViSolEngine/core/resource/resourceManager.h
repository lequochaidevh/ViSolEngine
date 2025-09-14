#pragma once

#include "pch.h"
#include "core/renderer/rendererAPI.h"

namespace ViSolEngine {
	class VISOL_API ResourceManager {
	public:
		static ResourceManager& get();
		static void onInit(ERendererSpec rendererSpec);
		static void onShutdown();
	private:
		static ResourceManager* sInstance;


	public:
		virtual ~ResourceManager() = default;


		virtual void onReset() = 0;
		virtual class VertexBuffer* newVertexBuffer() = 0;
		virtual void freeVertexBuffer(void* memory) = 0;
		virtual class IndexBuffer* newIndexBuffer() = 0;
		virtual void freeIndexBuffer(void* memory) = 0;
		virtual class Shader* newShader(const char* filepath) = 0;
		virtual void freeShader(void* memory) = 0;
		virtual void* allocatePerFrame(uint32_t size, uint8_t alignment) = 0;
	protected:
		ResourceManager() = default;
	};
}