# LCD

Earlier embedded systems mainly used LEDs and seven-segment displays. As technology improved, LCDs became the preferred choice due to several advantages.

---

# LCD Pin Description

A standard **16×2 LCD** has **14 pins** (or **16 pins** if backlight pins are included). Each pin performs a specific function.

## Pin 1 – VSS (Ground)

* This pin is connected to **0V (Ground)**.
* It completes the electrical circuit and acts as the reference voltage for the LCD.

---

## Pin 2 – VCC/VDD

* This pin supplies **+5V** to power the LCD module.
* Without this supply, the LCD will not function.

---

## Pin 3 – VEE/V0 (Contrast Control)

* This pin controls the contrast of the display.
* It is usually connected to the middle terminal of a **10 kΩ potentiometer**.
* Rotating the potentiometer changes the voltage at VEE, which adjusts the darkness of the displayed characters.

If the contrast is set incorrectly:

* Characters may become invisible.
* The screen may appear completely black.

---

## Pin 4 – RS (Register Select)

The LCD contains two internal registers:

### Command Register

Stores commands that control the LCD.

Examples:

* Clear display
* Move cursor
* Turn display ON/OFF
* Shift display

**To access the command register:** `RS = 0`

### Data Register

Stores the actual data (ASCII characters) that should appear on the screen.

Example:

* If the microcontroller sends the ASCII value for **'A'**, the LCD displays **A**.

**To access the data register:** `RS = 1`

---

## Pin 5 – R/W (Read/Write)

This pin determines whether the microcontroller reads from or writes to the LCD.

### R/W = 0

* Write mode.
* The microcontroller sends commands or characters to the LCD.
* This is the most commonly used mode.

### R/W = 1

* Read mode.
* The microcontroller reads information such as the busy flag or data from the LCD.

---

## Pin 6 – Enable (E)

The Enable pin acts like a confirmation signal.

Even if the microcontroller places data on the data bus, the LCD will not read it until the Enable pin receives a pulse.

---

## Pins 7–14 (DB0–DB7)

These eight pins form the **8-bit data bus**.

They are used to transfer:

* Commands
* Characters
* Numbers
* Symbols

### Two Operating Modes

#### 8-bit mode

* Uses all eight data pins.
* Faster communication.
* Requires more microcontroller pins.

#### 4-bit mode

* Uses only DB4–DB7.
* Saves four I/O pins.
* Data is transmitted in two steps (upper nibble followed by lower nibble).

---

## Pin 15 & 16

| Pin | Name     | Function                               | Connection                        |
| --- | -------- | -------------------------------------- | --------------------------------- |
| 15  | LED+ (A) | Positive terminal of the backlight LED | +5 V (usually through a resistor) |
| 16  | LED− (K) | Negative terminal of the backlight LED | Ground (GND)                      |

---

# Busy Flag

The Busy Flag tells whether the LCD is currently processing a command. It is located at **D7 (the MSB of the data bus)**.

To read the Busy Flag:

* `RS = 0` (since it's a command)
* `RW = 1` (reading)

Now read **D7**.

| D7 | Meaning                                   |
| -- | ----------------------------------------- |
| 1  | LCD is busy. Do not send another command. |
| 0  | LCD is ready to receive the next command. |

This method is better than giving a fixed software delay because it avoids unnecessary waiting.

---

# COMMON LCD COMMANDS

| Command (Hex) | Function                                                        |
| ------------- | --------------------------------------------------------------- |
| 01H           | Clear display                                                   |
| 02H           | Return cursor to home position                                  |
| 06H           | Cursor moves to the right after each character (Entry Mode Set) |
| 0CH           | Display ON, Cursor OFF                                          |
| 0EH           | Display ON, Cursor ON                                           |
| 0FH           | Display ON, Cursor Blinking                                     |
| 10H           | Move cursor left                                                |
| 14H           | Move cursor right                                               |
| 18H           | Shift display left                                              |
| 1CH           | Shift display right                                             |
| 38H           | Function Set (8-bit mode, 2 lines, 5×8 font)                    |
| 80H + Address | Set DDRAM (cursor) address                                      |
| 40H + Address | Set CGRAM address                                               |

---

# Difference between DDRAM and CGRAM

| DDRAM                             | CGRAM                                      |
| --------------------------------- | ------------------------------------------ |
| Stores characters to be displayed | Stores custom character patterns           |
| Holds ASCII codes                 | Holds pixel patterns                       |
| Used every time text is displayed | Used only when custom symbols are required |
| Large memory                      | Small memory (8 custom characters)         |
| Example: 'A', 'B', '1', '2'       | Example: Heart, Battery, Smiley            |

---

# Steps to Display a Character on an LCD

1. Initialize the LCD by sending the required commands (e.g., function set, display ON, entry mode).
2. Set the cursor position by sending the desired DDRAM address.
3. Send the ASCII value of the character to the LCD.
4. The ASCII value is stored in DDRAM.
5. The LCD controller reads the ASCII code from DDRAM.
6. Using the built-in CGROM, the LCD converts the ASCII code into the corresponding character pattern.
7. The character is displayed at the selected cursor position.

---

# Steps to Display a Custom Graphic (Custom Character)

1. Initialize the LCD.
2. Send the CGRAM address where the custom character will be stored.
3. Write the 8-byte pixel pattern of the custom character into CGRAM.
4. Set the cursor position by sending the required DDRAM address.
5. Send the CGRAM location number (0–7) as data to the LCD.
6. The LCD retrieves the custom character pattern from CGRAM.
7. The custom graphic is displayed at the specified position on the LCD.
