#pragma once
/*1*/
#include "pch.h"
#include "core/time/time.h"
#include "ECStype.h"

namespace ViSolEngine {
	namespace ECS {
		class VISOL_API ISystem {
		public:
			virtual ~ISystem() = default;
			virtual void onInit() = 0;
			virtual void onUpdate(Time) = 0;
			virtual void onShutdown() = 0;
			virtual SystemID getID() = 0;
			virtual void setID(SystemID) = 0;
			virtual float getUpdateInterval() const = 0;
			virtual void setUpdateInterval(float value) = 0;
			virtual ESystemPriority getPriority() const = 0;
			virtual void setPriority(ESystemPriority value) = 0;
			virtual float getLastUpdateTime() const = 0;
			virtual void setLastUpdateTime(float) = 0;
			virtual void setCoordinator(class Coordinator*) = 0;
		protected:
			ISystem() = default;
		};

		template<typename T>
		class VISOL_API System : public ISystem {
		public:
			static SystemTypeID getStaticTypeID() { return sStaticType; }
		public:
			System() = default;
			System(SystemID id, ESystemPriority priority = ESystemPriority::Low) : mID(id), mPriority(priority) {}
			~System() = default;

			virtual void onInit() override {}
			virtual void onUpdate(Time) override {}
			virtual void onShutdown() override {}

			VISOL_FORCE_INLINE virtual SystemID getID() override { return mID; }
			VISOL_FORCE_INLINE virtual void setID(SystemID id) override { mID = id; }

			VISOL_FORCE_INLINE float getUpdateInterval() const { return mUpdateInterval; }
			VISOL_FORCE_INLINE void setUpdateInterval(float value) { mUpdateInterval = value; }

			VISOL_FORCE_INLINE ESystemPriority getPriority() const { return mPriority; }
			VISOL_FORCE_INLINE void setPriority(ESystemPriority value) { mPriority = value; }

			VISOL_FORCE_INLINE virtual float getLastUpdateTime() const override { return mLastUpdateTime; }
			VISOL_FORCE_INLINE virtual void setLastUpdateTime(float value) override { mLastUpdateTime = value; }

			VISOL_FORCE_INLINE virtual void setCoordinator(class Coordinator* coordinator) override { mCoordinator = coordinator; }
		private:
			static SystemTypeID sStaticType;
		private:
			SystemID mID = INVALID_ID;
			float mUpdateInterval = -1.0f;
			float mLastUpdateTime = 0.0f;
			ESystemPriority mPriority = ESystemPriority::Low;
			class Coordinator* mCoordinator;
		};

		template<typename T>
		SystemTypeID System<T>::sStaticType = getTypeUUID<T>();
	} // namespace ECS
} // namespace ViSolEngine