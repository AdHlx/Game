#include "fhpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Fountainhead {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		FH_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		FH_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);//创建当前上下文
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FH_CORE_ASSERT(status, "Failed to initialize Glad!");

		FH_CORE_INFO("OpenGL Info");
		FH_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		FH_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		FH_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		FH_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);//交换缓冲区
	}
}