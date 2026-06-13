#pragma once

#include "Math.h"
#include "FrameBuffer.h"

class Rasterizer
{
public:
    static void DrawLine(FrameBuffer& framebuffer, ivec2 a, ivec2 b, uint8_t brightness);
    static void DrawTriangle(FrameBuffer& framebuffer, ivec2 a, ivec2 b, ivec2 c, uint8_t brightness);
};