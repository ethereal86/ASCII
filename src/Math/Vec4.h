#pragma once

template<typename T>
struct Vec4
{
    T x, y, z, w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    Vec4(const Vec3<T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}

    Vec4 operator+(const Vec4& o) const { return {x + o.x, y + o.y, z + o.z, w + o.w}; }
    Vec4 operator-(const Vec4& o) const { return {x - o.x, y - o.y, z - o.z, w - o.w}; }
    Vec4 operator*(T s) const { return {x * s, y * s, z * s, w * s}; }
    Vec4 operator/(T s) const { return {x / s, y / s, z / s, w / s}; }

    Vec4& operator+=(const Vec4& o) { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }
    Vec4& operator-=(const Vec4& o) { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }
    Vec4& operator*=(T s) { x *= s; y *= s; z *= s; w *= s; return *this; }
    Vec4& operator/=(T s) { x /= s; y /= s; z /= s; w /= s; return *this; }

    Vec4 operator-() const { return {-x, -y, -z, -w}; }

    Vec3<T> ToVec3() const { return { x, y, z }; }

    Vec3<T> PerspectiveDivide() const
    {
        if (w == 0) return {x, y, z};
        return {x / w, y / w, z / w};
    }
};

using Vec4f = Vec4<float>;
using Vec4i = Vec4<int>;