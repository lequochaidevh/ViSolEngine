#pragma once

#include"ECS/ISystem.h"
#include"core/logger/logger.h"
#include"core/time/time.h"
#include"core/type/RTTI.h"

namespace ViSolEngine {
	class CollisionResolver : public ECS::System<CollisionResolver> {
	public:
		DECLARE_RTTI
	public:
		CollisionResolver() = default;
		CollisionResolver(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low) : System(id, priority) {}
		~CollisionResolver() = default;

		virtual void onInit() override {
			CORE_LOG_INFO("CollisionResolver init!");
		}

		virtual void onUpdate(Time time) override {
			CORE_LOG_INFO("CollisionResolver update!");
		}

		virtual void onShutdown() override {
			CORE_LOG_INFO("CollisionResolver is shutdown!");
		}
	};

	class AnimationSystem : public ECS::System<AnimationSystem> {
	public:
		DECLARE_RTTI
	public:
		AnimationSystem() = default;
		AnimationSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low) : System(id, priority) {}
		~AnimationSystem() = default;

		virtual void onInit() override {
			CORE_LOG_INFO("AnimationSystem init!");
		}

		virtual void onUpdate(Time time) override {
			CORE_LOG_INFO("AnimationSystem update!");
		}

		virtual void onShutdown() override {
			CORE_LOG_INFO("AnimationSystem is shutdown!");
		}
	};

	class Renderer2D : public ECS::System<Renderer2D> {
	public:
		DECLARE_RTTI
	public:
		Renderer2D() = default;
		Renderer2D(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low) : System(id, priority) {}
		~Renderer2D() = default;

		virtual void onInit() override {
			CORE_LOG_INFO("Renderer2D init!");
		}

		virtual void onUpdate(Time time) override {
			CORE_LOG_INFO("Renderer2D update!");
		}

		virtual void onShutdown() override {
			CORE_LOG_INFO("Renderer2D is shutdown!");
		}
	};
}