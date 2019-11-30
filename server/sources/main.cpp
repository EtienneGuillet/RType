/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** main.cpp
*/

/* Created the 07/11/2019 at 18:05 by julian.frabel@epitech.eu */

#include <csignal>
#include <thread>
#include <memory>
#include "config/Configuration.hpp"
#include "exception/B12SoftwareException.hpp"
#include "logger/DefaultLogger.hpp"
#include "logger/StandardLogger.hpp"
#include "RTypeServer.hpp"

volatile std::sig_atomic_t gSignalStatus;

namespace {
    void signalHandler(int s)
    {
        gSignalStatus = s;
    }
}

void runGame(std::string);
void runMain(const rtype::Configuration &config)
{
    if (config.isDebug()) {
        runGame(config.getLibsFolder());
        return;
    }
    auto server = std::make_unique<rtype::RTypeServer>(config.getPort(), config.getLibsFolder());

    while (gSignalStatus == 0) {
        server->run();
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
}

int main(int ac, char **av)
{
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));
    std::signal(SIGINT, signalHandler);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Logger and signal handler set");

    rtype::Configuration config(ac, av);
    if (config.hasError()) {
        config.displayErrors();
        config.displayHelp(true);
        return 84;
    } else if (config.shouldDisplayHelp()) {
        config.displayHelp();
        return 0;
    }

    try {
        runMain(config);
    } catch (b12software::exception::B12SoftwareException &e) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelFatal, e.what());
        return 84;
    } catch (std::exception &e) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelFatal, e.what());
        return 84;
    } catch (...) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelFatal, "An unknown error occurred.");
        return 84;
    }

    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Exit gracefully");
    return 0;
}