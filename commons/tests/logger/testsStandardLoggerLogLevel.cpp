/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** testsStandardLoggerLogLevel.cpp
*/

/* Created the 16/11/2019 at 13:55 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "logger/StandardLogger.hpp"

static void init()
{
    cr_redirect_stderr();
}

static void fini()
{}

Test(standardlogger_log_level, default_log_level,
     .timeout=10,
     .description="Assert that a standard logger is on log level error by default",
     .init=init,
     .fini=fini
)
{
    b12software::logger::StandardLogger logger;
    cr_assert_eq(logger.getLogLevel(), b12software::logger::LogLevelError);
}

Test(standardlogger_log_level, ctor_log_level,
     .timeout=10,
     .description="Assert that a standard logger is on log level passed in the ctor by default",
     .init=init,
     .fini=fini
)
{
    b12software::logger::StandardLogger logger(b12software::logger::LogLevelDebug);
    cr_assert_eq(logger.getLogLevel(), b12software::logger::LogLevelDebug);
}

Test(standardlogger_log_level, set_log_level,
     .timeout=10,
     .description="Assert that a standard logger is on log level set",
     .init=init,
     .fini=fini
)
{
    b12software::logger::StandardLogger logger;
    logger.setLogLevel(b12software::logger::LogLevelDebug);
    cr_assert_eq(logger.getLogLevel(), b12software::logger::LogLevelDebug);
}

Test(standardlogger_log_level, cpy_ctor,
     .timeout=10,
     .description="Assert that a standard logger is on the same log level as the logger copied",
     .init=init,
     .fini=fini
)
{
    b12software::logger::StandardLogger logger;
    logger.setLogLevel(b12software::logger::LogLevelDebug);
    b12software::logger::StandardLogger logger2(logger);
    cr_assert_eq(logger2.getLogLevel(), b12software::logger::LogLevelDebug);
}

Test(standardlogger_log_level, assignment,
     .timeout=10,
     .description="Assert that a standard logger is on the same log level as the logger assigned",
     .init=init,
     .fini=fini
)
{
    b12software::logger::StandardLogger logger;
    logger.setLogLevel(b12software::logger::LogLevelDebug);
    b12software::logger::StandardLogger logger2 = logger;
    cr_assert_eq(logger2.getLogLevel(), b12software::logger::LogLevelDebug);
}