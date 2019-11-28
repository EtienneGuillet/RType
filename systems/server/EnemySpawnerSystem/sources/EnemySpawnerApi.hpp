//
// Created by Lilian on 28/11/2019.
//

#ifndef R_TYPE_ENEMYSPAWNERAPI_HPP
#define R_TYPE_ENEMYSPAWNERAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

namespace systems {

    /*!
     * @class EnemySpawnerApi
     * @brief EnemySpawner api
     */
    class EnemySpawnerApi : public ecs::ISystemAPI {
    public:
        static const ecs::Version Version;

    public:
        [[nodiscard]] const ecs::Version &getVersion() const override;
        [[nodiscard]] std::shared_ptr<ecs::ISystem> createNewSystem() const override;
    };
}

#endif //R_TYPE_ENEMYSPAWNERAPI_HPP

