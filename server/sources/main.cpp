/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** main.cpp
*/

/* Created the 07/11/2019 at 18:05 by julian.frabel@epitech.eu */

#include <csignal>
#include <iostream>
#include <memory>
#include "logger/DefaultLogger.hpp"
#include "logger/StandardLogger.hpp"
#include "network/INetworkManager.hpp"
#include "network/asio/AsioNetworkManager.hpp"

namespace {
    volatile std::sig_atomic_t gSignalStatus;
}

void signalHandler(int s)
{
    std::cout << "Caught signal " << s << std::endl;
    gSignalStatus = s;
}

int main()
{
    std::cout << "Setting up signal handler..." << std::endl;
    std::signal(SIGINT, signalHandler);
    std::cout << "Signal handler set!" << std::endl;

    std::cout << "Loading default logger..." << std::endl;
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>());
    std::cout << "Default logger loaded!" << std::endl;

    std::cout << "Creating manager..." << std::endl;
    std::unique_ptr<b12software::network::INetworkManager> manager = std::make_unique<b12software::network::asio::AsioNetworkManager>();
    std::cout << "Manager created!" << std::endl;
    std::cout << "Starting manager..." << std::endl;
    manager->start();
    std::cout << "Manager started" << std::endl;

    std::cout << "Creating udp socket..." << std::endl;
    auto udpSocket = manager->createNewUdpSocket();
    udpSocket.lock()->bind(54321);
    std::cout << "Udp socket created!" << std::endl;

    std::cout << "Starting app" << std::endl;

    while (gSignalStatus == 0) {
        if (udpSocket.lock()->hasPendingDatagrams()) {
            std::cout << "Got datagram:" << std::endl;
            auto dg = udpSocket.lock()->receive();
            std::cout << "Host: " << dg.getHostInfos().host << ":" << dg.getHostInfos().port << std::endl;
            std::cout << "Message[" << dg.getDatagramSize() << "]: " << reinterpret_cast<const char *>(dg.getData()) << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }

    std::cout << "Shutting down gracefully" << std::endl;
    return 0;
}