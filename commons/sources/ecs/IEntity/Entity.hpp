/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Entity.hpp
*/

/* Created the 19/11/2019 at 20:55 by julian.frabel@epitech.eu */

#ifndef R_TYPE_ENTITY_HPP
#define R_TYPE_ENTITY_HPP

#include <vector>
#include "ecs/IDGenerator/IdGenerator.hpp"
#include "ecs/IEntity/IEntity.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class Entity
     * @brief An entity
     */
    class Entity : public IEntity {
    public:
        /*!
         * @brief ctor
         */
        explicit Entity(const std::string &name);
        /*!
         * @brief no cpy ctor
         * @param other the entity to copy
         */
        Entity(const Entity &other) = delete;
        /*!
         * @brief no assignment operator
         * @param rhs the object to assign to
         * @return *this
         */
        Entity &operator=(const Entity &rhs) = delete;
        /*!
         * @brief dtor
         */
        ~Entity() override;

    public:
        int getID() const override;
        void setId(int id) override ;
        const std::string &getName() const override;
        bool hasComponent(const Version &componentType) const override;
        bool hasComponents(const std::vector<Version> &componentTypes) override;
        void addComponent(const std::shared_ptr<IComponent> &component) override;
        std::weak_ptr<IComponent> getComponent(const Version &componentType) override;
        std::vector<std::weak_ptr<IComponent>> getComponents(const std::vector<Version> &componentTypes) override;
        std::shared_ptr<IComponent> removeComponent(const Version &version) override;
        bool shouldBeKeeped() const override;
        void setShouldBeKeeped(bool value) override;

        bool operator ==(const Entity &rhs) const;
        bool operator !=(const Entity &rhs) const;

    private:
        int _id; /*!< A unique id for this entity */
        std::string _name; /*!< A name for this entity */
        std::vector<std::shared_ptr<IComponent>> _components; /*!< this entity components */
        bool _shouldBeKeeped; /*!< Should this entity be keeped */
    };
}

#endif //R_TYPE_ENTITY_HPP
