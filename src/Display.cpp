#include "Display.h"

Display::Display(int width, int height, int fontSize, const wchar_t* fontName)
    : m_width(width), m_height(height), m_fontSize(fontSize)
    , m_screenBuffer(static_cast<size_t>(width) * height)
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
}

Display::~Display()
{
    if (m_hOriginalOutput)
        SetConsoleActiveScreenBuffer(m_hOriginalOutput);

    if (m_hOutput)
        CloseHandle(m_hOutput);
}

void Display::Present()
{
    COORD bufferSize = {(SHORT) m_width, (SHORT) m_height};
    COORD bufferCoord = {0, 0};
    SMALL_RECT writeRegion = {0, 0, (SHORT)(m_width - 1), (SHORT)(m_height - 1)};

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

    WriteConsoleOutputA(m_hOutput, m_screenBuffer.data(), bufferSize, bufferCoord, &writeRegion);
}

void Display::Clear(char c)
{
    for (auto& cell : m_screenBuffer)
    {
        cell.Char.AsciiChar = c;
        cell.Attributes = WhiteOnBlack;
    }
}

void Display::SetChar(int x, int y, char c)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;

    size_t i = static_cast<size_t>(y) * m_width + x;
    m_screenBuffer[i].Char.AsciiChar = c;
    m_screenBuffer[i].Attributes = WhiteOnBlack;
}