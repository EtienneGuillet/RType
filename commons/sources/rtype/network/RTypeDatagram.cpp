/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagram.cpp
*/

/* Created the 18/11/2019 at 13:11 by julian.frabel@epitech.eu */

#include <algorithm>
#include <memory>
#include <cstring>
#include "RTypeDatagram.hpp"
#include "rtype/exceptions/DatagramErrorException.hpp"
#include "rtype/exceptions/DatagramMalformedException.hpp"

rtype::network::RTypeDatagram::RTypeDatagram()
    : Datagram()
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const rtype::network::RTypeDatagram &other)
    : Datagram(other)
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const rtype::network::RTypeDatagram::Datagram &other)
    : Datagram(other)
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const rtype::network::RTypeDatagram::HostInfos &destination)
    : Datagram(destination)
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const void *data, size_t size)
    : Datagram(data, size)
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const rtype::network::RTypeDatagram::HostInfos &destination,
                                             const void *data, size_t size)
    : Datagram(destination, data, size)
{

}

rtype::network::RTypeDatagram::~RTypeDatagram()
{

}

rtype::network::RTypeDatagram &rtype::network::RTypeDatagram::operator=(const rtype::network::RTypeDatagram &rhs)
{
    if (this == &rhs)
        return *this;
    return *this;
}

rtype::network::RTypeDatagram & rtype::network::RTypeDatagram::operator=(const rtype::network::RTypeDatagram::Datagram &rhs)
{
    if (this == &rhs)
        return *this;
    Datagram::operator=(rhs);
    return *this;
}

void rtype::network::RTypeDatagram::initSingleOpCodeDatagram(rtype::network::RTypeDatagramType type)
{
    std::vector<RTypeDatagramType> authorizedTypes = {
        T_101_CONNECTED,
        T_102_PING,
        T_103_PONG,
        T_104_DISCONNECT,
        T_105_DISCONNECTED,
        T_107_OK_CLIENT_DISCONNECTED,
        T_109_OK_NEW_CLIENT_CONNECTED,
        T_110_GET_ROOMS,
        T_113_ROOM_CREATED,
        T_114_QUIT_ROOM,
        T_115_ROOM_QUITTED,
        T_260_GAME_ENDED,
        T_300_UNKNOWN_PACKET,
        T_301_INVALID_PACKET,
        T_302_INVALID_PARAM,
        T_303_USERNAME_ALREADY_USED,
        T_304_ROOM_NAME_ALREADY_USED,
        T_305_NOT_IN_A_ROOM,
        T_306_UNKNOWN_ROOM,
        T_307_INVALID_PASSWORD,
        T_308_ROOM_FULL,
        T_309_OPERATION_NOT_PERMITTED,
    };
    if (std::find(authorizedTypes.begin(), authorizedTypes.end(), type) == authorizedTypes.end()) {
        throw exceptions::DatagramErrorException("Datagram " + std::to_string(type) + " is not a valid type in a single op code datagram", WHERE);
    }
    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type)]);
    auto wType = HTONS(type);
    std::memcpy(buff.get(), &wType, sizeof(type));

    this->setData(buff.get(), sizeof(type));
}

void rtype::network::RTypeDatagram::init100ConnectDatagram(const std::string &username)
{
    RTypeDatagramType type = T_100_CONNECT;
    constexpr size_t maxUsernameSize = 10;

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + maxUsernameSize]);
    std::memset(buff.get(), 0, sizeof(type) + maxUsernameSize);

    auto wType = HTONS(type);
    std::memcpy(buff.get(), &wType, sizeof(type));
    std::memcpy(reinterpret_cast<void *>(reinterpret_cast<intptr_t>(buff.get()) + sizeof(type)), &username[0], (std::min)(maxUsernameSize, username.size()));

    this->setData(buff.get(), sizeof(type) + maxUsernameSize);
}

