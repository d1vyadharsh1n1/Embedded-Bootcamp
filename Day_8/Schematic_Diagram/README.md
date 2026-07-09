# 8051 Development Board Schematic

---

# Objective

The objective of this session was to understand how to read electronic schematics using an **AT89S52 (8051) development board** schematic, identify components and their connections, understand power distribution, and verify hardware connections using a multimeter.

---

# What is a Schematic Diagram?

A schematic diagram is a symbolic representation of an electronic circuit.

It shows:

- Components used in the circuit
- Electrical connections between components
- Signal flow
- Power distribution
- Functional blocks of the system

A schematic does not show physical placement; it only shows electrical connectivity.

---

# How We Started Reading the Schematic

When reading any schematic, we learned to follow this order:

1. Power supply section
2. Ground connections
3. Main controller/processor
4. Clock circuit
5. Reset circuit
6. Input/output peripherals
7. Communication interfaces
8. External connectors

This method helps avoid confusion when dealing with complex circuits.

---

# Step 1: Identify the Main Component

The first component we identified was the microcontroller:

**AT89S52**

This is the brain of the board, and all other components connect to it.

## Important Pins Identified

| Pin | Function |
|-----|----------|
| 40 | VCC |
| 20 | GND |
| 18 | XTAL2 |
| 19 | XTAL1 |
| 9 | RESET |
| 10 | RXD |
| 11 | TXD |
| 12 | INT0 |
| 13 | INT1 |

---

# Step 2: Understanding VCC and Ground

## VCC

In the schematic:

```text
+5V
```

means every point carrying **+5 V** is electrically connected.

For example:

```text
+5V
  |
MCU
LCD
ADC
LED
Pullups
```

Although wires may not physically touch on the schematic, the same label indicates the same electrical connection.

## Ground

Similarly,

```text
GND
```

represents the common reference point of the entire circuit.

Every component must share the same ground reference.

Examples:

- LCD ground
- ADC ground
- MCU ground
- USB ground

are all electrically connected.

---

# Using the Multimeter to Identify Connectivity

We learned to use the multimeter in continuity mode.

## Procedure

1. Turn the multimeter to continuity mode.
2. Place one probe on the first pin.
3. Place the second probe on another pin.

If the multimeter beeps:

```text
BEEP
```

the two points are electrically connected.

### Example

```text
MCU VCC ---- LCD VCC
```

Testing:

- Probe 1 → MCU VCC
- Probe 2 → LCD VCC

Result:

```text
BEEP
```

Therefore, both share the same power line.

---

# Step 3: Understanding the Clock Circuit

We then identified the clock section.

The board uses:

- **11.0592 MHz Crystal**

connected between:

- XTAL1
- XTAL2

along with two:

- **33 pF capacitors**

connected to ground.

## Purpose

- Generates the clock signal
- Synchronizes all microcontroller operations
- Provides accurate serial communication timing

## Circuit

```text
XTAL1 ---- Crystal ---- XTAL2
             |
           33pF
             |
            GND
```

---

# Step 4: Understanding the Reset Circuit

The reset circuit contains:

- Push button
- Capacitor
- Resistor

connected to the **RESET** pin.

## Purpose

- Reset the microcontroller
- Initialize all registers
- Restart program execution

When the reset button is pressed:

```text
RESET = HIGH
```

and the MCU restarts.

---

# Step 5: Understanding Pull-up Resistors

We learned that **Port 0** requires pull-up resistors.

The schematic contains:

- **10K Pull-up Resistor Network**

connected to **Port 0**.

## Purpose

- Provide logic HIGH
- Prevent floating states
- Allow proper operation of Port 0

---

# Step 6: Understanding LED Connections

The board contains an LED connected to:

**P1.0**

through a resistor.

## Circuit

```text
P1.0
 |
Resistor
 |
LED
 |
GND
```

## Purpose of Resistor

- Limit current
- Protect LED from damage

---

# Step 7: Understanding the LCD Section

The schematic contains a:

**16×2 LCD**

with:

- RS
- RW
- EN
- D4–D7
- Contrast pin

connections.

We learned:

| Pin | Function |
|-----|----------|
| RS | Command/Data selection |
| RW | Read/Write |
| EN | Enable pulse |
| VO | Contrast adjustment |

The contrast is controlled using a potentiometer.

---

# Step 8: Understanding the ADC Circuit

The board contains:

**ADC0804**

connected to the 8051.

## Important Signals

| Signal | Function |
|---------|----------|
| WR | Start conversion |
| RD | Read result |
| INTR | Conversion complete |

We learned that:

- Analog input enters the ADC.
- ADC converts voltage into digital data.
- Digital data is sent to the microcontroller.

---

# Step 9: Understanding the Keypad Matrix

The schematic contains a:

**4×4 keypad**

connected to **Port 2**.

We learned:

- Keypads use matrix scanning.
- Four rows and four columns create sixteen keys.
- This saves microcontroller pins.

---

# Step 10: Understanding the Seven-Segment Display

The schematic contains a seven-segment display connected to **Port 0**.

Segments:

- A
- B
- C
- D
- E
- F
- G
- DP

We learned how individual segments combine to display numbers.

---

# Step 11: Understanding Timers and Interrupts

We identified special pins:

| Pin | Function |
|-----|----------|
| P3.2 | INT0 |
| P3.3 | INT1 |
| P3.4 | Timer0 |
| P3.5 | Timer1 |

We learned:

## Interrupts

Allow the microcontroller to respond immediately to external events.

Examples:

- Button press
- Sensor trigger
- External signal

## Timers

Used for:

- Delay generation
- PWM generation
- Frequency measurement
- Event counting

---

# Step 12: Understanding Connectors

We learned how connectors expose microcontroller pins externally.

Examples:

- D0–D7
- D8–D15
- A0–A5
- +5V
- GND

These connectors allow additional sensors and modules to be connected to the board.

---

# General Methodology Learned for Reading Any Schematic

We learned to follow the following sequence:

1. Find the power supply.
2. Locate all ground connections.
3. Identify the main controller IC.
4. Locate the clock circuit.
5. Locate the reset circuit.
6. Identify input devices.
7. Identify output devices.
8. Identify communication interfaces.
9. Trace signal flow.
10. Verify connectivity using a multimeter.

---

# How Continuity Testing Was Performed

To identify connectivity, we used a multimeter in continuity mode:

- Probe 1 → Source pin
- Probe 2 → Destination pin

## Results

- Continuous beep → Electrically connected
- No beep → Not connected

This helped us verify:

- VCC rails
- Ground rails
- MCU-to-LCD connections
- MCU-to-ADC connections
- Connector pin mappings
