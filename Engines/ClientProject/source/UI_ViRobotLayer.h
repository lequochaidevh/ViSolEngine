#pragma once

/*Layer{5}: Add NEW: Layer*/
#include "core/application.h"

class UserPlayLayer : public ViSolEngine::Layer
{
public:
	UserPlayLayer() {}
	~UserPlayLayer() {}
	virtual void onAttach() override
	{
		LOG_TRACE("UserPlayLayer is attached");
		// testCaseMemoryAllocator
		size_t size = 128 * 1024 * 1024;
		/*Allocate avaiable memory in heap*/
		void *address = malloc(size);
		/* Init allocator memory size manager by LinearAllocator */
		struct RobotObject
		{
			size_t ID = 0;
			std::string Name = "RobotObject";
		};
		
		mAllocator = new ViSolEngine::PoolAllocator(size, address, sizeof(RobotObject), alignof(RobotObject));

		std::vector<RobotObject *> robotObjects;
		for (int i = 0; i < 10; i++)
		{
			void *memory = mAllocator->allocateChunk();
			RobotObject *go = new (memory) RobotObject();
			go->ID = i;
			go->Name = "RobotObject: " + std::to_string(i);
			robotObjects.emplace_back(go);
		}
		LOG_TRACE("Free memory");
		mAllocator->memFree(robotObjects[1]);
		mAllocator->memFree(robotObjects[2]);

		void *memory = mAllocator->allocateChunk();
		RobotObject *go = new (memory) RobotObject();
		go->ID = 11;
		go->Name = "RobotObject: " + std::to_string(11);
		
		memory = mAllocator->allocateChunk();
		go = new (memory) RobotObject();
		go->ID = 12;
		go->Name = "RobotObject: " + std::to_string(12);
		// mAllocator->memClear();
		robotObjects.clear();
		// for (int i = 0; i < 10; i++)
		// {
		// 	void *memory = mAllocator->memAllocate(sizeof(RobotObject), alignof(RobotObject));
		// 	RobotObject *go = new (memory) RobotObject();
		// 	go->ID = i + 10000;
		// 	go->Name = "RobotObject: " + std::to_string(i);
		// 	robotObjects.emplace_back(go);
		// }
		// mAllocator->memClear();
		// robotObjects.clear();
	}

	virtual void onDetach() override
	{
		LOG_TRACE("UserPlayLayer is detached");
	}

	virtual void onUpdate(ViSolEngine::Time time) override
	{
		// LOG_TRACE("UserPlayLayer get time: {}", time.getDeltaTime());
	}

	virtual bool onKeyPressedEvent(const ViSolEngine::KeyPressedEvent &eventContext) override
	{
		LOG_TRACE("Key {0} is pressed", (char)eventContext.getKey());
		if (eventContext.getKey() == (int32_t)ViSolEngine::EKeyCode::ESCAPE)
		{
			CORE_LOG_CRITICAL("EXIT");
		}

		return false;
	}

	virtual bool onMouseButtonPressedEvent(const ViSolEngine::MouseButtonPressedEvent &eventContext) override
	{
		if (eventContext.isButton(ViSolEngine::EMouseButton::BUTTON_LEFT))
		{
			LOG_TRACE("UserPlayLayer Left mouse button is clicked");
			return true;
		}
		return false;
	}

private:
	ViSolEngine::PoolAllocator *mAllocator;
};

void testCaseMemoryAllocator(ViSolEngine::MemoryAllocator *mAllocator)
{
	size_t size = 128 * 1024 * 1024;
	/*Allocate avaiable memory in heap*/
	void *address = malloc(size);
	/* Init allocator memory size manager by LinearAllocator */
	mAllocator = new ViSolEngine::LinearAllocator(size, address);
	struct RobotObject
	{
		size_t ID = 0;
		std::string Name = "RobotObject";
	};

	std::vector<RobotObject *> robotObjects;
	for (int i = 0; i < 10000; i++)
	{
		void *memory = mAllocator->memAllocate(sizeof(RobotObject), alignof(RobotObject));
		RobotObject *go = new (memory) RobotObject();
		go->ID = i;
		go->Name = "RobotObject: " + std::to_string(i);
		robotObjects.emplace_back(go);
	}

	mAllocator->memClear();
	robotObjects.clear();
	for (int i = 0; i < 10000; i++)
	{
		void *memory = mAllocator->memAllocate(sizeof(RobotObject), alignof(RobotObject));
		RobotObject *go = new (memory) RobotObject();
		go->ID = i + 10000;
		go->Name = "RobotObject: " + std::to_string(i);
		robotObjects.emplace_back(go);
	}
	mAllocator->memClear();
	robotObjects.clear();
}