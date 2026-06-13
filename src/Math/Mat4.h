#pragma once

#include "Vec3.h"
#include "Vec4.h"

struct Mat4
{
    float m[4][4];

    static Mat4 Identity()
    {
        Mat4 r {};
        for (int i = 0; i < 4; i++) r.m[i][i] = 1.0f;

        return r;
    }

    static Mat4 Translate(const Vec3f& t)
    {
        Mat4 r = Identity();
        r.m[3][0] = t.x;
        r.m[3][1] = t.y;
        r.m[3][2] = t.z;

        return r;
    }

    static Mat4 Scale(const Vec3f& s)
    {
        Mat4 r = Identity();
        r.m[0][0] = s.x;
        r.m[1][1] = s.y;
        r.m[2][2] = s.z;

        return r;
    }

    static Mat4 RotateX(float radians)
    {
        Mat4 r = Identity();

        float c = std::cos(radians);
        float s = std::sin(radians);

        r.m[1][1] = c; r.m[2][1] = -s;
        r.m[1][2] = s; r.m[2][2] = c;

        return r;
    }

    static Mat4 RotateY(float radians)
    {
        Mat4 r = Identity();

        float c = std::cos(radians);
        float s = std::sin(radians);

        r.m[0][0] = c;  r.m[2][0] = s;
        r.m[0][2] = -s; r.m[2][2] = c;
        
        return r;
    }
 
    static Mat4 RotateZ(float radians)
    {
        Mat4 r = Identity();

        float c = std::cos(radians);
        float s = std::sin(radians);

        r.m[0][0] = c;  r.m[1][0] = -s;
        r.m[0][1] = s;  r.m[1][1] = c;
        
        return r;
    }

    Mat4 operator*(const Mat4& o) const
    {
        Mat4 r {};
        for (int col = 0; col < 4; col++)
        {
            for (int row = 0; row < 4; row++)
            {
                float sum = 0.0f;

                for (int k = 0; k < 4; k++)
                    sum += m[k][row] * o.m[col][k];

                r.m[col][row] = sum;
            }
        }
        return r;
    }

    Vec4f operator*(const Vec4f& v) const
    {
        return {
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
            m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w
        };
    }
};