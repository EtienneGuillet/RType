/*
** EPITECH PROJECT, 2022
** UpdateTextComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _UPDATE_COMPONENT_HPP_
#define _UPDATE_COMPONENT_HPP_

#include "ecs/IComponent/AComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class UpdateTextComponent
     * @brief This class is a component allowing to display a sprite.
     */
    class UpdateTextComponent : public ecs::AComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         */
        UpdateTextComponent(const bool isHoverable = true);

        /*!
         * @brief Dtor.
         */
        ~UpdateTextComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

        void setHoverable(const bool isHoverable);
        bool getHoverable() const;

        void setFunctionPointer(void (*functionPointer)());
    private:
        std::weak_ptr<ecs::IEntity> _entity;
        bool _isUpdatable;
    };
} /* r-type */

#endif // _UPDATE_COMPONENT_HPP_
