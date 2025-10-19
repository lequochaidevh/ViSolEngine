#include "UI_ViRobotLayer.h"
#include <ViSolEngine/base.h>
#include <ViSolEngine/core/system/system.h>
#include <ViSolEngine/core/renderer/renderer2D.h>

UIplayLayer::UIplayLayer() {

}

UIplayLayer::~UIplayLayer() {

}

void UIplayLayer::onAttach() {

	LOG_TRACE("UIplayLayer is attached");
	
	using namespace ViSolEngine;

	mVertexBuffer = VertexBuffer::create();
	mIndexBuffer = IndexBuffer::create();
	mShader = Shader::create("assets/shader/quad.glsl");

	Vertex vertices[4] = {
		{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top-left
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
		{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
		{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)} // top-right
	};
	mVertexBuffer->setData(vertices, sizeof(vertices));

	uint32_t indicies[6] = {
		0, 1, 2, // left-bottom triangle
		2, 3, 0 // right-top triangle
	};
	mIndexBuffer->setData(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));
	
}

void UIplayLayer::onDetach() {
	LOG_TRACE("UIplayLayer is detached");
}

void UIplayLayer::onUpdate(ViSolEngine::Time time) {
	ViSolEngine::Renderer::clearColor(1.0f, 0.3f, 0.6f);

	static float temp = 0.0f;
	temp += time.getDeltaTime();

	mShader->bind();
	mShader->setVector3("tempColor", glm::vec3(glm::cos(temp) + 1.0f, 1.0f, glm::sin(temp) + 1.0f));
	mShader->setFloat("alpha", glm::sin(temp) + 1.0f);
	mVertexBuffer->bind();
	mIndexBuffer->bind();
	ViSolEngine::Renderer::drawIndexed(mIndexBuffer->getNums());
}

bool UIplayLayer::onKeyPressedEvent(const ViSolEngine::KeyPressedEvent& eventContext) {
	return false;
}