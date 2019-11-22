/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Configuration.cpp
*/

/* Created the 22/11/2019 at 15:05 by julian.frabel@epitech.eu */

#include <iostream>
#include "Configuration.hpp"

rtype::Configuration::Configuration(int nbArgs, char * const *args)
    : _binaryName(args[0]), _help(false), _port(54321), _errors()
{
    int optionIdx = 0;
    while (true) {
        int c = ::getopt_long(nbArgs, args, "hp:", longOptions, &optionIdx);
        if (c == -1)
            break;
        switch (c) {
        case 'h': _help = true;
            break;
        case 'p':
            try {
                _port = std::stoi(std::string(optarg));
            } catch (std::invalid_argument &e) {
                _port = 0;
                _errors.push_back(std::string("Invalid port: ") + e.what());
            } catch (std::out_of_range &e) {
                _port = 0;
                _errors.push_back(std::string("Invalid port: ") + e.what());
            }
            break;
        case '?': _errors.emplace_back("Missing argument");
            break;
        default: _errors.push_back(std::string("Unknown code ") + std::to_string(c));
            break;
        }
    }
    while (optind < nbArgs) {
        _errors.push_back(std::string("non-option argument element ") + args[optind++] + " is invalid");
    }
}

bool rtype::Configuration::shouldDisplayHelp() const
{
    return _help;
}

unsigned short rtype::Configuration::getPort() const
{
    return _port;
}

void rtype::Configuration::displayHelp(bool onError) const
{
    auto &stream = onError ? std::cerr : std::cout;
    stream << "HELP " << _binaryName << std::endl;
    stream << _binaryName << " [-h|--help] [-p|--port PORT]" << std::endl << std::endl;
    stream << "-h, --help: Print this help and exit" << std::endl;
    stream << "-p PORT, --port=PORT: Use PORT as the port for this server" << std::endl;
}

bool rtype::Configuration::hasError() const
{
    return !_errors.empty();
}

void rtype::Configuration::displayErrors() const
{
    for (auto &error : _errors) {
        std::cerr << error << std::endl;
    }
}
