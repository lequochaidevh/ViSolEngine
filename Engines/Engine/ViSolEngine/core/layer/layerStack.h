
#pragma once
#include"layer.h"
#include"core/type/RTTI.h"

namespace ViSolEngine {
	using LayerList = std::vector<Layer*>;
	class VISOL_API LayerStack {
	public:
		DECLARE_RTTI
		class VISOL_API ReversedIterator {
		public:
			ReversedIterator() = default;
			explicit ReversedIterator(LayerList::reverse_iterator iter) : mCurrentIter(iter) {
			}
			ReversedIterator& operator++() {
				++mCurrentIter;
				return *this; // return addr
			}
			ReversedIterator& operator--() {
				--mCurrentIter;
				return *this; // return addr
			}
			bool operator!=(const ReversedIterator& other) const {
				return mCurrentIter != other.mCurrentIter;
			}
			
			Layer* operator*() const { return *mCurrentIter; }
			Layer* operator->() const { return *mCurrentIter; }
		private:
			LayerList::reverse_iterator mCurrentIter;
		};
	public:
		LayerStack();
		~LayerStack();
		void push(Layer* layer);
		void pushOverlay(Layer* layer);
		void pop(Layer* layer);
		void popOverlay(Layer* layer);
		/*define class->vector: begin() end() rbegin() rend()*/
		LayerList::iterator begin() { return mLayers.begin(); }
		LayerList::iterator end() { return mLayers.end(); }
		ReversedIterator rbegin() { return ReversedIterator(mLayers.rbegin()); }
		ReversedIterator rend() { return ReversedIterator(mLayers.rend()); }
	private:
		LayerList mLayers;
		uint8_t mIndex;
	};
}
