#pragma once

#include"pch.h"
#include"rendererAPI.h"
#include"core/type/RTTI.h"

namespace ViSolEngine {
	class VISOL_API RenderCommand { // Interface - Bridge Pattern
	public:
		static void clearColor(float r, float g, float b, float w = 1.0f) 
        { sInstance->clearColorImpl(r, g, b, w); }

		static void drawIndexed(uint32_t nums, ERendererPrimitive primitive = ERendererPrimitive::Triangles, uint32_t offset = 0) 
		{ sInstance->drawIndexedImpl(nums, primitive, offset); }

	protected:
		virtual void clearColorImpl(float r, float g, float b, float w = 1.0f) = 0;
		virtual void drawIndexedImpl(uint32_t nums, ERendererPrimitive primitive = ERendererPrimitive::Triangles, uint32_t offset = 0) = 0;

	public:
		static void onInit(ERendererSpec rendererSpec);
		static void onShutdown();
	public:
		virtual ~RenderCommand() = default;
	protected:
		RenderCommand() = default;

	protected:
		static RenderCommand* sInstance;
	};

		class OpenGLRenderCommand : public RenderCommand {
	public:
		DECLARE_RTTI
	public:
		OpenGLRenderCommand();
		~OpenGLRenderCommand();
	protected:
		virtual void clearColorImpl(float r, float g, float b, float w = 1.0f) override;
		virtual void drawIndexedImpl(uint32_t nums, ERendererPrimitive primitive = ERendererPrimitive::Triangles, uint32_t offset = 0) override;
	private:
		uint32_t mVertexArrayID;
	};
}