#pragma once

#include"pch.h"
#include"core/type/actor.h"
#include"core/logger/logger.h"
#include"core/event/eventContext.h"
#include"memory/memoryManager.h"
#include"core/type/component.h"
namespace ViSolEngine {
	template<typename To, typename From>
	VISOL_FORCE_INLINE To staticCast(From from) { return (To)from; }

	template<typename T>
	T* downCast(Object* obj) {
		if (obj && obj->isDerivedFrom(T::runTimeType)) {
			return (T*)obj;
		}

		return nullptr;
	}

	template<typename T>
	const T* downCast(const Object* obj) {
		if (obj && obj->isDerivedFrom(T::runTimeType)) {
			return (const T*)obj;
		}

		return nullptr;
	}
}