void rtype::network::RTypeDatagram::init106ClientDisconnectedDatagram(const std::string &username)
{
    RTypeDatagramType type = T_106_CLIENT_DISCONNECTED;
    constexpr size_t maxUsernameSize = 10;

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + maxUsernameSize]);
    std::memset(buff.get(), 0, sizeof(type) + maxUsernameSize);

    auto wType = HTONS(type);
    std::memcpy(buff.get(), &wType, sizeof(type));
    std::memcpy(reinterpret_cast<void *>(reinterpret_cast<intptr_t>(buff.get()) + sizeof(type)), &username[0], (std::min)(maxUsernameSize, username.size()));

    this->setData(buff.get(), sizeof(type) + maxUsernameSize);
}

void rtype::network::RTypeDatagram::init108NewClientConnectedDatagram(const std::string &username)
{
    RTypeDatagramType type = T_108_NEW_CLIENT_CONNECTED;
    constexpr size_t maxUsernameSize = 10;

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + maxUsernameSize]);
    std::memset(buff.get(), 0, sizeof(type) + maxUsernameSize);

    auto wType = HTONS(type);
    std::memcpy(buff.get(), &wType, sizeof(type));
    std::memcpy(reinterpret_cast<void *>(reinterpret_cast<intptr_t>(buff.get()) + sizeof(type)), &username[0], (std::min)(maxUsernameSize, username.size()));

    this->setData(buff.get(), sizeof(type) + maxUsernameSize);
}

void rtype::network::RTypeDatagram::init111RoomListDatagram(const std::vector<RTypeDatagramRoom> &rooms)
{
    RTypeDatagramType type = T_111_ROOM_LIST;
    constexpr size_t maxRoomNameSize = 10;
    uint32_t nbRoom = rooms.size();
    size_t packetSize = sizeof(nbRoom) + (maxRoomNameSize + sizeof(char) + sizeof(RTypeDatagramRoom::slotUsed) + sizeof(RTypeDatagramRoom::capacity)) * nbRoom;

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    nbRoom = HTONL(nbRoom);
    std::memcpy(reinterpret_cast<void *>(wPtr), &nbRoom, sizeof(nbRoom));
    wPtr += sizeof(nbRoom);
    for (auto &room : rooms) {
        std::memcpy(reinterpret_cast<void *>(wPtr), &room.name[0], (std::min)(room.name.size(), maxRoomNameSize));
        wPtr += maxRoomNameSize;
        char hasPassword = room.hasPassword ? 1 : 0;
        std::memcpy(reinterpret_cast<void *>(wPtr), &hasPassword, sizeof(hasPassword));
        wPtr += sizeof(hasPassword);
        std::memcpy(reinterpret_cast<void *>(wPtr), &room.slotUsed, sizeof(room.slotUsed));
        wPtr += sizeof(room.slotUsed);
        std::memcpy(reinterpret_cast<void *>(wPtr), &room.capacity, sizeof(room.capacity));
        wPtr += sizeof(room.capacity);
    }

    this->setData(buff.get(), sizeof(type) + packetSize);
}

void rtype::network::RTypeDatagram::init112CreateRoomDatagram(const rtype::network::RTypeDatagramRoom &room)
{
    RTypeDatagramType type = T_112_CREATE_ROOM;
    constexpr size_t maxRoomNameSize = 10;
    uint32_t passwordSize = room.password.size();
    size_t packetSize = maxRoomNameSize + sizeof(RTypeDatagramRoom::capacity) + sizeof(passwordSize) + passwordSize;

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    std::memcpy(reinterpret_cast<void *>(wPtr), &room.name[0], (std::min)(room.name.size(), maxRoomNameSize));
    wPtr += maxRoomNameSize;
    std::memcpy(reinterpret_cast<void *>(wPtr), &room.capacity, sizeof(room.capacity));
    wPtr += sizeof(room.capacity);
    auto wPasswordSize = HTONL(passwordSize);
    std::memcpy(reinterpret_cast<void *>(wPtr), &wPasswordSize, sizeof(wPasswordSize));
    wPtr += sizeof(wPasswordSize);
    std::memcpy(reinterpret_cast<void *>(wPtr), &room.password[0], passwordSize);

    this->setData(buff.get(), sizeof(type) + packetSize);
}

