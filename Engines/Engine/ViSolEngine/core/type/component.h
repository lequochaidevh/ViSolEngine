#pragma once

#include "object.h"
#include "actor.h"
#include "ECS/IComponent.h"

namespace ViSolEngine {
	class TransformComponent : public ECS::Component<TransformComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
		TransformComponent() = default;
		TransformComponent(float x, float y) : mX(x), mY(y) {}
		~TransformComponent() {}

		float getX() const { return mX; }
		void setX(float value) { mX = value; }
		float getY() const { return mY; }
		void setY(float value) { mY = value; }
	private:
		float mX, mY;
	};

	// DEFINE_RTTI_NO_PARENT(TransformComponent) // Linux platform will impl in cpp
}