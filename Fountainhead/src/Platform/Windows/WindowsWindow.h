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

		void OnUpdate() override;//����glfw��������������ȥ�����¼��ȵȣ�Ӧ��ÿ֡����һ�Σ����Ҵ�Application�е���

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }//���Դ��ڵĳ�����
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		//���ڻص���Ҫ�õ�����������ݽṹ
		struct WindowData//�洢��glfw����ͨ���¼��ص�request������
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;//�ṹ����������ݵ�glfw����Ϊ�û��Զ�������
	};
}