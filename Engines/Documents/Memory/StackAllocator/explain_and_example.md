# StackAllocator
## Explain

### Code c++

```c++
// =======================================================================================
// Function: getAddressAdjustment
// Purpose:  Calculate the padding (extra space) needed so that the memory address
//           aligns properly and also has room for a header.
// =======================================================================================

uint8_t MemoryAllocator::getAddressAdjustment(const void* address,
                                              uint8_t alignment,
                                              uint8_t extraMemory) {
    // Make sure alignment is valid (must be power of 2)
    VI_ASSERT(isPowerOfTwo(alignment) && "Alignment is invalid");

    // First, get normal padding without considering extra memory
    uint8_t padding = getAddressAdjustment(address, alignment);
    // Example: pading = 0; 
    // -------------------Example padding = 2; header need 1; return padding
    // If normal padding is not enough to fit the header,
    // we must add more to guarantee both alignment + header space.
    if (padding < extraMemory) {
        uint8_t remainPadding = extraMemory - padding;
        // remainPadding = 1 - 0 = 1
        // If remainPadding is NOT already aligned
        // 1 & (4 - 1) = 1 != 0 -> excute if
        if ((remainPadding & (alignment - 1)) != 0) {
            // Round up to next multiple of alignment
            // Example: remainPadding=1, alignment=4 → padding += 4
            padding += alignment * (1 + (remainPadding / alignment));
            // padding = 0 + 4 * ( 1 + (1/4)) = 4 * 1 = 4
        }
        else {
            // remainPadding is already multiple of alignment
            padding += alignment * (remainPadding / alignment);
        }
    }
    return padding; // return 4
}


// =======================================================================================
// Function: StackAllocator::memAllocate
// Purpose:  Allocate memory block inside stack allocator with correct alignment.
// =======================================================================================

void* StackAllocator::memAllocate(size_t memorySize, uint8_t alignment) {
    VI_ASSERT(memorySize > INVALID_MEMORY_SIZE && "Allocate invalid memory size");
    VI_ASSERT(alignment < MAX_ALLOWED_ALIGNMENT && "Invalid alignment");

    union {
        void* asVoidPtrAddress;
        uintptr_t asUintPtrAddress;
        Header* asHeader;
    };

    // Start from the beginning of the free region
    asVoidPtrAddress = mStartAddress;
    asUintPtrAddress += mUsedMemory;

    // Calculate padding (includes adjustment for header size)
    uintptr_t padding = getAddressAdjustment(asVoidPtrAddress,
                                             alignment,
                                             sizeof(Header));

    // Out of memory check
    if (mUsedMemory + padding + memorySize > mMemorySize) {
        CORE_LOG_WARN("StackAllocator is full, cannot allocate {0} bytes", memorySize);
        return nullptr;
    }

    // Update usage
    mUsedMemory += memorySize + padding; // Ex: 0 + 16 + 4 -> used

    // Move pointer forward by padding
    asUintPtrAddress += padding; // Ex: 0 + 4 -> offset affter padding

    // Reserve space for header BEFORE actual object
    asUintPtrAddress -= sizeof(Header); // 4 - 1 = 3
    asHeader->Padding = padding;   // Save padding info into header // Write 4 to address=3*
    asUintPtrAddress += sizeof(Header); // move to 4

    mAllocationCount++; // Number of Ojects are allocated

    // Return aligned pointer to user
    return asVoidPtrAddress;
}
```

## Example Case:

**Case: alignment = 4, Header = 1**
```sh
Before allocation:

[ StartAddr ][ Free ....................... ]


Step 1: getAddressAdjustment() = 0 (already aligned)
Step 2: Need 1 extra byte for Header → round up to 4
        => padding = 4


After allocation (object size = N):

[ P ][ P ][ P ][ H ][ D ][ D ][ D ]...[ D ]
  ^              ^
  |              |
  |              --> User pointer returned (aligned) Header->Padding = 4
  |
  --> Padding bytes (4 bytes)

Legend:
P = Padding (to ensure alignment)
H = Header (stores metadata like padding size)
D = User data (actual object memory)
```

**Case: alignment = 8, Header = 2**
```sh
Before allocation:

[ StartAddr ][ Free ....................... ]


Step 1: getAddressAdjustment() = 0 (aligned)
Step 2: Need 2 extra bytes for Header → round up to 8
        => padding = 8


After allocation:

[ P ][ P ][ P ][ P ][ P ][ P ][ H ][ H ][ D ][ D ]...[ D ]
  ^                                  ^
  |                                  --> User pointer returned (aligned to 8 bytes)
  --> 8 bytes of padding
```