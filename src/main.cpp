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
#include <BMPReader.h>

int main(int argc, char* argv[])
{

  if (argc <= 1)
  {
    std::cout << "Not enough arguments!" << std::endl;
    return 0;
  }

  Adafruit_ILI9341 device(320, 240, 0, 0, 0);
  device.reset();
  device.begin(0);
  device.setRotation(3);
  
  BMPReader::BMPReader bmpParser(argv[1]);

  for(int i=0; i<4; i++)
  {
    device.setRotation(i);
    device.drawRGBBitmap(0, 0, bmpParser.pixelData.data(), bmpParser.width, bmpParser.height);
  }  
  device.reset();
  return 1;
}