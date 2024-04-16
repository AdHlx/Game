#include "fhpch.h"
#include "Fountainhead/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Fountainhead {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;
	
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");//%T是时间，%n是日志名，后面的都是实际的信息
		s_CoreLogger = spdlog::stdout_color_mt("Fountainhead");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}