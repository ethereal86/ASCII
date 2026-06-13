#pragma once

#include "FrameBuffer.h"
#include "Math/Math.h"

class Rasterizer
{
public:
    static void DrawLine(FrameBuffer& framebuffer, Vec2i a, Vec2i b, uint8_t brightness);
    static void DrawTriangle(FrameBuffer& framebuffer, Vec2i a, Vec2i b, Vec2i c, uint8_t brightness);
};