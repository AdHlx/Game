#pragma once

#include "Fountainhead/Events/Event.h"

namespace Fountainhead {
	class KeyEvent : public Event//�������࣬�����������������ֲ�ͬ�����¼�
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)//�ڻ���KeyEvent��ʵ�����������Ϊ�������º͵�����¼����������û��Ҫ�������Լ�������ʵ��
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}//�����������࣬û�����������ܹ�������

		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent//���������¼�
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
		}//��дToString��������ӡ�����µİ������Լ��ظ��Ĵ���

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class  KeyReleasedEvent : public KeyEvent//���������¼������˺Ͱ����¼����ظ���������������ͬ
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

	class KeyTypedEvent : public KeyEvent//���������¼�
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent:" << m_KeyCode;
			return ss.str();
		}//��дToString��������ӡ�����µİ������Լ��ظ��Ĵ���

		EVENT_CLASS_TYPE(KeyTyped)
	};
}