# Interrupts

---

# What is an Interrupt?

An interrupt is a signal that temporarily stops the normal execution of the CPU and forces it to execute a special function called an **Interrupt Service Routine (ISR)**. After the ISR finishes, the CPU resumes execution from where it stopped.

## Purpose

- Respond to external events immediately.
- Avoid continuous polling.
- Improve CPU efficiency.

---

# Interrupt Working Sequence

```text
Program Execution
        │
        ▼
Interrupt Occurs
        │
        ▼
Current Instruction Completes
        │
        ▼
Return Address Stored in Stack
        │
        ▼
CPU Jumps to ISR
        │
        ▼
ISR Executes
        │
        ▼
RETI Instruction
        │
        ▼
Program Continues
```

---

# Types of Interrupts

The 8051 has **5 interrupt sources**.

| Interrupt | Flag | Vector Address | Description |
|-----------|------|----------------|-------------|
| External Interrupt 0 | IE0 | 0003H | Triggered by INT0 pin |
| Timer 0 Overflow | TF0 | 000BH | Timer0 overflow |
| External Interrupt 1 | IE1 | 0013H | Triggered by INT1 pin |
| Timer 1 Overflow | TF1 | 001BH | Timer1 overflow |
| Serial Port | RI/TI | 0023H | UART receive/transmit |

---

# Interrupt Vector Table

| Interrupt | Address |
|-----------|---------|
| Reset | 0000H |
| External Interrupt 0 | 0003H |
| Timer0 | 000BH |
| External Interrupt 1 | 0013H |
| Timer1 | 001BH |
| Serial Port | 0023H |

Whenever an interrupt occurs, the CPU automatically jumps to the corresponding vector address to execute the Interrupt Service Routine (ISR).

---

# Interrupt Enable (IE) Register

Address: **A8H**

```text
Bit:  7   6   5   4   3   2   1   0
      EA  -   -   ES  ET1 EX1 ET0 EX0
```

| Bit | Name | Function |
|-----|------|----------|
| EA | Global Enable | Enables all interrupts |
| ES | Serial Enable | Enables Serial interrupt |
| ET1 | Timer1 Enable | Enables Timer1 interrupt |
| EX1 | External1 Enable | Enables External Interrupt 1 |
| ET0 | Timer0 Enable | Enables Timer0 interrupt |
| EX0 | External0 Enable | Enables External Interrupt 0 |

## Example

```c
IE = 0x82;
```

Binary Representation:

```text
10000010
```

Meaning:

- EA = 1 → Enable all interrupts
- EX0 = 1 → Enable External Interrupt 0

---

# Interrupt Priority (IP) Register

Address: **B8H**

```text
Bit: 7 6 5 4 3 2 1 0
     - - - PS PT1 PX1 PT0 PX0
```

| Bit | Interrupt |
|-----|-----------|
| PS | Serial Port |
| PT1 | Timer1 |
| PX1 | External Interrupt 1 |
| PT0 | Timer0 |
| PX0 | External Interrupt 0 |

## Priority Levels

- **0** → Low Priority
- **1** → High Priority

## Example

```c
IP = 0x02;
```

Meaning:

- PT0 = 1 → Timer0 becomes High Priority.
- All remaining interrupts remain Low Priority.

---

# Default Interrupt Priority Order

If all interrupts have the same priority, the CPU services them in the following order:

| Priority | Interrupt |
|----------|-----------|
| 1 | External Interrupt 0 |
| 2 | Timer0 |
| 3 | External Interrupt 1 |
| 4 | Timer1 |
| 5 | Serial Port |

---

# External Interrupts

The 8051 provides two external interrupt pins:

- INT0 → P3.2
- INT1 → P3.3

These interrupts can be configured in two modes:

- Edge Triggered
- Level Triggered

Configuration is performed using the **TCON Register**.

---

# TCON Register

```text
Bit
7  TF1
6  TR1
5  TF0
4  TR0
3  IE1
2  IT1
1  IE0
0  IT0
```

