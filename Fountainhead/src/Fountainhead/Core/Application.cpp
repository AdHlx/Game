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

		m_Window = Window::Create();//����ʹ��unique_ptr������Ӧ�ó�����ֹʱ�����ǲ����Լ�ɾ������
		//Window::Create()����ù��캯����Ȼ������Init()
		m_Window->SetEventCallback(FH_BIND_EVENT_FN(Application::OnEvent));
		//��std::bind��һ����Ա�������ú��

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		FH_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)//һ���������������Ͼ��ǰѲ���߸��������ջ
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
		dispatcher.Dispatch<WindowCloseEvent>(FH_BIND_EVENT_FN(Application::OnWindowClose));//����ǹرղ������͵��ȵ�OnWindowClosed�������
		dispatcher.Dispatch<WindowResizeEvent>(FH_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)//�������
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		FH_PROFILE_FUNCTION();

		while (m_Running)//�������imgui����
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