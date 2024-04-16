#pragma once

#include "Fountainhead/Core/Core.h"

#include "Fountainhead/Core/Window.h"
#include "Fountainhead/Core/LayerStack.h"
#include "Fountainhead/Events/ApplicationEvent.h"

#include "Fountainhead/Core/Timestep.h"

#include "Fountainhead/ImGui/ImGuiLayer.h"

namespace Fountainhead {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }//���ش�������

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;//���洰�����һ��ʵ��
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;//��ջ������ջ�ڴ��ǣ��̳�App�����������
		float m_LastFrameTime = 0.0f;//��Ⱦ���һ֡��ʹ�õ�ʱ��
	private:
		static Application* s_Instance;
	};

	//To defined in CLIENT
	Application* CreateApplication();
}