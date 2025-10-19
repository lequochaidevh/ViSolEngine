#include"OpenGLShader.h"
#include"core/renderer/renderer2D.h"
#include"core/resource/resourceManager.h"
#include"core/type/cast.h"
#include"core/logger/logger.h"

#include<glad/gl.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace ViSolEngine {
	DEFINE_RTTI(OpenGLShader, Shader::runTimeType)

	OpenGLShader::OpenGLShader(const char* name, const char* vertexSource, const char* fragmentSource) : 
		mName(name), mVertexSource(vertexSource), mFragmentSource(fragmentSource)
	{
		Renderer::submit([this]() {
			uint32_t vertexShaderID, fragmentShaderID;
			const char* vertexSource = mVertexSource.c_str();
			const char* fragmentSource = mFragmentSource.c_str();
			// Vertex Shader
			vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShaderID, 1, &vertexSource, nullptr);
			glCompileShader(vertexShaderID);
			// Fragment Shader
			fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShaderID, 1, &fragmentSource, nullptr);
			glCompileShader(fragmentShaderID);
			// Shader Program
			mID = glCreateProgram();
			if (
				isValidShader(vertexShaderID, ERendererResource::VertexShader) &&
				isValidShader(fragmentShaderID, ERendererResource::FragmentShader)
			) {
				glAttachShader(mID, vertexShaderID);
				glAttachShader(mID, fragmentShaderID);
				glLinkProgram(mID);

				if (isValidShader(mID, ERendererResource::Shader)) {
					CORE_LOG_INFO("Shader program {0} with id {1} is loaded!", mName.c_str(), mID);
				}
			}

			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
		});
	}

	OpenGLShader::~OpenGLShader()
	{
	}

	void OpenGLShader::release() {
		Renderer::submit([this]() {
			glDeleteShader(mID);
			ResourceManager::get().freeShader(this);
		});
	}

	void OpenGLShader::bind()
	{
		Renderer::submit([this]() {
			glUseProgram(mID);
		});
	}

	void OpenGLShader::unbind()
	{
		Renderer::submit([]() {
			glUseProgram(0);
		});
	}

	void OpenGLShader::setBool(const std::string& name, bool value)
	{
		Renderer::submit([name, value, this]() {
			glUniform1i(glGetUniformLocation(mID, name.c_str()), StaticCast<int>(value));
		});
	}

	void OpenGLShader::setInt(const std::string& name, int32_t value)
	{
		Renderer::submit([name, value, this]() {
			glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
		});
	}

	void OpenGLShader::setInts(const std::string& name, int32_t* value, uint32_t count)
	{
		Renderer::submit([name, value, count, this]() {
			glUniform1iv(glGetUniformLocation(mID, name.c_str()), count, value);
		});
	}

	void OpenGLShader::setFloat(const std::string& name, float value)
	{
		Renderer::submit([name, value, this]() {
			glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
		});
	}

	void OpenGLShader::setFloats(const std::string& name, float* value, uint32_t count)
	{
		Renderer::submit([name, value, count, this]() {
			glUniform1fv(glGetUniformLocation(mID, name.c_str()), count, value);
		});
	}

	void OpenGLShader::setFloats2(const std::string& name, float* value, uint32_t count)
	{
		Renderer::submit([name, value, count, this]() {
			glUniform2fv(glGetUniformLocation(mID, name.c_str()), count, value);
		});
	}

	void OpenGLShader::setVector2(const std::string& name, float x, float y)
	{
		Renderer::submit([name, x, y, this]() {
			glUniform2f(glGetUniformLocation(mID, name.c_str()), x, y);
		});
	}

	void OpenGLShader::setVector2(const std::string& name, const glm::vec2& value)
	{
		Renderer::submit([name, value, this]() {
			glUniform2fv(glGetUniformLocation(mID, name.c_str()), 1, glm::value_ptr(value));
		});
	}

	void OpenGLShader::setVector3(const std::string& name, float x, float y, float z)
	{
		Renderer::submit([name, x, y, z, this]() {
			glUniform3f(glGetUniformLocation(mID, name.c_str()), x, y, z);
		});
	}

	void OpenGLShader::setVector3(const std::string& name, const glm::vec3& value)
	{
		Renderer::submit([name, value, this]() {
			glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, glm::value_ptr(value));
		});
	}

	void OpenGLShader::setMatrix4(const std::string& name, const glm::mat4& value)
	{
		Renderer::submit([name, value, this]() {
			glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		});
	}

	bool OpenGLShader::isValidShader(uint32_t shaderID, ERendererResource resource) {
		int32_t success;
		char info[512];

		switch (resource)
		{
		case ViSolEngine::ERendererResource::VertexShader:
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Vertex Shader", info);
				return false;
			}
			break;
		case ViSolEngine::ERendererResource::FragmentShader:
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Fragment Shader", info);
				return false;
			}
			break;
		case ViSolEngine::ERendererResource::Shader:
			glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Shader Program", info);
				return false;
			}
			break;
		default:
			CORE_LOG_WARN("Invalid resource");
			break;
		}

		return true;
	}
}