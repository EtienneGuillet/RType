/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** testsStandardLoggerLog.cpp
*/

/* Created the 16/11/2019 at 14:02 by julian.frabel@epitech.eu */

#include <thread>
#include <string>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "logger/StandardLogger.hpp"

static void init()
{
    cr_redirect_stderr();
}

static void fini()
{}

Test(standardlogger_log, display_log_level_debug,
     .timeout=10,
     .description="Assert that a standard logger on debug level display all log messages",
     .init=init,
     .fini=fini
)
{
    std::stringstream expected;
    b12software::logger::StandardLogger logger(b12software::logger::LogLevelDebug);
    logger.log(b12software::logger::LogLevelDebug, "debug");
    expected << "[DEBUG][" << std::this_thread::get_id() << "]debug" << std::endl;
    logger.log(b12software::logger::LogLevelInfo, "info");
    expected << "[INFO][" << std::this_thread::get_id() << "]info" << std::endl;
    logger.log(b12software::logger::LogLevelWarn, "warn");
    expected << "[WARN][" << std::this_thread::get_id() << "]warn" << std::endl;
    logger.log(b12software::logger::LogLevelError, "error");
    expected << "[ERROR][" << std::this_thread::get_id() << "]error" << std::endl;
    logger.log(b12software::logger::LogLevelFatal, "fatal");
    expected << "[FATAL][" << std::this_thread::get_id() << "]fatal" << std::endl;
    cr_assert_stderr_eq_str(expected.str().c_str());
}

Test(standardlogger_log, display_log_level_info,
     .timeout=10,
     .description="Assert that a standard logger on info level display log messages info and above",
     .init=init,
     .fini=fini
)
{
    std::stringstream expected;
    b12software::logger::StandardLogger logger(b12software::logger::LogLevelInfo);
    logger.log(b12software::logger::LogLevelDebug, "debug");
    logger.log(b12software::logger::LogLevelInfo, "info");
    expected << "[INFO][" << std::this_thread::get_id() << "]info" << std::endl;
    logger.log(b12software::logger::LogLevelWarn, "warn");
    expected << "[WARN][" << std::this_thread::get_id() << "]warn" << std::endl;
    logger.log(b12software::logger::LogLevelError, "error");
    expected << "[ERROR][" << std::this_thread::get_id() << "]error" << std::endl;
    logger.log(b12software::logger::LogLevelFatal, "fatal");
    expected << "[FATAL][" << std::this_thread::get_id() << "]fatal" << std::endl;
    cr_assert_stderr_eq_str(expected.str().c_str());
}

Test(standardlogger_log, display_log_level_warn,
     .timeout=10,
     .description="Assert that a standard logger on warn display log messages warn and above",
     .init=init,
     .fini=fini
)
{
    std::stringstream expected;
    b12software::logger::StandardLogger logger(b12software::logger::LogLevelWarn);
    logger.log(b12software::logger::LogLevelDebug, "debug");
    logger.log(b12software::logger::LogLevelInfo, "info");
    logger.log(b12software::logger::LogLevelWarn, "warn");
    expected << "[WARN][" << std::this_thread::get_id() << "]warn" << std::endl;
    logger.log(b12software::logger::LogLevelError, "error");
    expected << "[ERROR][" << std::this_thread::get_id() << "]error" << std::endl;
    logger.log(b12software::logger::LogLevelFatal, "fatal");
    expected << "[FATAL][" << std::this_thread::get_id() << "]fatal" << std::endl;
    cr_assert_stderr_eq_str(expected.str().c_str());
}

Test(standardlogger_log, display_log_level_error,
     .timeout=10,
     .description="Assert that a standard logger on error display log messages error and above",
     .init=init,
     .fini=fini
)
{
    std::stringstream expected;
    b12software::logger::StandardLogger logger(b12software::logger::LogLevelError);
    logger.log(b12software::logger::LogLevelDebug, "debug");
    logger.log(b12software::logger::LogLevelInfo, "info");
    logger.log(b12software::logger::LogLevelWarn, "warn");
    logger.log(b12software::logger::LogLevelError, "error");
    expected << "[ERROR][" << std::this_thread::get_id() << "]error" << std::endl;
    logger.log(b12software::logger::LogLevelFatal, "fatal");
    expected << "[FATAL][" << std::this_thread::get_id() << "]fatal" << std::endl;
    cr_assert_stderr_eq_str(expected.str().c_str());
}

Test(standardlogger_log, display_log_level_fatal,
     .timeout=10,
     .description="Assert that a standard logger on fatal display log messages fatal",
     .init=init,
     .fini=fini
)
{
    std::stringstream expected;
    b12software::logger::StandardLogger logger(b12software::logger::LogLevelFatal);
    logger.log(b12software::logger::LogLevelDebug, "debug");
    logger.log(b12software::logger::LogLevelInfo, "info");
    logger.log(b12software::logger::LogLevelWarn, "warn");
    logger.log(b12software::logger::LogLevelError, "error");
    logger.log(b12software::logger::LogLevelFatal, "fatal");
    expected << "[FATAL][" << std::this_thread::get_id() << "]fatal" << std::endl;
    cr_assert_stderr_eq_str(expected.str().c_str());
}

Test(standardlogger_log, display_log_level_none,
     .timeout=10,
     .description="Assert that a standard logger on none display no log messages",
     .init=init,
     .fini=fini,
     .disabled=true
)
{
    std::stringstream expected;
    b12software::logger::StandardLogger logger(b12software::logger::LogLevelNone);
    logger.log(b12software::logger::LogLevelDebug, "debug");
    logger.log(b12software::logger::LogLevelInfo, "info");
    logger.log(b12software::logger::LogLevelWarn, "warn");
    logger.log(b12software::logger::LogLevelError, "error");
    logger.log(b12software::logger::LogLevelFatal, "fatal");
    cr_assert_stderr_eq_str(expected.str().c_str());
}