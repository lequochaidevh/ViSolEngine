
#pragma once

#include"IComponent.h"
#include"core/type/cast.h"
#include"core/memory/memoryChunkManager.h"

namespace ViSolEngine {
	namespace ECS {
		constexpr size_t MAX_COMPONENT_PER_ARRAY = 500;
		template<typename T>
		using MemChunkManagerAlias = MemoryChunkManager<T, MAX_COMPONENT_PER_ARRAY>;
		class ComponentManager {
			
			class IComponentArray {
			public:
				virtual ~IComponentArray() = default;
				virtual bool hasComponent(EntityID) = 0;
				virtual void removeComponent(EntityID) = 0;
			protected:
				IComponentArray() = default;
			};

		public:
			template<typename T>
			class ComponentArray : \
            public MemChunkManagerAlias<T>, \
            public IComponentArray {
			using MemChunkManagerAlias<T>::newObject;
			using MemChunkManagerAlias<T>::freeObject;

			public:
				ComponentArray() = default;
				ComponentArray(const char* resourceName)  \
                : MemChunkManagerAlias<T>(resourceName) {} // MemoryChunkManger set default config
				~ComponentArray() = default;

				template<typename... Args>
				T& addComponent(EntityID id, Args&&... args) {
					VISOL_BASE_CLASS_ASSERT(IComponent, T, "Add invalid component");
					T* component = newObject(std::forward<Args>(args)...);
					component->setOwner(id);
					component->setID(getUUID());
					
					mComponentsMap[id] = component;

					return *component;
				}

				T& getComponent(EntityID id) {
					VISOL_BASE_CLASS_ASSERT(IComponent, T, "Get invalid component");
					VISOL_ASSERT(mComponentsMap.count(id) && "Get non-existing component of entity");
					
					return *StaticCast<T*>(mComponentsMap.at(id));
				}

				virtual bool hasComponent(EntityID id) override {
					VISOL_BASE_CLASS_ASSERT(IComponent, T, "Check invalid component");
					return mComponentsMap.count(id) != 0;
				}

				virtual void removeComponent(EntityID id) override {
					VISOL_BASE_CLASS_ASSERT(IComponent, T, "Remove invalid component");
					VISOL_ASSERT(hasComponent(id) && "Remove non-existing component");
					
					freeObject(mComponentsMap.at(id));
					mComponentsMap.erase(id);
				}
			private:
				std::unordered_map<EntityID, IComponent*> mComponentsMap;
			}; // ComponentArray

			using ComponentTypeMap = std::unordered_map<ComponentTypeID, IComponentArray*>;

		public:
			ComponentManager() : mComponentTypeMap() {}
			~ComponentManager() {
				for (auto& [typeId, componentArray] : mComponentTypeMap) {
					VISOL_FREE_MEMORY(componentArray);
				}
				mComponentTypeMap.clear();
			}

			template<typename T>
			ComponentArray<T>& getComponentArray() {
				VISOL_BASE_CLASS_ASSERT(IComponent, T, "Get invalid component");
				ComponentTypeID typeID = T::getStaticTypeID();
				VISOL_ASSERT(mComponentTypeMap.count(typeID) && "Component array is not registered yet");
				return *StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID));
			}

			template<typename T, typename... Args>
			T& addComponent(EntityID id, Args&&... args) {
				ComponentTypeID typeID = T::getStaticTypeID();

				if (!mComponentTypeMap.count(typeID)) {
					IComponentArray* componentArray = new ComponentArray<T>(T::runTimeType.getTypeName());
					mComponentTypeMap[typeID] = componentArray;
				}
                // IComponent* not have addComponent. Because not need id of component type, need use StaticCast
                // addComponent is a method of child class (ComponentArray) of IComponentArray
                // ComponentManager:addComponent -> ComponentArray:addComponent -> MemoryChunkManager(Pool)
				return StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID))->addComponent(id, std::forward<Args>(args)...);
			}

			template<typename T>
			T& getComponent(EntityID id) {
				ComponentTypeID typeID = T::getStaticTypeID();
				return StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID))->getComponent(id);
			}

			template<typename T>
			bool hasComponent(EntityID id) {
				ComponentTypeID typeID = T::getStaticTypeID();

				if (!mComponentTypeMap.count(typeID)) {
					CORE_LOG_WARN("Check non-existing component {0}", T::runTimeType.getTypeName());
					return false; // INVALID = 0
				}

				return StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID))->hasComponent(id);
			}

			template<typename T>
			void removeComponent(EntityID id) {
				if (!hasComponent<T>(id)) return;

				ComponentTypeID typeID = T::getStaticTypeID();
				StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID))->removeComponent(id);
			}

			void removeRelatedComponents(EntityID id) {
				for (auto& [_, componentArray] : mComponentTypeMap) {
					if (!componentArray->hasComponent(id)) continue;
					componentArray->removeComponent(id);
				}

				mComponentTypeMap.erase(id);
			}

		private:
			ComponentTypeMap mComponentTypeMap;
		};
	} // namespace ECS
} // namespace ViSolEngine
