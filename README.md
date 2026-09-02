# Smart Building Security, Access Control & IoT Monitoring System

Embedded security system built on the LPC2129 (ARM7) microcontroller. Combines RFID and keypad-based access control, motion detection, automated door lock, event logging, and remote status reporting over CAN bus and Wi-Fi.

Developed as part of an embedded systems training project at **Vector India**.

## Features
- RFID (EM18) based access, with keypad password as backup
- PIR motion sensor to trigger monitoring
- Servo-controlled door lock (auto opens/closes on valid access)
- RTC (DS1307) timestamped event logging to EEPROM (AT24Cxx)
- 16x2 LCD + UART status output
- CAN bus messaging for access status
- Wi-Fi (ESP8266) upload of status to ThingSpeak

## Hardware Used
- LPC2129 (ARM7) microcontroller board
- EM18 RFID reader
- 4x4 matrix keypad
- Servo motor (door lock actuator)
- PIR motion sensor
- 16x2 LCD
- DS1307 RTC module
- AT24Cxx EEPROM
- ESP8266 Wi-Fi module
- CAN transceiver

## Tools
- Keil µVision (development/compilation)
- Flash Magic (flashing to board)

## File Structure
### main.c
Main control loop, access flow, sensor checks

### header.h
Shared type defs and function declarations

### uart_driver.c
UART0 init, tx/rx, string/int helpers

### i2c_driver.c
I2C init, read/write (used by RTC + EEPROM)

### lcd_driver.c
16x2 LCD init and display functions

### keypad_driver.c
4x4 keypad scan and password check

### rfid_driver.c
RFID card read and ID comparison

### servo_driver.c
PWM-based servo control (lock/unlock)

### pir_sensor.c
PIR motion detection and status display

### rtc_driver.c
DS1307 RTC read/write/display

### eeprom.c
Logs access events (time/date) to EEPROM

### can_driver.c
CAN1 init, tx/rx, status message send

### wifi_driver.c
ESP8266 AT commands, ThingSpeak upload

## How It Works
1. PIR sensor detects motion and wakes the system from monitoring mode
2. RFID is checked first (2 attempts); on failure, keypad password is checked (3 attempts)
3. On valid access, servo unlocks the door for a fixed duration, then re-locks
4. Every access attempt (granted or denied) is logged to EEPROM with timestamp
5. Access status is broadcast on the CAN bus and pushed to ThingSpeak over Wi-Fi

## Setup
1. Open the project in Keil µVision
2. Build the project
3. Flash the generated `.hex` file using Flash Magic
4. Power the board and connect peripherals as wired

## Author
**Yachcharesh**
Trainee ID: v25be8y2
Institute: Vector India
