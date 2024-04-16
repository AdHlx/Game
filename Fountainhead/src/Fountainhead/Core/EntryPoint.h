#pragma once

#include "Fountainhead/Core/Core.h"

#ifdef FH_PLATFORM_WINDOWS

extern Fountainhead::Application* Fountainhead::CreateApplication();

int main(int argc, char** argv)
{
	Fountainhead::Log::Init();


	FH_PROFILE_BEGIN_SESSION("Startup", "FountainheadProfile-Startup.json");

	auto app = Fountainhead::CreateApplication();
	FH_PROFILE_END_SESSION();

	FH_PROFILE_BEGIN_SESSION("Runtime", "FountainheadProfile-Runtime.json");
	app->Run();
	FH_PROFILE_END_SESSION();

	FH_PROFILE_BEGIN_SESSION("Startup", "FountainheadProfile-Shutdown.json");
	delete app;
	FH_PROFILE_END_SESSION();
}
#endif // FH_PLATFORM_WINDOWS
