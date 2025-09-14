#pragma once

#include "core/type/object.h"
#include <glm/glm.hpp>

namespace ViSolEngine {
	class VISOL_API Shader : public Object {
	public:
		DECLARE_RTTI
	public:
		static Shader* create(const char* filepath);
	public:
		virtual ~Shader() = default;
		virtual void release() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual uint32_t getID() const = 0;
		virtual const char* getName() const = 0;
        // Upload unifier
		virtual void setBool(const std::string& name, bool value) = 0;
		virtual void setInt(const std::string& name, int32_t value) = 0;
		virtual void setInts(const std::string& name, int32_t* value, uint32_t count) = 0;
		virtual void setFloat(const std::string& name, float value) = 0;
		virtual void setFloats(const std::string& name, float* value, uint32_t count) = 0;
		virtual void setFloats2(const std::string& name, float* value, uint32_t count) = 0;
		virtual void setVector2(const std::string& name, float x, float y) = 0;
		virtual void setVector2(const std::string& name, const glm::vec2& value) = 0;
		virtual void setVector3(const std::string& name, float x, float y, float z) = 0;
		virtual void setVector3(const std::string& name, const glm::vec3& value) = 0;
		virtual void setMatrix4(const std::string& name, const glm::mat4& value) = 0;
	protected:
		Shader() = default;
	};
}