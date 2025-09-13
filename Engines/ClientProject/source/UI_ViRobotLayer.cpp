#include "UI_ViRobotLayer.h"
#include<ViSolEngine/base.h>
#include<core/system/system.h>

UIplayLayer::UIplayLayer() {

}

UIplayLayer::~UIplayLayer() {

}

void UIplayLayer::onAttach() {

	LOG_TRACE("UIplayLayer is attached");
	
	// VertexBuffer* vertex = VertexBuffer::Create();
	// IndexBuffer* index = IndexBuffer::Create();
	// Shader* shader = Shader::Create();

	// shader->Bind();
	// vertex->Bind();
	// index->Bind();
	// DrawIndexed(VI_TRIANGLES, index->Count());
	
}

void UIplayLayer::onDetach() {
	LOG_TRACE("UIplayLayer is detached");
}

void UIplayLayer::onUpdate(ViSolEngine::Time time) {
	
}

bool UIplayLayer::onKeyPressedEvent(const ViSolEngine::KeyPressedEvent& eventContext) {
	return false;
}