#include "Display.h"
#include "Rasterizer.h"

#define WIDTH 72
#define HEIGHT 54

int main(int argc, char* argv[])
{
    SetConsoleTitleA("ASCII 3D");

    HWND hWnd = GetConsoleWindow();
    LONG originalStyle = GetWindowLong(hWnd, GWL_STYLE);
    LONG style = originalStyle;
    style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX | WS_VSCROLL | WS_HSCROLL);
    SetWindowLong(hWnd, GWL_STYLE, style);
    SetWindowPos(hWnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    Display display(WIDTH, HEIGHT, 14, L"Cascadia Mono");
    FrameBuffer frameBuffer(WIDTH, HEIGHT);

    Viewport viewport;
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = WIDTH;
    viewport.height = HEIGHT;

    vec3 vertices[] =
    {
        {0.2f, 0.7f, 0.0f},
        {-0.3f, -0.3f, 0.0f},
        {0.7f, -0.3f, 0.0f},

        {0.0f, 0.5f, 0.0f},
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f}
    };

    while (true)
    {
        frameBuffer.Clear();
        
        for (size_t i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i += 3)
        {
            Rasterizer::DrawTriangle(frameBuffer,
                viewport.Transform(vertices[i]), 
                viewport.Transform(vertices[i + 1]),
                viewport.Transform(vertices[i + 2]),
                i < 3 ? 64 : 255
            );
        }

        display.Present(frameBuffer.GetData());
    }
    SetWindowLong(hWnd, GWL_STYLE, originalStyle);

    return 0;
}