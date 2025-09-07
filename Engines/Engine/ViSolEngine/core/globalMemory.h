#pragma once

#include "pch.h"
#include "memory/memoryManager.h"

namespace ViSolEngine {
	class VISOL_API GlobalMemoryUsage {
	public:
		static GlobalMemoryUsage& get();
	private:
		static GlobalMemoryUsage* sInstance;

	public:
		~GlobalMemoryUsage();

		void freeOnStack(void* memory);

		// Allocate temporary memory that will be automatically freed at the end of a frame
		template<typename T, typename... Args>
		T* newPerFrame(Args&&... args) {
			return mMemoryManager.newPerFrame<T>(std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		T* newOnStack(const char* usage, Args&&... args) {
			return mMemoryManager.newOnStack<T>(usage, std::forward<Args>(args)...);
		}

	protected:
		GlobalMemoryUsage();

	private:
		MemoryManager mMemoryManager;
	};
}