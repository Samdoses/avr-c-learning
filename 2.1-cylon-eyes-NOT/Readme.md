# 04 - Inverse Cylon Scanner (ATmega328P)

## Project Overview
A variation of the standard Cylon scanner that inverts the logical state. Instead of a single dot of light moving across a dark array, this firmware leaves the entire array illuminated and bounces a single "shadow" (a disabled LED) back and forth. 

## Core Engineering Concepts Demonstrated
* **Inverse Bitwise Masking:** Demonstrates advanced Read-Modify-Write techniques. It utilizes the bitwise NOT (`~`) operator in conjunction with AND (`&`) to safely punch a single "hole" (logic LOW) into a register full of logic HIGHs, without destructively overwriting the entire port.
* **State Initialization:** Setting a baseline logic state across multiple pins (`LED_PORT |= ALL_LEDS`) before entering the main event loop to establish the visual canvas.
* **Hardware Abstraction:** Continued use of C preprocessor macros to define the hardware port (`PORTD`) and pin mask, keeping the main loop clean and hardware-agnostic.

## Hardware Specifications
* **Target MCU:** ATmega328P (16 MHz)
* **Components:** 6x 5mm LEDs, 6x 220Ω current-limiting resistors.
* **Pinout:** Output driven across pins `PD2` through `PD7` (Arduino Nano pins D2 through D7).
