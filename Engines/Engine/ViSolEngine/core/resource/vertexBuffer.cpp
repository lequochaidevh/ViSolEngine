#include"vertexBuffer.h"
#include"resourceManager.h"

namespace ViSolEngine {
	DEFINE_RTTI(VertexBuffer, Object::runTimeType)

	VertexBuffer* VertexBuffer::create() {
		return ResourceManager::get().newVertexBuffer();
	}
}