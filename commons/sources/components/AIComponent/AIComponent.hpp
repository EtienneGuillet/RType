#ifndef R_TYPE_AIComponent_HPP
#define R_TYPE_AIComponent_HPP

#include <ecs/IEntity/AComponent.hpp>

namespace ecs {

    namespace components {

        class AIComponent : public ecs::AComponent {
        public:
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

        public:

            /*!
             * @brief ctor
             */
            AIComponent();

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

        private:
        };
    }
}

#endif