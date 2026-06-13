#pragma once

#include "Math/Math.h"

struct Viewport
{
    int x, y;
    int width, height;

    Vec2i Transform(const Vec3f& ndc) const
    {
        Vec2i result;
        result.x = x + (int)((ndc.x * 0.5f + 0.5f) * (width - 1));
        result.y = y + (int)((1.0f - (ndc.y * 0.5f + 0.5f)) * (height - 1));
        return result;
    }
};