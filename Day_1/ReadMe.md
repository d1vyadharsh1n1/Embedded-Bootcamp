# Embedded Systems — Day 1 Notes

## Controller Fundamentals

### Why Controllers?
- **Automated Tasks**: Execute predefined operations without manual intervention
- **Need Instructions & Resources**: Require both program (code) and data to produce meaningful output
- **Core Role**: Manage how data and instructions are processed

### Basic Architecture Flow
```
(Program + Data) → Processing Engine → Output
```

---

## Processor Architecture Layers

### Hierarchy of Abstraction
1. **Processor Level**
   - ALU (Arithmetic Logic Unit) — Computing units
   - Microarchitecture — Internal organization
2. **Digital Logic Level**
   - Data Path & Control Path
   - Combinational & Sequential circuits
3. **Physical Level**
   - Gates
   - Transistors
   - Devices

### Key Insight
- All functions can be broken down into mathematical/arithmetic operations
- Optimization can occur at any layer

---

## Communication Protocols

### TDMA (Time Division Multiple Access)
- Protocol for multiple device communication
- Scalability: Protocols that scale well have longer lifespans

### Industry-Specific Protocols

| Protocol | Application |
|---|---|
| I2S | Audio transmission |
| Thread/Matter | Low-power concurrency |
| UART | Serial communication |
| I2C | Inter-chip communication |

### Wireless Communication
- WiFi Chips
- RF (Radio Frequency) modules

---

## Processor Operation

### Basic Components
- **Processor**: Data processing engine
- **Memory**: Flash/ROM for data storage
- **Clock**: Synchronization signal
- **Address Bus**: Identifies memory locations

### BIOS/UART
- Basic Input/Output System
- Universal Asynchronous Receiver-Transmitter

---

## Digital Logic Fundamentals

### Circuit Types
1. **Combinational Circuits**
   - Output depends only on current inputs
   - No memory element
2. **Sequential Circuits**
   - Output depends on current inputs + previous state
   - Contains memory elements

### Latch
- Level-triggered (enables when clock is HIGH/LOW)
- Transparent — output follows input during enable
- Simple construction (2 NAND/NOR gates)
- Used for: Address decoding, simple storage

### Flip-Flop
- Edge-triggered (samples only on clock edge)
- Non-transparent — stable output
- Master-slave configuration (two latches)
- Used for: Registers, counters, PC, IR

---

## Instruction Cycle

### Program Execution Flow
1. **Fetch**: Get instruction from memory
2. **Decode**: Interpret instruction
3. **Execute**: ALU performs operation
4. **Store**: Write back result

### Key Registers
- **Program Counter (PC)**: Address of next instruction
- **Instruction Register (IR)**: Currently executing instruction
- **Control Path**: Enables ALU and coordinates operations
- **Data Path**: Handles actual data movement

### Debugging Techniques
- Use status flags for monitoring
- Implement proper error handling
- Test under various conditions

### Boot Process
- **Power-On Reset**: Initializes system
- **Boot Loader**: First program that runs
- **Initialization**: Sets up processor and peripherals

---

## Memory Architecture Summary

```
┌─────────────────────┐
│  4GB Address Space   │
├─────────────────────┤
│  Peripheral Memory    │ ← Memory-Mapped I/O
├─────────────────────┤
│  Kernel & Drivers     │ ← OS Layer
├─────────────────────┤
│  Application Code     │ ← User Programs
├─────────────────────┤
│  Stack & Heap         │ ← Dynamic Memory
└─────────────────────┘
```

- Memory mapping is continuous from processor perspective
- OS abstracts physical memory allocation
- Heap vs Stack: Know the difference
- Variable size depends on datatype and compiler

---

## Introduction to 8051 Microcontroller

### Overview
- **Intel 8051**: Introduced in 1980
- 8-bit Harvard architecture
- 40-pin DIP package
- Still widely used in embedded systems

### Special Function Registers (SFRs)
- **Located**: Top of internal RAM
- **Purpose**: Control peripherals
- **Examples**:
  - P0, P1, P2, P3: Port registers
  - TMOD: Timer Mode Register
  - TCON: Timer Control Register
  - SCON: Serial Control Register
  - SBUF: Serial Buffer

---

## Stack

- LIFO (Last In, First Out) memory structure
- Grows downward in memory (usually)
- Managed automatically by compiler

### What's Stored in Stack?
1. **Local Variables**: Function-scope variables
2. **Function Parameters**: Arguments passed to functions
3. **Return Addresses**: Where to continue after function
4. **Context Switching**: All status saved before interrupts
   - Critical: Interrupts store all status in stack before ISR execution

### Stack Pointer (SP)
- Points to top of stack
- Updated automatically during PUSH/POP
- 8051: 8-bit SP register

---

## Heap

- Dynamic memory allocation
- Grows upward in memory (usually)
- Manual management by programmer

### What's Stored in Heap?
1. **Dynamic Arrays**: Runtime-sized arrays
2. **Objects**: Created with 'new' keyword
3. **Data Structures**: Linked lists, trees, etc.
4. **Large Data**: Big buffers/images

### Heap Management
- **OS Handles**: Continuous memory allocation
- **Memory Mapping**: Processor sees all as memory
- **Fragmentation**: Major issue in heap
