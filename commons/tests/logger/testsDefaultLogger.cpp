/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** testsDefaultLogger.cpp
*/

/* Created the 16/11/2019 at 14:12 by julian.frabel@epitech.eu */


#include <thread>
#include <string>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "logger/DefaultLogger.hpp"
#include "logger/StandardLogger.hpp"

static void init()
{
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));
    cr_redirect_stderr();
}

static void fini()
{
    b12software::logger::DefaultLogger::ClearDefautLogger();
}

Test(defaultlogger_log, display_log,
     .timeout=10,
     .description="Assert that a default logger based on standard logger call log function",
     .init=init,
     .fini=fini
)
{
    std::stringstream expected;
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "debug");
    expected << "[DEBUG][" << std::this_thread::get_id() << "]debug" << std::endl;
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelInfo, "info");
    expected << "[INFO][" << std::this_thread::get_id() << "]info" << std::endl;
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelWarn, "warn");
    expected << "[WARN][" << std::this_thread::get_id() << "]warn" << std::endl;
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "error");
    expected << "[ERROR][" << std::this_thread::get_id() << "]error" << std::endl;
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelFatal, "fatal");
    expected << "[FATAL][" << std::this_thread::get_id() << "]fatal" << std::endl;
    cr_assert_stderr_eq_str(expected.str().c_str());
}

Test(defaultlogger_log, set_log_level,
     .timeout=10,
     .description="Assert that a default logger based on standard logger call set and get log level function",
     .init=init,
     .fini=fini
)
{
    cr_assert_eq(b12software::logger::DefaultLogger::GetLogLevel(), b12software::logger::LogLevelDebug);
    b12software::logger::DefaultLogger::SetLogLevel(b12software::logger::LogLevelError);
    cr_assert_eq(b12software::logger::DefaultLogger::GetLogLevel(), b12software::logger::LogLevelError);
}

Test(defaultlogger_log, no_logger,
     .timeout=10,
     .description="Assert that a default logger without logger does not crash",
     .init=init,
     .fini=fini
)
{
    b12software::logger::DefaultLogger::ClearDefautLogger();
    cr_assert_eq(b12software::logger::DefaultLogger::GetLogLevel(), b12software::logger::LogLevelNone);
    b12software::logger::DefaultLogger::SetLogLevel(b12software::logger::LogLevelError);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "debug");
}