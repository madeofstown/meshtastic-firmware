#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define USB_VID 0x2886
#define USB_PID 0x0059

// Default SPI is mapped to the E22/SX1262 so the Arduino SPI bus the SerialHal
// device handler drives matches the radio wiring.
static const uint8_t MISO = 8;
static const uint8_t SCK = 7;
static const uint8_t MOSI = 9;
static const uint8_t SS = 5;

#endif /* Pins_Arduino_h */
