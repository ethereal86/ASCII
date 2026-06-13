#pragma once

struct vec2
{
    float x, y;
};

struct vec3
{
    float x, y, z;
};

struct ivec2
{
    int x, y;
};

struct ivec3
{
    int x, y, z;
};

struct Viewport
{
    int x;
    int y;
    int width;
    int height;

    ivec2 Transform(const vec3& ndc) const
    {
        ivec2 result;
        result.x = static_cast<int>(x + (ndc.x + 1.0f) * (width / 2.0f));
        result.y = static_cast<int>(y + (1.0f - ndc.y) * (height / 2.0f));
        return result;
    }
};