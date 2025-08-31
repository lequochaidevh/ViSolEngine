#include"entityManager.h"
#include"core/logger/logger.h"

namespace ViSolEngine { 
	namespace ECS {
		EntityManager::EntityManager() {

		}

		EntityManager::~EntityManager() {

		}

		EntityID EntityManager::getNextID() {
			EntityID id = INVALID_ID;

			if (!mReusableIDs.empty()) {
				id = mReusableIDs.front();
				mReusableIDs.pop();
			}
			else {
				id = getUUID();
			}

			return id;
		}

		void EntityManager::addEntity(EntityID id) {
			if (mEntitiesSet.count(id)) {
				CORE_LOG_WARN("Insert duplicated entity id {0}", id);
				return;
			}

			mEntitiesSet.insert(id);
		}

		void EntityManager::removeEntity(EntityID id) {
			mEntitiesSet.erase(id);
		}

		void EntityManager::releaseForReuse(EntityID id) {
			mEntitiesSet.erase(id);
			mReusableIDs.push(id);
		}
	} // namespace ECS
} // namespace ViSolEngine