void rtype::network::RTypeDatagram::init116JoinRoomDatagram(const rtype::network::RTypeDatagramRoom &room)
{
    RTypeDatagramType type = T_116_JOIN_ROOM;
    constexpr size_t maxRoomNameSize = 10;
    uint32_t passwordSize = room.password.size();
    size_t packetSize = maxRoomNameSize + sizeof(passwordSize) + passwordSize;

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    std::memcpy(reinterpret_cast<void *>(wPtr), &room.name[0], (std::min)(room.name.size(), maxRoomNameSize));
    wPtr += maxRoomNameSize;
    auto wPasswordSize = HTONL(passwordSize);
    std::memcpy(reinterpret_cast<void *>(wPtr), &wPasswordSize, sizeof(wPasswordSize));
    wPtr += sizeof(wPasswordSize);
    std::memcpy(reinterpret_cast<void *>(wPtr), &room.password[0], passwordSize);

    this->setData(buff.get(), sizeof(type) + packetSize);
}

void rtype::network::RTypeDatagram::init117RoomJoinedDatagram(const std::vector<std::string> &users)
{
    RTypeDatagramType type = T_117_ROOM_JOINED;
    constexpr size_t maxUsernameSize = 10;
    unsigned char nbUser = users.size();
    size_t packetSize = sizeof(nbUser) + maxUsernameSize * nbUser;

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    std::memcpy(reinterpret_cast<void *>(wPtr), &nbUser, sizeof(nbUser));
    wPtr += sizeof(nbUser);
    for (auto &user : users) {
        std::memcpy(reinterpret_cast<void *>(wPtr), &user[0], (std::min)(maxUsernameSize, user.size()));
        wPtr += maxUsernameSize;
    }

    this->setData(buff.get(), sizeof(type) + packetSize);
}

void rtype::network::RTypeDatagram::init200ActionDatagram(const rtype::network::RTypeDatagramAction &action)
{
    RTypeDatagramType type = T_200_ACTION;
    size_t packetSize = 5 * sizeof(bool);

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    std::memcpy(reinterpret_cast<void *>(wPtr), &action.shot, sizeof(action.shot));
    wPtr += sizeof(action.shot);
    std::memcpy(reinterpret_cast<void *>(wPtr), &action.up, sizeof(action.up));
    wPtr += sizeof(action.up);
    std::memcpy(reinterpret_cast<void *>(wPtr), &action.down, sizeof(action.down));
    wPtr += sizeof(action.down);
    std::memcpy(reinterpret_cast<void *>(wPtr), &action.left, sizeof(action.left));
    wPtr += sizeof(action.left);
    std::memcpy(reinterpret_cast<void *>(wPtr), &action.right, sizeof(action.right));

    this->setData(buff.get(), sizeof(type) + packetSize);
}

void rtype::network::RTypeDatagram::init210DisplayDatagram(const rtype::network::RTypeDatagramDisplay &entity)
{
    RTypeDatagramType type = T_210_DISPLAY;
    auto entityID = HTONLL(entity.entityId);
    auto xPos = HTONL(entity.position.x);
    auto yPos = HTONL(entity.position.y);
    auto zPos = HTONL(entity.position.z);
    auto xRot = HTONL(entity.rotation.x);
    auto yRot = HTONL(entity.rotation.y);
    auto xScale = HTONL(entity.scale.x);
    auto yScale = HTONL(entity.scale.y);
    auto entityType = HTONL(entity.type);
    size_t packetSize = sizeof(uint64_t) + 8 * sizeof(uint32_t);

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    std::memcpy(reinterpret_cast<void *>(wPtr), &entityID, sizeof(entityID));
    wPtr += sizeof(entityID);
    std::memcpy(reinterpret_cast<void *>(wPtr), &xPos, sizeof(xPos));
    wPtr += sizeof(xPos);
    std::memcpy(reinterpret_cast<void *>(wPtr), &yPos, sizeof(yPos));
    wPtr += sizeof(yPos);
    std::memcpy(reinterpret_cast<void *>(wPtr), &zPos, sizeof(zPos));
    wPtr += sizeof(zPos);
    std::memcpy(reinterpret_cast<void *>(wPtr), &xRot, sizeof(xRot));
    wPtr += sizeof(xRot);
    std::memcpy(reinterpret_cast<void *>(wPtr), &yRot, sizeof(yRot));
    wPtr += sizeof(yRot);
    std::memcpy(reinterpret_cast<void *>(wPtr), &xScale, sizeof(xScale));
    wPtr += sizeof(xScale);
    std::memcpy(reinterpret_cast<void *>(wPtr), &yScale, sizeof(yScale));
    wPtr += sizeof(yScale);
    std::memcpy(reinterpret_cast<void *>(wPtr), &entityType, sizeof(entityType));
    wPtr += sizeof(entityType);

    this->setData(buff.get(), sizeof(type) + packetSize);
}

