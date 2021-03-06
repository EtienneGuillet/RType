/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Vectors.hpp
*/

/* Created the 24/04/2019 at 23:23 by jfrabel */

#ifndef JFENTITYCOMPONENTSYSTEM_VECTORS_HPP
#define JFENTITYCOMPONENTSYSTEM_VECTORS_HPP

#include <iostream>

#define RAD2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.0174533f)

namespace b12software {

    /*!
     * @namespace b12software::maths
     * @brief A namespace containing math related classes
     */
    namespace maths {
        struct Vector2D {
            union {
                struct {
                    float x;
                    float y;
                };
                float asArray[2];
            };

            Vector2D();
            explicit Vector2D(float value);
            Vector2D(float x, float y);

            float &operator[](int i);
            const float &operator[](int i) const;

            [[nodiscard]] float magnitude() const;
            [[nodiscard]] float magnitudeSq() const;

            void normalize();
            [[nodiscard]] Vector2D normalized() const;

            static float Dot(const Vector2D &lhs, const Vector2D &rhs);
            static float Magnitude(const Vector2D &vec);
            static float MagnitudeSq(const Vector2D &vec);
            static float Distance(const Vector2D &p1, const Vector2D &p2);

            static void Normalize(Vector2D &vec);
            static Vector2D Normalized(const Vector2D &vec);

            static float Angle(const Vector2D &lhs, const Vector2D &rhs);
            static Vector2D Project(const Vector2D &len, const Vector2D &dir);
            static Vector2D Perpendicular(const Vector2D &len, const Vector2D &dir);
            static Vector2D Reflection(const Vector2D &vec, const Vector2D &normal);

            Vector2D operator+(const Vector2D &rhs) const;
            Vector2D operator-(const Vector2D &rhs) const;
            Vector2D operator*(const Vector2D &rhs) const;
            Vector2D operator*(float rhs) const;
            bool operator==(const Vector2D &rhs) const;
            bool operator!=(const Vector2D &rhs) const;
        };

        struct Vector3D {
            union {
                struct {
                    float x;
                    float y;
                    float z;
                };
                float asArray[3];
            };

            Vector3D();
            explicit Vector3D(float value);
            Vector3D(float x, float y, float z);

            float &operator[](int i);
            const float &operator[](int i) const;

            [[nodiscard]] float magnitude() const;
            [[nodiscard]] float magnitudeSq() const;

            void normalize();
            [[nodiscard]] Vector3D normalized() const;

            static float Dot(const Vector3D &lhs, const Vector3D &rhs);
            static float Magnitude(const Vector3D &vec);
            static float MagnitudeSq(const Vector3D &vec);
            static float Distance(const Vector3D &p1, const Vector3D &p2);

            static void Normalize(Vector3D &vec);
            static Vector3D Normalized(const Vector3D &vec);

            static Vector3D Cross(const Vector3D &lhs, const Vector3D &rhs);
            static float Angle(const Vector3D &lhs, const Vector3D &rhs);
            static Vector3D Project(const Vector3D &len, const Vector3D &dir);
            static Vector3D Perpendicular(const Vector3D &len, const Vector3D &dir);
            static Vector3D Reflection(const Vector3D &vec, const Vector3D &normal);

            Vector3D operator+(const Vector3D &rhs) const;
            Vector3D operator-(const Vector3D &rhs) const;
            Vector3D operator*(const Vector3D &rhs) const;
            Vector3D operator*(float rhs) const;
            bool operator==(const Vector3D &rhs) const;
            bool operator!=(const Vector3D &rhs) const;
        };
    }

    std::ostream &operator<<(std::ostream &s, const maths::Vector2D &vec);
    std::ostream &operator<<(std::ostream &s, const maths::Vector3D &vec);
}

#endif
