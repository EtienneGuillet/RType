/*
** EPITECH PROJECT, 2022
** EntityID.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_ENTITYID_HPP
#define R_TYPE_ENTITYID_HPP

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
 namespace rtype {

     /*!
      * @class EntityID
      * @brief This class is a component refering to the ID of a entity on the network.
      */
     class EntityIdComponent : public ecs::IComponent {

         public:
            static const ecs::Version Version;

            EntityIdComponent(int id);
            ~EntityIdComponent() override = default;

            void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
            const ecs::Version &getVersion() const override;

            [[nodiscard]] int getID() const;

         private:

         std::weak_ptr<ecs::IEntity> _entity;
         int _id;
     };
 }

#endif //R_TYPE_ENTITYID_HPP
