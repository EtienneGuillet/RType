/*
** EPITECH PROJECT, 2022
** HoverComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _HOVER_COMPONENT_HPP_
#define _HOVER_COMPONENT_HPP_

#include "ecs/IComponent/AComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class HoverComponent
     * @brief This class is a component allowing to display a sprite.
     */
    class HoverComponent : public ecs::AComponent {

    public:
        using functionPointer = std::function<void()>;

        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         */
        HoverComponent(const bool isHoverable = false);

        /*!
         * @brief Dtor.
         */
        ~HoverComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

        void setHoverable(const bool isHoverable);
        bool getHoverable() const;

        void setFunctionPointer(const functionPointer &func);
        const functionPointer &getFunctionPointer() const;
    private:
        std::weak_ptr<ecs::IEntity> _entity;
        bool _isHoverable;
        functionPointer _functionPointer;
    };
} /* r-type */

#endif // _SPRITE_COMPONENT_HPP_
