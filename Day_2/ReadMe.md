# Report on 8051 Peripherals, Memory Mapping, and Reset

## 1. Introduction

The 8051 is an 8-bit microcontroller developed by Intel. It integrates a CPU, memory, and several peripherals onto a single chip, making it suitable for embedded systems such as industrial controllers, home appliances, and automation systems.

The major peripherals of the 8051 include Input/Output (I/O) ports, Timers/Counters, UART, Interrupt Controller, Oscillator, ROM, RAM, and Special Function Registers (SFRs).

---

# 2. 8051 Peripherals

## 2.1 Input/Output (I/O) Ports

The 8051 contains four 8-bit I/O ports:

* Port 0
* Port 1
* Port 2
* Port 3

Together they provide **32 programmable input/output pins**.

These ports are used to interface LEDs, switches, LCDs, sensors, motors, keypads, and other external devices. Some pins of **Port 3** have alternate functions such as UART communication and external interrupts.

---

## 2.2 Timers/Counters

The standard 8051 contains two 16-bit timers:

* Timer 0
* Timer 1

These timers can operate as:

* **Timer** (counts internal clock pulses)
* **Counter** (counts external events)

Applications include:

* Generating delays
* Measuring time intervals
* Frequency measurement
* Baud rate generation for UART

---

## 2.3 UART (Universal Asynchronous Receiver Transmitter)

The UART enables serial communication between the 8051 and external devices such as computers, Bluetooth modules, GPS modules, or other microcontrollers.

Communication occurs through two pins:

* `TXD` (Transmit)
* `RXD` (Receive)

The UART supports **full-duplex communication**, meaning transmission and reception can occur simultaneously.

---

## 2.4 Interrupt System

Interrupts allow the processor to temporarily stop its current task and execute a higher-priority task.

The standard 8051 supports five interrupt sources:

* External Interrupt 0
* Timer 0 Overflow
* External Interrupt 1
* Timer 1 Overflow
* Serial Communication Interrupt

Interrupts improve system responsiveness by eliminating the need for continuous polling.

---

## 2.5 Oscillator

The oscillator generates the clock signal required by the CPU.

A crystal oscillator of **11.0592 MHz** is commonly connected to the 8051 because it allows accurate UART baud-rate generation.

Although many references mention a **12 MHz** clock for explanation, practical development boards commonly use **11.0592 MHz**.

### Instruction Execution

Every instruction generally passes through four stages:

1. Fetch
2. Decode
3. Execute
4. Store (Write Back)

The processor executes instructions according to the system clock.

For the standard 8051:

* Crystal frequency = **11.0592 MHz**
* One machine cycle = **12 clock cycles**

Therefore,

```text
Machine cycle time
= 12 / 11.0592 MHz
≈ 1.085 μs
```

Different instructions require different numbers of machine cycles.

---

## 2.6 ROM (Program Memory)

The 8051 stores its program in Read Only Memory (ROM).

Depending on the microcontroller, this may be:

* Mask ROM
* EPROM
* EEPROM
* Flash Memory

Program memory stores the firmware that the processor executes.

---

## 2.7 Special Function Registers (SFRs)

Special Function Registers control the operation of the peripherals.

| Register | Function                            |
| :------- | :---------------------------------- |
| `ACC`    | Accumulator                         |
| `B`      | Used in multiplication and division |
| `PSW`    | Program Status Word                 |
| `TMOD`   | Timer Mode Register                 |
| `TCON`   | Timer Control Register              |
| `SCON`   | Serial Control Register             |
| `SBUF`   | Serial Buffer Register              |
| `IE`     | Interrupt Enable Register           |
| `IP`     | Interrupt Priority Register         |
| `P0–P3`  | I/O Port Registers                  |

SFRs occupy addresses from **`80H` to `FFH`** in the internal data memory.

---

### 2.7.1 Program Status Word (PSW)

The **Program Status Word (`PSW`)** is an 8-bit Special Function Register (SFR) located at address **`D0H`**. It stores the current status of the CPU and controls certain processor operations such as register bank selection and arithmetic flags.

The bit mapping of the `PSW` register is shown below.

