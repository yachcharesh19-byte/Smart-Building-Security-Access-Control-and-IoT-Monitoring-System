Smart Building Security, Access Control & IoT Monitoring System
Project Overview
Embedded security system built on the LPC2129 (ARM7) microcontroller, combining RFID and keypad-based access control, motion detection, automated door locking, event logging, and remote status reporting through CAN bus and Wi-Fi.

Features
RFID (EM18) based access control, with keypad password as backup
PIR motion sensor for monitoring and motion detection
Servo-controlled door lock with automatic opening and closing
RTC (DS1307) timestamped event logging to EEPROM (AT24Cxx)
16x2 LCD for system status display
UART status output
CAN bus messaging for access status
ESP8266 Wi-Fi connectivity for uploading data to ThingSpeak
Hardware Used
LPC2129 (ARM7) Microcontroller Board
EM18 RFID Reader
4x4 Matrix Keypad
Servo Motor – Door Lock Actuator
PIR Motion Sensor
16x2 LCD
DS1307 RTC Module
AT24Cxx EEPROM
ESP8266 Wi-Fi Module
CAN Transceiver
Tools Used
Keil µVision – Development and Compilation
Flash Magic – Flashing the .hex file to the microcontroller
File Structure
main.c – Main control loop, access flow, and sensor checks
header.h – Shared type definitions and function declarations
uart_driver.c – UART0 initialization, TX/RX, string and integer helpers
i2c_driver.c – I2C initialization and read/write functions for RTC and EEPROM
lcd_driver.c – 16x2 LCD initialization and display functions
keypad_driver.c – 4x4 keypad scanning and password verification
rfid_driver.c – RFID card reading and ID comparison
servo_driver.c – PWM-based servo control for locking/unlocking
pir_sensor.c – PIR motion detection and status display
rtc_driver.c – DS1307 RTC read, write, and display functions
eeprom.c – Access-event logging with date and time
can_driver.c – CAN1 initialization, transmission, reception, and status messaging
wifi_driver.c – ESP8266 AT commands and ThingSpeak data upload
How It Works
PIR sensor detects motion and wakes the system from monitoring mode.
The system checks the RFID card first, allowing 2 attempts.
If RFID authentication fails, the system requests the keypad password, allowing 3 attempts.
On valid authentication, the servo unlocks the door for a fixed duration.
After the specified duration, the door automatically re-locks.
Every access attempt, whether granted or denied, is recorded in EEPROM with an RTC timestamp.
The access status is transmitted through the CAN bus.
The system also uploads the status remotely to ThingSpeak through ESP8266 Wi-Fi.
Setup
Open the project in Keil µVision.
Build and compile the project.
Generate the .hex file.
Flash the .hex file to the LPC2129 using Flash Magic.
Connect the required peripherals according to the hardware wiring.
Power on the board and test the security system.
Author
Name: yachcharesh
Trainee ID: v25be8y2
Institute: Vector India
