/*
** EPITECH PROJECT, 2018
** indieEntityComponentSystem
** File description:
** Vectors.cpp
*/

/* Created the 24/04/2019 at 23:23 by indierabel */

#include <cmath>
#include <cfloat>
#include "maths/Vectors.hpp"

#define CMP(x, y)  (fabsf((x) - (y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

/* ================================================================================================================ */
/* ----------------------------------------------------Vector2D---------------------------------------------------- */

/* ================================================================================================================ */

b12software::maths::Vector2D::Vector2D(): x(0), y(0)
{

}

b12software::maths::Vector2D::Vector2D(float value): x(value), y(value)
{

}

b12software::maths::Vector2D::Vector2D(float _x, float _y): x(_x), y(_y)
{

}

float &b12software::maths::Vector2D::operator[](int i)
{
    return asArray[i];
}

const float &b12software::maths::Vector2D::operator[](int i) const
{
    return asArray[i];
}

float b12software::maths::Vector2D::magnitude() const
{
    return Magnitude(*this);
}

float b12software::maths::Vector2D::magnitudeSq() const
{
    return MagnitudeSq(*this);
}

void b12software::maths::Vector2D::normalize()
{
    Normalize(*this);
}

b12software::maths::Vector2D b12software::maths::Vector2D::normalized() const
{
    return Normalized(*this);
}

