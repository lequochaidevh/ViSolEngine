#pragma once

#include "pch.h"
#include "memoryManager.h"

namespace ViSolEngine {
	class VISOL_API MemoryMonitor {
	public:
		static MemoryMonitor& get();
	private:
		static MemoryMonitor* sInstance;

	public:
		~MemoryMonitor();
	protected:
		MemoryMonitor();
	public:
		void add(MemoryManager* memoryUsage);
		void remove(MemoryManager* memoryUsage);
		void update();
		void clear();
		void detectMemoryLeaks();
	private:
		std::vector<MemoryManager*> mUsages;
	};
}