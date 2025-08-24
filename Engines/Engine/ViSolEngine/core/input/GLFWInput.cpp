
#include "inputState.h"
#include <GLFW/glfw3.h>
/*3*/

class GLFWwindow;

namespace ViSolEngine {
	/*Create func to check and convert type to enum class*/
	static EKeyState GLFWToEngineKeyState(int32_t action) {
		if (action == GLFW_PRESS) return EKeyState::Pressed;
		if (action == GLFW_REPEAT) return EKeyState::Held;
		if (action == GLFW_RELEASE) return EKeyState::Released;
		return EKeyState::None;
	}

	/*Define func in GLFWKeyboard*/
	GLFWKeyboardInput::GLFWKeyboardInput(void* window) {
		mWindow = (GLFWwindow*)window;
	}

	EKeyState GLFWKeyboardInput::getState(int32_t keyCode) const {
		return GLFWToEngineKeyState(glfwGetKey(mWindow, keyCode));
	}
    
	bool GLFWKeyboardInput::isPressed(int32_t keyCode) const {
		return glfwGetKey(mWindow, keyCode) == GLFW_PRESS;
	}

	bool GLFWKeyboardInput::isHeld(int32_t keyCode) const {
		// TODO: Not use this method, it not work on GLFW
		return glfwGetKey(mWindow, keyCode) == GLFW_REPEAT;
	}
	bool GLFWKeyboardInput::isReleased(int32_t keyCode) const {
		return glfwGetKey(mWindow, keyCode) == GLFW_RELEASE;
	}

	GLFWMouseInput::GLFWMouseInput(void* window) {
		mWindow = (GLFWwindow*)window;
	}
	EKeyState GLFWMouseInput::getState(int32_t button) const {
		return GLFWToEngineKeyState(glfwGetMouseButton(mWindow, button));
	}

	bool GLFWMouseInput::isPressed(int32_t button) const {
		return glfwGetMouseButton(mWindow, button) == GLFW_PRESS;
	}

	bool GLFWMouseInput::isHeld(int32_t button) const {
		// TODO: Not use this method, it not work on GLFW
		return glfwGetMouseButton(mWindow, button) == GLFW_REPEAT;
	}

	bool GLFWMouseInput::isReleased(int32_t button) const {
		return glfwGetMouseButton(mWindow, button) == GLFW_RELEASE;
	}




}
