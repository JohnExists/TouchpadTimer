![TOUCHPAD_TIMER](https://github.com/user-attachments/assets/33a8ab38-764d-46ab-b4f4-582e6c9b83c1)
## Introduction
This microcontroller project is a interactive timer where the user uses an aluminum foil touchpad to start, stop, or select timer length. The code for the timer and touchpad is present in the `main.c` `Timer.h` `Timer.c` `Touchpad.h` `Touchpad.c` files.
### Features
* Utilizes STM32-F44RE for Managing All Timer Functions and Operations
* Programming in C and utilizes the STM32 Hal Library
* Uses an aluminum foil as the touchpad for user input
  * Implemented an algorithm that detects user touch using Analog-To-Digital Conversion (ADC)
* Visual output through 7-segment displays and LEDs
* Audio output through passive buzzers

## Images
![unnamed](https://github.com/user-attachments/assets/3de334b8-2de8-4c10-b922-dbce483e2ab5)

## The Electronics Setup
To setup this project the following components are needed:
* STM32-F4XXX Microcontroller
* 7-Segment Display
* Passive Buzzer
* 1 500 Ohm Resistor
* 2 2k Ohm Resistors
* 1 LED
* 14 Jumper / DuPont Wires
* 3 Sheets of Aluminum Foil
* Any Sticky Tape

### How To Wire The Entire Project:

#### 1) Wire The Aluminum Foil
* Use tape to a attach 3 pieces of aluminum foil to a surface (ideally paper)
* Pull out 3 jumper wires, attach one end of each jumper wire to the STM32 microntroller and tape the other end to each aluminum foil
  * Attach the start/stop foil to A0, decrement timer to A1, increment timer to A4

### 2) Wire The Seven Segment Display
* Pull out 2 2k Ohm resistor and 7 jumper wires to connect the display to the micronctroller
* When wiring, use this configuration:
![7segment](https://github.com/user-attachments/assets/bd3aa2ff-7c7e-4ca9-9037-1ca0775d8efd)

### 3) Wiring the Buzzer
* Wire the cathode (the longer end) to the PB7 pin and the anode to ground

### 4) Wiring The LED
* Wire the cathode (the longer end) to the PB12 pin and the anode to ground
