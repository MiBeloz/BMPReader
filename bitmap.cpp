#include "bitmap.h"

Bitmap::Bitmap() {}

bool Bitmap::open(const char *fileName) {
    m_iStream.open(fileName, std::ios_base::binary);
    return m_iStream.is_open();
}

void Bitmap::read() {
    m_iStream.read(reinterpret_cast<char*>(&m_bmpFileHeader), sizeof(m_bmpFileHeader));
    if (m_bmpFileHeader.bfType != BMP_FORMAT) {
        throw std::runtime_error("Error! Unknown file format.");
    }

    m_iStream.read(reinterpret_cast<char*>(&m_bmpInfoHeader), sizeof(m_bmpInfoHeader));
    if (m_bmpInfoHeader.biBitCount != 24 && m_bmpInfoHeader.biBitCount != 32) {
        throw std::runtime_error("Error! The program can treat only 24 or 32 bits per pixel BMP files.");
    }

    m_iStream.seekg(m_bmpFileHeader.bfOffBits, m_iStream.beg);

    m_rowSize = (m_bmpInfoHeader.biWidth * m_bmpInfoHeader.biBitCount / 8);
    if (m_bmpInfoHeader.biWidth % 4 != 0) {
        while (m_rowSize % 4 != 0) {
            ++m_rowSize;
        }
    }

    m_data.resize(m_rowSize * m_bmpInfoHeader.biHeight);
    m_iStream.read(reinterpret_cast<char*>(m_data.data()), m_data.size());
    if (!colorCheck()) {
        throw std::runtime_error("Error! The file must be black and white.");
    }
}

void Bitmap::close() {
    m_data.clear();
    m_iStream.close();
}

void Bitmap::display() const {
    for (uint32_t y = m_bmpInfoHeader.biHeight - 1; y >= 0; --y) {
        for (uint32_t x = 0; x < m_bmpInfoHeader.biWidth; ++x) {
            uint32_t pixelIndex = y * m_rowSize + x * (m_bmpInfoHeader.biBitCount / 8);
            uint8_t blue = m_data[pixelIndex];
            uint8_t green = m_data[pixelIndex + 1];
            uint8_t red = m_data[pixelIndex + 2];

            if (blue == 0 && green == 0 && red == 0) {
                std::cout << 1;
            }
            else {
                std::cout << 0;
            }
        }
        std::cout << std::endl;
        if (y == 0) {
            break;
        }
    }
}

int32_t Bitmap::getWidth() const {
    return m_bmpInfoHeader.biWidth;
}

int32_t Bitmap::getHeight() const {
    return m_bmpInfoHeader.biHeight;
}

uint16_t Bitmap::getBitCount() const {
    return m_bmpInfoHeader.biBitCount;
}

bool Bitmap::colorCheck() const {
    for (uint32_t y = 0; y < m_bmpInfoHeader.biHeight; ++y) {
        for (uint32_t x = 0; x < m_bmpInfoHeader.biWidth; ++x) {
            uint32_t pixelIndex = y * m_rowSize + x * (m_bmpInfoHeader.biBitCount / 8);
            if (m_data[pixelIndex] != m_data[pixelIndex + 1] || m_data[pixelIndex + 1] != m_data[pixelIndex + 2]) {
                return false;
            }
        }
    }
    return true;
}
