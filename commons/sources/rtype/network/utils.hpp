/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** utils.hpp
*/

/* Created the 18/11/2019 at 13:45 by julian.frabel@epitech.eu */

#ifndef R_TYPE_UTILS_HPP
#define R_TYPE_UTILS_HPP

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #include <ws2tcpip.h>
    #include <winsock2.h>

    #define HTONS(x) (htons(x))
    #define NTOHS(x) (ntohs(x))

    #define HTONL(x) (htonl(x))
    #define NTOHL(x) (ntohl(x))

    #define HTONLL(x) (htonll(x))
    #define NTOHLL(x) (ntohll(x))

    #define PACKED(__DECLARATION__) __pragma(pack(push, 1)) __DECLARATION__ __pragma(pack(pop))
#else
    #include <sys/types.h>
    #include <netinet/in.h>

    #define HTONS(x) (htons(x))
    #define NTOHS(x) (ntohs(x))

    #define HTONL(x) (htonl(x))
    #define NTOHL(x) (ntohl(x))

    #define HTONLL(x) ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t)((x) >> 32)))
    #define NTOHLL(x) ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t)((x) >> 32)))

    #define PACKED(__DECLARATION__) __DECLARATION__ __attribute__((packed))
#endif

#endif //R_TYPE_UTILS_HPP
