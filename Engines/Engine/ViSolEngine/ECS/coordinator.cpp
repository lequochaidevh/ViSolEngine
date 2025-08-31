#include"coordinator.h"

namespace ViSolEngine {
	namespace ECS {
		Coordinator::Coordinator() : mEntityManager(), mComponentManager() {

		}

		Coordinator::~Coordinator() {

		}

		EntityID Coordinator::addEntity() {
			EntityID nextID = mEntityManager.getNextID();
			mEntityManager.addEntity(nextID);
			return nextID;
		}

		void Coordinator::addEntity(EntityID id) {
			mEntityManager.addEntity(id);
		}

		void Coordinator::removeEntity(EntityID id) {
			mEntityManager.removeEntity(id);
			mComponentManager.removeRelatedComponents(id);
		}

		void Coordinator::releaseForReuseEntity(EntityID id) {
			mEntityManager.releaseForReuse(id);
			mComponentManager.removeRelatedComponents(id);
		}
	} // namespace ECS
} // namespace ViSolEngine