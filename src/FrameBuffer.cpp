#include "Framebuffer.h"

FrameBuffer::FrameBuffer(int width, int height)
    : m_width(width), m_height(height)
    , m_buffer(static_cast<size_t>(width) * height, 0)
{
}

void FrameBuffer::SetBrightness(int x, int y, uint8_t brightness)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;
 
    m_buffer[static_cast<size_t>(y) * m_width + x] = brightness;
}

void FrameBuffer::Clear(uint8_t brightness)
{
    std::fill(m_buffer.begin(), m_buffer.end(), brightness);
}