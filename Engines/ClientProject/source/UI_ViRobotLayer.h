#pragma once

#include "core/application.h"
#include<chrono>

#define STACK_MEMORY_ALLOCATOR

#ifndef POOL_MEMORY_ALLOCATOR
	#ifndef STACK_MEMORY_ALLOCATOR
		#define LINEAR_MEMORY_ALLOCATOR
	#endif
#endif // POOL_ALLOCATOR

//void testCaseMemoryAllocator(ViSolEngine::MemoryAllocator* mAllocator);
//void testCaseMemoryPoolAllocator(ViSolEngine::PoolAllocator* mAllocator);
void testPerformanceMemoryAllocator();

class UserPlayLayer : public ViSolEngine::Layer {
public:
	UserPlayLayer() {}
	~UserPlayLayer() {}
	virtual void onAttach() override {
		LOG_TRACE("UserPlayLayer is attached");
		testPerformanceMemoryAllocator();
		/*#ifdef POOL_MEMORY_ALLOCATOR
			testCaseMemoryPoolAllocator(mAllocator);
		#elif defined(LINEAR_MEMORY_ALLOCATOR) || defined(STACK_MEMORY_ALLOCATOR)
			testCaseMemoryAllocator(mAllocator);
		#endif*/
		
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
#ifdef POOL_MEMORY_ALLOCATOR
	ViSolEngine::PoolAllocator* mAllocator;
#elif defined(LINEAR_MEMORY_ALLOCATOR) || defined(STACK_MEMORY_ALLOCATOR)
	ViSolEngine::MemoryAllocator* mAllocator;	
#endif // POOL_ALLOCATOR

	
};

void testCaseMemoryAllocator(ViSolEngine::MemoryAllocator* mAllocator) {
	size_t size = 128 * 1024 * 1024;
	void* address = malloc(size);
#ifdef LINEAR_MEMORY_ALLOCATOR 
	mAllocator = new ViSolEngine::LinearAllocator(size, address);
#elif defined(STACK_MEMORY_ALLOCATOR)
	mAllocator = new ViSolEngine::StackAllocator(size, address);
#endif // LINEAR_MEMORY_ALLOCATOR 
	struct RobotObject {
		size_t ID = 0;
		std::string Name = "RobotObject";
	};
	std::vector<RobotObject*> gameObjects;

	for (int i = 0; i < 10; i++) {
		void* memory = mAllocator->allocate(sizeof(RobotObject), alignof(RobotObject));
		RobotObject* go = new (memory)RobotObject();
		go->ID = i;
		go->Name = "RobotObject: " + std::to_string(i);
		gameObjects.emplace_back(go);
	}

	#ifdef LINEAR_MEMORY_ALLOCATOR 
		mAllocator->clear();
	#elif defined(STACK_MEMORY_ALLOCATOR)
		/*Clear Memory 1 stack*/
		for (auto iter = gameObjects.rbegin(); iter != gameObjects.rend(); ++iter) {
			mAllocator->free(*iter);
		}
	#endif 
	
	gameObjects.clear();

	for (int i = 0; i < 10; i++) {
		void* memory = mAllocator->allocate(sizeof(RobotObject), alignof(RobotObject));
		RobotObject* go = new (memory)RobotObject();
		go->ID = i + 10;
		go->Name = "RobotObject: " + std::to_string(i);
		gameObjects.emplace_back(go);
	}
	mAllocator->clear();
	gameObjects.clear();
}

void testCaseMemoryPoolAllocator(ViSolEngine::PoolAllocator* mAllocator) {
	size_t size = 128 * 1024 * 1024;
	void* address = malloc(size);

	struct RobotObject {
		size_t ID = 0;
		std::string Name = "RobotObject";
	};

	mAllocator = new ViSolEngine::PoolAllocator(size, address, sizeof(RobotObject), alignof(RobotObject));



	std::vector<RobotObject*> gameObjects;
	for (int i = 0; i < 10; i++) {
		void* memory = mAllocator->allocateChunk();
		RobotObject* go = new (memory)RobotObject();
		go->ID = i;
		go->Name = "RobotObject: " + std::to_string(i);
		gameObjects.emplace_back(go);
	}

	mAllocator->free(gameObjects[1]);
	mAllocator->free(gameObjects[2]);

	void* memory = mAllocator->allocateChunk();
	RobotObject* go = new (memory)RobotObject();
	go->ID = 11;
	go->Name = "RobotObject: " + std::to_string(11);
	gameObjects.emplace_back(go);

	memory = mAllocator->allocateChunk();
	go = new (memory)RobotObject();
	go->ID = 12;
	go->Name = "RobotObject: " + std::to_string(12);
	gameObjects.emplace_back(go);

	mAllocator->clear();
	gameObjects.clear();

	for (int i = 0; i < 10; i++) {
		void* memory = mAllocator->allocateChunk();
		RobotObject* go = new (memory)RobotObject();
		go->ID = i + 10;
		go->Name = "RobotObject: " + std::to_string(i);
		gameObjects.emplace_back(go);
	}

	mAllocator->clear();
	gameObjects.clear();
}

void testPerformanceMemoryAllocator() {
	ViSolEngine::LinearAllocator* mLinearAllocator;
	ViSolEngine::StackAllocator* mStackAllocator;
	ViSolEngine::PoolAllocator* mPoolAllocator;
	size_t size = 2000 * 1024 * 1024;

	struct RobotObject {
		size_t ID = 0;
		std::string Name = "RobotObject";
	};

	int numOfObjects = 40000000;
	std::vector<RobotObject*> objects;

	// NEW and DELETE operator
	auto startTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numOfObjects; i++) {
		RobotObject* go = new RobotObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	for (RobotObject* object : objects) {
		VISOL_FREE_MEMORY(object);
	}

	objects.clear();

	for (int i = 0; i < numOfObjects; i++) {
		RobotObject* go = new RobotObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	for (RobotObject* object : objects) {
		VISOL_FREE_MEMORY(object);
	}

	objects.clear();

	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = endTime - startTime;
	CORE_LOG_INFO("Delete operator takes: {0} seconds", duration.count() / 1000.0f);


	mLinearAllocator = new ViSolEngine::LinearAllocator(size, malloc(size));
	// LINEAR ALLOCATOR
	startTime = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mLinearAllocator->allocate(sizeof(RobotObject), alignof(RobotObject));
		RobotObject* go = new (memory)RobotObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mLinearAllocator->clear();
	objects.clear();

	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mLinearAllocator->allocate(sizeof(RobotObject), alignof(RobotObject));
		RobotObject* go = new (memory)RobotObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mLinearAllocator->clear();
	objects.clear();

	endTime = std::chrono::high_resolution_clock::now();
	duration = endTime - startTime;
	CORE_LOG_INFO("LinearAllocator takes: {0} seconds", duration.count() / 1000.0f);

	mStackAllocator = new ViSolEngine::StackAllocator(size, malloc(size));
	// STACK ALLOCATOR
	startTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mStackAllocator->allocate(sizeof(RobotObject), alignof(RobotObject));
		RobotObject* go = new (memory)RobotObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mStackAllocator->clear();
	objects.clear();

	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mStackAllocator->allocate(sizeof(RobotObject), alignof(RobotObject));
		RobotObject* go = new (memory)RobotObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mStackAllocator->clear();
	objects.clear();

	endTime = std::chrono::high_resolution_clock::now();
	duration = endTime - startTime;
	CORE_LOG_INFO("StackAllocator takes: {0} seconds", duration.count() / 1000.0f);

	mPoolAllocator = new ViSolEngine::PoolAllocator(size, malloc(size), sizeof(RobotObject), alignof(RobotObject));
	// Pool ALLOCATOR
	startTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mPoolAllocator->allocateChunk();
		RobotObject* go = new (memory)RobotObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mPoolAllocator->clear();
	objects.clear();

	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mPoolAllocator->allocateChunk();
		RobotObject* go = new (memory)RobotObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mPoolAllocator->clear();
	objects.clear();

	endTime = std::chrono::high_resolution_clock::now();
	duration = endTime - startTime;
	CORE_LOG_INFO("PoolAllocator takes: {0} seconds", duration.count() / 1000.0f);

	CORE_LOG_TRACE("DONE TESTING MEMROY ALLOCATOR");
}