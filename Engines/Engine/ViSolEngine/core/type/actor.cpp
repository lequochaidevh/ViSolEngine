#include "actor.h"

namespace ViSolEngine {
	DEFINE_RTTI(Actor, &Object::runTimeType)
	
	Actor::Actor(ECS::Coordinator* coordinator) : mID(INVALID_ID), mCoordinator(coordinator) {

	};
	
	Actor::Actor(ECS::EntityID id, ECS::Coordinator* coordinator) : mID(id), mCoordinator(coordinator) {

	};

	Actor::~Actor() {
		mCoordinator->releaseForReuseEntity(mID);
	};
}