
#pragma once
/*2*/
#include"ECStype.h"

namespace ViSolEngine {
	namespace ECS {
		class EntityManager {
		public:
			EntityManager();
			~EntityManager();

			EntityID getNextID();
			void addEntity(EntityID id);
			void removeEntity(EntityID id);
			void releaseForReuse(EntityID id);
		private:
			std::unordered_set<EntityID> mEntitiesSet;
			std::queue<EntityID> mReusableIDs;
		};
	}
}
