/*
 * XiaoWow ESP32-S3 as a SerialHal *device* (radio proxy).
 *
 * This is the companion-modem half of upstream PR #10351: the ESP32 runs a
 * normal Meshtastic build with HAS_SERIAL_HAL_DEVICE compiled in and
 * serial_hal_only set, so it does NOT run its own mesh stack. Instead it
 * answers SPI/GPIO/interrupt frames from a native meshtasticd host over USB-CDC
 * serial, driving the on-board Ebyte E22-900M30S (SX1262). The host's
 * SerialHal (platform/portduino/SerialHal.cpp) is the other half.
 *
 * PIN MAP PROVISIONAL: these GPIOs are taken from the madeofstown
 * xiaowow_esp32s3 variant and still need to be confirmed against the real
 * XiaoWow ESP32-S3 schematic. Every pin is #ifndef-guarded so it can be
 * overridden from platformio.ini build_flags (e.g. -DSX126X_CS_PIN=5) without
 * editing this file once the correct map is known.
 */

// ---- Radio SPI bus (ESP32-S3 native SPI) ----
#ifndef LORA_SCK
#define LORA_SCK 7
#endif
#ifndef LORA_MISO
#define LORA_MISO 8
#endif
#ifndef LORA_MOSI
#define LORA_MOSI 9
#endif
#ifndef LORA_CS
#define LORA_CS 5
#endif

// ---- SX1262 control lines ----
#ifndef LORA_RESET
#define LORA_RESET 3
#endif
#ifndef LORA_DIO1
#define LORA_DIO1 2
#endif
#ifndef LORA_BUSY
#define LORA_BUSY 4
#endif
#ifndef LORA_RXEN
#define LORA_RXEN 6
#endif

#define USE_SX1262

#ifdef USE_SX1262
#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY LORA_BUSY
#define SX126X_RESET LORA_RESET

// DIO2 drives the antenna switch; DIO3 supplies the TCXO rail (1.8 V).
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_RXEN LORA_RXEN
#define SX126X_TXEN RADIOLIB_NC
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#endif

// No screen, no GPS, no battery sense: this board is a dumb radio proxy.
// The SerialHal device handler only needs the SPI bus + the GPIO lines above.
