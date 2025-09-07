#pragma once

#include "ISystem.h"
#include "memory/memoryManager.h"
#include "core/logger/logger.h"

#include"core/type/RTTI.h"
#include"core/type/cast.h"

namespace ViSolEngine {
	namespace ECS {
		class SystemManager : public MemoryManager {
			using DependenciesMatrix = std::vector<std::vector<bool>>;
		public:
			DECLARE_RTTI

		public:
			SystemManager();
			SystemManager(class Coordinator*);
			~SystemManager();

			void onInit();
			void onUpdate(Time);
			void onShutdown();

			template<typename T, typename... Args>
			T& addSystem(Args&&... args) {
				VISOL_BASE_CLASS_ASSERT(ISystem, T, "Add not valid system type");

				ISystem* system = newOnStack<T>(T::runTimeType.getTypeName(), std::forward<Args>(args)...);

				system->setID(mSystemIdx++);
				system->setCoordinator(mCoordinator);

				mSystemMap[T::getStaticTypeID()] = system;
				mUnsortedOrderSystems.emplace_back(system);

				CORE_LOG_TRACE("{0} is added with ID {1}.", T::runTimeType.getTypeName(), system->getID());
				mDependenciesMatrix.resize(mSystemIdx);
				for (uint8_t i = 0; i < mDependenciesMatrix.size(); i++) {
					mDependenciesMatrix[i].resize(mSystemIdx);
				}
				mRebuildSystemWorkOrder = true;

				return *StaticCast<T*>(system);
			}

			template<typename T>
			T& getSystem() {
				VISOL_BASE_CLASS_ASSERT(ISystem, T, "Get not valid system type");

				SystemTypeID systemID = T::getStaticTypeID();
				VISOL_ASSERT(mSystemMap.count(systemID) && "Get non-existing system");

				return *StaticCast<T*>(mSystemMap.at(systemID));
			}

			template<typename T, typename Dependency>
			void addSystemDependency(T* target, Dependency* dependency) {
				VISOL_BASE_CLASS_ASSERT(ISystem, T, "Not valid system target type");
				VISOL_BASE_CLASS_ASSERT(ISystem, Dependency, "Not valid system dependency type");
				
				SystemID targetID = target->getID();
				SystemID dependencyID = dependency->getID();

				mDependenciesMatrix[targetID][dependencyID] = true;
				CORE_LOG_TRACE("{1} is added as a dependency of {0}", T::runTimeType.getTypeName(), Dependency::runTimeType.getTypeName());
			}

			template<typename T, typename Dependency, typename... Dependencies>
			void addSystemDependency(T* target, Dependency* dependency, Dependencies&&... dependencies) {
				VISOL_BASE_CLASS_ASSERT(ISystem, T, "Not valid system target type");
				VISOL_BASE_CLASS_ASSERT(ISystem, Dependency, "Not valid system dependency type");
				
				SystemID targetID = target->getID();
				SystemID dependencyID = dependency->getID();

				mDependenciesMatrix[targetID][dependencyID] = true;
				CORE_LOG_TRACE("{1} is added as a dependency of {0}", T::runTimeType.getTypeName(), Dependency::runTimeType.getTypeName());
				
				addSystemDependency(target, std::forward<Dependencies>(dependencies)...);
			}

		private:
			void buildSystemWorkOrder();

		private:
			std::unordered_map<SystemTypeID, ISystem*> mSystemMap;
			std::vector<ISystem*> mUnsortedOrderSystems;
			std::vector<ISystem*> mSortedOrderSystems;
			SystemID mSystemIdx;
			DependenciesMatrix mDependenciesMatrix;
			class Coordinator* mCoordinator;
			bool mRebuildSystemWorkOrder;
		};
	}
}