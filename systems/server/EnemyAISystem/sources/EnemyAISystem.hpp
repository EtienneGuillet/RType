//
// Created by Lilian on 28/11/2019.
//

#ifndef R_TYPE_ENEMYAISYSTEM_HPP
#define R_TYPE_ENEMYAISYSTEM_HPP

#include <ecs/ASystem/ASystem.hpp>

namespace systems {

    /*!
     * @class EnemyAISystem
     * @brief EnemyAI system
     */
    class EnemyAISystem : public ecs::ASystem {
    public:
        EnemyAISystem();
    public:
        static const ecs::Version Version;

    public:
        void tick(long deltatime) override;
        [[nodiscard]] const ecs::Version &getType() const override;
        void start() override;
        void stop() override;

    private:

    private:
        long _elapsedTime; /*!< The passed elapsed time in ms */
        long _computeEvery; /*!< Compute actual damages every x ms*/
    };
}

#endif //R_TYPE_ENEMYAISYSTEM_HPP
