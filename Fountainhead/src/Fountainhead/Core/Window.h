#pragma once

#include "fhpch.h"

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Events/Event.h"

namespace Fountainhead {

	struct WindowProps//Windows上的默认窗口属性
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
		using EventCallbackFn = std::function<void(Event&)>;//一个以事件为参数，返回void的函数
		//在WindowsWindow.cpp中生成事件时，我们会把事件调度到事件回调函数

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;//从应用程序中调用来告知窗口，把所有事件回调到应用程序
		//然后我们可以把事件传播到所有的层，这基本上就是处理各种类型事件的方式，包括窗口事件
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;//使用void*可以不必须是GLFWwindow，如果我们使用其他的窗口库，也可以

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}