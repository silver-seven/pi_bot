#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <cstdint>
#include "Adafruit_GFX.h"

#define RPI_CS_PIN 8
#define RPI_RST_PIN 24
#define RPI_DC_PIN 25

class PiWiringSPIDriver : public Adafruit_GFX{

private:

public:

  PiWiringSPIDriver(int16_t w, int16_t h);
  void SPI_DC_LOW();
  void SPI_DC_HIGH();
  void SPI_CS_LOW();
  void SPI_CS_HIGH();
  void reset();
  void sendCommand(uint8_t commandByte, const uint8_t *dataBytes, uint8_t numDataBytes);
  void writeCommand(uint8_t commandByte);
  void SPI_WRITE16(uint16_t w);

  void drawPixel(int16_t x, int16_t y, uint16_t color) override;
  uint16_t convertRGBto565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
  }
  void startWrite() override {SPI_CS_LOW();};
  void endWrite() override {SPI_CS_HIGH();};
  virtual void setAddrWindow(uint16_t x, uint16_t y, uint16_t w,
                             uint16_t h) = 0;

};
