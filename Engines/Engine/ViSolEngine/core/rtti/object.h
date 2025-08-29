#pragma once

#include "RTTI.h"
#include "pch.h"

namespace ViSolEngine {
	class VISOL_API Object {
	public:
		DECLARE_RTTI

		VISOL_FORCE_INLINE bool isTypeOf(const RTTI& other) const { return getRunTimeTypeInfo().isTypeOf(other); }
		VISOL_FORCE_INLINE bool isDerivedFrom(const RTTI& other) const { return getRunTimeTypeInfo().isDerivedFrom(other); }

		VISOL_FORCE_INLINE bool isExactlyTypeOf(const Object* obj) const { return obj && getRunTimeTypeInfo().isTypeOf(obj->getRunTimeTypeInfo()); }
		VISOL_FORCE_INLINE bool isExactlyDerivedFrom(const Object* obj) const { return obj && getRunTimeTypeInfo().isDerivedFrom(obj->getRunTimeTypeInfo()); }
	};

	class VISOL_API Actor : public Object {
	public:
		DECLARE_RTTI
	};
}