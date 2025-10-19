#pragma once

#include "core/type/RTTI.h"
#include "core/resource/resourceManager.h"
#include "memory/memoryChunkManager.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLShader.h"

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
		MemoryManager mGeneralMemoryManager;
	private:
		MemoryChunkManager<OpenGLVertexBuffer, 100> mVertexBufferMemoryManager;
		MemoryChunkManager<OpenGLIndexBuffer, 100> mIndexBufferMemoryManager;
		MemoryChunkManager<OpenGLShader, 100> mShaderMemoryManager;
		std::unordered_map<const char*, OpenGLShader*> mShaderMap; // Cache info shader file readed before
	private:
		std::unordered_map<std::string, std::string> parseGLSL(const char* shaderSource);
		std::string readFromFile(const char* filepath);
	};
}