void rtype::network::RTypeDatagram::init220LivingDatagram(const rtype::network::RTypeDatagramLiving &data)
{
    RTypeDatagramType type = T_220_LIVING;
    auto entityID = HTONLL(data.entityId);
    auto hp = HTONL(data.life);
    size_t packetSize = sizeof(entityID) + sizeof(hp);

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    std::memcpy(reinterpret_cast<void *>(wPtr), &entityID, sizeof(entityID));
    wPtr += sizeof(entityID);
    std::memcpy(reinterpret_cast<void *>(wPtr), &hp, sizeof(hp));
    wPtr += sizeof(hp);

    this->setData(buff.get(), sizeof(type) + packetSize);
}

void rtype::network::RTypeDatagram::init230ChargeDatagram(unsigned char charge)
{
    RTypeDatagramType type = T_230_CHARGE;
    size_t packetSize = sizeof(charge);

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    std::memcpy(reinterpret_cast<void *>(wPtr), &charge, sizeof(charge));
    wPtr += sizeof(charge);

    this->setData(buff.get(), sizeof(type) + packetSize);
}

void rtype::network::RTypeDatagram::init240ScoreDatagram(const rtype::network::RTypeDatagramScore &score)
{
    RTypeDatagramType type = T_240_SCORE;
    auto p1Score = HTONL(score.p1Score);
    auto p2Score = HTONL(score.p2Score);
    auto p3Score = HTONL(score.p3Score);
    auto p4Score = HTONL(score.p4Score);
    size_t packetSize = sizeof(p1Score) + sizeof(p2Score) + sizeof(p3Score) + sizeof(p4Score);

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    std::memcpy(reinterpret_cast<void *>(wPtr), &p1Score, sizeof(p1Score));
    wPtr += sizeof(p1Score);
    std::memcpy(reinterpret_cast<void *>(wPtr), &p2Score, sizeof(p2Score));
    wPtr += sizeof(p2Score);
    std::memcpy(reinterpret_cast<void *>(wPtr), &p3Score, sizeof(p3Score));
    wPtr += sizeof(p3Score);
    std::memcpy(reinterpret_cast<void *>(wPtr), &p4Score, sizeof(p4Score));
    wPtr += sizeof(p4Score);

    this->setData(buff.get(), sizeof(type) + packetSize);
}

