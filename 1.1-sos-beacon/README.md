# 02 - Multi-LED SOS Beacon (ATmega328P)

## Project Overview
An expanded bare-metal C application that drives a 6-LED array to transmit an automated SOS distress signal in Morse code. This project scales up the concepts from the basic blink project to demonstrate safe, simultaneous manipulation of multiple GPIO pins and timing logic.

## Core Engineering Concepts Demonstrated
* **Hardware Abstraction (Macros):** Extensively utilizing C preprocessor macros (`#define`) to abstract hardware-specific registers (e.g., `PORTD`, `DDRD`) and pin masks. This ensures the code is highly readable and easily portable to other AVR microcontrollers.
* **Non-Destructive Port Manipulation:** Employing Read-Modify-Write bitwise operations (`|=` and `&= ~`) to safely toggle 6 specific output pins simultaneously without inadvertently altering or destroying the state of neighboring serial communication pins (`PD0`, `PD1`).
* **Timing & Logic Control:** Implementing nested loops and conditional statments to translate timing requirements (Morse code dots, dashes, and gaps) into execution cycles.
* **DRY Build System Architecture:** Utilizing a shared, root-level `Makefile.common` imported via an `include` directive to prevent redundant build configurations across the repository.

## Hardware Specifications
* **Target MCU:** ATmega328P (16 MHz)
* **Components:** 6x 5mm LEDs, 6x 220Ω current-limiting resistors.
* **Pinout:** Output driven simultaneously across pins `PD2` through `PD7`.

## Quick Start
```bash
# Compile the source code into a .hex binary
make

# Compile and flash the firmware
make flash
