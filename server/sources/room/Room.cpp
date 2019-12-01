/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Room.cpp
*/

/* Created the 26/11/2019 at 05:12 by julian.frabel@epitech.eu */

#include <algorithm>
#include <rtype/game/RTypeEntityType.hpp>
#include <rtype/LibLoader/LibLoader.hpp>
#include <ecs/IECS/ECS.hpp>
#include <systems/NetworkSyncSystem/NetworkSyncSystem.hpp>
#include <entities/PlayerEntity/PlayerEntityApi.hpp>
#include <entities/PlayerEntity/PlayerEntity.hpp>
#include <systems/NetworkSyncSystem/NetworkSyncSystemApi.hpp>
#include <components/Transform/TransformComponent.hpp>
#include <components/server/networkIdentity/NetworkIdentityComponent.hpp>
#include <components/server/collider/ColliderComponent.hpp>
#include "Room.hpp"
#include "logger/DefaultLogger.hpp"

rtype::Room::Room(const std::string &libsFolder)
    : _name(""),
      _capacity(0),
      _slotUsed(0),
      _hasPassword(false),
      _password(""),
      _gameRunning(false),
      _clients(),
      _shouldGameBeRunning(false),
      _gameInfos(),
      _clientPlayerMap(),
      _threadRunning(false),
      _thread(),
      _libsFolder(libsFolder)
{

}

rtype::Room::~Room()
{
    //this should never happen but just in case
    if (_thread && _thread->joinable()) {
        _threadRunning = false;
        _thread->join();
    }
}

const std::string &rtype::Room::getName() const
{
    return _name;
}

void rtype::Room::setName(const std::string &name)
{
    _name = name;
}

unsigned char rtype::Room::getCapacity() const
{
    return _capacity;
}

void rtype::Room::setCapacity(unsigned char capacity)
{
    if (capacity > 4)
        return;
    _capacity = capacity;
}

unsigned char rtype::Room::getSlotUsed() const
{
    return _slotUsed;
}

void rtype::Room::setSlotUsed(unsigned char slotUsed)
{
    if (slotUsed > 4)
        return;
    _slotUsed = slotUsed;
}

bool rtype::Room::hasPassword() const
{
    return _hasPassword;
}

void rtype::Room::setHasPassword(bool hasPassword)
{
    _hasPassword = hasPassword;
}

const std::string &rtype::Room::getPassword() const
{
    return _password;
}

void rtype::Room::setPassword(const std::string &password)
{
    _password = password;
}

bool rtype::Room::isGameRunning() const
{
    return _gameRunning;
}

void rtype::Room::setGameRunning(bool gameRunning)
{
    _gameRunning = gameRunning;
}

void rtype::Room::addClient(rtype::Client &client)
{
    if (_gameRunning)
        return;
    auto it = std::find_if(_clients.begin(), _clients.end(), [client](const auto &elem) {
        return elem.get() == client;
    });
    if (it == _clients.end()) {
        _clients.push_back(client);
        _slotUsed++;
    }
}

void rtype::Room::removeClient(const rtype::Client &client)
{
    _clients.erase(std::remove_if(_clients.begin(), _clients.end(), [this, client](const std::reference_wrapper<Client> &elem) {
        if (elem.get() == client) {
            _slotUsed--;
            if (_gameRunning) {
                _gameInfos.getPlayer(_clientPlayerMap[client.getUsername()]).setIsUsed(false);
                _clientPlayerMap.erase(client.getUsername());
            }
            return true;
        }
        return false;
    }));
}

void rtype::Room::applyToClients(std::function<void(Client & )> func)
{
    for (auto &client : _clients) {
        func(client);
    }
}

void rtype::Room::startGame()
{
    if (_shouldGameBeRunning)
        return;
    _shouldGameBeRunning = true;
    _gameInfos.reset();
    _clientPlayerMap.clear();
    _gameInfos.setNbPlayers(_clients.size());
    int idx = 0;
    for (auto it = _clients.begin(); it != _clients.end(); ++it, idx++) {
        _clientPlayerMap[it->get().getUsername()] = idx;
        _gameInfos.getPlayer(idx).setIsUsed(true);
        rtype::network::RTypeDatagram dg(it->get().getHost());
        dg.initSingleOpCodeDatagram(rtype::network::T_270_GAME_STARTING);
        it->get().setDatagram(network::T_270_GAME_STARTING, dg);
    }
}

