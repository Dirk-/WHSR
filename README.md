# WHSR

![alt text](https://github.com/Dirk-/WHSR/blob/master/images/WHSR1.0.png "WHSR v1.0")

Firmware for an educational robot of Westfälische Hochschule (Westphalian University of Applied Sciences, Gelsenkirchen, Germany). The WHSR ("Wizzer") is a successor for the ASURO robot at our university. It has similar but enhanced features compared to the ASURO, such as Arduino Nano or Maple Mini compatibility and Bluetooth connection.

## Info

The Library works for the plain Arduino Nano board (avr), Arduino Nano 33 BLE (mbed) support is in the making.

## Installation

- Select `Download ZIP` from the GitHub `Code` button. Unzip the archive if it isn't already. You will end up with a folder `WHSR-master` in your download folder. 
- Rename that folder to `WHSR`.
- Move it to `Arduino/libraries` in your documents folder.
- Restart Arduino IDE.

For Arduino Nano:
- In the `Tools` menu, select Board `Arduino Nano` from `Arduino AVR Boards`, Processor `ATmega328P (Old Bootloader)`, Port `/dev/cu.usb.serial-142310` (or similar).

For Arduino Nano 33 BLE:
- In the `Tools` menu, select Board `Arduino Nano 33 BLE` from `Arduino Mbed OS Boards`, Port `/dev/cu.usbmodem-1423401 (Arduino Nano 33 BLE)` (or similar).

## TODO

Arduino Nano 33 BLE support:
- Line follower works
- Status LED works
- Switches work
- Motors just drive forward
- Interrupts do not work
- Odometry does not work
- Ambient light works
- Distance sensors work

Documentation

## Hints

- The F() macro used in the DebugSerial_print statements is for saving RAM (https://www.baldengineer.com/arduino-f-macro.html)

## Credits

Library written by Maximilian Richter, based on the [ASURINO library](https://github.com/Dirk-/Asurino-Library) for the ASURO robot.
