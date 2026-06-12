#pragma once

#include <windows.h>

#include "FrameBuffer.h"

class Display
{
public:
    Display(int width, int height, int fontSize, const wchar_t* fontName);
    ~Display();

    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;

    void Present(const FrameBuffer& frameBuffer);

private:
    static constexpr char Ramp[] = " .-~=c#@";
    static constexpr int RampLength = sizeof(Ramp) - 1;

    HANDLE m_hOutput = nullptr;
    HANDLE m_hOriginalOutput = nullptr;

    int m_width;
    int m_height;

    int m_fontSize;

    std::vector<CHAR_INFO> m_screenBuffer;
};