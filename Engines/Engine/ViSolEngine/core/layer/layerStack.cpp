#include"layerStack.h"

/*4 Define func in LayerStack*/

namespace ViSolEngine {
	LayerStack::LayerStack() : mIndex(0), mLayers() {
        CORE_LOG_TRACE("Create layer stack");
	}
	LayerStack::~LayerStack() {
	}
	void LayerStack::push(Layer* layer) {
		mLayers.emplace(mLayers.begin() + mIndex, layer);
		mIndex++;
	}
	void LayerStack::pushOverlay(Layer* layer) {
		mLayers.emplace_back(layer);
	}
	void LayerStack::pop(Layer* layer) {
		auto iter = std::find(mLayers.begin(), mLayers.end(), layer);
		if (iter != mLayers.end()) {
			mLayers.erase(iter);
			mIndex--;
		}
	}
	void LayerStack::popOverlay(Layer* layer) {
		auto iter = std::find(mLayers.begin() + mIndex, mLayers.end(), layer);//fix: to improve performent
		if (iter != mLayers.end()) {
			mLayers.erase(iter);
		}
	}
}