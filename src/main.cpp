#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
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

int main(int argc, char* argv[])
{

  // gfx.fillScreen(0x00)
  // wiringPiSPIDataRW(0, buffer, 1);
  // gfx.setRotation(1); // now canvas is 11x21
  // wiringPiSPIDataRW(0, buffer, 1);
  // gfx.fillCircle(5, 10, 5, 0xAA);

  Adafruit_ILI9341 device(0, 0, 0);
  device.reset();
  device.begin(0);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  device.setAddrWindow(5, 5, 25, 25);
  device.fillScreen(device.convertRGBto565(255, 0, 0));
  device.invertDisplay(true);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  device.invertDisplay(false);
  device.reset();
  
}