#pragma once
/*1*/
#include "core/input/inputState.h"

class GLFWwindow;
namespace ViSolEngine
{
	enum class EWindowPlatformSpec
	{
		GLFW,
		SDL,
		None
	};

	struct ApplicationConfiguration; // Forward delaration when not include application.h

	/*for close source*/
	class EventDispatcher;

	typedef struct windownData_t
	{
		EventDispatcher *pEventDispatcher;
		int32_t width, height;
		InputState input;
	} windownData_t;
	class NativeWindow
	{
	public:
		virtual ~NativeWindow() = default;
		virtual bool init(const struct ApplicationConfiguration &, EventDispatcher *) = 0;
		virtual void shutdown() = 0;
		virtual void swapbuffers() = 0;
		virtual void pollsEvent() = 0;
		virtual bool shouldClose() = 0;
		virtual InputState* getInputState() = 0;

	private:
	protected:
		NativeWindow() = default;
		NativeWindow(NativeWindow &) = default;
	};
	class GLFWPlatformWindow : public NativeWindow
	{
	public:
		bool init(const struct ApplicationConfiguration &, EventDispatcher*) override;
		void shutdown() override;
		void swapbuffers() override;
		void pollsEvent() override;
		bool shouldClose() override;
		InputState* getInputState() override;

		GLFWPlatformWindow();
		~GLFWPlatformWindow();

	private:
		GLFWwindow *mWindow;
		windownData_t mData;

	protected:
	};

}