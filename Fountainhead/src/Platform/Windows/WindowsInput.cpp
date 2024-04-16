#include "fhpch.h"
#include "Platform/Windows/WindowsInput.h"

#include "Fountainhead/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Fountainhead {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		//从Application类中获得GLFWwindow
		//要访问GLFWwindow，就要调用glfwGetKey()来判断按键按下，就需要传入窗口指针和按键码
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());//调用这个函数来询问GLFW
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return y;
	}

}