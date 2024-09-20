#ifndef BITMAP_H
#define BITMAP_H

#include <windows.h>
#include <fstream>
#include <vector>
#include <iostream>

#define BMP_FORMAT 0x4D42

class Bitmap {
public:
    Bitmap();

    bool open(const char* fileName);

    void read();

    void close();

    void display() const;

    int32_t getWidth() const;

    int32_t getHeight() const;

    uint16_t getBitCount() const;

private:
    BITMAPFILEHEADER m_bmpFileHeader;
    BITMAPINFOHEADER m_bmpInfoHeader;
    std::ifstream m_iStream;
    std::vector<uint8_t> m_data;
    uint32_t m_rowSize = 0;

    bool colorCheck() const;
};

#endif // BITMAP_H
