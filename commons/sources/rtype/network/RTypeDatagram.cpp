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
        T_308_ROOM_FULL
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
    std::memcpy(reinterpret_cast<void *>(reinterpret_cast<intptr_t>(buff.get()) + sizeof(type)), &username[0], std::min(maxUsernameSize, username.size()));

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
        std::memcpy(reinterpret_cast<void *>(wPtr), &room.name[0], std::min(room.name.size(), maxRoomNameSize));
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
    std::memcpy(reinterpret_cast<void *>(wPtr), &room.name[0], std::min(room.name.size(), maxRoomNameSize));
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
    std::memcpy(reinterpret_cast<void *>(wPtr), &room.name[0], std::min(room.name.size(), maxRoomNameSize));
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
        std::memcpy(reinterpret_cast<void *>(wPtr), &user[0], std::min(maxUsernameSize, user.size()));
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