float b12software::maths::Vector2D::Dot(const b12software::maths::Vector2D &lhs, const b12software::maths::Vector2D &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float b12software::maths::Vector2D::Magnitude(const b12software::maths::Vector2D &vec)
{
    return sqrtf(Dot(vec, vec));
}

float b12software::maths::Vector2D::MagnitudeSq(const b12software::maths::Vector2D &vec)
{
    return Dot(vec, vec);
}

float b12software::maths::Vector2D::Distance(const b12software::maths::Vector2D &p1, const b12software::maths::Vector2D &p2)
{
    Vector2D t = p1 - p2;
    return Magnitude(t);
}

void b12software::maths::Vector2D::Normalize(b12software::maths::Vector2D &vec)
{
    vec = vec * (1.0f / Magnitude(vec));
}

b12software::maths::Vector2D b12software::maths::Vector2D::Normalized(const b12software::maths::Vector2D &vec)
{
    return vec * (1.0f / Magnitude(vec));
}

float b12software::maths::Vector2D::Angle(const b12software::maths::Vector2D &lhs, const b12software::maths::Vector2D &rhs)
{
    float m = sqrtf(MagnitudeSq(lhs) * MagnitudeSq(rhs));
    return acos(Dot(lhs, rhs) / m);
}

b12software::maths::Vector2D b12software::maths::Vector2D::Project(const b12software::maths::Vector2D &len, const b12software::maths::Vector2D &dir)
{
    float dot = Dot(len, dir);
    float magSq = MagnitudeSq(dir);
    return dir * (dot / magSq);
}

b12software::maths::Vector2D b12software::maths::Vector2D::Perpendicular(const b12software::maths::Vector2D &len, const b12software::maths::Vector2D &dir)
{
    return len - Project(len, dir);
}

b12software::maths::Vector2D b12software::maths::Vector2D::Reflection(const b12software::maths::Vector2D &vec, const b12software::maths::Vector2D &normal)
{
    float d = Dot(vec, normal);
    return vec - normal * (d * 2.0f);
}

b12software::maths::Vector2D b12software::maths::operator+(const b12software::maths::Vector2D &lhs, const b12software::maths::Vector2D &rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

b12software::maths::Vector2D b12software::maths::operator-(const b12software::maths::Vector2D &lhs, const b12software::maths::Vector2D &rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

b12software::maths::Vector2D b12software::maths::operator*(const b12software::maths::Vector2D &lhs, const b12software::maths::Vector2D &rhs)
{
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}

b12software::maths::Vector2D b12software::maths::operator*(const b12software::maths::Vector2D &lhs, float rhs)
{
    return {lhs.x * rhs, lhs.y * rhs};
}

bool b12software::maths::operator==(const b12software::maths::Vector2D &lhs, const b12software::maths::Vector2D &rhs)
{
    return CMP(lhs.x, rhs.x) && CMP(lhs.y, rhs.y);
}

bool b12software::maths::operator!=(const b12software::maths::Vector2D &lhs, const b12software::maths::Vector2D &rhs)
{
    return !(lhs == rhs);
}

/* ================================================================================================================ */
/* ----------------------------------------------------Vector3D---------------------------------------------------- */
/* ================================================================================================================ */

b12software::maths::Vector3D::Vector3D(): x(0), y(0), z(0)
{

}

b12software::maths::Vector3D::Vector3D(float value): x(value), y(value), z(value)
{

}

b12software::maths::Vector3D::Vector3D(float _x, float _y, float _z): x(_x), y(_y), z(_z)
{

}

float &b12software::maths::Vector3D::operator[](int i)
{
    return asArray[i];
}

const float &b12software::maths::Vector3D::operator[](int i) const
{
    return asArray[i];
}

float b12software::maths::Vector3D::magnitude() const
{
    return Magnitude(*this);
}

float b12software::maths::Vector3D::magnitudeSq() const
{
    return MagnitudeSq(*this);
}

void b12software::maths::Vector3D::normalize()
{
    Normalize(*this);
}

b12software::maths::Vector3D b12software::maths::Vector3D::normalized() const
{
    return Normalized(*this);
}

float b12software::maths::Vector3D::Dot(const b12software::maths::Vector3D &lhs, const b12software::maths::Vector3D &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float b12software::maths::Vector3D::Magnitude(const b12software::maths::Vector3D &vec)
{
    return sqrtf(Dot(vec, vec));
}

float b12software::maths::Vector3D::MagnitudeSq(const b12software::maths::Vector3D &vec)
{
    return Dot(vec, vec);
}

float b12software::maths::Vector3D::Distance(const b12software::maths::Vector3D &p1, const b12software::maths::Vector3D &p2)
{
    Vector3D t = p1 - p2;
    return Magnitude(t);
}

void b12software::maths::Vector3D::Normalize(b12software::maths::Vector3D &vec)
{
    vec = vec * (1.0f / Magnitude(vec));
}

b12software::maths::Vector3D b12software::maths::Vector3D::Normalized(const b12software::maths::Vector3D &vec)
{
    return vec * (1.0f / Magnitude(vec));
}

b12software::maths::Vector3D b12software::maths::Vector3D::Cross(const b12software::maths::Vector3D &lhs, const b12software::maths::Vector3D &rhs)
{
    Vector3D result;
    result.x = lhs.y * rhs.z - lhs.z * rhs.y;
    result.y = lhs.z * rhs.x - lhs.x * rhs.z;
    result.z = lhs.x * rhs.y - lhs.y * rhs.x;
    return result;
}

float b12software::maths::Vector3D::Angle(const b12software::maths::Vector3D &lhs, const b12software::maths::Vector3D &rhs)
{
    float m = sqrtf(MagnitudeSq(lhs) * MagnitudeSq(rhs));
    return acos(Dot(lhs, rhs) / m);
}

b12software::maths::Vector3D b12software::maths::Vector3D::Project(const b12software::maths::Vector3D &len, const b12software::maths::Vector3D &dir)
{
    float dot = Dot(len, dir);
    float magSq = MagnitudeSq(dir);
    return dir * (dot / magSq);
}

b12software::maths::Vector3D b12software::maths::Vector3D::Perpendicular(const b12software::maths::Vector3D &len, const b12software::maths::Vector3D &dir)
{
    return len - Project(len, dir);
}

b12software::maths::Vector3D b12software::maths::Vector3D::Reflection(const b12software::maths::Vector3D &vec, const b12software::maths::Vector3D &normal)
{
    float d = Dot(vec, normal);
    return vec - normal * (d * 2.0f);
}

b12software::maths::Vector3D b12software::maths::operator+(const b12software::maths::Vector3D &lhs, const b12software::maths::Vector3D &rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

b12software::maths::Vector3D b12software::maths::operator-(const b12software::maths::Vector3D &lhs, const b12software::maths::Vector3D &rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

b12software::maths::Vector3D b12software::maths::operator*(const b12software::maths::Vector3D &lhs, const b12software::maths::Vector3D &rhs)
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

b12software::maths::Vector3D b12software::maths::operator*(const b12software::maths::Vector3D &lhs, float rhs)
{
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

bool b12software::maths::operator==(const b12software::maths::Vector3D &lhs, const b12software::maths::Vector3D &rhs)
{
    return CMP(lhs.x, rhs.x) && CMP(lhs.y, rhs.y) && CMP(lhs.z, rhs.z);
}

bool b12software::maths::operator!=(const b12software::maths::Vector3D &lhs, const b12software::maths::Vector3D &rhs)
{
    return !(lhs == rhs);
}

std::ostream &b12software::operator<<(std::ostream &s, const b12software::maths::Vector2D &vec)
{
    s << vec.x << "," << vec.y;
    return s;
}

std::ostream &b12software::operator<<(std::ostream &s, const b12software::maths::Vector3D &vec)
{
    s << vec.x << "," << vec.y << "," << vec.z;
    return s;
}
