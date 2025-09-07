#include "memoryMonitor.h"

namespace ViSolEngine {
	MemoryMonitor* MemoryMonitor::sInstance = nullptr;

	MemoryMonitor& MemoryMonitor::get() {
		if (sInstance == nullptr) {
			sInstance = new MemoryMonitor();
		}

		return *sInstance;
	}

	MemoryMonitor::MemoryMonitor() {

	}

	MemoryMonitor::~MemoryMonitor() {

	}


	void MemoryMonitor::add(MemoryManager* memoryUsage) {
		if (memoryUsage != nullptr) {
			mUsages.push_back(memoryUsage);
		}
	}
	
	void MemoryMonitor::remove(MemoryManager* memoryUsage) {
		auto iter = std::find(mUsages.begin(), mUsages.end(), memoryUsage);

		if (iter != mUsages.end()) {
			(*iter)->clear();
			(*iter)->detectMemoryLeaks();
			mUsages.erase(iter);
		}
	}

	void MemoryMonitor::update() {
		for (auto usage : mUsages) {
			if (usage != nullptr) {
				usage->update();
			}
		}
	}

	void MemoryMonitor::clear() {
		for (auto usage : mUsages) {
			if (usage != nullptr) {
				usage->clear();
			}
		}
	}
	
	void MemoryMonitor::detectMemoryLeaks() {
		for (auto usage : mUsages) {
			if (usage != nullptr) {
				usage->detectMemoryLeaks();
			}
		}
	}
}