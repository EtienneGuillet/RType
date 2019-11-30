/*
** EPITECH PROJECT, 2022
** TitleSpriteEntityAPI.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_TITLESPRITEENTITYAPI_HPP
#define R_TYPE_TITLESPRITEENTITYAPI_HPP

#include <ecs/IEntityAPI/IEntityAPI.hpp>
#include <ecs/IEntityAPI/AUnspawnableEntityAPI.hpp>

class TitleSpriteEntityAPI : public ecs::AUnspawnableEntityAPI {
    public:
    const ecs::Version &getVersion() const override;

    std::shared_ptr<ecs::IEntity> createNewEntity() const override;

    public:
    static const ecs::Version Version;
};

#endif //R_TYPE_TITLESPRITEENTITYAPI_HPP
