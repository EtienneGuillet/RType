#ifndef R_TYPE_TRANSFORMCOMPONENT_HPP
#define R_TYPE_TRANSFORMCOMPONENT_HPP

#include <maths/Vectors.hpp>
#include <ecs/IComponent/AComponent.hpp>

class TransformComponent : public ecs::AComponent {
public:
    using Vector2 = b12software::maths::Vector2D;
    using Vector3 = b12software::maths::Vector3D;

    /*!
     * @brief ctor
     * @param position The position to use
     * @param rotation The rotation to use
     * @param scale The scale to use
     */
    TransformComponent(const Vector3 &position, const Vector2 &rotation, const Vector2 &scale);

    /*!
     * @brief cpy ctor
     * @param other The transform to copy
     */
    TransformComponent(const TransformComponent &other);

    /*!
     * @brief Assignment operator
     * @param rhs the object to assign as
     * @return *this
     */
    TransformComponent &operator=(const TransformComponent &rhs);

    /*!
     * @brief Get the position contained is the component
     * @return The position contained in the component
     */
    [[nodiscard]] const Vector3 &getPosition() const;

    /*!
     * @brief Set the position contained is the component
     */
    void setPosition(const Vector3 &position);

    /*!
     * @brief Get the rotation contained is the component
     * @return The rotation contained in the component
     */
    [[nodiscard]] const Vector2 &getRotation() const;

    /*!
     * @brief Set the rotation contained is the component
     */
    void setRotation(const Vector2 &rotation);

    /*!
     * @brief Get the scale contained is the component
     * @return The scale contained in the component
     */
    [[nodiscard]] const Vector2 &getScale() const;

    /*!
     * @brief Set the scale contained is the component
     */
    void setScale(const Vector2 &scale);

private:
    Vector3 _position; /*!< position */
    Vector2 _rotation; /*!< rotation */
    Vector2 _scale; /*!< scale */
};

#endif