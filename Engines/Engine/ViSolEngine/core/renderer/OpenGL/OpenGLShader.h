#pragma once

#include"core/resource/shader.h"
#include"core/renderer/rendererAPI.h"

namespace ViSolEngine {
	class OpenGLShader : public Shader {
	public:
		DECLARE_RTTI
	public:
		OpenGLShader(const char* name, const char* vertexSource, const char* fragmentSource);
		~OpenGLShader();
		virtual void release() override;
		virtual void bind() override;
		virtual void unbind() override;
		VISOL_FORCE_INLINE virtual uint32_t getID() const override { return mID; }
		VISOL_FORCE_INLINE virtual const char* getName() const override { return mName.c_str(); }
		virtual void setBool(const std::string& name, bool value) override;
		virtual void setInt(const std::string& name, int32_t value) override;
		virtual void setInts(const std::string& name, int32_t* value, uint32_t count) override;
		virtual void setFloat(const std::string& name, float value) override;
		virtual void setFloats(const std::string& name, float* value, uint32_t count) override;
		virtual void setFloats2(const std::string& name, float* value, uint32_t count) override;
		virtual void setVector2(const std::string& name, float x, float y) override;
		virtual void setVector2(const std::string& name, const glm::vec2& value) override;
		virtual void setVector3(const std::string& name, float x, float y, float z) override;
		virtual void setVector3(const std::string& name, const glm::vec3& value) override;
		virtual void setMatrix4(const std::string& name, const glm::mat4& value) override;
	private:
		bool isValidShader(uint32_t shaderID, ERendererResource resource);
	private:
		uint32_t mID;
		std::string mName, mVertexSource, mFragmentSource;
	};
}