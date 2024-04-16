#pragma once

#include "Fountainhead/Core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>//����spdlog���������������Ա����ǿ�����־�Զ�������

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

//������־�궨��
#define FH_CORE_TRACE(...)	::Fountainhead::Log::GetCoreLogger()->trace(__VA_ARGS__)//__VA_ARGS__�����еı�������ת����ʵ�ʲ���
#define FH_CORE_INFO(...)	::Fountainhead::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FH_CORE_WARN(...)	::Fountainhead::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FH_CORE_ERROR(...)	::Fountainhead::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FH_CORE_FATAL(...)	::Fountainhead::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//�ͻ�����־�궨��
#define FH_TRACE(...)		::Fountainhead::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FH_INFO(...)		::Fountainhead::Log::GetClientLogger()->info(__VA_ARGS__)
#define FH_WARN(...)		::Fountainhead::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FH_ERROR(...)		::Fountainhead::Log::GetClientLogger()->error(__VA_ARGS__)
#define FH_FATAL(...)		::Fountainhead::Log::GetClientLogger()->fatal(__VA_ARGS__)