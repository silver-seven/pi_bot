#include <BMPReader.h>
#include <iostream>

namespace BMPReader {

void BMPReader::read16BitBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file." << std::endl;
        return;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (infoHeader.bit_count != 16) {
        std::cerr << "Error: Not a 16-bit BMP. BPP is: " << infoHeader.bit_count << std::endl;
        return;
    }

    width = infoHeader.width;
    height = std::abs(infoHeader.height); // Height can be negative for top-down
    
    // BMP rows are padded to 4-byte boundaries
    // For 16-bit (2 bytes per pixel), the row size in bytes is:
    int rowSize = ((width * 16 + 31) / 32) * 4;
    int padding = rowSize - (width * 2);

    pixelData.reserve(width * height);

    file.seekg(fileHeader.offset_data, std::ios::beg);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uint16_t pixel;
            file.read(reinterpret_cast<char*>(&pixel), 2);
            pixelData.push_back(pixel);
        }
        // Skip the padding bytes at the end of the row
        if (padding > 0) {
            file.seekg(padding, std::ios::cur);
        }
    }
}
}