#pragma once
#include "memoryAllocator.h"


namespace ViSolEngine {
	struct MemoryConfiguration {
		// 10MB default buffer size for a single frame
		size_t perFrameBufferSize = 10 * 1024 * 1024;
		// 10MB default buffer size for stack allocator
		size_t stackBufferSize = 10 * 1024 * 1024;
	};

	struct MemoryUsage { 
		const char* resouceName;
		void* resouceAddress;
	};

    // Not parser API for user. It belong Engine
	class MemoryManager { 
	public:
		MemoryManager(const MemoryConfiguration& config);
		~MemoryManager();
		// Clear temporary memories on a single frame allocated by allocators
		void update();

		// Clear all memories allocated by allocators
		void clear();
		// Allocate temporary memory that will be automatically freed at the end of a frame
		void* allocatePerFrame(size_t memorySize, uint8_t alignment);
		void* allocateOnStack(const char* usage, size_t memorySize, uint8_t alignment);


		void freeOnStack(void* memory);
		void clearOnStack();
		void detectMemoryLeaks();
		// Allocate temporary memory that will be automatically freed at the end of a frame
		template<typename T, typename... Args>
		T* newPerFrame(Args&&... args) {
			void* address = mPerFrameAllocator.allocate(sizeof(T), alignof(T));
			return new (address)T(std::forward<Args>(args)...);
		}
		template<typename T, typename... Args>
		T* newOnStack(const char* usage, Args&&... args) {
			void* address = allocateOnStack(usage, sizeof(T), alignof(T));
				return new (address)T(std::forward<Args>(args)...);
		}
	private:
		LinearAllocator mPerFrameAllocator;
		StackAllocator mStackAllocator;
		MemoryConfiguration mConfig;
		std::vector<MemoryUsage> mActiveMemoryList;

        // Memory address be call free but violation on top to bottom
		std::vector<void*> mFreedMemoryList;
	};
}
