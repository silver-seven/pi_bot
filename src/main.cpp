#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <httpconnection.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IL19341.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <thread>
#include <fstream>
#include <vector>


#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{0x4D42}; // "BM"
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{0};    // Start of pixel data
};

struct BMPInfoHeader {
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bit_count{0};      // 24 for RGB
    uint32_t compression{0};
    uint32_t size_image{0};
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};
#pragma pack(pop)


void readBMP(char* filename, std::vector<uint8_t>& bmp, BMPFileHeader& fileHeader, BMPInfoHeader& infoHeader);
void readBMP(char* filename, std::vector<uint8_t>& bmp, BMPFileHeader& fileHeader, BMPInfoHeader& infoHeader) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) 
    {
      std::cout << "Invalid file" << std::endl;
      return;
    }

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // Jump to the pixel data
    file.seekg(fileHeader.offset_data, std::ios::beg);

    bmp.resize(infoHeader.size_image);
    file.read(reinterpret_cast<char*>(bmp.data()), bmp.size());

    std::cout << "Width: " << infoHeader.width << " Height: " << infoHeader.height << std::endl;
}


int main(int argc, char* argv[])
{

  // gfx.fillScreen(0x00)
  // wiringPiSPIDataRW(0, buffer, 1);
  // gfx.setRotation(1); // now canvas is 11x21
  // wiringPiSPIDataRW(0, buffer, 1);
  // gfx.fillCircle(5, 10, 5, 0xAA);
  if (argc <= 1)
  {
    std::cout << "Not enough arguments!" << std::endl;
    return 0;
  }

  Adafruit_ILI9341 device(320, 240, 0, 0, 0);
  device.reset();
  device.begin(0);
  device.setRotation(0);

  device.fillScreen(device.convertRGBto565(255, 0, 0));
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  device.fillScreen(ILI9341_BLACK);
  
  BMPFileHeader fileHeader;
  BMPInfoHeader infoHeader;
  std::vector<uint8_t> bmp;
  readBMP(argv[1], bmp, fileHeader, infoHeader);

  device.drawBitmap(0, 0, bmp.data(), infoHeader.width, infoHeader.height, ILI9341_BLACK, ILI9341_WHITE);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  device.reset();
  return 1;
}