/*
 * XiaoWow ESP32-S3 as a SerialHal *device* (radio proxy).
 *
 * Companion-modem half of upstream PR #10351: the ESP32 runs a normal Meshtastic
 * build with HAS_SERIAL_HAL_DEVICE compiled in and serial_hal_only set, so it
 * does NOT run its own mesh stack. Instead it answers SPI/GPIO/interrupt frames
 * from a native meshtasticd host over USB-CDC serial, driving the on-board
 * Ebyte E22-900M30S (SX1262). The host's SerialHal (platform/portduino/SerialHal)
 * is the other half.
 *
 * Radio pin map is taken verbatim from the user's known-good standalone XiaoWow
 * ESP32-S3 firmware (confirmed running on their network): SCK=7, MISO=8, MOSI=9,
 * CS=5, RESET=3, DIO1(IRQ)=2, DIO2(BUSY)=4, RXEN=6, TXEN=NC, DIO2 RF-switch,
 * DIO3 TCXO 1.8V. Every pin is #ifndef-guarded so it can be overridden from
 * platformio.ini build_flags without editing this file.
 *
 * This variant is intentionally lean (no GPS, no display, no battery sense):
 * a dumb radio proxy does not need them, and skipping them cuts boot time and
 * power. The device handler only needs the SPI bus + the GPIO lines below.
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
#define LORA_DIO1 2 // SX1262 IRQ
#endif
#ifndef LORA_DIO2
#define LORA_DIO2 4 // SX1262 BUSY
#endif
#ifndef LORA_RXEN
#define LORA_RXEN 6
#endif

#define USE_SX1262

#ifdef USE_SX1262
#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY LORA_DIO2
#define SX126X_RESET LORA_RESET

// DIO2 drives the antenna switch; DIO3 supplies the TCXO rail (1.8 V).
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_RXEN LORA_RXEN
#define SX126X_TXEN RADIOLIB_NC
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#endif
