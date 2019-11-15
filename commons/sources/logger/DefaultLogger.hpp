/*
** EPITECH PROJECT, 2019
** B12Software
** File description:
** DefaultLogger.hpp
*/

/* Created the 18/09/2019 at 15:38 by julian.frabel@epitech.eu */

#ifndef B12SOFTWARE_DEFAULTLOGGER_HPP
#define B12SOFTWARE_DEFAULTLOGGER_HPP

#include <memory>
#include "ILogger.hpp"

/*!
 * @namespace b12software
 * @brief Main namespace for all b12 software
 */
namespace b12software {

    /*!
     * @namespace b12software::logger
     * @brief Main namespace for loggers
     */
    namespace logger {

        /*!
         * @class DefaultLogger
         * @brief A static class used to set and use a default logger
         */
        class DefaultLogger {
        private:
            /*!
             * @brief You should not be able to instantiate a DefaultLogger class
             */
            DefaultLogger() = default;
        public:
            /*!
             * @brief Cpy ctor
             * @param other The object to copy
             */
            DefaultLogger(const DefaultLogger &other) = delete;

            /*!
             * @brief Assignment operator
             * @param rhs The other default logger to assign to
             * @return *this
             */
            DefaultLogger &operator=(const DefaultLogger &rhs) = delete;

            /*!
             * @brief Set the logger to use as default
             * @param logger The logger to use
             */
            static void SetDefaultLogger(const std::shared_ptr<ILogger> &logger);

            /*!
             * @brief Get the current logger
             * @return The current used logger
             */
            static const std::shared_ptr<ILogger> &GetCurrentLogger();

            /*!
             * @brief Clear the current default logger
             */
            static void ClearDefautLogger();

            /*!
             * @brief Set the current log level to the current logger
             * @param level The level to set to
             *
             * If no logger is set will do nothing
             */
            static void SetLogLevel(LogLevel level);

            /*!
             * @brief Get the current log level to the current logger
             * @return The level the current log level is at
             *
             * If no logger is set will return LogLevelNone
             */
            static LogLevel GetLogLevel();

            /*!
             * @brief Log to the current logger
             * @param messageLevel The level of the message
             * @param message The message to log
             *
             * If no logger is set will do nothing
             */
            static void Log(LogLevel messageLevel, const std::string &message);

        private:
            static std::shared_ptr<ILogger> currentLogger; /*!< The current logger to use */
        };
    }
}

#endif //B12SOFTWARE_DEFAULTLOGGER_HPP
