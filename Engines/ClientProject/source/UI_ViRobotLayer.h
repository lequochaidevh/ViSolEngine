#pragma once

#include<core/layer/layer.h>
#include<ViSolEngine/base.h>
class UIplayLayer : public ViSolEngine::Layer {
public:
	UIplayLayer();
	~UIplayLayer();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(ViSolEngine::Time time);
	virtual bool onKeyPressedEvent(const ViSolEngine::KeyPressedEvent& eventContext);

};