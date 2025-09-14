#include "shader.h"
#include "resourceManager.h"

namespace ViSolEngine {
	DEFINE_RTTI(Shader, Object::runTimeType)

	Shader* Shader::create(const char* filepath) {
		return ResourceManager::get().newShader(filepath);
	}
}