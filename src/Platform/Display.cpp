#include <pch.h>
#include "Display.h"

Display::Display(int width, int height, int fontSize, const wchar_t* fontName, const char* title)
    : m_width(width), m_height(height), m_fontSize(fontSize)
{
    m_hOriginalOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    m_hOutput = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    SetConsoleActiveScreenBuffer(m_hOutput);

    m_screenBuffer = new CHAR_INFO[static_cast<size_t>(width) * height];

    SMALL_RECT windowRect = {0, 0, 1, 1};
    SetConsoleWindowInfo(m_hOutput, TRUE, &windowRect);

    COORD bufferSize = {(SHORT) width, (SHORT) height};
    SetConsoleScreenBufferSize(m_hOutput, bufferSize);

    windowRect = {0, 0, (SHORT)(width - 1), (SHORT)(height - 1)};
    SetConsoleWindowInfo(m_hOutput, TRUE, &windowRect);

    CONSOLE_FONT_INFOEX cfi = {};
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    cfi.dwFontSize.X = fontSize;
    cfi.dwFontSize.Y = fontSize;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, fontName);
    SetCurrentConsoleFontEx(m_hOutput, FALSE, &cfi);

    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(m_hOutput, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(m_hOutput, &cci);

    HWND hWnd = GetConsoleWindow();
    m_originalStyle = GetWindowLong(hWnd, GWL_STYLE);
    LONG style = m_originalStyle;
    style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX | WS_VSCROLL | WS_HSCROLL);
    SetWindowLong(hWnd, GWL_STYLE, style);
    SetWindowPos(hWnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    SetConsoleTitleA("ASCII 3D");
}

Display::~Display()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, m_originalStyle);

    if (m_hOriginalOutput)
        SetConsoleActiveScreenBuffer(m_hOriginalOutput);

    if (m_hOutput)
        CloseHandle(m_hOutput);

    delete[] m_screenBuffer;
}

void Display::Present(const uint8_t* framebuffer)
{
    size_t count = static_cast<size_t>(m_width) * m_height;

    for (size_t i = 0; i < count; i++)
    {
        int rampIndex = 1 + (framebuffer[i] - 1) * 6 / 254;
        if (framebuffer[i] == 0) rampIndex = 0;
        if (framebuffer[i] == 255) rampIndex = 7;

        m_screenBuffer[i].Char.AsciiChar = Ramp[rampIndex];
        m_screenBuffer[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }

    COORD bufferSize = {(SHORT) m_width, (SHORT) m_height};
    COORD bufferCoord = {0, 0};
    SMALL_RECT writeRegion = {0, 0, (SHORT)(m_width - 1), (SHORT)(m_height - 1)};

    WriteConsoleOutputA(m_hOutput, m_screenBuffer, bufferSize, bufferCoord, &writeRegion);

    CONSOLE_FONT_INFOEX fontInfo = {};
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx(m_hOutput, FALSE, &fontInfo);
 
    if ((fontInfo.dwFontSize.X != m_fontSize) || (fontInfo.dwFontSize.Y != m_fontSize))
    {
        SetConsoleScreenBufferSize(m_hOutput, bufferSize);
        SetConsoleWindowInfo(m_hOutput, TRUE, &writeRegion);

        fontInfo.dwFontSize.X = m_fontSize;
        fontInfo.dwFontSize.Y = m_fontSize;
        fontInfo.FontFamily = FF_DONTCARE;
        
        SetCurrentConsoleFontEx(m_hOutput, FALSE, &fontInfo);   
    }
}