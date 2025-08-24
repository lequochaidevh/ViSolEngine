#pragma once
#include"pch.h"

namespace ViSolEngine {
	const uint8_t INVALID_MEMORY_SIZE = 0;
	const uint8_t MAX_ALLOWED_ALIGNMENT = 128;
	class VISOL_API MemoryAllocator {
	public:
		MemoryAllocator(size_t memorySize, void* address);
		virtual ~MemoryAllocator() = default;
		virtual void* memAllocate(size_t memorySize, uint8_t alignment) { return nullptr; }
		virtual void memFree(void* memory) {}
		virtual void memClear() {}
	protected:
		uint8_t getAddressAdjustment(const void* address, uint8_t alignment);
		bool isPowerOfTwo(uint8_t alignment);
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
		virtual void* memAllocate(size_t memorySize, uint8_t alignment) override;
		virtual void memFree(void* memory) override;
		virtual void memClear() override;
	};
}