#pragma once

#include "Fountainhead/Core/Window.h"
#include "Fountainhead/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Fountainhead {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;//更新glfw交换缓冲区，拉去输入事件等等，应当每帧运行一次，并且从Application中调用

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }//来自窗口的抽象类
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		//窗口回调需要用到这个窗口数据结构
		struct WindowData//存储了glfw可能通过事件回调request的数据
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;//结构体变量，传递到glfw，作为用户自定义数据
	};
}