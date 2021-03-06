#pragma once
#ifndef INC_SAMPLOG_LOGGER_H
#define INC_SAMPLOG_LOGGER_H

#include "LogLevel.h"
#include "DebugInfo.h"
#include <stddef.h>

//NOTE: Passing "-fvisibility=hidden" as a compiler option to GCC is advised!
#if defined _WIN32 || defined __CYGWIN__
# ifdef __GNUC__
#  define DLL_PUBLIC __attribute__ ((dllimport))
# else
#  define DLL_PUBLIC __declspec(dllimport)
# endif
#else
# if __GNUC__ >= 4
#  define DLL_PUBLIC __attribute__ ((visibility ("default")))
# else
#  define DLL_PUBLIC
# endif
#endif


extern "C" DLL_PUBLIC void samplog_Init();
extern "C" DLL_PUBLIC void samplog_Exit();
extern "C" DLL_PUBLIC bool samplog_LogMessage(
	const char *module, samplog_LogLevel level, const char *msg,
	const samplog_AmxFuncCallInfo *call_info = NULL);


#ifdef __cplusplus

#include <string>

namespace samplog
{
	inline void Init()
	{
		samplog_Init();
	}
	inline void Exit()
	{
		samplog_Exit();
	}
	inline bool LogMessage(
		const char *module, LogLevel level, const char *msg,
		const AmxFuncCallInfo *call_info = nullptr)
	{
		return samplog_LogMessage(module, level, msg, call_info);
	}
	
	class CLogger
	{
	public:
		explicit CLogger(std::string modulename) :
			m_Module(std::move(modulename)),
			m_LogLevel(static_cast<LogLevel>(LogLevel::ERROR | LogLevel::WARNING))
		{ }
		~CLogger() = default;
		CLogger(CLogger const &rhs) = delete;
		CLogger& operator=(CLogger const &rhs) = delete;

		CLogger(CLogger &&other) = delete;
		CLogger& operator=(CLogger &&other) = delete;

	public:
		inline void SetLogLevel(LogLevel log_level)
		{
			m_LogLevel = log_level;
		}
		inline bool IsLogLevel(LogLevel log_level) const
		{
			return (m_LogLevel & log_level) == log_level;
		}

		inline bool Log(LogLevel level, const char *msg,
			const AmxFuncCallInfo &call_info)
		{
			if (!IsLogLevel(level))
				return false;

			return samplog::LogMessage(m_Module.c_str(), level, msg, &call_info);
		}

		inline bool Log(LogLevel level, const char *msg)
		{
			if (!IsLogLevel(level))
				return false;

			return samplog::LogMessage(m_Module.c_str(), level, msg, nullptr);
		}

	protected:
		std::string m_Module;

	private:
		LogLevel m_LogLevel;

	};

	typedef CLogger Logger_t;

}

#endif /* __cplusplus */

#undef DLL_PUBLIC

#endif /* INC_SAMPLOG_LOGGER_H */
