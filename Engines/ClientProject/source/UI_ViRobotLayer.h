#pragma once

#include "core/application.h"
#include<chrono>
#include "core/memory/memoryChunkManager.h"

static size_t Count = 0;

struct Texture {
	Texture() {
		id = Count++;
	}

	uint32_t id;
	std::string filePath;
};

using namespace ViSolEngine;

class ResourceManager {

	class TextureManager : public MemoryChunkManager<Texture, 4> {
	public:
		TextureManager(const char* usage, const MemoryConfiguration& config) : MemoryChunkManager(usage, config) {

		}

		Texture* loadTexture() {
			return newObject();
		}

		void unload(void* memory) {
			freeObject(memory);
		}
	};

public:
	ResourceManager() : mTextureManager("TextureManager", {}) {

	}

	Texture* loadTexture() {
		return mTextureManager.loadTexture();
	}

	void unloadTexture(void* memory) {
		mTextureManager.unload(memory);
	}

	void unloadAllTextures() {
		mTextureManager.reset();
	}

	void shutdown() {
		mTextureManager.detectMemoryLeaks();
	}

private:
	TextureManager mTextureManager;
};


class UserPlayLayer : public ViSolEngine::Layer {
public:
	UserPlayLayer() {}
	~UserPlayLayer() {}
	virtual void onAttach() override {
		LOG_TRACE("UserPlayLayer is attached");
		LOG_TRACE("GameplayLayer is attached");

		std::vector<Texture*> textures;

		int count = 10;
		for (int i = 0; i < count; i++) {
			textures.emplace_back(mResourceManager.loadTexture());
		}

		mResourceManager.unloadTexture(textures[1]);
		mResourceManager.unloadTexture(textures[9]);

		mResourceManager.loadTexture();
		mResourceManager.loadTexture();

		mResourceManager.unloadAllTextures();
		textures.clear();

		for (int i = 0; i < count; i++) {
			textures.emplace_back(mResourceManager.loadTexture());
		}

		//mResourceManager.unloadAllTextures();
		mResourceManager.shutdown();

		CORE_LOG_WARN("Testing point");
	}
	virtual void onDetach() override {
		LOG_TRACE("UserPlayLayer is detached");
	}
	virtual bool onKeyPressedEvent(const ViSolEngine::KeyPressedEvent& eventContext) override {
		//LOG_TRACE("Key {0} is pressed", (char)eventContext.getKey());
		return false;
	}
	virtual void onUpdate(ViSolEngine::Time time) {
		//LOG_TRACE("{0} Delta Time", time.getDeltaTime());
	}
	

private:
	ResourceManager mResourceManager;
};
