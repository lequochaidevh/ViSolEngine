#pragma once

/*1*/
#include "pch.h"
/*Define Macro IS */
#include"core/input/keyCode.h"
#define IS_KEY_FUNC VISOL_FORCE_INLINE bool isKey(EKeyCode keyCode) const { return mKeyCode == (int32_t)keyCode; } ;
#define IS_BUTTON_FUNC VISOL_FORCE_INLINE bool isButton(EMouseButton button) const { return mButton == (int32_t)button; } ;
namespace ViSolEngine {
	class VISOL_API EventContext {
	public:
		virtual ~EventContext() = default;
	};

	class VISOL_API WindowResizedEvent : public EventContext {
	public:
		WindowResizedEvent(int32_t width, int32_t height) : mWidth(width)
            , mHeight(height) {}
            
		VISOL_FORCE_INLINE int32_t getWidth() const { return mWidth; }
		VISOL_FORCE_INLINE int32_t getHeight() const { return mHeight; }
	private:
		int32_t mWidth, mHeight;
	};

	/*9_Create event KeyCode and Mouse*/
	class VISOL_API KeyPressedEvent : public EventContext {
	public:
		KeyPressedEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VISOL_FORCE_INLINE int32_t getKeyCode() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	public:
		VISOL_FORCE_INLINE int32_t getKey() const { return mKeyCode; }
		IS_KEY_FUNC;
	};

	class VISOL_API KeyHeldEvent : public EventContext {
	public:
		KeyHeldEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VISOL_FORCE_INLINE int32_t getKeyCode() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	public:
		VISOL_FORCE_INLINE int32_t getKey() const { return mKeyCode; }
		IS_KEY_FUNC;
	};

	class VISOL_API KeyReleasedEvent : public EventContext {
	public:
		KeyReleasedEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VISOL_FORCE_INLINE int32_t getKeyCode() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	public:
		VISOL_FORCE_INLINE int32_t getKey() const { return mKeyCode; }
		IS_KEY_FUNC;
	};

	class VISOL_API MouseMovedEvent : public EventContext {
	public:
		MouseMovedEvent(double x, double y, double offsetX, double offsetY) :
			xPosition(x), yPosition(y),
			xOffset(offsetX), yOffset(offsetY) {}
		VISOL_FORCE_INLINE double getPositionX() const { return xPosition; }
		VISOL_FORCE_INLINE double getPositionY() const { return yPosition; }
		VISOL_FORCE_INLINE double getOffsetX() const { return xOffset; }
		VISOL_FORCE_INLINE double getOffsetY() const { return yOffset; }
	private:
		double xPosition, yPosition;
		double xOffset, yOffset;
	};

	class VISOL_API MouseScrolledEvent : public EventContext {
	public:
		MouseScrolledEvent(double offsetX, double offsetY) : xOffset(offsetX), yOffset(offsetY) {}
		VISOL_FORCE_INLINE double getScrollX() const { return xOffset; }
		VISOL_FORCE_INLINE double getScrollY() const { return yOffset; }
	private:
		double xOffset, yOffset;
	};

	class VISOL_API MouseButtonPressedEvent : public EventContext {
	public:
		MouseButtonPressedEvent(int32_t button) : mButton(button) {}
		VISOL_FORCE_INLINE int32_t getButton() const { return mButton; }
	private:
		int32_t mButton;
	public:
		IS_BUTTON_FUNC;
	};

	class VISOL_API MouseButtonHeldEvent : public EventContext {
	public:
		MouseButtonHeldEvent(int32_t button) : mButton(button) {}
		VISOL_FORCE_INLINE int32_t getButton() const { return mButton; }
	private:
		int32_t mButton;
	public:
		IS_BUTTON_FUNC;
	};

	class VISOL_API MouseButtonReleasedEvent : public EventContext {
	public:
		MouseButtonReleasedEvent(int32_t button) : mButton(button) {}
		VISOL_FORCE_INLINE int32_t getButton() const { return mButton; }
	private:
		int32_t mButton;
	public:
		IS_BUTTON_FUNC;
	};

}
