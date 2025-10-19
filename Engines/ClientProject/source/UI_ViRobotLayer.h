#pragma once

#include<core/layer/layer.h>
// #include<ViSolEngine/base.h>
#include<ViSolEngine/core/resource/vertexBuffer.h>
#include<ViSolEngine/core/resource/indexBuffer.h>
#include<ViSolEngine/core/resource/shader.h>
class UIplayLayer : public ViSolEngine::Layer {
public:
	UIplayLayer();
	~UIplayLayer();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(ViSolEngine::Time time);
	virtual bool onKeyPressedEvent(const ViSolEngine::KeyPressedEvent& eventContext);
private:
	ViSolEngine::VertexBuffer* mVertexBuffer;
	ViSolEngine::IndexBuffer* mIndexBuffer;
	ViSolEngine::Shader* mShader;
};