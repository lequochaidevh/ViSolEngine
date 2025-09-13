#pragma once

#include"pch.h"
#include"core/type/RTTI.h"

namespace ViSolEngine {
	class VISOL_API Renderer {
	public:
		DECLARE_RTTI

	public:
		Renderer();
		~Renderer();

		void onInit();
		bool beginScene();
		void render();
		void endScene();
		void shutDown();
	};
}