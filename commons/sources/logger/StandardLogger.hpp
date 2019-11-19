/*
** EPITECH PROJECT, 2019
** B12Software
** File description:
** StandardLogger.hpp
*/

/* Created the 18/09/2019 at 14:34 by julian.frabel@epitech.eu */

#ifndef B12SOFTWARE_STANDARDLOGGER_HPP
#define B12SOFTWARE_STANDARDLOGGER_HPP

#include "logger/ILogger.hpp"

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
         * @class StandardLogger
         * @brief A logger that output on the standard error output
         */
        class StandardLogger : public ILogger {
        public:
            /*!
             * @brief ctor
             * @param defaultLevel The default log level of the logger
             */
            explicit StandardLogger(LogLevel defaultLevel = LogLevelError);
            /*!
             * @brief dtor
             */
            ~StandardLogger() override = default;

            /*!
             * @brief Cpy ctor
             * @param other the logger to copy
             */
            StandardLogger(const StandardLogger &other) = default;

            /*!
             * @brief Assignment operator
             * @param rhs the standard logger to assign to
             * @return *this
             */
            StandardLogger &operator=(const StandardLogger &rhs) = default;

            void setLogLevel(LogLevel level) override;
            [[nodiscard]] LogLevel getLogLevel() const override;
            void log(LogLevel messageLevel, const std::string &message) override;

        private:
            LogLevel _currentLevel; /*!< Current log level on this logger */
        };
    }
}

#endif //B12SOFTWARE_STANDARDLOGGER_HPP
