//
// Created by Lilian on 28/11/2019.
//

#ifndef R_TYPE_ENEMYSPAWNERSYSTEM_HPP
#define R_TYPE_ENEMYSPAWNERSYSTEM_HPP

#include <ecs/ASystem/ASystem.hpp>
#include <map>

namespace systems {

    /*!
     * @class EnemySpawnerSystem
     * @brief EnemySpawner system
     */
    class EnemySpawnerSystem : public ecs::ASystem {
    public:
        EnemySpawnerSystem();
    public:
        static const ecs::Version Version;

    public:
        void tick(long deltatime) override;
        [[nodiscard]] const ecs::Version &getType() const override;
        void start() override;
        void stop() override;

    private:
        void computeSpawn(std::shared_ptr<ecs::IEntityAPI> &entityApi, std::shared_ptr<ecs::IWorld> lockedWorld);

    private:
        long _elapsedTime; /*!< The passed elapsed time in ms */
        long _computeEvery; /*!< Compute actual damages every x ms*/

        std::map<ecs::Version, long> _timeBeforeSpawnMap; /*< A map for each spawnable entity version and remaining time before spawn */
        void spawnEntity(std::shared_ptr<ecs::IEntityAPI> &entity, std::shared_ptr<ecs::IWorld> lockedWorld);
    };
}

#endif //R_TYPE_ENEMYSPAWNERSYSTEM_HPP
