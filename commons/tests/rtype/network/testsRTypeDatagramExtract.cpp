/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** testsRTypeDatagramExtract.cpp
*/

/* Created the 18/11/2019 at 22:18 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>
#include "rtype/network/RTypeDatagram.hpp"

static void init()
{}

static void fini()
{}

Test(extractPacket, T_100_CONNECT,
     .timeout=10,
     .description="Test the deserialisation of the T_100_CONNECT packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram1;
    std::string expected1 = "short";
    datagram1.init100ConnectDatagram(expected1);
    std::string name1;
    datagram1.extract100ConnectDatagram(name1);
    cr_assert(name1 == expected1);

    rtype::network::RTypeDatagram datagram2;
    datagram2.init100ConnectDatagram("0123456789");
    std::string name2;
    datagram2.extract100ConnectDatagram(name2);
    cr_assert(name2 == "0123456789");

    rtype::network::RTypeDatagram datagram3;
    datagram3.init100ConnectDatagram("0123456789abcdef");
    std::string name3;
    datagram3.extract100ConnectDatagram(name3);
    cr_assert(name3 == "0123456789");
}

Test(extractPacket, T_111_ROOM_LIST,
     .timeout=10,
     .description="Test the deserialisation of the T_111_ROOM_LIST packet",
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
    std::vector<rtype::network::RTypeDatagramRoom> vec2;
    datagram1.extract111RoomListDatagram(vec2);
    cr_assert_eq(vec.size(), vec2.size());
    for (size_t i = 0; i < vec2.size(); ++i) {
        cr_assert(vec[i].name == vec2[i].name);
        cr_assert_eq(vec2[i].capacity, vec[i].capacity);
        cr_assert_eq(vec2[i].slotUsed, vec[i].slotUsed);
        cr_assert_eq(vec2[i].hasPassword, vec[i].hasPassword);
        cr_assert(vec2[i].password == "");
    }

    rtype::network::RTypeDatagram datagram2;
    std::vector<rtype::network::RTypeDatagramRoom> vec3 = {};
    datagram2.init111RoomListDatagram(vec3);
    std::vector<rtype::network::RTypeDatagramRoom> vec4;
    datagram2.extract111RoomListDatagram(vec4);
    cr_assert_eq(vec3.size(), vec4.size());
}

Test(extractPacket, T_112_CREATE_ROOM,
     .timeout=10,
     .description="Test the deserialisation of the T_112_CREATE_ROOM packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram1;
    rtype::network::RTypeDatagramRoom room = {"room1", 3, 1, true, "toto"};
    datagram1.init112CreateRoomDatagram(room);
    rtype::network::RTypeDatagramRoom roomExpected;
    datagram1.extract112CreateRoomDatagram(roomExpected);
    cr_assert(room.name == roomExpected.name);
    cr_assert_eq(roomExpected.capacity, room.capacity);
    cr_assert_eq(roomExpected.hasPassword, room.hasPassword);
    cr_assert(room.password == roomExpected.password);

    rtype::network::RTypeDatagram datagram2;
    rtype::network::RTypeDatagramRoom room2 = {"room2", 3, 1, false, ""};
    datagram2.init112CreateRoomDatagram(room2);
    rtype::network::RTypeDatagramRoom roomExpected2;
    datagram2.extract112CreateRoomDatagram(roomExpected2);
    cr_assert(room2.name == roomExpected2.name);
    cr_assert_eq(roomExpected2.capacity, room2.capacity);
    cr_assert_eq(roomExpected2.hasPassword, room2.hasPassword);
    cr_assert(room2.password == roomExpected2.password);

}

Test(extractPacket, T_116_JOIN_ROOM,
     .timeout=10,
     .description="Test the deserialisation of the T_116_JOIN_ROOM packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram1;
    rtype::network::RTypeDatagramRoom room = {"room1", 3, 1, true, "toto"};
    datagram1.init116JoinRoomDatagram(room);
    rtype::network::RTypeDatagramRoom roomExpected;
    datagram1.extract116JoinRoomDatagram(roomExpected);
    cr_assert(room.name == roomExpected.name);
    cr_assert_eq(roomExpected.hasPassword, room.hasPassword);
    cr_assert(room.password == roomExpected.password);

    rtype::network::RTypeDatagram datagram2;
    rtype::network::RTypeDatagramRoom room2 = {"room2", 3, 1, false, ""};
    datagram2.init116JoinRoomDatagram(room2);
    rtype::network::RTypeDatagramRoom room2Expected;
    datagram2.extract116JoinRoomDatagram(room2Expected);
    cr_assert(room2.name == room2Expected.name);
    cr_assert_eq(room2Expected.hasPassword, room2.hasPassword);
    cr_assert(room2.password == room2Expected.password);

}

Test(extractPacket, T_117_ROOM_JOINED,
     .timeout=10,
     .description="Test the deserialisation of the T_117_ROOM_JOINED packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.init117RoomJoinedDatagram({"user1", "0123456789abcde", "azertyuiop"});
    std::vector<std::string> vec;
    datagram.extract117RoomJoinedDatagram(vec);
    cr_assert_eq(vec.size(), 3);
    cr_assert(vec[0] == "user1");
    cr_assert(vec[1] == "0123456789");
    cr_assert(vec[2] == "azertyuiop");
}

Test(extractPacket, T_200_ACTION,
     .timeout=10,
     .description="Test the deserialisation of the T_200_ACTION packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramAction actionExpected = {true, false, false, true, true};
    datagram.init200ActionDatagram(actionExpected);
    rtype::network::RTypeDatagramAction action;
    datagram.extract200ActionDatagram(action);
    cr_assert_eq(action.shot, actionExpected.shot);
    cr_assert_eq(action.up, actionExpected.up);
    cr_assert_eq(action.down, actionExpected.down);
    cr_assert_eq(action.left, actionExpected.left);
    cr_assert_eq(action.right, actionExpected.right);
}

Test(extractPacket, T_210_DISPLAY,
     .timeout=10,
     .description="Test the deserialisation of the T_210_DISPLAY packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramDisplay dispExpected = {234522244, {3, 2, 1}, {4, 5}, {6, 7}, 8};
    datagram.init210DisplayDatagram(dispExpected);
    rtype::network::RTypeDatagramDisplay disp;
    datagram.extract210DisplayDatagram(disp);
    cr_assert_eq(disp.entityId, dispExpected.entityId);
    cr_assert_eq(disp.position.x, dispExpected.position.x);
    cr_assert_eq(disp.position.y, dispExpected.position.y);
    cr_assert_eq(disp.position.z, dispExpected.position.z);
    cr_assert_eq(disp.rotation.x, dispExpected.rotation.x);
    cr_assert_eq(disp.rotation.y, dispExpected.rotation.y);
    cr_assert_eq(disp.scale.x, dispExpected.scale.x);
    cr_assert_eq(disp.scale.y, dispExpected.scale.y);
    cr_assert_eq(disp.type, dispExpected.type);
}

Test(extractPacket, T_220_LIVING,
     .timeout=10,
     .description="Test the deserialisation of the T_220_LIVING packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramLiving lifeExpected = {234522244, 10};
    datagram.init220LivingDatagram(lifeExpected);
    rtype::network::RTypeDatagramLiving life;
    datagram.extract220LivingDatagram(life);
    cr_assert_eq(life.entityId, lifeExpected.entityId);
    cr_assert_eq(life.life, lifeExpected.life);
}

Test(extractPacket, T_230_CHARGE,
     .timeout=10,
     .description="Test the deserialisation of the T_230_CHARGE packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    datagram.init230ChargeDatagram(89);
    unsigned char charge;
    datagram.extract230ChargeDatagram(charge);
    cr_assert_eq(charge, 89);
}

Test(extractPacket, T_240_SCORE,
     .timeout=10,
     .description="Test the deserialisation of the T_240_SCORE packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramScore scoreExpected = {400, 14502, 12333, 82863};
    datagram.init240ScoreDatagram(scoreExpected);
    rtype::network::RTypeDatagramScore score;
    datagram.extract240ScoreDatagram(score);
    cr_assert_eq(score.p1Score, scoreExpected.p1Score);
    cr_assert_eq(score.p2Score, scoreExpected.p2Score);
    cr_assert_eq(score.p3Score, scoreExpected.p3Score);
    cr_assert_eq(score.p4Score, scoreExpected.p4Score);
}

Test(extractPacket, T_250_END_GAME,
     .timeout=10,
     .description="Test the deserialisation of the T_250_END_GAME packet",
     .init=init,
     .fini=fini
)
{
    rtype::network::RTypeDatagram datagram;
    rtype::network::RTypeDatagramScore scoreExpected = {400, 14502, 12333, 82863};
    datagram.init250EndGameDatagram(scoreExpected);
    rtype::network::RTypeDatagramScore score;
    datagram.extract250EndGameDatagram(score);
    cr_assert_eq(score.p1Score, scoreExpected.p1Score);
    cr_assert_eq(score.p2Score, scoreExpected.p2Score);
    cr_assert_eq(score.p3Score, scoreExpected.p3Score);
    cr_assert_eq(score.p4Score, scoreExpected.p4Score);
}