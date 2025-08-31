#include "UI_ViRobotLayer.h"

using namespace ViSolEngine;

UIplayLayer::UIplayLayer() {

}

UIplayLayer::~UIplayLayer() {

}

void UIplayLayer::onAttach() {
	MemoryManager memoryManager;
	{
		ECS::Coordinator* coordinator = memoryManager.newOnStack<ECS::Coordinator>("Coordinator");
		Actor* actor = memoryManager.newOnStack<Actor>("Actor", coordinator);

		actor->addComponent<TransformComponent>(2.0f, 3.0f);
		TransformComponent& transform = actor->getComponent<TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.getX(), transform.getY());

		transform.setX(10.0f);
		transform.setY(-20.0f);
		transform = actor->getComponent<TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.getX(), transform.getY());

		if (actor->hasComponent<TransformComponent>()) {
			actor->removeComponent<TransformComponent>();
		}

		if (!actor->hasComponent<TransformComponent>()) {
			LOG_WARN("Actor transform component has been removed");
		}
	}
	memoryManager.clearOnStack();
}

void UIplayLayer::onDetach() {
	LOG_TRACE("UIplayLayer is detached");
}

void UIplayLayer::onUpdate(Time time) {
	
}

bool UIplayLayer::onKeyPressedEvent(const KeyPressedEvent& eventContext) {
	return false;
}