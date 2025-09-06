#include "actor.h"

namespace ViSolEngine {
	DEFINE_RTTI(Actor, &Object::runTimeType)
	
	Actor::Actor(ECS::Coordinator* coordinator) : mCoordinator(coordinator) {
		mID = mCoordinator->addEntity();
	};
	
	Actor::Actor(ECS::EntityID id, ECS::Coordinator* coordinator) : mID(id), mCoordinator(coordinator) {

	};

	Actor::~Actor() {
		// mCoordinator->releaseForReuseEntity(mID);
	};
}