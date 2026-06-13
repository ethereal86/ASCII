#include <pch.h>
#include "Rasterizer.h"

void Rasterizer::DrawLine(FrameBuffer& framebuffer, Vec2i a, Vec2i b, uint8_t brightness)
{
    int dx = std::abs(b.x - a.x);
    int dy = std::abs(b.y - a.y);

    int sx = (b.x > a.x) ? 1 : -1;
    int sy = (b.y > a.y) ? 1 : -1;

    int x = a.x;
    int y = a.y;

    int err = dx - dy;

    while (true)
    {
        framebuffer.SetBrightness(x, y, brightness);

        if (x == b.x && y == b.y)
            break;

        int e2 = err * 2;
        
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx) { err += dx; y += sy; }
    }
}

void Rasterizer::DrawTriangle(FrameBuffer& framebuffer, Vec2i a, Vec2i b, Vec2i c, uint8_t brightness)
{
    int minX = std::min({a.x, b.x, c.x});
    int maxX = std::max({a.x, b.x, c.x});
    int minY = std::min({a.y, b.y, c.y});
    int maxY = std::max({a.y, b.y, c.y});

    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, framebuffer.GetWidth() - 1);
    maxY = std::min(maxY, framebuffer.GetHeight() - 1);

    auto edge = [](const Vec2i& p0, const Vec2i& p1, int px, int py)
    {
        return (px - p0.x) * (p1.y - p0.y) - (py - p0.y) * (p1.x - p0.x);
    };

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            int w0 = edge(b, c, x, y);
            int w1 = edge(c, a, x, y);
            int w2 = edge(a, b, x, y);
 
            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0))
                framebuffer.SetBrightness(x, y, brightness);
        }
    }
}