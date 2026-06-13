#pragma once

#include <cmath>

template<typename T>
struct Vec2
{
    T x, y;

    Vec2() : x(0), y(0) { }
    Vec2(T x, T y) : x(x), y(y) { }

    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    Vec2 operator*(T s) const { return {x * s, y * s}; }
    Vec2 operator/(T s) const { return {x / s, y / s}; }
    
    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }
    Vec2& operator-=(const Vec2& o) { x -= o.x; y -= o.y; return *this; }
    Vec2& operator*=(T s) { x *= s; y *= s; return *this; }
    Vec2& operator/=(T s) { x /= s; y /= s; return *this; }

    Vec2 operator-() const { return {-x, -y}; }

    T Dot(const Vec2& o) const { return x * o.x + y * o.y; }

    T Length() const { return std::sqrt(Dot(*this)); }

    Vec2 Normalized() const
    {
        T len = Length();
        if (len == 0) return { 0, 0 };
        return {x / len, y / len};
    }
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;