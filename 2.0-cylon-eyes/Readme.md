# 03 - Cylon Eyes Scanner (ATmega328P)

## Project Overview
This project implements a classic "Cylon" or "Knight Rider" LED scanning animation. It demonstrates how to dynamically iterate through microcontroller hardware pins using loop variables and bitwise shifts, rather than hardcoding individual pin states.

## Core Engineering Concepts Demonstrated
* **Dynamic Bit-Shifting:** Utilizing a loop variable (`i`) in a bitwise shift (`1 << i`) to programmatically target sequential pins on a hardware port. 
* **Directional State Management:** Using nested `while` loops to manage the state and direction of the animation (scanning up the port, then scanning down).
* **Serial Pin Protection:** Explicitly constraining the loop bounds n(e.g., `i = 2` to `6`) to ensure the animation safely skips `PD0` and `PD1`, which are reserved for hardware UART/Serial communication.

## Hardware Specifications
* **Target MCU:** ATmega328P (16 MHz)
* **Components:** 6x 5mm LEDs, 6x 220Ω current-limiting resistors.
* **Pinout:** Output driven across pins `PD2` through `PD7` (Arduino Nano pins D2 through D7).
