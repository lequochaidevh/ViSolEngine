#include "indexBuffer.h"
#include "resourceManager.h"

namespace ViSolEngine {
	DEFINE_RTTI(IndexBuffer, Object::runTimeType)

	IndexBuffer* IndexBuffer::create() {
		return ResourceManager::get().newIndexBuffer();
	}
}
