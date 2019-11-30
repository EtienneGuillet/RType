/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Configuration.cpp
*/

/* Created the 22/11/2019 at 15:05 by julian.frabel@epitech.eu */

#include <iostream>
#include <sys/stat.h>
#include "Configuration.hpp"

rtype::Configuration::Configuration(int nbArgs, char * const *args)
    : _binaryName(args[0]), _libsFolder("./server"), _help(false), _port(54321), _errors(), _debug(false)
{
#ifdef __linux__
    int optionIdx = 0;
    while (true) {
        int c = ::getopt_long(nbArgs, args, "hpl:", longOptions, &optionIdx);
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
        case 'l': _libsFolder = optarg;
            break;
        case 'D': _debug = true;
            break;
        default: _errors.push_back(std::string("Unknown code ") + std::to_string(c));
            break;
        }
    }
    while (optind < nbArgs) {
        _errors.push_back(std::string("non-option argument element ") + args[optind++] + " is invalid");
    }
#else
	bool nextShouldBePort = false;
    bool nextShouldBeLibsFolder = false;

	for (int i = 1; i < nbArgs; i++) {
		std::string strArg(args[i]);
		if (strArg == "-h" || strArg == "--help") {
			_help = true;
		} else if (strArg == "-p" || strArg == "--port") {
			nextShouldBePort = true;
		} else if (nextShouldBePort) {
			try {
				_port = std::stoi(strArg);
			}
			catch (std::invalid_argument &e) {
				_port = 0;
				_errors.push_back(std::string("Invalid port: ") + e.what());
			}
			catch (std::out_of_range &e) {
				_port = 0;
				_errors.push_back(std::string("Invalid port: ") + e.what());
			}
			nextShouldBePort = false;
		} else if (strArg == "-l" || strArg == "--lib") {
		    nextShouldBeLibsFolder = true;
		} else if (nextShouldBeLibsFolder) {
		    _libsFolder = strArg;
		} else {
			_errors.push_back("Unknown argument " + strArg);
		}
	}
#endif
    struct stat info;

    if (stat(_libsFolder.c_str(), &info) != 0) {
        _errors.push_back("Cannot access " + _libsFolder);
    } else if(!(info.st_mode & S_IFDIR)) {
        _errors.push_back(_libsFolder + " is not a directory");
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
    stream << _binaryName << " [-h|--help] [-p|--port PORT] [-l|--libs FOLDER]" << std::endl << std::endl;
    stream << "-h, --help: Print this help and exit" << std::endl;
    stream << "-p PORT, --port=PORT: Use PORT as the port for this server" << std::endl;
    stream << "-l FOLDER, --libs=FOLDER: Use PORT as the folder containing entities and systems" << std::endl;
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

const std::string & rtype::Configuration::getLibsFolder() const {
    return _libsFolder;
}

bool rtype::Configuration::isDebug() const {
    return _debug;
}
