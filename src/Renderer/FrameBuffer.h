#pragma once

class FrameBuffer
{
public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();

    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer& operator=(const FrameBuffer&) = delete;
    
    void Clear(uint8_t brightness = 0);

    void SetBrightness(int x, int y, uint8_t brightness);
    uint8_t GetBrightness(int x, int y) const;

    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }  
    inline const uint8_t* GetData() const { return m_data; }

private:
    int m_width;
    int m_height;

    uint8_t* m_data;
};