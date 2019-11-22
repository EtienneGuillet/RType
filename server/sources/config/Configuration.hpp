/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Configuration.hpp
*/

/* Created the 22/11/2019 at 15:05 by julian.frabel@epitech.eu */

#ifndef R_TYPE_CONFIGURATION_HPP
#define R_TYPE_CONFIGURATION_HPP

#include <string>
#include <vector>
#include <getopt.h>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class Configuration
     * @brief A class used to configure the project
     */
    class Configuration {
    public:
        /*!
         * @brief ctor
         * @param nbArgs number of arguments
         * @param args arguments
         */
        Configuration(int nbArgs, char * const *args);
        /*!
         * @brief cpy ctor
         * @param other the configuration to copy
         */
        Configuration(const Configuration &other) = default;

        /*!
         * @brief dtor
         */
        ~Configuration() = default;

        /*!
         * @brief Assignment operator
         * @param rhs The object to assign to
         * @return *this
         */
        Configuration &operator=(const Configuration &rhs) = default;

    public:
        /*!
         * @brief Get if the user required help
         * @return true if --help or -h was added to command line
         */
        bool shouldDisplayHelp() const;

        /*!
         * @brief Get the port to open the server on
         * @return the port to open the server on
         */
        unsigned short getPort() const;

        /*!
         * @brief display the help on the standard output
         * @param onError should use the error output instead of standard
         */
        void displayHelp(bool onError = false) const;

        /*!
         * @brief Return if an invalid argument was provided
         * @return true if an error occurred false otherwise
         */
        bool hasError() const;

        /*!
         * @brief display error messages on the standard error output
         */
        void displayErrors() const;

    private:
        static constexpr struct option longOptions[] = {
            {"help", no_argument, 0, 'h'},
            {"port", required_argument, 0, 'p'},
        };

    private:
        std::string _binaryName; /*!< The name of this binary */
        bool _help; /*!< Should the program display help */
        unsigned short _port; /*!< The port this program should start on */
        std::vector<std::string> _errors; /*!< Unknown parameters */
    };
}

#endif //R_TYPE_CONFIGURATION_HPP
