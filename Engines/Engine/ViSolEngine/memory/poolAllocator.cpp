#include "memoryAllocator.h"
namespace ViSolEngine {
	PoolAllocator::PoolAllocator(size_t memorySize, void* address, size_t chunkSize, uint8_t chunkAlignment) :
		MemoryAllocator(memorySize, address), mChunkSize(chunkSize), mChunkAlignment(chunkAlignment)
	{
		union {
			void* asVoidPtrAddress;
			uintptr_t asUintPtrAddress;
		};
		asVoidPtrAddress = mStartAddress;
        // 1) Align the starting address of the pool to the required chunk alignment.
        // Example: if mStartAddress = 1002 and chunkAlignment = 8,
        // alignForward(1002, 8) = 1008 (the next multiple of 8).
        // This ensures that every chunk in the pool will begin at a properly aligned address.
		size_t adjustedAddress = alignForward(asUintPtrAddress, mChunkAlignment);
		mAddressOffset = adjustedAddress - asUintPtrAddress;
		mMemorySize -= mAddressOffset;


        // 2) Align the chunk size itself to the same alignment.
        // Example: if chunkSize = 10 and chunkAlignment = 8,
        // alignForward(10, 8) = 16. Now every chunk is guaranteed
        // to start at an aligned address, and have size multiple of alignment.
		mChunkSize = alignForward(mChunkSize, mChunkAlignment);
		VISOL_ASSERT(mChunkSize >= sizeof(FreeNode) && "Invalid chunk size");
		VISOL_ASSERT(mMemorySize >= mChunkSize && "Invalid memory size");
		mFreeListHead = nullptr;
		this->clear();
	}

	PoolAllocator::~PoolAllocator() {
	}

	void* PoolAllocator::allocate() {
		FreeNode* node = mFreeListHead;
		VISOL_ASSERT(node != nullptr && "PoolAllocator is full, no more chunk to allocate");
		mFreeListHead = node->next;
		mUsedMemory += mChunkSize;
		mAllocationCount++;
		return node;
	}

	void PoolAllocator::free(void* memory) {
		VISOL_ASSERT(memory != nullptr && "Free invalid memory address");
		uintptr_t numberOfChunks = mMemorySize / mChunkSize;
		VISOL_ASSERT(contains(memory) && "Free out of bound memory address");
		
		FreeNode* node = reinterpret_cast<FreeNode*>(memory);
		node->next = mFreeListHead; // Its make value in vector change
		mFreeListHead = node;
		mUsedMemory -= mChunkSize;
		mAllocationCount--;
	}

	void PoolAllocator::clear() {
		size_t numberOfChunks = mMemorySize / mChunkSize;
		union {
			void* asVoidPtrAddress;
			char* asCharPtrAddress;
		};
		asVoidPtrAddress = mStartAddress;
		for (size_t idx = 0; idx < numberOfChunks; idx++) {
			FreeNode* node = reinterpret_cast<FreeNode*>(asCharPtrAddress + mAddressOffset + idx * mChunkSize);
			node->next = mFreeListHead;
			mFreeListHead = node;
		}
		mUsedMemory = 0;
		mAllocationCount = 0;
	}

	bool PoolAllocator::contains(void* memory) {
		union {
			void* asVoidPtrAddress;
			uintptr_t asUintPtrAddress;
		};
		asVoidPtrAddress = mStartAddress;
		uintptr_t numberOfChunks = mMemorySize / mChunkSize;
		uintptr_t uintPtrMemory = reinterpret_cast<uintptr_t>(memory);
		// is bounding
		return uintPtrMemory >= asUintPtrAddress && uintPtrMemory <= asUintPtrAddress + mAddressOffset + (numberOfChunks - 1) * mChunkSize;
	}

}
