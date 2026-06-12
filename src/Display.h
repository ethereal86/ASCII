#pragma once

#include <vector>
#include <windows.h>

class Display
{
public:
    Display(int width, int height, int fontSize, const wchar_t* fontName);
    ~Display();

    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;

    void Present();
    void Clear(char c = ' ');
    void SetChar(int x, int y, char c);

private:
    static constexpr WORD WhiteOnBlack = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; 

    HANDLE m_hOutput = nullptr;
    HANDLE m_hOriginalOutput = nullptr;

    int m_width;
    int m_height;

    int m_fontSize;

    std::vector<CHAR_INFO> m_screenBuffer;
};