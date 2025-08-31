#pragma once
/*4*/
#include"pch.h"
#include"ECStype.h"

namespace ViSolEngine {
	namespace ECS {
		class IComponent {
		public:
			virtual ~IComponent() = default;
			virtual EntityID getOwner() const = 0;
			virtual void setOwner(EntityID id) = 0;
			virtual ComponentID getID() const = 0;
			virtual void setID(ComponentID id) = 0;
			virtual bool getIsActive() const = 0;
			virtual void setIsActive(bool value) = 0;
		protected:
			IComponent() = default;
		};

		template<typename T>
		class Component : public IComponent {
		public:
			VISOL_FORCE_INLINE static ComponentTypeID getStaticTypeID() { return sStaticType; }
		public:
			Component() = default;
			Component(EntityID owner, ComponentID id) : mOwner(owner), mID(id) {}

			VISOL_FORCE_INLINE virtual EntityID getOwner() const override { return mOwner; }
			VISOL_FORCE_INLINE virtual void setOwner(EntityID id) override { mOwner = id; }
			VISOL_FORCE_INLINE virtual ComponentID getID() const override { return mID; }
			VISOL_FORCE_INLINE virtual void setID(ComponentID id) override { mID = id; }
			VISOL_FORCE_INLINE virtual bool getIsActive() const override { return mIsActive; }
			VISOL_FORCE_INLINE virtual void setIsActive(bool value) override { mIsActive = value; }
		private:
			static ComponentTypeID sStaticType;
		private:
			EntityID mOwner;
			ComponentID mID;
			bool mIsActive;
		};

		template<typename T>
		ComponentTypeID Component<T>::sStaticType = getTypeUUID<T>();
	} // namespace ECS
} // namespace ViSolEngine