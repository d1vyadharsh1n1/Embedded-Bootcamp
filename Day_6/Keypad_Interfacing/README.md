# Keypad

A keypad is an input device used to enter numbers, characters, or commands into a microcontroller system. Instead of using several individual push buttons, a keypad arranges keys in a matrix of rows and columns, reducing the number of I/O pins required.

---

# Matrix Keypad Structure

A **4 × 4 keypad** consists of:

* 4 Row lines (R0–R3)
* 4 Column lines (C0–C3)

```text
       C0  C1  C2  C3

R0      1   2   3   A

R1      4   5   6   B

R2      7   8   9   C

R3      *   0   #   D
```

Each key is placed at the intersection of one row and one column. When a key is pressed, the corresponding row and column become electrically connected.

---

# Pull-up Resistors

Each column is connected to **+5 V** through a **4.7 kΩ resistor**. These resistors are called **pull-up resistors**.

## Purpose of Pull-up Resistors

A pull-up resistor ensures that the input pin remains at **Logic 1 (HIGH)** when no key is pressed.

Without a pull-up resistor, the input pin would be floating, meaning its voltage would be unpredictable. A floating input may randomly read HIGH or LOW due to electrical noise, causing false key detections.

## Why not connect the column directly to +5 V?

If the column is directly connected to **+5 V** without a resistor:

* Pressing a key while the corresponding row is LOW (0 V) would create a direct path between +5 V and Ground.
* This causes a short circuit, resulting in excessive current that can damage the microcontroller or keypad.
* The resistor limits the current to a safe value.

Using Ohm's Law:

```text
I = V / R = 5 / 4700 = 1.06 mA
```

So, only about **1 mA** flows when a key is pressed, protecting the circuit.

---

# Working Principle

The microcontroller continuously checks whether any key has been pressed.

This process is called **Keypad Scanning**.

The basic steps are:

1. Configure the rows as outputs.
2. Configure the columns as inputs.
3. Make one row LOW while keeping the others HIGH.
4. Read all the column pins.
5. If any column becomes LOW, a key in that row is pressed.
6. Repeat the same procedure for all rows until the pressed key is identified.

---

# Keypad Scanning Algorithm

## Step 1

Initially,

* Rows → Output
* Columns → Input

## Step 2

Keep all rows HIGH.

```text
R0 = 1
R1 = 1
R2 = 1
R3 = 1
```

No key is detected.

## Step 3

Pull only Row 0 LOW.

```text
R0 = 0
R1 = 1
R2 = 1
R3 = 1
```

Now check all columns.

If `C1 = 0`

then the key pressed is

**(Row 0, Column 1) = Key '2'**

## Step 4

If no column becomes LOW,

Restore Row 0 HIGH and pull Row 1 LOW.

Repeat the process.

## Step 5

Continue scanning all rows until the pressed key is found.

---

# Why is Debouncing Required?

A mechanical switch does not change from OFF to ON instantly. When pressed, its contacts vibrate for a few milliseconds, producing multiple transitions. Instead of **OFF → ON**, the signal becomes

```text
OFF
ON
OFF
ON
OFF
ON
```

within a very short time.

This phenomenon is called **Switch Bounce**.

Without handling this, one key press may be detected multiple times.
