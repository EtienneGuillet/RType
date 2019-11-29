#ifndef R_TYPE_AIComponent_HPP
#define R_TYPE_AIComponent_HPP

#include <ecs/IEntity/AComponent.hpp>
#include <functional>

namespace ecs {

    namespace components {

        class AIComponent : public ecs::AComponent {
        public:
            typedef std::function<void (std::shared_ptr<IEntity> &entity)> Handler;
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

            void operator() (std::shared_ptr<IEntity> &entity);
        private:
            Handler _handler;
        };
    }
}

#endif