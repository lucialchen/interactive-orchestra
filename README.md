# Interactive Orchestra

## Overview
This project transforms an unused decorative wall piece into an interactive musical interface. The object, which features multiple musical instruments, is modified with copper touch sensors so that each instrument can be played through physical interaction.

The system uses an ESP32 to detect touch input and communicates with a laptop-based program via serial connection to trigger corresponding sound effects. A secondary touch sensor functions as a mode switch, allowing users to toggle between discrete playback and looping composition modes.

## Materials and Components

### Hardware
- LILYGO TTGO T1 ESP32
- Copper tape
- Breadboard
- Solid core wire 
- Decorative object (used as interface)
- USB cable
- Soldering tools

### Software
- Arduino development environment (PlatformIO on VS Code recommended) 
- Web serial communication
- Computer with control program for audio playback


## System Architecture
1. Copper tape pads act as touch sensors connected to ESP32 touch pins through the breadboard.  
2. ESP32 detects touch events and sends signals via serial communication.
3. A computer connected to the ESP32 via USB-C receives the signals and maps them to audio playback.
4. Mode selection determines whether sounds are played once or looped.  

## Installation and Setup

### 1. Hardware Assembly
- Attach copper tape to each place where you want a sensor on the decorative object  
- Connect each copper sensor to a capacitive touch pin on the ESP32  
- Solder wires to the copper tape 
- Connect all components through a breadboard  

### 2. Software Setup
- Create a new PlatformIO project for the TTGO T1 board
- Copy the provided `main.cpp` into the `/src` folder of the project  
- Upload the code to the ESP32
- Install any required dependencies (e.g., `pyserial`, audio libraries if used)
- Place `play.py` on your computer and ensure it has access to the audio files used for playback  
- Update the serial port in `play.py` to match your ESP32 connection  
- Run play.py to start the program; Ctrl+C to quit


## Usage
1. Connect the ESP32 to your computer via USB  
2. Start the `play.py` program
3. Interact with the copper touch sensors:
   - Touch a copper sensor to trigger its sound  
   - Touch the mode switch to toggle between playback and loop modes  
4. In loop mode, layer multiple instruments to create compositions  


## Reproducibility Notes
- Touch sensitivity may vary depending on the size of the copper tape sensors; adding extra solder near spots where the sensors are less effective is recommended
