#pragma once

#include"pch.h"
#include"object.h"

namespace ViSolEngine {
	template<typename To, typename From>
	VISOL_FORCE_INLINE To StaticCast(From from) { return (To)from; }

	template<typename T>
	T* DownCast(Object* obj) {
		if (obj && obj->isDerivedFrom(T::runTimeType)) {
			return (T*)obj;
		}

		return nullptr;
	}

	template<typename T>
	const T* DownCast(const Object* obj) {
		if (obj && obj->isDerivedFrom(T::runTimeType)) {
			return (const T*)obj;
		}

		return nullptr;
	}
}