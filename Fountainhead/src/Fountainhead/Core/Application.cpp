#include "fhpch.h"
#include "Fountainhead/Core/Application.h"

#include "Fountainhead/Core/Log.h"

#include "Fountainhead/Renderer/Renderer.h"

#include "Fountainhead/Core/Input.h"

#include <GLFW/glfw3.h>

namespace Fountainhead {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FH_PROFILE_FUNCTION();

		FH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();//我们使用unique_ptr所以在应用程序终止时，我们不必自己删除窗口
		//Window::Create()会调用构造函数，然后会调用Init()
		m_Window->SetEventCallback(FH_BIND_EVENT_FN(Application::OnEvent));
		//用std::bind绑定一个成员函数，用宏简化

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		FH_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)//一个适配器，本质上就是把层或者覆层推入层栈
	{
		FH_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		FH_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		FH_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(FH_BIND_EVENT_FN(Application::OnWindowClose));//如果是关闭操作，就调度到OnWindowClosed这个函数
		dispatcher.Dispatch<WindowResizeEvent>(FH_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)//反向遍历
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		FH_PROFILE_FUNCTION();

		while (m_Running)//层更新与imgui更新
		{
			FH_PROFILE_FUNCTION();

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					FH_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					FH_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		FH_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}