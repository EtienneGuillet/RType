/*
** EPITECH PROJECT, 2022
** TTLComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _TTL_COMPONENT_HPP_
#define _TTL_COMPONENT_HPP_

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class TTLComponent
     * @brief This class is a component allowing to choose the position the scale and the rotation of an entity.
     */
    class TTLComponent : public ecs::IComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         * @param pos Vectore3 indicating the position of the entity
         * @param rot Vectore2 indicating the rotation of the entity
         * @param scale Vectore2 indicating the scale of the entity
         */
        TTLComponent();

        /*!
         * @brief Dtor.
         */
        ~TTLComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

        void updateTTL();
        const std::chrono::time_point<std::chrono::system_clock> &getTTL();
    private:
        std::weak_ptr<ecs::IEntity> _entity;
        std::chrono::time_point<std::chrono::system_clock> _ttl;
    };
} /* rtype */

#endif // _TTL_COMPONENT_HPP_
