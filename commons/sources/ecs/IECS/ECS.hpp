/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ECS.hpp
*/

/* Created the 19/11/2019 at 20:47 by julian.frabel@epitech.eu */

#ifndef R_TYPE_ECS_HPP
#define R_TYPE_ECS_HPP

#include "ecs/IECS/IECS.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

class ECS : public IECS, public std::enable_shared_from_this<ECS> {
    public:
        /*!
         * @brief ctor
         */
        ECS();
        /*!
         * @brief dtor
         */
        ~ECS() override;

    public:
        std::shared_ptr<IWorld> createWorld() override;
        std::shared_ptr<IEntity> createEntityFromAPI(const Version &version) override;
        std::shared_ptr<ISystem> createSystemFromAPI(const Version &version) override;
        bool knowSystem(const Version &version) override;
        bool knowEntity(const Version &version) override;
        bool knowSystems(const std::vector<Version> &versions) override;
        bool knowEntities(const std::vector<Version> &versions) override;
        void learnSystem(const std::shared_ptr<ISystemAPI> &api) override;
        void learnEntity(const std::shared_ptr<IEntityAPI> &api) override;
        std::shared_ptr<ISystemAPI> forgetSystem(const Version &version) override;
        std::shared_ptr<IEntityAPI> forgetEntity(const Version &version) override;
        [[nodiscard]] std::vector<std::shared_ptr<ecs::IEntityAPI>> getKnownEntities() const override;

    private:
        std::vector<std::shared_ptr<ISystemAPI>> _systemsAPI; /*!< known system api */
        std::vector<std::shared_ptr<IEntityAPI>> _entitysAPI; /*!< known entity api */
    };
}
#endif //R_TYPE_ECS_HPP
