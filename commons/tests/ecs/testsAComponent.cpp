/*
** EPITECH PROJECT, 2022
** testASytem.cpp
** File description:
** testsASystem.cpp
*/

#include <criterion/criterion.h>
#include <ecs/IEntity/AComponent.hpp>
#include <ecs/IEntity/Entity.hpp>
#include "ecs/ASystem/ASystem.hpp"


class TestAComponent : public ecs::AComponent {
public:
    static ecs::Version Version;

    [[nodiscard]] const ecs::Version &getVersion() const override {
        return TestAComponent::Version;
    }
};

ecs::Version TestAComponent::Version("", 0, 0, 0, 0);

Test(AComponent, setEntity)
{
    auto component = std::make_shared<TestAComponent>();
    auto entity = std::make_shared<ecs::Entity>("ENTITY");

    const std::weak_ptr<ecs::IEntity> ptr = std::weak_ptr<ecs::Entity>(entity);

    entity->addComponent(component);
    component->setEntity(ptr);

//    cr_assert_eq(ptr, component->getEntity());
}
