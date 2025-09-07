#include "globalMemory.h"

namespace ViSolEngine {
	GlobalMemoryUsage* GlobalMemoryUsage::sInstance = nullptr;

	GlobalMemoryUsage& GlobalMemoryUsage::get() {
		if (sInstance == nullptr) {
			sInstance = new GlobalMemoryUsage();
		}

		return *sInstance;
	}

	GlobalMemoryUsage::GlobalMemoryUsage() : mMemoryManager() {

	}

	GlobalMemoryUsage::~GlobalMemoryUsage() {

	}

	void GlobalMemoryUsage::freeOnStack(void* memory) {
		mMemoryManager.freeOnStack(memory);
	}
}