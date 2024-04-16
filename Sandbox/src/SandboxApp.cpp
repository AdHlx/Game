#include <Fountainhead.h>
#include <Fountainhead/Core/EntryPoint.h>

#include "GameLayer.h"

class Sandbox : public Fountainhead::Application
{
public:
	Sandbox()
	{
		PushLayer(new GameLayer());
		//PushOverlay(new Fountainhead::ImGuiLayer());//推入ImGuiLayer作为覆层
	}

	~Sandbox()
	{

	}
};

Fountainhead::Application* Fountainhead::CreateApplication()
{
	return new Sandbox();
}