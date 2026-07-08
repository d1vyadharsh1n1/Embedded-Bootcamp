# 8051 Serial Communication

---

# Serial vs Parallel Communication

**Parallel communication:** Transfers multiple bits at the same time using multiple wires.

**Serial communication:** Transfers data one bit at a time using a single wire.

Serial communication is cheaper, simpler, and suitable for long-distance communication.

---

# Types of Data Transmission

## Simplex

Data flows in only one direction.

**Example:** Keyboard → Computer.

## Half Duplex

Data flows in both directions, but not simultaneously.

**Example:** Walkie-talkie.

## Full Duplex

Data flows in both directions simultaneously.

**Example:** Telephone communication.

---

# Asynchronous Serial Communication

Uses start and stop bits to identify the beginning and end of data.

No common clock signal is required.

Standard frame:

- 1 Start bit (0)
- 8 Data bits
- Optional parity bit
- 1 or 2 Stop bits (1)

---

# Baud Rate

**Baud rate = Number of bits transmitted per second.**

Common baud rates:

- 1200
- 2400
- 4800
- 9600
- 19200

---

# RS232 Standard

Standard used for serial communication between computers and devices.

Voltage levels:

- Logic 1 = −3V to −25V
- Logic 0 = +3V to +25V

RS232 is not TTL compatible.

---

# MAX232 / MAX233

## MAX232

- Converts TTL voltage levels ↔ RS232 voltage levels.
- Requires external capacitors.

## MAX233

- Performs the same function as MAX232.
- Does not require external capacitors.

---

# 8051 Serial Port Pins

| Pin | Function |
|------|----------|
| P3.1 (TxD) | Transmit Data |
| P3.0 (RxD) | Receive Data |

---

# Important Registers

## SBUF (Serial Buffer Register)

Used to send and receive serial data.

- Writing to SBUF transmits data.
- Reading from SBUF receives data.

## SCON (Serial Control Register)

Controls serial communication settings.

Important bits:

- SM0, SM1 → Select serial mode.
- REN → Enables receiving.
- TI → Transmission complete flag.
- RI → Reception complete flag.

---

# Serial Mode 1

Most commonly used mode.

Features:

- 8-bit data
- 1 start bit
- 1 stop bit
- Variable baud rate

---

# Programming Steps for Serial Communication

1. Configure Timer1 Mode 2.
2. Load TH1 with baud rate value.
3. Configure SCON.
4. Start Timer1.
5. Write data to SBUF.
6. Wait for TI = 1.
7. Clear TI and send next byte.

---

# TI and RI Flags

## TI (Transmit Interrupt)

- Set by hardware after transmission is complete.
- Must be cleared by software.

## RI (Receive Interrupt)

- Set when a byte is received.
- Must be cleared after reading the data.

---

# Baud Rate Generation (11.0592 MHz Crystal)

| Baud Rate | TH1 Value (Hex) |
|-----------|-----------------|
| 9600 | FDH |
| 4800 | FAH |
| 2400 | F4H |
| 1200 | E8H |

---

# SMOD Bit

Located in the **PCON** register.

Used to double the baud rate.

- **SMOD = 0:** Normal baud rate.
- **SMOD = 1:** Baud rate becomes **2×** faster.