void rtype::Room::syncGame(std::weak_ptr<b12software::network::udp::IUdpSocket> socket)
{
    if (_shouldGameBeRunning && !_gameRunning) {
        bool allClientsRdy = true;
        for (auto &client : _clients) {
            if (client.get().getClientState() != CS_IN_GAME)
                allClientsRdy = false;
        }
        if (allClientsRdy) {
            _threadRunning = true;
            _thread = std::make_unique<std::thread>(rtype::Room::gameThreadFunc, std::ref(_shouldGameBeRunning), std::ref(_threadRunning), std::ref(_gameInfos), _libsFolder);
            _gameRunning = true;
        }
    } else if (_shouldGameBeRunning && _gameRunning) {
        syncGameOnNetwork(socket);
        if (_clients.empty() || !_threadRunning) {
            endGame();
        }
    } else if (!_shouldGameBeRunning && _gameRunning) {
        bool allClientsRdy = true;
        for (auto &client : _clients) {
            if (client.get().getClientState() != CS_IN_ROOM)
                allClientsRdy = false;
        }
        if (allClientsRdy) {
            _threadRunning = false;
            if (_thread && _thread->joinable()) {
                _thread->join();
            }
            _gameRunning = false;
        }
    }
}

void rtype::Room::setUsernameInputs(const std::string &username, const rtype::network::RTypeDatagramAction &inputs)
{
    if (!_gameRunning)
        return;
    auto it = _clientPlayerMap.find(username);
    if (it != _clientPlayerMap.end()) {
        auto idx = it->second;
        auto &player = _gameInfos.getPlayer(idx);
        player.setIsShooting(inputs.shot);
        player.setIsMovingUp(inputs.up);
        player.setIsMovingDown(inputs.down);
        player.setIsMovingLeft(inputs.left);
        player.setIsMovingRight(inputs.right);
    }
}

void rtype::Room::syncGameOnNetwork(const std::weak_ptr<b12software::network::udp::IUdpSocket>& socket)
{
    constexpr std::chrono::milliseconds timeBetweenDisplays(100);
    constexpr std::chrono::milliseconds timeBetweenLiving(100);
    constexpr std::chrono::milliseconds timeBetweenCharges(100);
    constexpr std::chrono::milliseconds timeBetweenScores(250);
    auto now = Client::Clock::now();
    for (auto &client : _clients) {
        bool syncDisplay = false;
        if (now - client.get().getClock(rtype::network::T_210_DISPLAY) >= timeBetweenDisplays) {
            syncDisplay = true;
            client.get().setClock(rtype::network::T_210_DISPLAY, now);
        }
        bool syncLiving = false;
        if (now - client.get().getClock(rtype::network::T_220_LIVING) >= timeBetweenLiving) {
            syncLiving = true;
            client.get().setClock(rtype::network::T_220_LIVING, now);
        }
        if (now - client.get().getClock(rtype::network::T_230_CHARGE) >= timeBetweenCharges) {
            syncCharge(client.get(), socket);
            client.get().setClock(rtype::network::T_230_CHARGE, now);
        }
        if (now - client.get().getClock(rtype::network::T_240_SCORE) >= timeBetweenScores) {
            syncScore(client.get(), socket);
            client.get().setClock(rtype::network::T_240_SCORE, now);
        }
        if (syncDisplay || syncLiving) {
            syncDisplayLiving(client.get(), socket, syncLiving, syncDisplay);
        }
    }
}

void rtype::Room::syncDisplayLiving(rtype::Client &client,
                                    const std::weak_ptr<b12software::network::udp::IUdpSocket>& socket, bool living,
                                    bool display)
{
    rtype::network::RTypeDatagram dg(client.getHost());
    rtype::network::RTypeDatagramDisplay displayData;
    rtype::network::RTypeDatagramLiving livingData;
    auto lockedSocket = socket.lock();
    if (!lockedSocket)
        return;
    for (int i = 0; i < 4; i++) {
        auto &player = _gameInfos.getPlayer(i);
        if (!player.isUsed())
            continue;
        auto id = player.getId();
        if (display && displayData.type != rtype::ET_UNKNOWN) {
            displayData.entityId = id;
            displayData.type = player.getType();
            auto position = player.getPosition();
            auto rotation = player.getRotation();
            auto scale = player.getScale();
            displayData.position = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z)};
            displayData.rotation = {static_cast<int>(rotation.x), static_cast<int>(rotation.y)};
            displayData.scale = {static_cast<int>(scale.x), static_cast<int>(scale.y)};
            dg.init210DisplayDatagram(displayData);
            lockedSocket->send(dg);
        }
        if (living) {
            livingData.entityId = id;
            livingData.life = player.getHp();
            dg.init220LivingDatagram(livingData);
            lockedSocket->send(dg);
        }
    }
    auto &entities = _gameInfos.getEntities();
    std::scoped_lock lock(entities);
    for (auto &entity : entities) {
        auto id = entity.getId();
        if (display && displayData.type != rtype::ET_UNKNOWN) {
            displayData.entityId = id;
            displayData.type = entity.getType();
            auto position = entity.getPosition();
            auto rotation = entity.getRotation();
            auto scale = entity.getScale();
            displayData.position = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(position.z)};
            displayData.rotation = {static_cast<int>(rotation.x), static_cast<int>(rotation.y)};
            displayData.scale = {static_cast<int>(scale.x), static_cast<int>(scale.y)};
            dg.init210DisplayDatagram(displayData);
            lockedSocket->send(dg);
        }
        if (living) {
            livingData.entityId = id;
            livingData.life = entity.getHp();
            dg.init220LivingDatagram(livingData);
            lockedSocket->send(dg);
        }
    }
}