|   Bit   | Symbol | Name                   | Function                                                                                                                                                 |
| :-----: | :----: | :--------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `PSW.7` |  `CY`  | Carry Flag             | Set to `1` if an arithmetic operation generates a carry out (addition) or borrow (subtraction). Used in multi-byte arithmetic operations.                |
| `PSW.6` |  `AC`  | Auxiliary Carry Flag   | Set if there is a carry from bit 3 to bit 4 during addition. Mainly used for BCD (Binary Coded Decimal) arithmetic.                                      |
| `PSW.5` |  `F0`  | User Flag 0            | A general-purpose flag available for use by the programmer. It has no predefined hardware function.                                                      |
| `PSW.4` |  `RS1` | Register Bank Select 1 | Used with `RS0` to select one of the four register banks.                                                                                                |
| `PSW.3` |  `RS0` | Register Bank Select 0 | Used with `RS1` to select one of the four register banks.                                                                                                |
| `PSW.2` |  `OV`  | Overflow Flag          | Set when a signed arithmetic operation produces a result outside the valid range (-128 to +127).                                                         |
| `PSW.1` |    —   | Reserved               | Reserved for future use. It should normally remain `0`.                                                                                                  |
| `PSW.0` |   `P`  | Parity Flag            | Automatically updated after every instruction. It is set to `1` if the accumulator (`A`) contains an odd number of `1`s; otherwise it is cleared to `0`. |

#### Register Bank Selection

The 8051 has four register banks, each containing eight registers (`R0–R7`). The active bank is selected using the `RS1` and `RS0` bits.

| RS1 | RS0 | Selected Register Bank |
| :-: | :-: | :--------------------- |
| `0` | `0` | Bank 0 (Default)       |
| `0` | `1` | Bank 1                 |
| `1` | `0` | Bank 2                 |
| `1` | `1` | Bank 3                 |

#### Example

```assembly
MOV A, #7FH
ADD A, #01H
```

After execution:

* **`CY = 0`** (no carry out of bit 7)
* **`AC = 1`** (carry from bit 3 to bit 4)
* **`OV = 1`** (signed overflow: +127 + 1 = -128)
* **`P = 1`** (`80H = 10000000₂` contains one `1`, which is odd)

These flags help the processor determine the outcome of arithmetic and logical operations and are frequently checked using conditional branch instructions.

---

# 3. Memory Mapping

Memory mapping refers to the organization of memory locations and the signals required to access them.

Different memory technologies include:

* SRAM
* Flash Memory
* EEPROM
* ROM

Each technology differs in speed, volatility, and storage capability.

### Example

Suppose an external memory chip is specified as:

**4K × 16**

This means:

* Number of memory locations = **4K = 4096 locations**
* Each location stores **16 bits**

### Address Bus

To uniquely address **4096 locations**:

```text
2¹² = 4096
```

Therefore:

**Address bus = 12 bits**

### Data Bus

Since each memory location stores **16 bits**:

**Data bus = 16 bits**

### Control Signals

Apart from the address and data buses, the memory requires control signals such as:

* `RD`
* `WR`
* `CE`
* `OE`
* Reset (optional, depending on the device)

These signals determine whether the processor is reading from or writing to memory.

---

# 4. Reset

The reset circuit initializes the microcontroller and places it into a known starting state.

When reset is activated:

* Program Counter returns to address **`0000H`**.
* Registers return to their default values.
* Program execution starts from the beginning.

Most 8051 systems use an RC reset circuit or a push-button reset switch.

---

# 5. Voltage Compatibility

Different microcontrollers operate at different logic voltages.

| Device                   | Logic High Voltage |
| :----------------------- | :----------------: |
| Arduino Uno (ATmega328P) |         5 V        |
| ESP32                    |        3.3 V       |

When connecting a 5 V device to a 3.3 V device, the voltage must be reduced to avoid damaging the lower-voltage device.

Two common methods are:

### Voltage Divider

A voltage divider uses two resistors to reduce the voltage.

For example, a 5 V signal can be reduced to approximately **3.3 V** before reaching an ESP32 input.

A logic LOW remains **0 V** because ground is common to both devices.

### Logic Level Converter

A logic level converter (level shifter) automatically converts signals between **5 V** and **3.3 V** in either direction.

This method is more reliable for bidirectional communication interfaces such as UART and I²C.

---

# 6. Conclusion

The 8051 microcontroller integrates several essential peripherals including I/O ports, timers, UART, interrupts, oscillator circuitry, ROM, and Special Function Registers. Its memory organization uses address, data, and control buses for accessing memory devices. A proper reset circuit ensures reliable startup, while voltage level conversion is necessary when interfacing the 8051 with modern 3.3 V microcontrollers such as the ESP32. These features make the 8051 a versatile and widely used microcontroller for embedded system applications.
