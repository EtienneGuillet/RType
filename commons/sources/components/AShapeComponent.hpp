/*
** EPITECH PROJECT, 2022
** TextComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _A_SHAPE_COMPONENT_HPP_
#define _A_SHAPE_COMPONENT_HPP_

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

namespace rtype {
    enum shapeType {
        UNDEFINED = -1,
        CIRCLE,
        RECTANGLE
    };

    class AShapeComponent : public ecs::IComponent {

    public:
        static const ecs::Version Version;
        AShapeComponent(const int type);
        ~AShapeComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;
        void setType(const int type);
        int getType() const;

    protected:
        std::weak_ptr<ecs::IEntity> _entity;
        int _type;
    };
} /*rtype */

#endif // _A_SHAPE_COMPONENT_HPP_
