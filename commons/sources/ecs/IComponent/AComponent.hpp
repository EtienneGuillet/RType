#ifndef R_TYPE_ACOMPONENT_HPP
#define R_TYPE_ACOMPONENT_HPP

#include <ecs/IComponent/IComponent.hpp>
#include <memory>

namespace ecs {
    class AComponent : public ecs::IComponent {
    public:
        void setEntity(const std::weak_ptr<IEntity> &entity) override;
        [[nodiscard]] std::weak_ptr<IEntity> getEntity() const override;

    private:
        std::weak_ptr<IEntity> _entity;
    };
}

#endif
