#include "window.h"

#include "pch.h"
#include "core/logger/logger.h"
#include "core/application.h"
#define GLFW_GL_IMPLEMENTATION
#include <glad/gl.h>
#include<GLFW/glfw3.h>
namespace ViSolEngine {
	GLFWPlatformWindow::GLFWPlatformWindow() : mWindow(nullptr) , mData() {
		CORE_LOG_INFO("Call constructor GLFW");
	}
	GLFWPlatformWindow::~GLFWPlatformWindow() {
		/*Free keyboard and mouse input (mData)*/
		VISOL_FREE_MEMORY(mData.input.Keyboard);
		VISOL_FREE_MEMORY(mData.input.Mouse);
	}
	/*Close source by pointer*/
	bool GLFWPlatformWindow::init(const ApplicationConfiguration& config, EventDispatcher* pEventDispatcher) {
		if (!glfwInit()) {
			CORE_LOG_CRITICAL("GLFW Init failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("GLFW Init success");

		// Setup context for Opengl 4.3 Core
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mWindow = glfwCreateWindow(config.width, config.height, config.title, nullptr, nullptr);
		if (!mWindow) {
			CORE_LOG_CRITICAL("Window created failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Window created success");
		
		glfwMakeContextCurrent(mWindow);
		
		//because the lambda not capture data by reference
		mData.pEventDispatcher = pEventDispatcher;

		glfwSetWindowUserPointer(mWindow, &mData);
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			//get data* from EventDispatcher
			windownData_t* data = (windownData_t*)glfwGetWindowUserPointer(window);
			data->width = width;
			data->height = height;
			WindowResizedEvent eventContext(width, height);
			data->pEventDispatcher->dispatchListener<WindowResizedEvent>(eventContext);
		});


		/*Create Input - Allocate memory heap*/
		mData.input.Keyboard = WindowPlatform::createKeyboard(config.eWindowSpec, mWindow);
		mData.input.Mouse = WindowPlatform::createMouse(config.eWindowSpec, mWindow);
		/*GLFW Set Callback Mouse and Keyboard*/
		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int keyCode, int scanCode, int action, int mods) {
			windownData_t* data = (windownData_t*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS) {
				data->pEventDispatcher->dispatchListener<KeyPressedEvent>({ keyCode });
			}
			else if (action == GLFW_REPEAT) {
				data->pEventDispatcher->dispatchListener<KeyHeldEvent>({ keyCode });
			}
			else if (action == GLFW_RELEASE) {
				data->pEventDispatcher->dispatchListener<KeyReleasedEvent>({ keyCode });
			}
			});
		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
			windownData_t* data = (windownData_t*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS) {
				data->pEventDispatcher->dispatchListener<MouseButtonPressedEvent>({ button });
			}
			else if (action == GLFW_RELEASE) {
				data->pEventDispatcher->dispatchListener<MouseButtonReleasedEvent>({ button });
			}
			});
		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double positionX, double positionY) {
			windownData_t* data = (windownData_t*)glfwGetWindowUserPointer(window);
			static double lastFrameX = positionX;
			static double lastFrameY = positionY;
			double offsetX = positionX - lastFrameX;
			double offsetY = positionY - lastFrameY;
			data->pEventDispatcher->dispatchListener<MouseMovedEvent>({ positionX, positionY, offsetX, offsetY });
			data->input.Mouse->setPosition(positionX, positionY);
			data->input.Mouse->setOffset(offsetX, offsetY);
			lastFrameX = positionX;
			lastFrameY = positionY;
			});
		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double scrollX, double scrollY) {
			windownData_t* data = (windownData_t*)glfwGetWindowUserPointer(window);
			data->pEventDispatcher->dispatchListener<MouseScrolledEvent>({ scrollX, scrollY });
			data->input.Mouse->setScroll(scrollX, scrollY);
			});
		
		//Check to see if window can successfully interact
		if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
			CORE_LOG_CRITICAL("Glad load failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Glad load success");

		return true;
	}
	void GLFWPlatformWindow::shutdown() {
		glfwTerminate();
	}
	void GLFWPlatformWindow::swapbuffers() {
		glClearColor(0.3f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mWindow);
	}
	void GLFWPlatformWindow::pollsEvent() {
		glfwPollEvents();
	}
	bool GLFWPlatformWindow::shouldClose() {
		return glfwWindowShouldClose(mWindow);
	}

	/*Allow pointer*/
	InputState* GLFWPlatformWindow::getInputState() {
		return &mData.input;
	}

	float GLFWPlatformWindow::getRealTime() {
		return glfwGetTime();
	}

}