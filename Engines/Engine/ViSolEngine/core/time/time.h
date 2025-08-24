#pragma once
#include"pch.h"

/* */
namespace ViSolEngine {
	class VISOL_API Time {
	public:
		Time() = default;
		// explicit Time(float deltaTime);
		explicit Time(float deltaTime) : mDeltaTime(deltaTime), mTimeScale(1.0f) {
		}
		~Time() = default;
		VISOL_FORCE_INLINE float getDeltaTime() const { return mDeltaTime; }
		VISOL_FORCE_INLINE void setDeltaTime(float value) { mDeltaTime = value; }
		VISOL_FORCE_INLINE float getTimeScale() const { return mTimeScale; }
		VISOL_FORCE_INLINE void setTimeScale(float value) { mTimeScale = value; }

		VISOL_FORCE_INLINE friend Time& operator+=(Time& t1, const Time& t2) { t1.mDeltaTime += t2.getDeltaTime(); return t1; }

		VISOL_FORCE_INLINE friend bool operator>=(const Time& t1, const Time& t2) { return t1.mDeltaTime >= t2.getDeltaTime(); }
		VISOL_FORCE_INLINE friend bool operator>(const Time& t1, const Time& t2) { return t1.mDeltaTime > t2.getDeltaTime(); }

		VISOL_FORCE_INLINE friend bool operator<=(const Time& t1, const Time& t2) { return t1.mDeltaTime <= t2.getDeltaTime(); }
		VISOL_FORCE_INLINE friend bool operator<(const Time& t1, const Time& t2) { return t1.mDeltaTime < t2.getDeltaTime(); }

		VISOL_FORCE_INLINE friend Time& operator-=(Time& t1, const Time& t2) { t1.mDeltaTime -= t2.getDeltaTime(); return t1; }
		
	private:
		float mDeltaTime, mTimeScale;
	};
}