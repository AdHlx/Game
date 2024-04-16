#pragma once

#include "Fountainhead/Events/Event.h"

namespace Fountainhead {
	class KeyEvent : public Event//创建基类，包含按键码用来区分不同按键事件
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)//在基类KeyEvent中实现了这个，因为按键按下和弹起的事件都是这个，没必要在他们自己的类中实现
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}//除了它的子类，没有其他东西能够构造它

		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent//按键按下事件
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:" << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}//重写ToString函数，打印被按下的按键码以及重复的次数

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class  KeyReleasedEvent : public KeyEvent//按键弹起事件，除了和按下事件在重复计数外其他都相同
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent:" << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent//按键按下事件
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent:" << m_KeyCode;
			return ss.str();
		}//重写ToString函数，打印被按下的按键码以及重复的次数

		EVENT_CLASS_TYPE(KeyTyped)
	};
}