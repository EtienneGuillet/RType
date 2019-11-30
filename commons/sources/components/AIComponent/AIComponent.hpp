#ifndef R_TYPE_AIComponent_HPP
#define R_TYPE_AIComponent_HPP

#include <ecs/IEntity/AComponent.hpp>
#include <functional>
#include <ecs/IWorld/IWorld.hpp>

namespace ecs {

    namespace components {

        class AIComponent : public ecs::AComponent {
        public:
            typedef std::function<void (std::shared_ptr<IEntity> &entity, std::shared_ptr<ecs::IWorld> world)> Handler;
        public:
            static const ecs::Version Version;
            [[nodiscard]] const ecs::Version &getVersion() const override;

        public:

            /*!
             * @brief ctor
             */
            AIComponent(Handler);

            /*!
             * @brief cpy ctor
             * @param other The transform to copy
             */
            AIComponent(const AIComponent &other);

            /*!
             * @brief Assignment operator
             * @param rhs the object to assign as
             * @return *this
             */
            AIComponent &operator=(const AIComponent &rhs);

            void operator ()(std::shared_ptr<IEntity> &entity, std::shared_ptr<ecs::IWorld> world);
        private:
            Handler _handler;
        };
    }
}

#endif