#pragma once

#include"core/type/RTTI.h"
#include"core/resource/resourceManager.h"
#include"memory/memoryChunkManager.h"

namespace ViSolEngine {
	class OpenGLResourceManager : public ResourceManager {
	public:
		DECLARE_RTTI

	public:
		OpenGLResourceManager();
		~OpenGLResourceManager();

		virtual void onReset() override;
		virtual class VertexBuffer* newVertexBuffer() override;
		virtual void freeVertexBuffer(void* memory) override;
		virtual class IndexBuffer* newIndexBuffer() override;
		virtual void freeIndexBuffer(void* memory) override;
		virtual class Shader* newShader(const char* filepath) override;
		virtual void freeShader(void* memory) override;
		virtual void* allocatePerFrame(uint32_t size, uint8_t alignment) override;
	private:
		std::string ReadFromFile(const char* filepath);
	private:
		MemoryManager mGeneralMemoryManager;
	};
}