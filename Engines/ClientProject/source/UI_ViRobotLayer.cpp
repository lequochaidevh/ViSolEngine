#include "UI_ViRobotLayer.h"
#include<ViSolEngine/base.h>
#include<core/system/system.h>

UIplayLayer::UIplayLayer() {

}

UIplayLayer::~UIplayLayer() {

}

void UIplayLayer::onAttach() {
	ViSolEngine::MemoryManager* memoryManager = new ViSolEngine::MemoryManager();
	// Move init memory allocator of component to Engine -> Application::init

	{
		ViSolEngine::ECS::Coordinator* coordinator = memoryManager->newOnStack<ViSolEngine::ECS::Coordinator>("Coordinator");
		ViSolEngine::Actor* actor = memoryManager->newOnStack<ViSolEngine::Actor>(ViSolEngine::Actor::runTimeType.getTypeName(), coordinator);

		actor->addComponent<ViSolEngine::TransformComponent>(2.0f, 3.0f);
		ViSolEngine::TransformComponent& transform = actor->getComponent<ViSolEngine::TransformComponent>();

		LOG_TRACE("Actor position: ({0}, {1})", transform.getX(), transform.getY());

		transform.setX(10.0f);
		transform.setY(-20.0f);
		transform = actor->getComponent<ViSolEngine::TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.getX(), transform.getY());

		if (actor->hasComponent<ViSolEngine::TransformComponent>()) {
			actor->removeComponent<ViSolEngine::TransformComponent>();
		}

		if (!actor->hasComponent<ViSolEngine::TransformComponent>()) {
			LOG_WARN("Actor transform component has been removed");
		}

		memoryManager->freeOnStack(actor);
		memoryManager->freeOnStack(coordinator);
		coordinator->~Coordinator(); // avoid deleting scalar destructor by delete<key>
	}
	memoryManager->clearOnStack();
}

void UIplayLayer::onDetach() {
	LOG_TRACE("UIplayLayer is detached");
}

void UIplayLayer::onUpdate(ViSolEngine::Time time) {
	
}

bool UIplayLayer::onKeyPressedEvent(const ViSolEngine::KeyPressedEvent& eventContext) {
	return false;
}