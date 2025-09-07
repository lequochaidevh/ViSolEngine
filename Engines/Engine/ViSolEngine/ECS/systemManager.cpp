#include "systemManager.h"
#include "ECS/coordinator.h"
#include "core/time/time.h"
#include"memory/memoryMonitor.h"

namespace ViSolEngine {
	namespace ECS {
		DEFINE_RTTI_NO_PARENT(SystemManager)

		SystemManager::SystemManager() : \
            MemoryManager(), mSystemIdx(0), mRebuildSystemWorkOrder(false) {

		}

		SystemManager::SystemManager(Coordinator* coordinator) : MemoryManager(), mCoordinator(coordinator), mSystemIdx(0), mRebuildSystemWorkOrder(false) {

		}

		SystemManager::~SystemManager() {

		}

        // Manage all component init process
		void SystemManager::onInit() {
			if (mRebuildSystemWorkOrder) {
				buildSystemWorkOrder();
				mRebuildSystemWorkOrder = false;
			}

			for (auto system : mSortedOrderSystems) {
				system->onInit();
			}

		}
        // Manage all component update process
		void SystemManager::onUpdate(Time time) {
			if (mRebuildSystemWorkOrder) {
				buildSystemWorkOrder();
				mRebuildSystemWorkOrder = false;
			}

			for (auto system : mSortedOrderSystems) {
				if (system->getUpdateInterval() < 0.0f) {
					system->onUpdate(time);
					continue;
				}

				float intervalPassBy = system->getLastUpdateTime() + time.getDeltaTime();
				if (intervalPassBy > system->getUpdateInterval()) {
					system->onUpdate(time);
					intervalPassBy -= system->getUpdateInterval();
				}

				system->setLastUpdateTime(intervalPassBy);
			}
		}

		void SystemManager::onShutdown() {
			for (auto iter = mUnsortedOrderSystems.rbegin(); iter != mUnsortedOrderSystems.rend(); iter++) {
				(*iter)->onShutdown();
				freeOnStack(*iter);
			}
			MemoryMonitor::get().remove(this);
		}

		void SystemManager::buildSystemWorkOrder() {
			mSortedOrderSystems.clear();

			enum class EVertexState {
				None, Visited, Done
			};

			using VertexTraverseStates = std::vector<EVertexState>;
			using TraversalPath = std::vector<SystemID>;
			using SystemPriorityGroups = std::unordered_map<ESystemPriority, std::vector<SystemID>>;

			VertexTraverseStates traversalStates(mSystemIdx, EVertexState::None);

			std::function<void(SystemID, VertexTraverseStates&, DependenciesMatrix&, TraversalPath&)> depthFirstSearch =
				[&](SystemID vertex, VertexTraverseStates& vertexStates, DependenciesMatrix& dependencies, TraversalPath& path)
				{
					vertexStates[vertex] = EVertexState::Visited;

					for (SystemID neighbor = 0; neighbor < dependencies[vertex].size(); neighbor++) {
						if (
							vertexStates[neighbor] == EVertexState::Visited
							|| vertexStates[neighbor] == EVertexState::Done
						) continue;

						if (dependencies[vertex][neighbor]) {
							depthFirstSearch(neighbor, traversalStates, dependencies, path);
						}
					}

					path.push_back(vertex);
					vertexStates[vertex] = EVertexState::Done;
				};

			SystemPriorityGroups systemGroups;
			for (uint8_t i = 0; i < mSystemIdx; i++) {
				ISystem* system = mUnsortedOrderSystems[i];
				systemGroups[system->getPriority()].push_back(system->getID());
			}

			std::multimap<ESystemPriority, std::vector<SystemID>> sortedGroups;
			// Starting Topological sort
			for (auto& [priority, systems] : systemGroups) {
				TraversalPath path;

				for (SystemID id : systems) {
					if (traversalStates[id] != EVertexState::Done) {
						depthFirstSearch(id, traversalStates, mDependenciesMatrix, path);
					}
				}

				sortedGroups.insert({ priority, path });
			}

			for (auto& [priority, path] : sortedGroups) {
				for (SystemID id : path) {
					mSortedOrderSystems.push_back(mUnsortedOrderSystems[id]);
				}
			}
		}

	} // namespace ECS
} // namespace ViSolEngine