void rtype::network::RTypeDatagram::init250EndGameDatagram(const rtype::network::RTypeDatagramScore &score)
{
    RTypeDatagramType type = T_250_END_GAME;
    auto p1Score = HTONL(score.p1Score);
    auto p2Score = HTONL(score.p2Score);
    auto p3Score = HTONL(score.p3Score);
    auto p4Score = HTONL(score.p4Score);
    size_t packetSize = sizeof(p1Score) + sizeof(p2Score) + sizeof(p3Score) + sizeof(p4Score);

    auto buff = std::unique_ptr<byte[]>(new byte[sizeof(type) + packetSize]);
    std::memset(buff.get(), 0, sizeof(type) + packetSize);

    auto wType = HTONS(type);
    intptr_t wPtr = reinterpret_cast<intptr_t>(buff.get());
    std::memcpy(reinterpret_cast<void *>(wPtr), &wType, sizeof(type));
    wPtr += sizeof(type);
    std::memcpy(reinterpret_cast<void *>(wPtr), &p1Score, sizeof(p1Score));
    wPtr += sizeof(p1Score);
    std::memcpy(reinterpret_cast<void *>(wPtr), &p2Score, sizeof(p2Score));
    wPtr += sizeof(p2Score);
    std::memcpy(reinterpret_cast<void *>(wPtr), &p3Score, sizeof(p3Score));
    wPtr += sizeof(p3Score);
    std::memcpy(reinterpret_cast<void *>(wPtr), &p4Score, sizeof(p4Score));
    wPtr += sizeof(p4Score);

    this->setData(buff.get(), sizeof(type) + packetSize);
}

unsigned short rtype::network::RTypeDatagram::getType() const
{
    if (getDatagramSize() < sizeof(RTypeDatagramType))
        return 0;
    return NTOHS(*static_cast<const unsigned short *>(getData()));
}

void rtype::network::RTypeDatagram::extract100ConnectDatagram(std::string &username)
{
    RTypeDatagramType type = T_100_CONNECT;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);
    if (getDatagramSize() != sizeof(type) + 10)
        throw exceptions::DatagramMalformedException("This T_100_CONNECT packet malformed", WHERE);
    auto wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    username = std::string(reinterpret_cast<const char *>(wPtr), strnlen(reinterpret_cast<const char *>(wPtr), 10));
}

void rtype::network::RTypeDatagram::extract106ClientDisconnectedDatagram(std::string &username)
{
    RTypeDatagramType type = T_106_CLIENT_DISCONNECTED;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);
    if (getDatagramSize() != sizeof(type) + 10)
        throw exceptions::DatagramMalformedException("This T_106_CLIENT_DISCONNECTED packet malformed", WHERE);
    auto wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    username = std::string(reinterpret_cast<const char *>(wPtr), strnlen(reinterpret_cast<const char *>(wPtr), 10));
}

void rtype::network::RTypeDatagram::extract108NewClientConnectedDatagram(std::string &username)
{
    RTypeDatagramType type = T_108_NEW_CLIENT_CONNECTED;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);
    if (getDatagramSize() != sizeof(type) + 10)
        throw exceptions::DatagramMalformedException("This T_108_NEW_CLIENT_CONNECTED packet malformed", WHERE);
    auto wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    username = std::string(reinterpret_cast<const char *>(wPtr), strnlen(reinterpret_cast<const char *>(wPtr), 10));
}

void rtype::network::RTypeDatagram::extract111RoomListDatagram(std::vector<RTypeDatagramRoom> &rooms)
{
    RTypeDatagramType type = T_111_ROOM_LIST;
    constexpr size_t maxRoomNameSize = 10;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);

    rooms.clear();

    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    if (getDatagramSize() < sizeof(type) + sizeof(uint32_t))
        throw exceptions::DatagramMalformedException("This T_111_ROOM_LIST packet malformed", WHERE);
    auto nbRoom = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(nbRoom);
    if (getDatagramSize() != sizeof(type) + sizeof(uint32_t) + nbRoom * (maxRoomNameSize + sizeof(bool) + sizeof(const unsigned char) + sizeof(const unsigned char)))
        throw exceptions::DatagramMalformedException("This T_111_ROOM_LIST packet malformed", WHERE);
    for (uint32_t i = 0; i < nbRoom; ++i) {
        std::string name(reinterpret_cast<const char *>(wPtr), strnlen(reinterpret_cast<const char *>(wPtr), maxRoomNameSize));
        wPtr += maxRoomNameSize;
        bool hasPassword = *reinterpret_cast<const bool *>(wPtr);
        wPtr += sizeof(hasPassword);
        unsigned char slotUsed = *reinterpret_cast<const unsigned char *>(wPtr);
        wPtr += sizeof(slotUsed);
        unsigned char capacity = *reinterpret_cast<const unsigned char *>(wPtr);
        wPtr += sizeof(capacity);
        rooms.push_back({name, capacity, slotUsed, hasPassword, ""});
    }
}

