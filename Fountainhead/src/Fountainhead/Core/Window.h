#pragma once

#include "fhpch.h"

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Events/Event.h"

namespace Fountainhead {

	struct WindowProps//Windows�ϵ�Ĭ�ϴ�������
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Fountainhead Engine",
			unsigned int width = 1200,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	//Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;//һ�����¼�Ϊ����������void�ĺ���
		//��WindowsWindow.cpp�������¼�ʱ�����ǻ���¼����ȵ��¼��ص�����

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;//��Ӧ�ó����е�������֪���ڣ��������¼��ص���Ӧ�ó���
		//Ȼ�����ǿ��԰��¼����������еĲ㣬������Ͼ��Ǵ�����������¼��ķ�ʽ�����������¼�
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;//ʹ��void*���Բ�������GLFWwindow���������ʹ�������Ĵ��ڿ⣬Ҳ����

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}