void rtype::Room::syncScore(rtype::Client &client, const std::weak_ptr<b12software::network::udp::IUdpSocket>& socket)
{
    rtype::network::RTypeDatagram dg(client.getHost());
    rtype::network::RTypeDatagramScore score;
    score.p1Score = _gameInfos.getPlayer(0).getScore();
    score.p2Score = _gameInfos.getPlayer(1).getScore();
    score.p3Score = _gameInfos.getPlayer(2).getScore();
    score.p4Score = _gameInfos.getPlayer(3).getScore();
    dg.init240ScoreDatagram(score);
    auto lockedSocket = socket.lock();
    if (lockedSocket) {
        lockedSocket->send(dg);
    }
}

void rtype::Room::syncCharge(rtype::Client &client, const std::weak_ptr<b12software::network::udp::IUdpSocket>& socket)
{
    auto it = _clientPlayerMap.find(client.getUsername());
    if (it == _clientPlayerMap.end())
        return;
    int idx = it->second;
    rtype::network::RTypeDatagram dg(client.getHost());
    dg.init230ChargeDatagram(_gameInfos.getPlayer(idx).getCharge());
    auto lockedSocket = socket.lock();
    if (lockedSocket) {
        lockedSocket->send(dg);
    }
}

void rtype::Room::endGame()
{
    if (!_shouldGameBeRunning)
        return;
    _shouldGameBeRunning = false;
    for (auto &_client : _clients) {
        rtype::network::RTypeDatagram dg(_client.get().getHost());
        rtype::network::RTypeDatagramScore scores;
        scores.p1Score = _gameInfos.getPlayer(0).getScore();
        scores.p2Score = _gameInfos.getPlayer(1).getScore();
        scores.p3Score = _gameInfos.getPlayer(2).getScore();
        scores.p4Score = _gameInfos.getPlayer(3).getScore();
        dg.init250EndGameDatagram(scores);
        _client.get().setDatagram(network::T_250_END_GAME, dg);
    }
    _gameInfos.reset();
    _clientPlayerMap.clear();
}

void rtype::Room::gameThreadFunc(const std::atomic_bool &shouldGameBeRunning, std::atomic_bool &threadRunning, GameInfos &infos, const std::string libsFolder)
{
    threadRunning = true;
    std::shared_ptr<ecs::IECS> ecs = std::make_shared<ecs::ECS>();
    auto world = ecs->createWorld();
    auto libLoader = rtype::LibLoader(ecs, world, libsFolder);
    auto start = std::chrono::system_clock::now();
    auto end = start;
    std::map<int, int> playersIdsMap;

    auto playerApi = std::make_shared<PlayerEntityAPI>();
    ecs->learnEntity(playerApi);

    for (int j = 0; j < infos.getNbPlayers(); ++j) {
        auto player = std::make_shared<PlayerEntity>(static_cast<rtype::RTypeEntityType>(j));
        auto transform = std::dynamic_pointer_cast<ecs::components::TransformComponent>(player->getComponent(ecs::components::TransformComponent::Version).lock());
        auto spawnPos = ((80 / infos.getNbPlayers()) * j) + 10;

        transform->setPosition(b12software::maths::Vector3D(10, spawnPos, 0));
        world->pushEntity(player);
        playersIdsMap[j] = player->getID();
        player->addComponent(std::make_shared<ecs::components::NetworkIdentityComponent>(player->getID()));
    }
    auto     networkApi = std::make_shared<systems::NetworkSyncSystemApi>();
    ecs->learnSystem(networkApi);
    auto system = std::dynamic_pointer_cast<systems::NetworkSyncSystem>(networkApi->createNewSystem());
    system->start();
    system->setGameInfosPtr(infos.getWeak());
    world->addSystem(system);

    while (shouldGameBeRunning && threadRunning) {
        end = std::chrono::system_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (deltaTime >= 10) {
            libLoader.checkForChanges();
            start = std::chrono::system_clock::now();
            world->tick(deltaTime);

            int used = 4;
            int alive = 4;
            for (int i = 0; i < 4; i++) {
                auto &player = infos.getPlayer(i);
                if (player.isUsed()) {
                    if (player.getHp() <= 0) {
                        alive--;
                    }
                } else {
                    alive--;
                    used--;
                }
            }
            if (used == 0 || alive == 0)
                break;
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    world = std::shared_ptr<ecs::IWorld>();
    ecs = std::unique_ptr<ecs::IECS>();
    threadRunning = false;
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Exit thread");
}

bool rtype::Room::shouldGameRun() const
{
    return _shouldGameBeRunning;
}
