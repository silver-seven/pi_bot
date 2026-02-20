#include "PiWiringSPIDriver.h"
#include <cstring>
#include <thread>
#include <chrono>
#include <iostream>

PiWiringSPIDriver::PiWiringSPIDriver(int16_t w, int16_t h)
: Adafruit_GFX(w, h)
{
  wiringPiSetupPinType(WPI_PIN_BCM);
  pinMode(RPI_CS_PIN, OUTPUT);
  pinMode(RPI_RST_PIN, OUTPUT);
  pinMode(RPI_DC_PIN, OUTPUT);
  digitalWrite(RPI_RST_PIN, LOW);
  digitalWrite(RPI_CS_PIN, HIGH);
  digitalWrite(RPI_DC_PIN, HIGH);
  wiringPiSPISetup(0, 24000000);
}

void PiWiringSPIDriver::SPI_DC_LOW() // Command mode
{
  digitalWrite(RPI_DC_PIN, LOW);
}

void PiWiringSPIDriver::SPI_DC_HIGH()
{
  digitalWrite(RPI_DC_PIN, HIGH);
}

void PiWiringSPIDriver::SPI_CS_LOW()
{
  digitalWrite(RPI_CS_PIN, LOW);
}

void PiWiringSPIDriver::SPI_CS_HIGH()
{
  digitalWrite(RPI_CS_PIN, HIGH);
}

void PiWiringSPIDriver::reset()
{
  digitalWrite(RPI_RST_PIN, HIGH);
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  digitalWrite(RPI_RST_PIN, LOW);
}

void PiWiringSPIDriver::sendCommand(uint8_t commandByte, const uint8_t *dataBytes,
                                  uint8_t numDataBytes) {
  // SPI_BEGIN_TRANSACTION();
  SPI_CS_LOW();

  uint8_t buf[numDataBytes];
  std::memcpy(buf, dataBytes, numDataBytes);   
  // std::cout << "Start sendCommand: " << std::hex << static_cast<int>(commandByte);                                
  SPI_DC_LOW();          // Command mode
  wiringPiSPIDataRW(0, &commandByte, 1); // Send the command byte
  SPI_DC_HIGH();

  // std::cout << "Before Send numDataBytes: "; 
  // printArr(buf, numDataBytes);                                   
  // std::cout << "After Send numDataBytes: "; 
  wiringPiSPIDataRW(0, buf, numDataBytes);
  // printArr(buf, numDataBytes);    


  SPI_CS_HIGH();
  // SPI_END_TRANSACTION();
}

void PiWiringSPIDriver::writeCommand(uint8_t commandByte) 
{                             
  SPI_DC_LOW();          // Command mode
  wiringPiSPIDataRW(0, &commandByte, 1); // Send the command byte
  SPI_DC_HIGH();
}

void PiWiringSPIDriver::SPI_WRITE16(uint16_t w)
{
  uint8_t buf = (uint8_t)(w >> 8);
  wiringPiSPIDataRW(0, &buf, 1);
  buf = (uint8_t)w; 
  wiringPiSPIDataRW(0, &buf, 1);
}

void PiWiringSPIDriver::drawPixel(int16_t x, int16_t y, uint16_t color) {
  // Clip first...
  if ((x >= 0) && (x < _width) && (y >= 0) && (y < _height)) {
    // THEN set up transaction (if needed) and draw...
    SPI_CS_LOW();
    setAddrWindow(x, y, 1, 1);
    SPI_WRITE16(color);
    SPI_CS_HIGH();
  }
}

//helper
void printArr(uint8_t* data, uint8_t len)
{
  for(int i=0; i<len; i++)
  {
    std::cout << std::hex << static_cast<int>(data[i]) << " ";
  }
  std::cout << std::endl;
}
