#pragma once

#include <vector>
#include <cstdint>

class FrameBuffer
{
public:
    FrameBuffer(int width, int height);

    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer& operator=(const FrameBuffer&) = delete;

    void SetBrightness(int x, int y, uint8_t brightness);
    
    void Clear(uint8_t brightness = 0);

    inline const uint8_t* GetBuffer() const { return m_buffer.data(); }

private:
    int m_width;
    int m_height;

    std::vector<uint8_t> m_buffer;
};