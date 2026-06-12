#include "Display.h"

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

    while (true)
    {
        frameBuffer.Clear();

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                frameBuffer.SetBrightness(x, y, 8.0f / WIDTH * x);
            }
        }
        display.Present(frameBuffer);
    }
    SetWindowLong(hWnd, GWL_STYLE, originalStyle);

    return 0;
}