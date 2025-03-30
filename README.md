# Atari 2600 Keyboard Interface (WIP)

This project enables the connection of a PS/2 keyboard (or a USB keyboard that supports the PS/2 protocol) to the Atari 2600 or 7800 console. The ATmega328P processes keystrokes and controls the joystick inputs of the Atari 2600 accordingly.

## Features
- **PS/2 Keyboard Support**: Supports various keyboard layouts (DE, US, FR).
- **Direct ASCII Conversion**: Translates keystrokes into Atari 2600-compatible signals.
- **Configurable Keymaps**: Customizable key assignments for Atari 2600 control.
- **Efficient GPIO Usage**: Utilizes an 8-bit port for direct control.
- **Configurable DIP Switches**: 4-bit resistor-ladder circuit for easy configuration.

## Hardware Requirements
- **ATmega328P 5V 16Mhz (Arduino-compatible)**
- **PS/2 Keyboard**
- **Resistors for Resistor-Ladder (10kΩ, 20kΩ, 40kΩ, 80kΩ, 100kΩ Pull-up)**
- **8-bit bus transceiver (SN74LVC245AN)**
- **Joystick port connection for the Atari 2600**

## Circuit Diagram
![Breadboard Setup with one joystick forwarded](https://github.com/Al-Nafuur/Keyboard-2600/blob/main/docs/Breadboard_v1.png)


## Installation & Setup
1. **Upload code to ATmega328P** (via Arduino IDE or AVRDUDE).
2. **Connect PS/2 keyboard** to the corresponding pins.
3. **Set DIP switches** for the desired configuration.
4. **Connect to the Atari 2600 joystick port**.

## Usage
- Each keystroke on the PS/2 keyboard is translated into joystick controls for the Atari 2600.
- Modifier keys like `Shift`, `Ctrl`, and `Alt` influence the key output (e.g., uppercase/lowercase characters).
- DIP switches can be used to activate different keyboard layout (US,DE,FR) configurations.

## Known Issues & Solutions

## Credits
- Project discussion: [AtariAge Forum](https://forums.atariage.com/topic/380359-keyboard-interface-for-the-atari-2600/)
- Open-source libraries: PS/2 Keyboard Library (modified for this project)

## License
This project is licensed under the **MIT License** – free to use and modify.

---
If you have any questions or suggestions, feel free to open an issue on GitHub! 🎮

