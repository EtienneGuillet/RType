#ifndef R_TYPE_ACOMPONENT_HPP
#define R_TYPE_ACOMPONENT_HPP

#include <ecs/IComponent/IComponent.hpp>

namespace ecs {
    class AComponent : ecs::IComponent {
    public:
        void setEntity(const std::weak_ptr<IEntity> &entity) override;
        const std::weak_ptr<IEntity> &getEntity() override;

    private:
        std::weak_ptr<IEntity> _entity;
    };
}

#endif
