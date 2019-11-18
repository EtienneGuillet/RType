/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** testsRTypeDatagramInitPackets.cpp
*/

/* Created the 18/11/2019 at 20:15 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>
#include "rtype/network/RTypeDatagram.hpp"

static void init()
{}

static void fini()
{}

static bool compareArrays(const unsigned char *a, const unsigned char *b, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

Test(initPacket, T_100_CONNECT,
    .timeout=10,
    .description="Test the serialisation of the T_100_CONNECT packet",
    .init=init,
    .fini=fini
)
{
    rtype::network::RTypeDatagram datagram1;
    datagram1.init100ConnectDatagram("short");
    const unsigned char expectedShort[] = {0x0, 0x64, 's', 'h', 'o', 'r', 't', '\0', '\0', '\0', '\0', '\0'};
    cr_assert_eq(datagram1.getDatagramSize(), 12);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram1.getData()), 12));
    cr_assert_eq(datagram1.getType(), rtype::network::T_100_CONNECT);

    rtype::network::RTypeDatagram datagram2;
    datagram2.init100ConnectDatagram("0123456789");
    const unsigned char expectedSameSize[] = {0x0, 0x64, '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    cr_assert_eq(datagram2.getDatagramSize(), 12);
    cr_assert(compareArrays(expectedSameSize, static_cast<const unsigned char *>(datagram2.getData()), 12));
    cr_assert_eq(datagram2.getType(), rtype::network::T_100_CONNECT);

    rtype::network::RTypeDatagram datagram3;
    datagram3.init100ConnectDatagram("0123456789abcdef");
    const unsigned char expectedBigger[] = {0x0, 0x64, '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    cr_assert_eq(datagram3.getDatagramSize(), 12);
    cr_assert(compareArrays(expectedBigger, static_cast<const unsigned char *>(datagram3.getData()), 12));
    cr_assert_eq(datagram3.getType(), rtype::network::T_100_CONNECT);
}

Test(initPacket, T_101_CONNECTED,
     .timeout=10,
     .description="Test the serialisation of the T_101_CONNECTED packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_101_CONNECTED);
    const unsigned char expectedShort[] = {0x0, 0x65};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_101_CONNECTED);
}

Test(initPacket, T_102_PING,
     .timeout=10,
     .description="Test the serialisation of the T_102_PING packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_102_PING);
    const unsigned char expectedShort[] = {0x0, 0x66};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_102_PING);
}

Test(initPacket, T_103_PONG,
     .timeout=10,
     .description="Test the serialisation of the T_103_PONG packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_103_PONG);
    const unsigned char expectedShort[] = {0x0, 0x67};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_103_PONG);
}

Test(initPacket, T_104_DISCONNECT,
     .timeout=10,
     .description="Test the serialisation of the T_104_DISCONNECT packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_104_DISCONNECT);
    const unsigned char expectedShort[] = {0x0, 0x68};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_104_DISCONNECT);
}

Test(initPacket, T_105_DISCONNECTED,
     .timeout=10,
     .description="Test the serialisation of the T_105_DISCONNECTED packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_105_DISCONNECTED);
    const unsigned char expectedShort[] = {0x0, 0x69};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_105_DISCONNECTED);
}

Test(initPacket, T_111_ROOM_LIST,
     .timeout=10,
     .description="Test the serialisation of the T_111_ROOM_LIST packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram1;
    std::vector<rtype::network::RTypeDatagramRoom> vec = {
        {"room1", 4, 2, false, ""},
        {"room2", 3, 1, true, "toto"}
    };
    datagram1.init111RoomListDatagram(vec);
    const unsigned char expected1[] = {0x0, 0x6f,
                                       0x0, 0x0, 0x0, 0x2,
                                       'r', 'o', 'o', 'm', '1', '\0', '\0', '\0', '\0', '\0', 0x0, 0x2, 0x4,
                                       'r', 'o', 'o', 'm', '2', '\0', '\0', '\0', '\0', '\0', 0x1, 0x1, 0x3};
    cr_assert_eq(datagram1.getDatagramSize(), 32);
    cr_assert(compareArrays(expected1, static_cast<const unsigned char *>(datagram1.getData()), 32));
    cr_assert_eq(datagram1.getType(), rtype::network::T_111_ROOM_LIST);

    rtype::network::RTypeDatagram datagram2;
    std::vector<rtype::network::RTypeDatagramRoom> vec2 = {};
    datagram2.init111RoomListDatagram(vec2);
    const unsigned char expected2[] = {0x0, 0x6f,
                                       0x0, 0x0, 0x0, 0x0};
    cr_assert_eq(datagram2.getDatagramSize(), 6);
    cr_assert(compareArrays(expected2, static_cast<const unsigned char *>(datagram2.getData()), 6));
    cr_assert_eq(datagram2.getType(), rtype::network::T_111_ROOM_LIST);
}

Test(initPacket, T_112_CREATE_ROOM,
     .timeout=10,
     .description="Test the serialisation of the T_112_CREATE_ROOM packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram1;
    rtype::network::RTypeDatagramRoom room = {"room1", 3, 1, true, "toto"};
    datagram1.init112CreateRoomDatagram(room);
    const unsigned char expected1[] = {0x0, 0x70,
                                       'r', 'o', 'o', 'm', '1', '\0', '\0', '\0', '\0', '\0',
                                       0x3,
                                       0x0, 0x0, 0x0, 0x4,
                                       't', 'o', 't', 'o'};
    cr_assert_eq(datagram1.getDatagramSize(), 21);
    cr_assert(compareArrays(expected1, static_cast<const unsigned char *>(datagram1.getData()), 21));
    cr_assert_eq(datagram1.getType(), rtype::network::T_112_CREATE_ROOM);

    rtype::network::RTypeDatagram datagram2;
    rtype::network::RTypeDatagramRoom room2 = {"room2", 3, 1, false, ""};
    datagram2.init112CreateRoomDatagram(room2);
    const unsigned char expected2[] = {0x0, 0x70,
                                       'r', 'o', 'o', 'm', '2', '\0', '\0', '\0', '\0', '\0',
                                       0x3,
                                       0x0, 0x0, 0x0, 0x0};
    cr_assert_eq(datagram2.getDatagramSize(), 17);
    cr_assert(compareArrays(expected2, static_cast<const unsigned char *>(datagram2.getData()), 17));
    cr_assert_eq(datagram2.getType(), rtype::network::T_112_CREATE_ROOM);
}

Test(initPacket, T_113_ROOM_CREATED,
     .timeout=10,
     .description="Test the serialisation of the T_113_ROOM_CREATED packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_113_ROOM_CREATED);
    const unsigned char expectedShort[] = {0x0, 0x71};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_113_ROOM_CREATED);
}

Test(initPacket, T_114_QUIT_ROOM,
     .timeout=10,
     .description="Test the serialisation of the T_114_QUIT_ROOM packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_114_QUIT_ROOM);
    const unsigned char expectedShort[] = {0x0, 0x72};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_114_QUIT_ROOM);
}

Test(initPacket, T_115_ROOM_QUITTED,
     .timeout=10,
     .description="Test the serialisation of the T_115_ROOM_QUITTED packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_115_ROOM_QUITTED);
    const unsigned char expectedShort[] = {0x0, 0x73};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_115_ROOM_QUITTED);
}

Test(initPacket, T_116_JOIN_ROOM,
     .timeout=10,
     .description="Test the serialisation of the T_116_JOIN_ROOM packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram1;
    rtype::network::RTypeDatagramRoom room = {"room1", 3, 1, true, "toto"};
    datagram1.init116JoinRoomDatagram(room);
    const unsigned char expected1[] = {0x0, 0x74,
                                       'r', 'o', 'o', 'm', '1', '\0', '\0', '\0', '\0', '\0',
                                       0x0, 0x0, 0x0, 0x4,
                                       't', 'o', 't', 'o'};
    cr_assert_eq(datagram1.getDatagramSize(), 20);
    cr_assert(compareArrays(expected1, static_cast<const unsigned char *>(datagram1.getData()), 20));
    cr_assert_eq(datagram1.getType(), rtype::network::T_116_JOIN_ROOM);

    rtype::network::RTypeDatagram datagram2;
    rtype::network::RTypeDatagramRoom room2 = {"room2", 3, 1, false, ""};
    datagram2.init116JoinRoomDatagram(room2);
    const unsigned char expected2[] = {0x0, 0x74,
                                      'r', 'o', 'o', 'm', '2', '\0', '\0', '\0', '\0', '\0',
                                      0x0, 0x0, 0x0, 0x0};
    cr_assert_eq(datagram2.getDatagramSize(), 16);
    cr_assert(compareArrays(expected2, static_cast<const unsigned char *>(datagram2.getData()), 16));
    cr_assert_eq(datagram2.getType(), rtype::network::T_116_JOIN_ROOM);
}

Test(initPacket, T_117_ROOM_JOINED,
     .timeout=10,
     .description="Test the serialisation of the T_117_ROOM_JOINED packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.init117RoomJoinedDatagram({"user1", "0123456789abcde", "azertyuiop"});
    const unsigned char expectedShort[] = {0x0, 0x75,
                                           0x3,
                                           'u', 's', 'e', 'r', '1', '\0', '\0', '\0', '\0', '\0',
                                           '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                           'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
    cr_assert_eq(datagram.getDatagramSize(), 33);
    cr_assert(compareArrays(expectedShort, static_cast<const unsigned char *>(datagram.getData()), 33));
    cr_assert_eq(datagram.getType(), rtype::network::T_117_ROOM_JOINED);
}

Test(initPacket, T_200_ACTION,
     .timeout=10,
     .description="Test the serialisation of the T_200_ACTION packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramAction action = {true, false, false, true, true};
    datagram.init200ActionDatagram(action);
    const unsigned char expected[] = {0x0, 0xc8, 0x1, 0x0, 0x0, 0x1, 0x1};
    cr_assert_eq(datagram.getDatagramSize(), 7);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 7));
    cr_assert_eq(datagram.getType(), rtype::network::T_200_ACTION);
}

Test(initPacket, T_210_DISPLAY,
     .timeout=10,
     .description="Test the serialisation of the T_210_DISPLAY packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramDisplay disp = {234522244, {3, 2, 1}, {4, 5}, {6, 7}, 8};
    datagram.init210DisplayDatagram(disp);
    const unsigned char expected[] = {0x0, 0xd2,
                                      0x0, 0x0, 0x0, 0x0, 0x0d, 0xfa, 0x86, 0x84,
                                      0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x1,
                                      0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x5,
                                      0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x7,
                                      0x0, 0x0, 0x0, 0x8};
    cr_assert_eq(datagram.getDatagramSize(), 42);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 42));
    cr_assert_eq(datagram.getType(), rtype::network::T_210_DISPLAY);
}

Test(initPacket, T_220_LIVING,
     .timeout=10,
     .description="Test the serialisation of the T_220_LIVING packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramLiving life = {234522244, 10};
    datagram.init220LivingDatagram(life);
    const unsigned char expected[] = {0x0, 0xdc,
                                      0x0, 0x0, 0x0, 0x0, 0x0d, 0xfa, 0x86, 0x84,
                                      0x0, 0x0, 0x0, 0x0a};
    cr_assert_eq(datagram.getDatagramSize(), 14);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 14));
    cr_assert_eq(datagram.getType(), rtype::network::T_220_LIVING);
}

Test(initPacket, T_230_CHARGE,
     .timeout=10,
     .description="Test the serialisation of the T_230_CHARGE packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.init230ChargeDatagram(89);
    const unsigned char expected[] = {0x0, 0xe6, 89};
    cr_assert_eq(datagram.getDatagramSize(), 3);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 3));
    cr_assert_eq(datagram.getType(), rtype::network::T_230_CHARGE);
}

Test(initPacket, T_240_SCORE,
     .timeout=10,
     .description="Test the serialisation of the T_240_SCORE packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramScore score = {400, 14502, 12333, 82863};
    datagram.init240ScoreDatagram(score);
    const unsigned char expected[] = {0x0, 0xf0,
                                      0x0, 0x0, 0x1, 0x90,
                                      0x0, 0x0, 0x38, 0xa6,
                                      0x0, 0x0, 0x30, 0x2d,
                                      0x0, 0x1, 0x43, 0xaf};
    cr_assert_eq(datagram.getDatagramSize(), 18);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 18));
    cr_assert_eq(datagram.getType(), rtype::network::T_240_SCORE);
}

Test(initPacket, T_250_END_GAME,
     .timeout=10,
     .description="Test the serialisation of the T_250_END_GAME packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramScore score = {400, 14502, 12333, 82863};
    datagram.init250EndGameDatagram(score);
    const unsigned char expected[] = {0x0, 0xfa,
                                      0x0, 0x0, 0x1, 0x90,
                                      0x0, 0x0, 0x38, 0xa6,
                                      0x0, 0x0, 0x30, 0x2d,
                                      0x0, 0x1, 0x43, 0xaf};
    cr_assert_eq(datagram.getDatagramSize(), 18);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 18));
    cr_assert_eq(datagram.getType(), rtype::network::T_250_END_GAME);
}

Test(initPacket, T_260_GAME_ENDED,
     .timeout=10,
     .description="Test the serialisation of the T_260_GAME_ENDED packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_260_GAME_ENDED);
    const unsigned char expected[] = {0x1, 0x4};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_260_GAME_ENDED);
}

Test(initPacket, T_300_UNKNOWN_PACKET,
     .timeout=10,
     .description="Test the serialisation of the T_300_UNKNOWN_PACKET packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_300_UNKNOWN_PACKET);
    const unsigned char expected[] = {0x1, 0x2c};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_300_UNKNOWN_PACKET);
}

Test(initPacket, T_301_INVALID_PACKET,
     .timeout=10,
     .description="Test the serialisation of the T_301_INVALID_PACKET packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_301_INVALID_PACKET);
    const unsigned char expected[] = {0x1, 0x2d};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_301_INVALID_PACKET);
}

Test(initPacket, T_302_INVALID_PARAM,
     .timeout=10,
     .description="Test the serialisation of the T_302_INVALID_PARAM packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_302_INVALID_PARAM);
    const unsigned char expected[] = {0x1, 0x2e};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_302_INVALID_PARAM);
}

Test(initPacket, T_303_USERNAME_ALREADY_USED,
     .timeout=10,
     .description="Test the serialisation of the T_303_USERNAME_ALREADY_USED packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_303_USERNAME_ALREADY_USED);
    const unsigned char expected[] = {0x1, 0x2f};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_303_USERNAME_ALREADY_USED);
}

Test(initPacket, T_304_ROOM_NAME_ALREADY_USED,
     .timeout=10,
     .description="Test the serialisation of the T_304_ROOM_NAME_ALREADY_USED packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_304_ROOM_NAME_ALREADY_USED);
    const unsigned char expected[] = {0x1, 0x30};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_304_ROOM_NAME_ALREADY_USED);
}

Test(initPacket, T_305_NOT_IN_A_ROOM,
     .timeout=10,
     .description="Test the serialisation of the T_305_NOT_IN_A_ROOM packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_305_NOT_IN_A_ROOM);
    const unsigned char expected[] = {0x1, 0x31};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_305_NOT_IN_A_ROOM);
}

Test(initPacket, T_306_UNKNOWN_ROOM,
     .timeout=10,
     .description="Test the serialisation of the T_306_UNKNOWN_ROOM packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_306_UNKNOWN_ROOM);
    const unsigned char expected[] = {0x1, 0x32};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_306_UNKNOWN_ROOM);
}

Test(initPacket, T_307_INVALID_PASSWORD,
     .timeout=10,
     .description="Test the serialisation of the T_307_INVALID_PASSWORD packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_307_INVALID_PASSWORD);
    const unsigned char expected[] = {0x1, 0x33};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_307_INVALID_PASSWORD);
}

Test(initPacket, T_308_ROOM_FULL,
     .timeout=10,
     .description="Test the serialisation of the T_308_ROOM_FULL packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.initSingleOpCodeDatagram(rtype::network::T_308_ROOM_FULL);
    const unsigned char expected[] = {0x1, 0x34};
    cr_assert_eq(datagram.getDatagramSize(), 2);
    cr_assert(compareArrays(expected, static_cast<const unsigned char *>(datagram.getData()), 2));
    cr_assert_eq(datagram.getType(), rtype::network::T_308_ROOM_FULL);
}