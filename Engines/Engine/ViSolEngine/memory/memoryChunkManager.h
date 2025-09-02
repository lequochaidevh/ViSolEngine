#pragma once

#include "memoryManager.h"
#include "core/logger/logger.h"

/*6*/
namespace ViSolEngine {
	template<typename T, std::size_t MAX_OBJECT_PER_CHUNK>
	class MemoryChunkManager : public MemoryManager { // be Stack (onStack) or Linear (PerFrame) Allocator
		static constexpr size_t MEMORY_CHUNK_MAX_SIZE = sizeof(T) * MAX_OBJECT_PER_CHUNK;
		using ObjectList = std::list<T*>;

        // **Poolallocator** to manage 1 chunk;
		class MemoryChunk {
		public:
			MemoryChunk(PoolAllocator* allocator) : mAllocator(allocator) {
			}

			void* allocate() {
				void* memory = mAllocator->allocate(); // **Poolallocator**
				VISOL_ASSERT(memory && "Failed to allocate memory");
				mObjectList.emplace_back((T*)memory);
				return memory;
			}

			//TODO: work not found case
			void free(void* memory) {				
				auto iter = std::find(mObjectList.begin(), mObjectList.end(), memory);
				if (iter != mObjectList.end()) {
					mAllocator->free(memory);
					mObjectList.erase(iter);
				}
			}

			bool hasSlot() {
				return mObjectList.size() < MAX_OBJECT_PER_CHUNK;
			}

			bool contains(void* memory) {
				return mAllocator->contains(memory);
			}

			const ObjectList& getObjects() const { return mObjectList; }

			void clear() {
				mAllocator->clear();
				mObjectList.clear();
			}

			void close() {
				clear();
				VISOL_FREE_MEMORY(mAllocator);
			}

			void* getStartAddress() const { return mAllocator->getStartAddress(); }

		private:
			PoolAllocator* mAllocator;
			ObjectList mObjectList;
		};

		using MemoryChunkList = std::list<MemoryChunk*>;
		class Iterator {
		public:
			Iterator(typename MemoryChunkList::iterator begin, typename MemoryChunkList::iterator end) : mCurrentChunk(begin), mEndChunk(end) {
				if (begin != end) {
					VISOL_ASSERT(*mCurrentChunk && "Invalid memory chunk");
					mCurrentObject = (*mCurrentChunk)->getObjects().begin();
				}
				else {
					mCurrentObject = (*std::prev(mEndChunk))->getObjects().end();
				}
			}
			Iterator& operator++() {
				mCurrentObject++;
				if (mCurrentObject == (*mCurrentChunk)->getObjects().end()) {
					mCurrentChunk++;
					if (mCurrentChunk != mEndChunk) {
						VISOL_ASSERT(*mCurrentChunk != nullptr && "Invalid memory chunk");
						mCurrentObject = (*mCurrentChunk)->getObjects().begin(); // start at next chunk
					}
				}
				return *this;
			}
			VISOL_FORCE_INLINE T* operator*() const { return *mCurrentObject; }
			VISOL_FORCE_INLINE T* operator->() const { return *mCurrentObject; }
			bool operator==(const Iterator& other) const {
				return mCurrentChunk == other.mCurrentChunk && mCurrentObject == other.mCurrentObject;
			}

			bool operator!=(const Iterator& other) const {
				return !(*this == other);
			}
		private:
			typename MemoryChunkList::iterator mCurrentChunk;
			typename MemoryChunkList::iterator mEndChunk;
			typename ObjectList::const_iterator mCurrentObject;
		};
	public:
		MemoryChunkManager(const char* usage, \
			const MemoryConfiguration& config = MemoryConfiguration()) \
			: mUsage(usage), MemoryManager(config) {
		}

		~MemoryChunkManager() {
		}

		void* allocate() {
			void* memory = nullptr;

			for (MemoryChunk* memoryChunk : mMemoryChunkList) {
				if (!memoryChunk->hasSlot()) {
					continue;
				}
				return memoryChunk->allocate(); // Allocate 1 PoolAllocator : 1 Chunk
			}
            // If list is full, allocate new chunk and atach to list
			if (memory == nullptr) {
				PoolAllocator* allocator = new PoolAllocator(
					MEMORY_CHUNK_MAX_SIZE,  // memorySize
					allocateOnStack(mUsage, MEMORY_CHUNK_MAX_SIZE, alignof(T)), // address: stack(sizeAll, alignment)
					sizeof(T), // chunkSize of object
                    alignof(T) // chunkAlignment
				);
				MemoryChunk* memoryChunk = new MemoryChunk(allocator);
				memory = memoryChunk->allocate();
				mMemoryChunkList.emplace_back(memoryChunk);
			}
			VISOL_ASSERT(memory && "Failed to allocate new memory");
			return memory;
		}

		template<typename... Args>
		T* newObject(Args&&... args) {
			void* address = allocate();
			return new (address)T(std::forward<Args>(args)...);
		}

		void freeObject(void* memory) {
			for (MemoryChunk* memoryChunk : mMemoryChunkList) {
				if (memoryChunk->contains(memory)) {
					memoryChunk->free(memory);
					return;
				}
			}
			CORE_LOG_WARN("Failed to free memory {0}, possible memory corruption");
		}

		void reset() {
			for (auto iter = mMemoryChunkList.rbegin(); iter != mMemoryChunkList.rend(); ++iter) {
				freeOnStack((*iter)->getStartAddress());
				(*iter)->close();
				VISOL_FREE_MEMORY(*iter);
			}
			mMemoryChunkList.clear();
		}

		VISOL_FORCE_INLINE Iterator begin() { return Iterator(mMemoryChunkList.begin(), mMemoryChunkList.end()); }
		// declare stop condition
		VISOL_FORCE_INLINE Iterator end() { return Iterator(mMemoryChunkList.end(), mMemoryChunkList.end()); }
	private:
		MemoryChunkList mMemoryChunkList;
		const char* mUsage;
	};
}