#pragma once

#include <cmath>

template<typename T>
struct Vec3
{
    T x, y, z;

    Vec3() : x(0), y(0), z(0) { }
    Vec3(T x, T y, T z) : x(x), y(y), z(z) { }

    Vec3 operator+(const Vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    Vec3 operator*(T s) const { return {x * s, y * s, z * s}; }
    Vec3 operator/(T s) const { return {x / s, y / s, z / s}; }
    
    Vec3& operator+=(const Vec3& o) { x += o.x; y += o.y; z += o.z; return *this; }
    Vec3& operator-=(const Vec3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    Vec3& operator*=(T s) { x *= s; y *= s; z *= s; return *this; }
    Vec3& operator/=(T s) { x /= s; y /= s; z /= s; return *this; }
    
    Vec3 operator-() const { return {-x, -y, -z}; }

    T Dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }

    Vec3 Cross(const Vec3& o) const
    {
        return {
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        };
    }

    T Length() const { return std::sqrt(Dot(*this)); }

    Vec3 Normalized() const
    {
        T len = Length();
        if (len == 0) return { 0, 0, 0 };
        return {x / len, y / len, z / len};
    }
};

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;