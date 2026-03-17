# 05 - Oscillating Binary Counter (ATmega328P)

## Project Overview
A bare-metal embedded C application that transforms a 6-LED array into an oscillating 6-bit binary counter. The program continuously counts up from 0 to 63, and then smoothly counts back down to 1. 

## Core Engineering Concepts Demonstrated
* **Hardware Alignment via Bit-Shifting:** Utilizing variable bit-shifting (`i << 2`) to dynamically align a 0-indexed logical counter with physical hardware pins that begin at `PD2`.
* **Hardware State Protection:** Enforcing Read-Modify-Write protocols (`|=` and `&= ~`) across dynamic variable states to guarantee that the hardware UART/Serial pins (`PD0`, `PD1`) remain completely undisturbed by the counter's logic.
* **Boundary Condition Logic:** Carefully calculating `while` loop boundaries (0 to 62, then 63 to 1) to create a continuous, smooth triangular wave effect without stalling or "double-counting" at the peaks of the oscillation.
* **Hardware Abstraction:** Continued use of C preprocessor macros to define the hardware port (`PORTD`) and pin mask, keeping the main event loop clean and highly readable.

## Hardware Specifications
* **Target MCU:** ATmega328P (16 MHz)
* **Components:** 6x 5mm LEDs, 6x 220Ω current-limiting resistors.
* **Pinout:** Output driven across pins `PD2` through `PD7` (Arduino Nano pins D2 through D7).
