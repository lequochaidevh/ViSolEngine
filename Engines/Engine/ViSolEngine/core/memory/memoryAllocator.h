#pragma once
#include"pch.h"

namespace ViSolEngine {
	const uint8_t INVALID_MEMORY_SIZE = 0;
	const uint8_t MAX_ALLOWED_ALIGNMENT = 128;
	class VISOL_API MemoryAllocator {
	public:
		MemoryAllocator(size_t memorySize, void* address);
		virtual ~MemoryAllocator() = default;
		virtual void* allocate(size_t memorySize, uint8_t alignment) { return nullptr; }
		virtual void free(void* memory) {}
		virtual void clear() {}
	protected:
		uint8_t getAddressAdjustment(const void* address, uint8_t alignment);
		bool isPowerOfTwo(uint8_t alignment);
	protected:
		uint8_t getAddressAdjustment(const void* address, uint8_t alignment, uint8_t extraMemory);
	protected:
		size_t alignForward(size_t memorySize, uint8_t alignment);
	protected:
		void* mStartAddress;
		size_t mMemorySize;
		size_t mUsedMemory;
		size_t mAllocationCount;
	};

	class VISOL_API LinearAllocator : public MemoryAllocator {
	public:
		LinearAllocator(size_t memorySize, void* address);
		~LinearAllocator();
		virtual void* allocate(size_t memorySize, uint8_t alignment) override;
		virtual void free(void* memory) override;
		virtual void clear() override;
	};

	class VISOL_API StackAllocator : public MemoryAllocator {
		struct Header {
			uint8_t padding;
		};
	public:
		StackAllocator(size_t memorySize, void* address);
		~StackAllocator();
		virtual void* allocate(size_t memorySize, uint8_t alignment) override;
		virtual void free(void* memory) override;
		virtual void clear() override;
	};

	class VISOL_API PoolAllocator : public MemoryAllocator {
		struct FreeNode {
			FreeNode* next;
		};
	public:
		PoolAllocator(size_t memorySize, void* address, size_t chunkSize, uint8_t chunkAlignment);
		~PoolAllocator();
		void* allocateChunk();
		virtual void free(void* memory) override;
		virtual void clear() override;
	private:
		size_t mChunkSize;
		uint8_t mChunkAlignment;
		FreeNode* mFreeListHead;
		uint8_t mAddressOffset;
	};
}