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

    while (true)
    {
        display.Clear('.');
    
        bool b = true;
        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                if (b) display.SetChar(x, y, '@');
                b = !b;
            }
            b = !b;
        }

        display.Present();
    }
    SetWindowLong(hWnd, GWL_STYLE, originalStyle);

    return 0;
}