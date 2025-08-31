#include "object.h"

namespace ViSolEngine {
	DEFINE_RTTI_NO_PARENT(Object)
	DEFINE_RTTI(Actor, &Object::runTimeType )
}