void rtype::network::RTypeDatagram::extract112CreateRoomDatagram(rtype::network::RTypeDatagramRoom &room)
{
    RTypeDatagramType type = T_112_CREATE_ROOM;
    constexpr size_t maxRoomNameSize = 10;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);

    if (getDatagramSize() < sizeof(type) + maxRoomNameSize + sizeof(unsigned char) + sizeof(uint32_t))
        throw exceptions::DatagramMalformedException("This T_112_CREATE_ROOM packet malformed", WHERE);
    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    std::string name(reinterpret_cast<const char *>(wPtr), strnlen(reinterpret_cast<const char *>(wPtr), maxRoomNameSize));
    wPtr += maxRoomNameSize;
    unsigned char capacity = *reinterpret_cast<const unsigned char *>(wPtr);
    wPtr += sizeof(capacity);
    uint32_t passwordSize = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(passwordSize);
    if (getDatagramSize() != sizeof(type) + maxRoomNameSize + sizeof(unsigned char) + sizeof(uint32_t) + passwordSize)
        throw exceptions::DatagramMalformedException("This T_112_CREATE_ROOM packet malformed", WHERE);
    std::string password(reinterpret_cast<const char *>(wPtr), passwordSize);
    wPtr += passwordSize;
    room = {name, capacity, 0, passwordSize != 0, password};
}

void rtype::network::RTypeDatagram::extract116JoinRoomDatagram(rtype::network::RTypeDatagramRoom &room)
{
    RTypeDatagramType type = T_116_JOIN_ROOM;
    constexpr size_t maxRoomNameSize = 10;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);

    if (getDatagramSize() < sizeof(type) + maxRoomNameSize + sizeof(uint32_t))
        throw exceptions::DatagramMalformedException("This T_116_JOIN_ROOM packet malformed", WHERE);
    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    std::string name(reinterpret_cast<const char *>(wPtr), strnlen(reinterpret_cast<const char *>(wPtr), maxRoomNameSize));
    wPtr += maxRoomNameSize;
    uint32_t passwordSize = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(passwordSize);
    if (getDatagramSize() != sizeof(type) + maxRoomNameSize + sizeof(uint32_t) + passwordSize)
        throw exceptions::DatagramMalformedException("This T_116_JOIN_ROOM packet malformed", WHERE);
    std::string password(reinterpret_cast<const char *>(wPtr), passwordSize);
    wPtr += passwordSize;
    room = {name, 0, 0, passwordSize != 0, password};
}

void rtype::network::RTypeDatagram::extract117RoomJoinedDatagram(std::vector<std::string> &users)
{
    RTypeDatagramType type = T_117_ROOM_JOINED;
    constexpr size_t maxUsernameSize = 10;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);

    users.clear();

    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    if (getDatagramSize() < sizeof(type) + sizeof(unsigned char))
        throw exceptions::DatagramMalformedException("This T_117_ROOM_JOINED packet malformed", WHERE);
    unsigned char nbUser = *reinterpret_cast<const unsigned char *>(wPtr);
    wPtr += sizeof(nbUser);
    if (getDatagramSize() != sizeof(type) + sizeof(unsigned char) + (maxUsernameSize * nbUser))
        throw exceptions::DatagramMalformedException("This T_117_ROOM_JOINED packet malformed", WHERE);
    for (unsigned char i = 0; i < nbUser; ++i) {
        std::string name(reinterpret_cast<const char *>(wPtr), strnlen(reinterpret_cast<const char *>(wPtr), maxUsernameSize));
        wPtr += maxUsernameSize;
        users.push_back(name);
    }
}

