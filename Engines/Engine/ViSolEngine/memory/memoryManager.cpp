#include"memoryManager.h"
#include"core/logger/logger.h"
#include"memoryMonitor.h"

namespace ViSolEngine {
	MemoryManager::MemoryManager(const MemoryConfiguration& config) : mConfig(config),
		mPerFrameAllocator(config.perFrameBufferSize, malloc(config.perFrameBufferSize)),
		mStackAllocator(config.stackBufferSize, malloc(config.stackBufferSize))
	{
		MemoryMonitor::get().add(this);
	}
	MemoryManager::~MemoryManager() {
	}
	void MemoryManager::update() {
		mPerFrameAllocator.clear();
	}
	void MemoryManager::clear() {
		mPerFrameAllocator.clear();
		mStackAllocator.clear();
	}
	void* MemoryManager::allocatePerFrame(size_t memorySize, uint8_t alignment) {
		return mPerFrameAllocator.allocate(memorySize, alignment);
	}
	/*
	* Allocate stack;
	* Save pointer for every component in array stackAllocator.
	*/
	void* MemoryManager::allocateOnStack(const char* usage, size_t memorySize, uint8_t alignment) {
		void* address = mStackAllocator.allocate(memorySize, alignment);
		mActiveMemoryList.push_back({ usage, address });
		return address;
	}
	void MemoryManager::freeOnStack(void* memory) {
		if (!mActiveMemoryList.empty() && memory == mActiveMemoryList.back().resourceAddress) {
			mStackAllocator.free(memory);
			mActiveMemoryList.pop_back();
			bool remainMemory = true;
			while (remainMemory) {
				remainMemory = false;
				for (auto iter = mFreedMemoryList.begin(); iter != mFreedMemoryList.end(); ++iter) {
					if (*iter == mActiveMemoryList.back().resourceAddress) {
						mStackAllocator.free(*iter);
						mActiveMemoryList.pop_back();
						mFreedMemoryList.erase(iter);
						remainMemory = true;
						break;
					}
				}
			}
		}
		else {
			CORE_LOG_WARN("User did not free memory {0} in order of stack", memory);
			mFreedMemoryList.emplace_back(memory);
		}
	}
	void MemoryManager::clearOnStack() {
		mStackAllocator.clear();
	}
	void MemoryManager::detectMemoryLeaks() {
		VISOL_ASSERT(!(mFreedMemoryList.size() && mActiveMemoryList.size() == 0) && "Implementation failure!");
		if (mActiveMemoryList.size()) {
			CORE_LOG_WARN("!!!  M E M O R Y  L E A K  D E T E C T E D  !!!");
			for (auto& pendingMemory : mActiveMemoryList) {
				bool isFreed = false;
				for (auto freedMemory : mFreedMemoryList) {
					if (freedMemory == pendingMemory.resourceAddress) {
						isFreed = true;
						break;
					}
				}
				if (isFreed == false) {
					CORE_LOG_WARN("{0} memory user did not release allocated memory {1}!", pendingMemory.resourceName, pendingMemory.resourceAddress);
				}
			}
		}
		else {
			CORE_LOG_INFO("No memory leaks detected");
		}
	}
}