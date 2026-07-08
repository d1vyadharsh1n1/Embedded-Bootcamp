# Seven Segment Display

A Seven Segment Display is an electronic display device used to display decimal digits (0–9). It consists of seven individual LED segments arranged in the shape of the number **8**. By turning ON specific segments, different numbers can be displayed.

---

# Seven Segment Structure

Each segment is represented by a letter from **a** to **g**.

```text
      a
     ───
  f |   | b
    | g |
     ───
  e |   | c
    |   |
     ───
      d

      • dp (Decimal Point)
```

---

# Segment Labels

| Segment | Position |
|---------|----------|
| a | Top horizontal |
| b | Upper right vertical |
| c | Lower right vertical |
| d | Bottom horizontal |
| e | Lower left vertical |
| f | Upper left vertical |
| g | Middle horizontal |
| dp | Decimal Point |

---

# Types of Seven Segment Displays

## Common Cathode (CC)

- All cathodes are connected together.
- Common pin is connected to **GND**.
- A segment glows when its pin is given **Logic HIGH (1)**.

## Common Anode (CA)

- All anodes are connected together.
- Common pin is connected to **+5 V**.
- A segment glows when its pin is given **Logic LOW (0)**.

---

# Hexadecimal Values for Digits

The following hexadecimal values assume the segment order:

```text
dp g f e d c b a
```

and are for a **Common Cathode** display.

| Digit | Segments ON | Hex Value |
|-------|-------------|-----------|
| 0     | a b c d e f   | 3FH |
| 1     |   b c         | 06H |
| 2     | a b   d e   g | 5BH |
| 3     | a b c d     g | 4FH |
| 4     |   b c     f g | 66H |
| 5     | a   c d   f g | 6DH |
| 6     | a   c d e f g | 7DH |
| 7     | a b c         | 07H |
| 8     | a b c d e f g | 7FH |
| 9     | a b c d   f g | 6FH |

---

# Common Anode Hex Values

For a Common Anode display, the hexadecimal values are the complement of the Common Cathode values.

| Digit | Hex Value |
|-------|-----------|
| 0     | C0H |
| 1     | F9H |
| 2     | A4H |
| 3     | B0H |
| 4     | 99H |
| 5     | 92H |
| 6     | 82H |
| 7     | F8H |
| 8     | 80H |
| 9     | 90H |

---

# Applications

- Digital clocks
- Calculators
- Counters
- Digital voltmeters
- Frequency meters
- Embedded system displays
