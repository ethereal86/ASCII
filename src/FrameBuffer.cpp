#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height)
    : m_width(width), m_height(height)
{
    m_buffer = new uint8_t[static_cast<size_t>(width) * height];
    Clear();
}

FrameBuffer::~FrameBuffer()
{
    delete[] m_buffer;
}

void FrameBuffer::SetBrightness(int x, int y, uint8_t brightness)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;
 
    m_buffer[static_cast<size_t>(y) * m_width + x] = brightness;
}

uint8_t FrameBuffer::GetBrightness(int x, int y) const
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return 0;

    return m_buffer[static_cast<size_t>(y) * m_width + x];
}

void FrameBuffer::Clear(uint8_t brightness)
{
    size_t count = static_cast<size_t>(m_width) * m_height;

    for (size_t i = 0; i < count; i++)
        m_buffer[i] = brightness;
}