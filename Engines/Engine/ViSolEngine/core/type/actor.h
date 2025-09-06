#pragma once

#include"ECS/coordinator.h"
#include"object.h"

namespace ViSolEngine {
	class VISOL_API Actor : public Object {
	public:
		DECLARE_RTTI
	public:
		Actor() = default;
		Actor(ECS::Coordinator* coordinator);
		Actor(ECS::EntityID id, ECS::Coordinator* coordinator);
		~Actor();

		template<typename T, typename... Args>
		VISOL_FORCE_INLINE T& addComponent(Args&&... args) \
		{ return mCoordinator->addComponent<T>(mID, mCoordinator, std::forward<Args>(args)...); }
		
		template<typename T>
		VISOL_FORCE_INLINE T& getComponent() { return mCoordinator->getComponent<T>(mID); }
		
		template<typename T>
		VISOL_FORCE_INLINE bool hasComponent() { return mCoordinator->hasComponent<T>(mID); }
		
		template<typename T>
		VISOL_FORCE_INLINE void removeComponent() { mCoordinator->removeComponent<T>(mID); }

		VISOL_FORCE_INLINE ECS::EntityID getID() const { return mID; }

	private:
		ECS::EntityID mID;
		ECS::Coordinator* mCoordinator;
	};
}