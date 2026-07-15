# DS12887 Real-Time Clock (RTC)
 
A reference guide covering the fundamentals of real-time clocks, the DS12887 RTC IC, its memory organization, pin functions, control/status registers, and interfacing with the 8051 microcontroller.
 
---
 
## Table of Contents
 
1. [What is an RTC?](#1-what-is-an-rtc)
2. [Internal RTC vs External RTC](#2-internal-rtc-vs-external-rtc)
3. [Introduction to DS12887](#3-introduction-to-ds12887)
4. [Important Features of DS12887](#4-important-features-of-ds12887)
5. [Memory Organization](#5-memory-organization)
6. [Address Map](#6-address-map)
7. [DS12887 Pin Functions](#7-ds12887-pin-functions)
8. [Interfacing DS12887 with 8051](#8-interfacing-ds12887-with-8051)
9. [When Can the DS12887 Be Accessed?](#9-when-can-the-ds12887-be-accessed)
10. [The Four Control/Status Registers](#10-the-four-controlstatus-registers)
11. [Register A](#11-register-a)
12. [Register B](#12-register-b)
13. [Register C](#13-register-c)
14. [Register D](#14-register-d)
15. [AIE, PIE and UIE — Quick Comparison](#15-aie-pie-and-uie--quick-comparison)
16. [How IRQ Works](#16-how-irq-works)
17. [Square-Wave Output](#17-square-wave-output)
---
 
## 1. What is an RTC?
 
**RTC = Real-Time Clock**
 
An RTC is an electronic clock that continuously maintains:
 
- Seconds
- Minutes
- Hours
- Day of the week
- Date
- Month
- Year
The main advantage of an RTC is that it continues keeping track of time and date even when the main system power supply is switched **OFF**.
 
### How does it work without external power?
 
The RTC contains:
 
- A low-power CMOS clock circuit
- A crystal oscillator/time base
- A backup lithium battery
When the main power supply is removed, the internal lithium battery powers the clock and RAM circuitry — so the RTC continues maintaining the correct time and date.
 
---
 
## 2. Internal RTC vs External RTC
 
| Internal RTC | External RTC |
|---|---|
| Built inside the microcontroller | Separate RTC IC |
| Uses microcontroller resources | Dedicated hardware |
| May require external crystal/battery circuitry | May contain integrated battery and oscillator |
| Depends on MCU features | Can operate independently |
| Less interfacing required | Requires interfacing with MCU |
| Example: RTC functionality in some microcontrollers | Example: DS12887 |
 
> An external RTC such as the DS12887 is useful because it provides dedicated timekeeping hardware, battery-backed RAM, alarms, and interrupt functions.
 
---
 
## 3. Introduction to DS12887
 
The DS12887 is a real-time clock IC developed for maintaining time, calendar information, alarms, and battery-backed data.
 
It integrates into a single package:
 
- RTC circuitry
- Crystal
- Lithium battery
- Battery-backed CMOS RAM
- Control registers
It was widely used in x86-based PCs and computer systems.
 
---
 
## 4. Important Features of DS12887
 
### Time and Calendar Information
 
The DS12887 maintains: Seconds, Minutes, Hours, Day, Date, Month, Year.
 
### Two Data Formats
 
**Binary Mode** — Values are stored directly in binary/hexadecimal representation.
 
**BCD Mode** — BCD = Binary-Coded Decimal. Each decimal digit is separately represented using 4 bits.
 
| Decimal | BCD | Hexadecimal |
|---|---|---|
| 25 | 0010 0101 | 0x25 |
 
### 12-Hour and 24-Hour Modes
 
The DS12887 supports both 12-hour format (with AM/PM indication) and 24-hour format. The mode is selected using the **DM bit of Register B**.
 
### Daylight Saving Time Option
 
The DS12887 provides automatic adjustment for Daylight Saving Time. When enabled, the RTC automatically adjusts the clock according to the programmed daylight-saving convention. Controlled using the **DSE bit in Register B**.
 
### Battery-Backed Operation
 
The DS12887 contains an internal lithium battery. When external power is removed:
 
- Timekeeping continues
- RAM data is retained
### CMOS Technology
 
The DS12887 uses CMOS technology. CMOS circuits consume very little power, allowing the internal lithium battery to maintain the clock and RAM for several years.
 
---
 
## 5. Memory Organization
 
The DS12887 contains **128 bytes** of addressable memory/register space, address range **00H – 7FH**.
 
| Address Range | Purpose |
|---|---|
| 00H – 09H | Time, calendar, and alarm registers |
| 0AH – 0DH | Control and status registers |
| 0EH – 7FH | General-purpose battery-backed RAM |
 
**Summary:**
 
- First 10 bytes → Time/calendar/alarm information
- Next 4 bytes → Control/status registers
- Remaining 114 bytes → General-purpose RAM
> **Important:** All 128 locations are addressable. However, the first 14 locations are not general-purpose RAM because they are assigned specific RTC and control functions.
 
---
 
## 6. Address Map
 
| Address | Register |
|---|---|
| 00H | Seconds |
| 01H | Seconds Alarm |
| 02H | Minutes |
| 03H | Minutes Alarm |
| 04H | Hours |
| 05H | Hours Alarm |
| 06H | Day of Week |
| 07H | Date of Month |
| 08H | Month |
| 09H | Year |
| 0AH | Register A |
| 0BH | Register B |
| 0CH | Register C |
| 0DH | Register D |
| 0EH – 7FH | General-Purpose RAM |
 
---
 
## 7. DS12887 Pin Functions



| Pin | Function |
|---|---|
| **AD0–AD7** | Multiplexed Address/Data Bus. The same eight pins carry address during the address phase and data during the data phase. The ALE signal separates the two phases. |
| **MOT** | Motorola/Intel bus timing selection pin. HIGH → Motorola timing, LOW → Intel timing. For interfacing with the 8051, Intel timing is used, so **MOT = LOW**. |
| **CS** (Chip Select) | Enables communication with the DS12887. When active, the RTC responds to read/write operations; when inactive, the device ignores bus operations. |
| **AS** (Address Strobe) | Used to latch the address present on AD0–AD7. During the address phase, the address appears on AD0–AD7, AS/ALE indicates the bus contains an address, and the RTC internally latches it — freeing AD0–AD7 for data. |
| **R/W** | Controls read and write operations in Motorola timing mode. Its exact function depends on the selected bus timing mode. |
| **DS** (Data Strobe) | Used during Motorola bus timing operations. Its function changes when Intel timing mode is selected. |
| **IRQ** | Interrupt Request output (active-low). Activated when an enabled interrupt event occurs (alarm, periodic, or update-ended interrupt). |
| **SQW** (Square Wave Output) | Generates a programmable square-wave signal. Frequency selected via RS3–RS0 (Register A); output enabled/disabled via SQWE (Register B). |
| **RESET** | Used to initialize/control certain RTC functions. Affects interrupt-related circuitry but does not destroy stored time, calendar, or RAM contents. |
| **VCC** | Main +5V power supply. |
| **GND** | Ground connection. |
| **NC** | No Connection — these pins should normally be left unconnected. |
 
**Quick relation to remember (SQW):**
 
```
RS3–RS0  →  Select the frequency
SQWE     →  Enable the square-wave output
SQW pin  →  Outputs the actual square wave
```
 
---
 
## 8. Interfacing DS12887 with 8051
 
- The 8051 and DS12887 both use a **multiplexed address/data bus** architecture.
- 8051 **Port 0** provides AD0–AD7, which first carry the lower address and later carry data.
- The 8051 also generates an **ALE (Address Latch Enable)** signal.
- The DS12887 has an **Address Strobe** input that can directly use this ALE signal, so the DS12887 internally latches the address.
> **Important Advantage:** An external address latch is not required for the lower address byte when interfacing the DS12887 using its multiplexed bus interface — the RTC internally latches the address using the Address Strobe signal.
 
---
 
## 9. When Can the DS12887 Be Accessed?
 
- The DS12887 monitors its supply voltage.
- When the supply voltage is sufficient, normal read and write operations are allowed.
- When the supply voltage drops below the required level:
  - The device automatically protects itself
  - External access is disabled
  - The internal battery maintains time and RAM data
- When power returns, the oscillator/timekeeping circuitry requires a startup period before normal operation stabilizes — the datasheet specifies approximately **500 ms** of oscillator startup time after the oscillator is enabled.
---
 
## 10. The Four Control/Status Registers
 
| Register | Address |
|---|---|
| Register A | 0AH |
| Register B | 0BH |
| Register C | 0CH |
| Register D | 0DH |
 
---
 
## 11. Register A
 
**Address:** `0AH`
 
| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|---|
| Function | UIP | DV2 | DV1 | DV0 | RS3 | RS2 | RS1 | RS0 |
 
### UIP — Update In Progress
 
| UIP | Meaning |
|---|---|
| 1 | The RTC is currently updating the time/calendar registers |
| 0 | The RTC is not updating the registers |
 
**Why it matters:** The RTC updates several registers together. If the microcontroller reads the RTC during an update, it may obtain inconsistent data (e.g., seconds may belong to the new minute while minutes still belong to the previous minute).
 
> **Rule:** Check UIP = 0 before reading time/calendar data.
 
### DV2, DV1, DV0
 
These bits control the oscillator and divider chain. They are used to:
 
- Turn the oscillator ON/OFF
- Reset the divider chain
- Select operating conditions
The normal operating configuration is selected using the appropriate DV bit combination.
 
### RS3–RS0
 
RS = Rate Select bits. These four bits select the frequency of the periodic interrupt/square-wave output. Different combinations generate different frequencies.
 
> RS3–RS0 determine the periodic interrupt and SQW frequency.
 
---
 
## 12. Register B
 
**Address:** `0BH`
 
| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|---|
| Function | SET | PIE | AIE | UIE | SQWE | DM | 24/12 | DSE |
 
| Bit | Function | 0 | 1 |
|---|---|---|---|
| SET | Update Control | Normal time updates occur | Updates to time/calendar registers inhibited (safe to modify values) |
| PIE | Periodic Interrupt Enable | Periodic interrupts disabled | Periodic interrupts enabled (rate set by RS3–RS0, Register A) |
| AIE | Alarm Interrupt Enable | Alarm interrupts disabled | Alarm interrupts enabled — triggers when current time matches alarm time |
| UIE | Update-Ended Interrupt Enable | Update-ended interrupts disabled | Interrupt generated after RTC completes an update cycle |
| SQWE | Square-Wave Enable | Square-wave output disabled | Square-wave output enabled (frequency set by RS3–RS0, Register A) |
| DM | Data Mode | BCD format | Binary format |
| 24/12 | Hour Format | 12-hour mode | 24-hour mode |
| DSE | Daylight Saving Enable | Daylight-saving adjustment disabled | Daylight-saving adjustment enabled |
 
---
 
## 13. Register C
 
**Address:** `0CH` (Read-only)
 
| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|---|
| Function | IRQF | PF | AF | UF | 0 | 0 | 0 | 0 |
 
Register C contains interrupt flags.
 
### IRQF — Interrupt Request Flag
 
IRQF indicates whether an enabled interrupt condition has generated an IRQ request:
 
```
IRQF = (PF · PIE) + (AF · AIE) + (UF · UIE)
```
 
| Flag | Meaning when set (=1) |
|---|---|
| PF (Periodic Interrupt Flag) | A periodic interrupt event has occurred (rate determined by Register A) |
| AF (Alarm Flag) | The current time has matched the programmed alarm time |
| UF (Update-Ended Flag) | The RTC has completed its time/calendar update cycle |
 
> **Important:** Reading Register C **clears** the interrupt flags. Register C must be read to clear the interrupt condition and release IRQ.
 
---
 
## 14. Register D
 
**Address:** `0DH` (Read-only)
 
| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|---|
| Function | VRT | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
 
### VRT — Valid RAM and Time
 
| VRT | Meaning |
|---|---|
| 1 | Battery-backed RAM and time information are valid |
| 0 | Internal battery voltage has dropped too low — RAM and time information may no longer be reliable |
 
---
 
## 15. AIE, PIE and UIE — Quick Comparison
 
| Enable Bit | Full Form | Event | Corresponding Flag (Register C) |
|---|---|---|---|
| PIE | Periodic Interrupt Enable | Interrupts occur repeatedly at selected frequency | PF |
| AIE | Alarm Interrupt Enable | Interrupt occurs when current time matches alarm | AF |
| UIE | Update-Ended Interrupt Enable | Interrupt occurs after RTC finishes updating time | UF |
 
---
 
## 16. How IRQ Works
 
**IRQ = Interrupt Request** — an active-low output.
 
- Normally: IRQ = HIGH
- When an enabled interrupt condition occurs: IRQ → LOW
**Example:**
 
```
If PIE = 1 and PF = 1  →  IRQF = 1  →  IRQ goes LOW
If AIE = 1 and AF = 1  →  IRQ goes LOW
If UIE = 1 and UF = 1  →  IRQ goes LOW
```
 
**Sequence of events:**
 
1. Microcontroller detects the interrupt
2. Executes the Interrupt Service Routine
3. Reads Register C
4. Determines the interrupt source
5. Reading Register C clears the flags → IRQ returns inactive
---
 
## 17. Square-Wave Output
 
The DS12887 can generate a continuous square-wave signal.
 
| Register | Role |
|---|---|
| Register A (RS3–RS0) | Selects the frequency |
| Register B (SQWE) | Enables/disables the output |
 
**Use cases:**
 
- Timing signals
- Periodic events
- Clock generation
- Synchronization
