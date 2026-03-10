# 01 - Bare-Metal Blink (ATmega328P)

## Project Overview
This project is a foundational exercise in bare-metal embedded C programming, bypassing the standard Arduino hardware abstraction layer (HAL) to interact directly with the microcontroller's hardware registers. It toggles the built-in LED on an ATmega328P using direct port manipulation.

## Core Engineering Concepts Demonstrated
* **Direct Register Manipulation:** Interacting directly with the Data Direction Register (`DDRB`) to configure pin modes and the Port Data Register (`PORTB`) to control output states.
* **Bitwise Operations:** Utilizing bit-shifting (`1 << PB5`) to target specific hardware pins.
* **Build Automation:** Implementing a modular `Makefile` build system using `avr-gcc` and `avrdude` to compile and flash the `.hex` binary directly to the target hardware.

## Hardware Specifications
* **Target MCU:** ATmega328P (16 MHz)
* **Development Board:** Arduino Nano V3.0 (CH340)
* **Pinout:** Built-in LED connected to `PB5` (Digital Pin 13)

## Quick Start
```bash
# Compile the source code into a .hex binary
make

# Flash the binary to the microcontroller via USB
make flashd