| Bit | Function |
|-----|----------|
| TF1 | Timer1 Overflow Flag |
| TR1 | Timer1 Run Control |
| TF0 | Timer0 Overflow Flag |
| TR0 | Timer0 Run Control |
| IE1 | External Interrupt 1 Flag |
| IT1 | INT1 Trigger Selection |
| IE0 | External Interrupt 0 Flag |
| IT0 | INT0 Trigger Selection |

---

# Edge Triggered Interrupt

## Configuration

```c
IT0 = 1;
IT1 = 1;
```

An interrupt occurs only when the signal changes from HIGH to LOW.

```text
HIGH
│
│
└────── LOW
```

## Advantages

- Generates only one interrupt per signal transition.
- Prevents repeated interrupt requests.
- Ideal for push buttons and pulse signals.

## Applications

- Push buttons
- Sensors
- Pulse counting
- Event detection

---

# Level Triggered Interrupt

## Configuration

```c
IT0 = 0;
IT1 = 0;
```

The interrupt remains active as long as the interrupt pin stays LOW.

```text
HIGH
│
└──────────── LOW
```

## Advantages

- Detects continuously active hardware requests.
- Suitable for devices requiring constant attention.

## Applications

- Hardware request lines
- Continuous event monitoring

---

# Timer Interrupt

A timer interrupt occurs whenever Timer0 or Timer1 overflows.

```text
Timer Count
      │
      ▼
Overflow
      │
      ▼
TF0 or TF1 = 1
      │
      ▼
CPU Executes Timer ISR
```

## Applications

- Delay generation
- Real-Time Clock (RTC) implementation
- Periodic task execution
- PWM generation
- Event timing

---

# Serial Interrupt

The serial interrupt is generated when:

- RI = 1 → Data reception completed.
- TI = 1 → Data transmission completed.

Both conditions use the same ISR.

## Example

```c
if(RI)
{
    // Receive data
}

if(TI)
{
    // Transmit complete
}
```

---

# Interrupt Service Routine (ISR)

An Interrupt Service Routine (ISR) is a function that automatically executes whenever its corresponding interrupt occurs.

## General Syntax (Keil C)

```c
void ISR_Name(void) interrupt Interrupt_Number
{
    // ISR code
}
```

## Example

```c
void timer0_ISR(void) interrupt 1
{
    // Timer0 interrupt code
}
```

## Interrupt Numbers

| Interrupt | Number |
|-----------|--------|
| External Interrupt 0 | 0 |
| Timer0 | 1 |
| External Interrupt 1 | 2 |
| Timer1 | 3 |
| Serial Port | 4 |

---

# RETI (Return from Interrupt)

```text
ISR Ends
    │
    ▼
RETI
    │
    ▼
Return Address Restored
    │
    ▼
Program Continues
```

The RETI instruction informs the CPU that the interrupt service routine has finished. The processor restores the saved return address from the stack and resumes execution of the interrupted program.

---

# Nested Interrupts

A High Priority interrupt can interrupt a Low Priority ISR.

```text
Main Program
      │
      ▼
Timer0 ISR (Low Priority)
      │
      ▼
External Interrupt 0 (High Priority)
      │
      ▼
External Interrupt 0 ISR
      │
      ▼
Resume Timer0 ISR
      │
      ▼
Main Program Continues
```

A Low Priority interrupt cannot interrupt a High Priority ISR.

---

# Polling vs Interrupts

| Polling | Interrupt |
|---------|-----------|
| CPU continuously checks devices | Device notifies CPU automatically |
| CPU time is wasted | Efficient CPU utilization |
| Slower response | Faster response |
| Simpler implementation | Requires ISR configuration |

---

# Advantages of Interrupts

- Fast response to external events.
- Better CPU utilization.
- Eliminates continuous polling.
- Supports multitasking-like operation.
- Suitable for real-time embedded systems.
- Improves overall system efficiency.
- Reduces unnecessary CPU workload.
- Enables immediate response to hardware events.
