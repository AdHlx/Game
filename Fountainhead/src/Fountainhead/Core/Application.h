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

		inline Window& GetWindow() { return *m_Window; }//返回窗口引用

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;//保存窗口类的一个实例
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;//层栈创建在栈内存是，继承App类的生命周期
		float m_LastFrameTime = 0.0f;//渲染最后一帧所使用的时间
	private:
		static Application* s_Instance;
	};

	//To defined in CLIENT
	Application* CreateApplication();
}