void rtype::network::RTypeDatagram::extract200ActionDatagram(rtype::network::RTypeDatagramAction &action)
{
    RTypeDatagramType type = T_200_ACTION;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);
    if (getDatagramSize() != sizeof(type) + sizeof(bool) * 5)
        throw exceptions::DatagramMalformedException("This T_200_ACTION packet malformed", WHERE);
    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    action.shot = *reinterpret_cast<const bool *>(wPtr);
    wPtr += sizeof(action.shot);
    action.up = *reinterpret_cast<const bool *>(wPtr);
    wPtr += sizeof(action.up);
    action.down = *reinterpret_cast<const bool *>(wPtr);
    wPtr += sizeof(action.down);
    action.left = *reinterpret_cast<const bool *>(wPtr);
    wPtr += sizeof(action.left);
    action.right = *reinterpret_cast<const bool *>(wPtr);
    wPtr += sizeof(action.right);
}

void rtype::network::RTypeDatagram::extract210DisplayDatagram(rtype::network::RTypeDatagramDisplay &entity)
{
    RTypeDatagramType type = T_210_DISPLAY;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);

    if (getDatagramSize() != 42)
        throw exceptions::DatagramMalformedException("This T_210_DISPLAY packet malformed", WHERE);
    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    entity.entityId = NTOHLL(*reinterpret_cast<const uint64_t *>(wPtr));
    wPtr += sizeof(entity.entityId);
    entity.position.x = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(entity.position.x);
    entity.position.y = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(entity.position.y);
    entity.position.z = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(entity.position.z);
    entity.rotation.x = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(entity.rotation.x);
    entity.rotation.y = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(entity.rotation.y);
    entity.scale.x = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(entity.scale.x);
    entity.scale.y = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(entity.scale.y);
    entity.type = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
}

void rtype::network::RTypeDatagram::extract220LivingDatagram(rtype::network::RTypeDatagramLiving &data)
{
    RTypeDatagramType type = T_220_LIVING;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);

    if (getDatagramSize() != 14)
        throw exceptions::DatagramMalformedException("This T_220_LIVING packet malformed", WHERE);
    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    data.entityId = NTOHLL(*reinterpret_cast<const uint64_t *>(wPtr));
    wPtr += sizeof(data.entityId);
    data.life = NTOHL(*reinterpret_cast<const uint64_t *>(wPtr));
}

void rtype::network::RTypeDatagram::extract230ChargeDatagram(unsigned char &charge)
{
    RTypeDatagramType type = T_230_CHARGE;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);

    if (getDatagramSize() != 3)
        throw exceptions::DatagramMalformedException("This T_230_CHARGE packet malformed", WHERE);
    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    charge = *reinterpret_cast<const unsigned char *>(wPtr);
}

void rtype::network::RTypeDatagram::extract240ScoreDatagram(rtype::network::RTypeDatagramScore &score)
{
    RTypeDatagramType type = T_240_SCORE;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);

    if (getDatagramSize() != 18)
        throw exceptions::DatagramMalformedException("This T_240_SCORE packet malformed", WHERE);
    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    score.p1Score = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(score.p1Score);
    score.p2Score = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(score.p2Score);
    score.p3Score = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(score.p3Score);
    score.p4Score = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
}

void rtype::network::RTypeDatagram::extract250EndGameDatagram(rtype::network::RTypeDatagramScore &score)
{
    RTypeDatagramType type = T_250_END_GAME;

    if (getType() != type)
        throw exceptions::DatagramErrorException("This packet is not a " + std::to_string(type) + " packet", WHERE);

    if (getDatagramSize() != 18)
        throw exceptions::DatagramMalformedException("This T_250_END_GAME packet malformed", WHERE);
    intptr_t wPtr = reinterpret_cast<intptr_t>(getData()) + sizeof(type);
    score.p1Score = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(score.p1Score);
    score.p2Score = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(score.p2Score);
    score.p3Score = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
    wPtr += sizeof(score.p3Score);
    score.p4Score = NTOHL(*reinterpret_cast<const uint32_t *>(wPtr));
}
