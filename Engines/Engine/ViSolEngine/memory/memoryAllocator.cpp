#include"memoryAllocator.h"
namespace ViSolEngine {
	MemoryAllocator::MemoryAllocator(size_t memorySize, void* address) :
		mMemorySize(memorySize), mStartAddress(address), mUsedMemory(0), mAllocationCount(0)
	{
	}
    
/* 
* This function support calculate suitable memory position in ram for cache L1 in cpu.
* Ensure cache hit almost time.
* Decrease cache miss case.
* Return needed step to jump (offset)
*/
	uint8_t MemoryAllocator::getAddressAdjustment(const void* address, uint8_t alignment) {
		VISOL_ASSERT(isPowerOfTwo(alignment) && "Alignment is invalid");

        // NOTE: This below mechanims only support with a number which is power of 2.
		/*  Example: Present address is 5, aligment of Obj is 4 bytes (support calc by function system)

			0101 = 5 (address = 0x0101)
			&
			0011 = 3 (alignment - 1 = 4 - 1 = 3)
			0001 -> 1 (remainder)
			-> offset   = alignment - remainder
                        = alignment - 1 = 4 - 1 
                        = 3 -> adjusted address = 0x1000
		*/
		uintptr_t remainder = reinterpret_cast<uintptr_t>(address) & (alignment - 1);
		if (remainder == 0) {
			return 0;
		}
		return alignment - remainder;
	}
	bool MemoryAllocator::isPowerOfTwo(uint8_t alignment) {
		/*  Example 1:
			0100 = 4
			&
			0011 = 3
			0000 -> true

            Example 2:
			0101 = 5
			&
			0100 = 4
			0100 -> false
		*/
		return (alignment & (alignment - 1)) == 0;
	}

	uint8_t MemoryAllocator::getAddressAdjustment(const void* address, uint8_t alignment, uint8_t extraMemory) {
		VISOL_ASSERT(isPowerOfTwo(alignment) && "Alignment is invalid");
		uint8_t padding = getAddressAdjustment(address, alignment);
		if (padding < extraMemory) {
			uint8_t remainPadding = extraMemory - padding;
			if ((remainPadding & (alignment - 1)) != 0) {
				padding += alignment * (1 + (remainPadding / alignment));
			}
			else {
				padding += alignment * (remainPadding / alignment);
			}
		}
		return padding;
	}

	/*
	* @param: memorySize: adress , interger
	* return address.
	*/
	size_t MemoryAllocator::alignForward(size_t memorySize, uint8_t alignment) {
		VISOL_ASSERT(isPowerOfTwo(alignment) && "Alignment is invalid");
		uintptr_t remainder = memorySize & (alignment - 1);
		if (remainder != 0) {
			memorySize += alignment - remainder;
		}
		return memorySize;
	}
}