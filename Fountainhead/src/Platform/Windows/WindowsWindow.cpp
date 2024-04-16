#include "fhpch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Fountainhead/Events/ApplicationEvent.h"
#include "Fountainhead/Events/MouseEvent.h"
#include "Fountainhead/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Fountainhead {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)//这个错误函数需要做的就是记下日志
	{
		FH_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	//创建窗口时，调用构造函数，构造函数调用Init()，根据属性设置所有数据
	Scope<Window> Window::Create(const WindowProps& props)//Create函数的实现
	{
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		FH_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		FH_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)//初始化glfw并创建我们的窗口
	{
		FH_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		FH_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{
			FH_PROFILE_FUNCTION();
			int success = glfwInit();
			FH_CORE_ASSERT(success, "Could not intialize GLFW!");//使用断言检查是否出现问题
			glfwSetErrorCallback(GLFWErrorCallback);//添加错误回调函数
		}

		{
			FH_PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);//创建glfw窗口
			++s_GLFWWindowCount;
		}
		
		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);//设置一个窗口用户指针，用于事件回调
		//这个函数，窗口结构体会以void*保存传入的用户数据指针，这就让我们可以让我们使用这个函数，从窗口中获得用户数据指针
		SetVSync(true);//垂直同步设置

		//设置GLFW回调
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)//需要传入一个窗口，和一个窗口大小改变之后要调用的函数
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);//这返回一个void*，我们需要转型成正确的类型
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);//接着我们要创建Fountainhead事件
			data.EventCallback(event);//完成创建窗口大小事件并且调度
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)//窗口关闭事件
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)//按键事件
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)//按键码是glfw独有的，因此需要转换为Fountainhead的按键码
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)//鼠标按键事件
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)//鼠标滚轮事件
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)//鼠标移动事件
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()//销毁窗口
	{
		FH_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		FH_PROFILE_FUNCTION();

		glfwPollEvents();//拉取事件
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)//垂直同步设置函数
	{
		FH_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);//这里可以设置n，n就是n次同步，相当于1/n显示器帧率
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;//跟踪它是否被启用，因为我们无法从glfw中查询这个数据
	}

	bool WindowsWindow::IsVSync() const//返回是否打开了垂直同步
	{
		return m_Data.VSync;
	}
}