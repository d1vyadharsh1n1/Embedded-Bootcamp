# External Memory Interface

## Why External Memory?

The 8051 has limited on-chip memory:

* **Program Memory (ROM):** 4 KB
* **Data Memory (RAM):** 128 Bytes (8051) / 256 Bytes (8052)

**Need:** Larger applications require external ROM and RAM.

---

## Memory Organization

* **Number of Memory Locations =** 2ˣ
* **x =** Number of Address Pins
* **y =** Number of Data Pins (bits per location)

### Formula

#### Capacity (bits)

```
Capacity = 2ˣ × y bits
```

#### Capacity (Bytes)

```
Capacity = (2ˣ × y) / 8 Bytes
```

---

## ROM (Non-Volatile Memory)

**Used for:** Storing firmware/program code.

| Type   | Erasable   | Erase Cycles | Access | Cost     | Notes                             |
| ------ | ---------- | ------------ | ------ | -------- | --------------------------------- |
| PROM   | No         | 1            | Slow   | Low      | Programmable once                 |
| EPROM  | UV Light   | ~1000        | Slow   | Moderate | Entire chip erased using UV light |
| EEPROM | Electrical | ~10,000      | Slow   | High     | Byte-wise erase/write             |
| Flash  | Electrical | ~100,000     | Fast   | Low      | Block-wise erase/write            |

---

## RAM (Volatile Memory)

**Used for:** Variables, stack, buffers, and temporary data.

| Feature          | SRAM           | NVRAM          | DRAM                       |
| ---------------- | -------------- | -------------- | -------------------------- |
| Memory Cell      | Flip-flop (6T) | SRAM + Battery | 1 Transistor + 1 Capacitor |
| Volatile         | Yes            | No             | Yes                        |
| Refresh Required | No             | No             | Yes                        |
| Speed            | Fast           | Moderate       | Slower than SRAM           |
| Density          | Low            | Low            | High                       |
| Cost             | High           | High           | Low                        |
| Applications     | Cache          | Backup Memory  | Main Memory                |

---

## DRAM Packaging Issue

### Problem

High-density DRAM requires many address pins, increasing chip size and package complexity.

### Solution

**Address Multiplexing**

* Same address pins are used for Row Address and Column Address.
* Reduces the number of address pins.

### Control Signals

| Signal                      | Function                   |
| --------------------------- | -------------------------- |
| RAS (Row Address Strobe)    | Latches the row address    |
| CAS (Column Address Strobe) | Latches the column address |

---

## Interfacing with 8051/8031

**8031 does not have an inbuilt ROM (on-chip ROM).**

| Component | Function                                               |
| --------- | ------------------------------------------------------ |
| P0        | Multiplexed Address/Data Bus (A0–A7 / D0–D7)           |
| P2        | Higher Address Bus (A8–A15)                            |
| ALE       | Latches lower address into 74LS373                     |
| 74LS373   | Stores A0–A7 so P0 can carry data                      |
| PSEN̅     | Enables external Program ROM during instruction fetch  |
| RD̅       | Reads from External RAM                                |
| WR̅       | Writes to External RAM                                 |
| 74LS138   | Decodes address and generates Chip Enable (CE) signals |
| CE        | Selects which memory chip is active                    |
| OE̅       | Enables memory output during a read                    |
| WE̅       | Enables writing into RAM                               |

---

## 1. EA̅ (External Access) Pin

Determines whether the program is executed from internal ROM or external ROM.

| EA̅ Connection | Program Memory Used                                 |
| -------------- | --------------------------------------------------- |
| VCC (Logic 1)  | Internal ROM first, then External ROM (if required) |
| GND (Logic 0)  | Entire program executes from External ROM           |

### Can Internal and External ROM be Used Together?

Yes.

* Internal ROM stores boot code/startup code.
* External ROM stores the remaining application program.
* After the internal ROM address space is exhausted, the 8051 automatically fetches instructions from external ROM (when EA̅ = 1).

### Why is EA̅ Active Low?

Using an active-low control signal improves noise immunity and matches the convention used by many memory chips, making interfacing simpler.

---

## 2. Port 0 & Port 2

| Port | Function                                           |
| ---- | -------------------------------------------------- |
| P0   | Multiplexed Lower Address/Data Bus (A0–A7 / D0–D7) |
| P2   | Higher Address Bus (A8–A15)                        |

### Address/Data Multiplexing

Since Port 0 carries both address and data, the lower address must be stored before Port 0 is reused for data.

---

## 3. ALE (Address Latch Enable)

Used with 74LS373 latch to separate address and data on Port 0.

| ALE | Operation                                                  |
| --- | ---------------------------------------------------------- |
| 1   | Address passes through D → Q (Address Latched)             |
| 0   | Previous address is held; Port 0 is free for data transfer |

### Working

1. Lower address appears on Port 0.
2. ALE = 1, 74LS373 latches the address.
3. ALE = 0, latch holds the address.
4. Port 0 is reused as the data bus.

---

## 4. PSEN̅ (Program Store Enable)

Connected to the OE̅ (Output Enable) pin of the external Program ROM.

Activated during instruction fetch.

Used only for external program memory.

---

## External Memory Pin Connections

| 8051 Pin   | Connected To        |
| ---------- | ------------------- |
| PSEN̅      | OE̅ of Program ROM  |
| RD̅ (P3.7) | OE̅ of External RAM |
| WR̅ (P3.6) | WE̅ of External RAM |

---

## If the Same ROM Stores Program & Data

Since both PSEN̅ and RD̅ can request a read operation, they are combined using an AND gate before connecting to the OE̅ pin of the ROM.

This ensures the ROM is enabled whenever either signal requests a read.

---

## MOV vs MOVC vs MOVX

| Instruction | Memory Accessed       | Purpose                       |
| ----------- | --------------------- | ----------------------------- |
| MOV         | Internal RAM / SFR    | Transfer data within the 8051 |
| MOVC        | Program (Code) Memory | Read constants stored in ROM  |
| MOVX        | External Data Memory  | Read/Write external RAM       |

---

## Interfacing Large External Memory

The 8051 has 16 address lines, so it can directly address:

```
2¹⁶ = 64 KB
```

To interface memory larger than 64 KB, additional address lines can be generated using external hardware (e.g., Port 1 with decoding logic) to select different 64 KB memory banks (bank switching).
