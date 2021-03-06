/*********************************************************************
This is an Arduino library for our Monochrome SHARP Memory Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1393

These displays use SPI to communicate, 3 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
 
#include <Adafruit_GFX.h>
#include <avr/pgmspace.h>
#include "font-custom.c"

// LCD Dimensions
#define SHARPMEM_LCDWIDTH       (320)
#define SHARPMEM_LCDHEIGHT      (240)
#define BUFFER_HEIGHT           (100) 

class Adafruit_SharpMem : public Adafruit_GFX {
 public:
  Adafruit_SharpMem(uint8_t clk, uint8_t mosi, uint8_t ss);
  void begin(void);
  void clearDisplay();
  // void refresh(void);

  // DRAW functions load the right pixels into the buffer
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void drawTabs(void);
  void drawTabSettings(uint8_t position);
  void drawTime(uint8_t min, uint8_t sec);
  void drawNum(int16_t x, int16_t y, uint8_t num);
  void drawColon(int16_t x, int16_t y);
  void drawDenominator(void);
  // REFRESH functions draw buffer contents to the screen
  // at the appropriate locations
  void refresh(uint8_t section);
  void refreshTabs(void);
  void refreshTabSettings(void);
  void refreshSetValues(void);
  void refreshCentral(void);
  void refreshDenominator(void);
  
  // RENDER functions wrap draw + refresh. 
  // Use these.
  void renderTime(uint8_t min, uint8_t sec);
  void renderDepth(uint8_t deep, uint8_t shallow, uint8_t side);
  void renderLength(uint8_t len);
  void renderUnits(bool imp);

  void renderScreenPace(void);
  void renderScreenLength(void);
  void renderScreenDepth(uint8_t side);
  void renderScreenUnits(void);
  void renderScreenSwim(uint8_t laps);
  // void renderScreenPause(uint8_t seconds);

  // getters and setters
  uint8_t
    getPixel(uint16_t x, uint16_t y),
    getPaceMin(void),
    getPaceSec(void),
    // getBreakMin(void),
    // getBreakSec(void),
    getLength(void),
    getDepthShallow(void),
    getDepthDeep(void);


  bool getImperial(void);

  void
    setPaceMin(uint8_t min),
    setPaceSec(uint8_t sec),
    // setBreakMin(uint8_t min),
    // setBreakSec(uint8_t sec),
    setLength(uint8_t len),
    setDepthShallow(uint8_t dep),
    setDepthDeep(uint8_t dep),
    setImperial(bool imp);
  
  unsigned char toUC(uint8_t in);


 private:
  volatile uint8_t *dataport, *clkport;
  uint8_t
    _ss, _clk, _mosi,
    _sharpmem_vcom, datapinmask, clkpinmask,
    paceMin, paceSec,
    // breakMin, breakSec,
    length, depthShallow, depthDeep;
  bool imperial;

  void sendbyte(uint8_t data);
  void sendbyteLSB(uint8_t data);
};
