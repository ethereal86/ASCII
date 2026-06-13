#pragma once

#include <cstdint>
#include <windows.h>

class Display
{
public:
    Display(int width, int height, int fontSize, const wchar_t* fontName);
    ~Display();

    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;

    void Present(const uint8_t* framebuffer);

private:
    static constexpr char Ramp[] = " .-~=c#@";
    static constexpr int RampLength = sizeof(Ramp) - 1;

    HANDLE m_hOutput = nullptr;
    HANDLE m_hOriginalOutput = nullptr;

    int m_width;
    int m_height;

    int m_fontSize;

    CHAR_INFO* m_screenBuffer;
};