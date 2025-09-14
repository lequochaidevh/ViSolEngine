#include "OpenGLResourceManager.h"
#include "core/type/cast.h"

namespace ViSolEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLResourceManager)

	OpenGLResourceManager::OpenGLResourceManager() : 
		mVertexBufferMemoryManager("VertexBufferMemoryManager"),
		mIndexBufferMemoryManager("IndexBufferMemoryManager")
        // TODO: Add 1 Shader buffer
	{

	}

	OpenGLResourceManager::~OpenGLResourceManager()
	{

	}

	void OpenGLResourceManager::onReset()
	{
		mVertexBufferMemoryManager.reset();
	}

	VertexBuffer* OpenGLResourceManager::newVertexBuffer()
	{
		return mVertexBufferMemoryManager.newObject();
	}

	void OpenGLResourceManager::freeVertexBuffer(void* memory)
	{
		mVertexBufferMemoryManager.freeObject(memory);
	}

	IndexBuffer* OpenGLResourceManager::newIndexBuffer()
	{
		return mIndexBufferMemoryManager.newObject();
	}

	void OpenGLResourceManager::freeIndexBuffer(void* memory)
	{
		mIndexBufferMemoryManager.freeObject(memory);
	}

	Shader* OpenGLResourceManager::newShader(const char* filepath)
	{
		// if (mShaderMap.count(filepath)) {
		// 	return mShaderMap.at(filepath);
		// }

		// auto shaderSources = ParseGLSL(filepath);
		// OpenGLShader* shader = mShaderMemoryManager.newObject(filepath, shaderSources["vertex"].c_str(), shaderSources["fragment"].c_str());
		// mShaderMap[filepath] = shader;
		// return shader;
        return nullptr;
	}

	void OpenGLResourceManager::freeShader(void* memory)
	{
		// mShaderMemoryManager.freeObject(memory);
		// mShaderMap.erase(StaticCast<OpenGLShader*>(memory)->GetName());
	}

	void* OpenGLResourceManager::allocatePerFrame(uint32_t size, uint8_t alignment)
	{
		return mGeneralMemoryManager.allocatePerFrame(size, alignment);
	}

	// std::unordered_map<std::string, std::string> OpenGLResourceManager::ParseGLSL(const char* shaderSource)
	// {
	// 	std::string source = ReadFromFile(shaderSource);
	// 	std::unordered_map<std::string, std::string> shaderSources;

	// 	const char* typeToken = "#type";
	// 	size_t typeTokenLength = strlen(typeToken);
	// 	size_t pos = source.find(typeToken, 0);
	// 	while (pos != std::string::npos)
	// 	{
	// 		size_t eol = source.find_first_of("\r\n", pos);
	// 		VI_ASSERT(eol != std::string::npos, "Syntax error");

	// 		size_t begin = pos + typeTokenLength + 1;
	// 		std::string type = source.substr(begin, eol - begin);
	// 		VI_ASSERT((type == "vertex" || type == "fragment") && "Invalid shader type specified");

	// 		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
	// 		pos = source.find(typeToken, nextLinePos);
	// 		shaderSources[type] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
	// 	}

	// 	return shaderSources;
	// }

	// std::string OpenGLResourceManager::ReadFromFile(const char* filepath)
	// {
	// 	std::string result;
	// 	std::ifstream in(filepath, std::ios::in | std::ios::binary);

	// 	if (in)
	// 	{
	// 		in.seekg(0, std::ios::end);
	// 		result.resize(in.tellg());
	// 		in.seekg(0, std::ios::beg);
	// 		in.read(&result[0], result.size());
	// 		in.close();
	// 	}
	// 	else
	// 	{
	// 		CORE_LOG_WARN("Could not read shader file {0}", filepath);
	// 	}

	// 	return result;
	// }
}