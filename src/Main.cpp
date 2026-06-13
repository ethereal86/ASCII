#include <pch.h>
#include "Platform/Display.h"

#include "Renderer/Rasterizer.h"
#include "Renderer/Viewport.h"

#define WIDTH 80
#define HEIGHT 60

int main(int argc, char* argv[])
{
    Display display(WIDTH, HEIGHT, 14, L"Cascadia Mono", "ASCII 3D");
    FrameBuffer framebuffer(WIDTH, HEIGHT);

    Viewport viewport;
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = WIDTH;
    viewport.height = HEIGHT;

    Vec3f vertices[] =
    {
        {-0.5f, 0.5f, 0.0f},
        {0.5f, 0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {-0.5f, -0.5f, 0.0f}
    };

    float t = 0.0;
    while (true)
    {
        framebuffer.Clear();

        Mat4 modelMat = Mat4::RotateZ(t) * Mat4::RotateX(t) * Mat4::RotateY(t);
        
        Vec2i screenVerts[4];
        for (int i = 0; i < 4; i++)
        {
            Vec4f clip = modelMat * Vec4f(vertices[i], 1.0f);
            screenVerts[i] = viewport.Transform(clip.PerspectiveDivide());
        }
        Rasterizer::DrawTriangle(framebuffer, screenVerts[0], screenVerts[1], screenVerts[2], 255);
        Rasterizer::DrawTriangle(framebuffer, screenVerts[0], screenVerts[2], screenVerts[3], 128);

        display.Present(framebuffer.GetData());

        t += 0.001;
    }

    return 0;
}