#pragma once

#include "Fountainhead/Core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>//用于spdlog的输出流运算符，以便我们可以日志自定义类型

namespace Fountainhead {
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

//核心日志宏定义
#define FH_CORE_TRACE(...)	::Fountainhead::Log::GetCoreLogger()->trace(__VA_ARGS__)//__VA_ARGS__将宏中的变量参数转发给实际参数
#define FH_CORE_INFO(...)	::Fountainhead::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FH_CORE_WARN(...)	::Fountainhead::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FH_CORE_ERROR(...)	::Fountainhead::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FH_CORE_FATAL(...)	::Fountainhead::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//客户端日志宏定义
#define FH_TRACE(...)		::Fountainhead::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FH_INFO(...)		::Fountainhead::Log::GetClientLogger()->info(__VA_ARGS__)
#define FH_WARN(...)		::Fountainhead::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FH_ERROR(...)		::Fountainhead::Log::GetClientLogger()->error(__VA_ARGS__)
#define FH_FATAL(...)		::Fountainhead::Log::GetClientLogger()->fatal(__VA_ARGS__)