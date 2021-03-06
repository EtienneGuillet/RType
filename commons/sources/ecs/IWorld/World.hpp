/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** World.hpp
*/

/* Created the 19/11/2019 at 21:56 by julian.frabel@epitech.eu */

#ifndef R_TYPE_WORLD_HPP
#define R_TYPE_WORLD_HPP

#include "ecs/IDGenerator/IdGenerator.hpp"
#include "ecs/IWorld/IWorld.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class World
     * @brief A class that represent an ecs world
     */
    class World : public IWorld, public std::enable_shared_from_this<World> {
    public:
        /*!
         * @brief ctor
         */
        World(std::weak_ptr<ecs::IECS> ecs);
        /*!
         * @brief no cpy ctor
         * @param other the other world
         */
        World(const World &other) = delete;
        /*!
         * @brief dtor
         */
        ~World() override;
        /*!
         * @brief no assignment operator
         * @param rhs The world to copy from
         * @return *this
         */
        World &operator=(const World &rhs) = delete;

    public:
        void tick(long deltatime) override;
        std::weak_ptr<IEntity> pushEntity(const std::shared_ptr<IEntity> &entity) override;
        std::shared_ptr<IEntity> popEntity(int id) override;
        void clearAllEntities() override;
        std::weak_ptr<IEntity> getEntityById(int id) const override;
        [[nodiscard]] std::vector<std::weak_ptr<IEntity>> getEntitiesWith(const std::vector<Version> &components) const override;
        void applyToEach(const std::vector<Version> &componentTypes, std::function<void(std::weak_ptr<IEntity>, std::vector<std::weak_ptr<IComponent>>)> toApply) override;
        std::weak_ptr<ISystem> addSystem(const std::shared_ptr<ISystem> &system) override;
        void removeSystem(const Version &system) override;
        std::weak_ptr<ISystem> getSystem(const Version &system) override;
        const std::weak_ptr<ecs::IECS> &getEcs() const override;
    private:
        IDGenerator Generator; /*!< A static generator used to create ids for entities */
        bool _entitiesClearCallBack;
        std::vector<std::shared_ptr<IEntity>> _afterClear; /*!< Tmp world entitites */
        std::vector<std::shared_ptr<IEntity>> _entities; /*!< this world entities */
        std::vector<std::shared_ptr<ISystem>> _systems; /*!< this world systems */
        std::weak_ptr<ecs::IECS> _ecs; /*!< The ECS owning this world */
    };
}

#endif //R_TYPE_WORLD_HPP
