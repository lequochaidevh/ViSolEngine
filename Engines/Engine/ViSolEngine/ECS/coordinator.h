#pragma once

#include "pch.h"
#include "entityManager.h"
#include "componentManager.h"
#include "systemManager.h"
namespace ViSolEngine {
	namespace ECS {
		class Coordinator {
		public:
			Coordinator();
			~Coordinator();

			template<typename T>
			VISOL_FORCE_INLINE ComponentManager::ComponentArray<T>& getComponentArray() \
            { return mComponentManager.getComponentArray<T>(); }
			
			template<typename T, typename... Args>
			VISOL_FORCE_INLINE T& addComponent(EntityID id, Coordinator* coordinator, Args&&... args) \
            { return mComponentManager.addComponent<T>(id, coordinator, std::forward<Args>(args)...); }
			
			template<typename T>
			VISOL_FORCE_INLINE T& getComponent(EntityID id) \
            { return mComponentManager.getComponent<T>(id); }

			template<typename T>
			VISOL_FORCE_INLINE bool hasComponent(EntityID id) \
            { return mComponentManager.hasComponent<T>(id); }
			
			template<typename T>
			VISOL_FORCE_INLINE void removeComponent(EntityID id) \
            { mComponentManager.removeComponent<T>(id); }

			EntityID addEntity();
			void addEntity(EntityID id);
			void removeEntity(EntityID id);
			void releaseForReuseEntity(EntityID id);

		private:
			EntityManager mEntityManager;
			ComponentManager mComponentManager;
			SystemManager mSystemManager;
		};
	} // namespace ECS
} // namespace ViSolEngine