# Bare-Metal AVR Programming Portfolio

This repository tracks my progress learning professional, bare-metal embedded C programming for the AVR microcontroller family. 

Instead of using the beginner-friendly Arduino IDE, these projects interact directly with the hardware registers of the chip (Bitwise operations, direct port manipulation, hardware timers, etc.). 

This learning journey follows the concepts taught in Elliot Williams' book: *Make: AVR Programming*.

## The Hardware
All projects in this repository are written for and tested on:
* **Microcontroller:** ATmega328P
* **Board:** Arduino Nano V3.0 Clone (CH340 USB-to-Serial)
* **Clock Speed:** 16 MHz External Crystal

## Project Directory

*(Click on any project folder to see its specific code, wiring instructions, and documentation).*

* **[1.0-simple-blink](./1.0-simple-blink/)** - The "Hello World" of embedded C. Blinking the built-in LED (PB5) using direct port manipulation.
* **[1.1-sos-beacon](./1.1-sos-beacon/)** - A 6-LED emergency SOS beacon demonstrating loops, delays, and manipulating the entire `PORTD` register simultaneously.

## The Toolchain
These projects are compiled and flashed using the standard open-source AVR toolchain via the command line:
* `avr-gcc` (C Compiler)
* `avrdude` (Flashing software targeting the Arduino bootloader)
* `make` (Build automation)
