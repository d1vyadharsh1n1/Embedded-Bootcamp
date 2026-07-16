# Embedded Systems Bootcamp (8051)

A structured collection of work completed during an Embedded Systems Bootcamp. This repository documents concepts, experiments, hardware interfacing, and projects using the **AT89S52 (8051) Microcontroller**.

---

## Software Used

- Keil µVision 5 (IDE & Compiler)
- ProgISP (Flash Programming)

---

## Topics Covered

- 8051 Architecture
- GPIO Programming
- LED Blinking
- Timers
- Interrupts
- External Memory
- RTC Interface
- LCD Interface
- Matrix Keypad
- UART Serial Communication
- External Peripherals
- Seven Segment Display
- Hardware Schematics

---

## Repository Structure

- [Day 1](#day-1)
- [Day 2](#day-2)
- [Day 3](#day-3)
- [Day 4](#day-4)
  - [External Memory](Day_4/External_Memory/README.md)
  - [RTC](Day_4/RTC/ReadMe.md)
- [Day 5](#day-5)
  - [Timers](Day_5/Timers/README.md)
  - [Serial Communication](Day_5/Serial_Communication/README.md)
- [Day 6](#day-6)
  - [Interrupts](Day_6/Interrupt/README.md)
  - [Keypad Interfacing](Day_6/Keypad_Interfacing/README.md)
  - [LCD Interfacing](Day_6/LCD_Interfacing/README.md)
- [Day 7](#day-7)
  - [LCD Implementation](Day_7/LCD_Implementation/lcd_alphabets.c)
- [Day 8](#day-8)
  - [Schematic Diagram](Day_8/Schematic_Diagram/README.md)
- [Day 9](#day-9)
  - [External Peripherals](Day_9/External_Peripherals/README.md)
  - [LED Fading](Day_9/LED_fading/led_fading.c)
  - [Seven Segment Display](Day_9/Seven_Segment/README.md)
- [README.md](#README.md)

---

## Folder Contents

Each topic generally contains:

- README.md
  - Theory
  - Register explanation
  - Circuit description
  - Working principle
  - Observations

- Source Code (.c)

- Keil Project (.uvproj)

---

## Programming Workflow

1. Write the program in **Keil µVision 5**.
2. Build the project to generate the **HEX** file.
3. Connect the **AT89S52 Development Board** to the computer using the **ISP (In-System Programming) header**.
4. Open **ProgISP**.
5. Select the appropriate programmer and target device.
6. Load the generated **.hex** file.
7. Click **Auto** or **Program** to flash the firmware.
8. Wait for the programming to complete successfully.
9. Reset the board (if required) and verify the output.
