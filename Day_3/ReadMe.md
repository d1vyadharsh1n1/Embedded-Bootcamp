# Scaling Voltage , Instruction Set Architecture  and Pipelining 
 
## 1. Voltage Differences & Level Shifting
Different ICs operate at different logic levels — e.g., **Arduino Uno (5 V)** vs. **ESP32 (3.3 V)**. Connecting incompatible levels directly can misbehave or damage the lower-voltage device.
 
**Check before connecting two devices:**
| Parameter | Why it matters |
|---|---|
| Supply voltage (VCC) | Device power requirement |
| GPIO logic voltage | Signal level compatibility |
| Max input voltage | Damage threshold |
| Logic HIGH/LOW thresholds | Correct signal interpretation |
| Current requirements | Load capacity |
| 5 V-tolerant GPIO? | Whether direct connection is safe |
 
### Voltage Divider
Scales a voltage down using two resistors:
 
$$V_{out} = V_{in} \times \dfrac{R2}{R1+R2}$$
 
*Example:* 5 V → 3.3 V using R1 = 1 kΩ, R2 = 2 kΩ → Vout = 5×2/3 ≈ **3.33 V**
> Good for low-current signals only — not for powering high-current loads.
 
### Level-Shifting Methods
- Voltage divider
- Logic level shifter IC
- MOSFET-based shifter
- Transistor-based circuit
Choice depends on: direction of communication, speed, current, and protocol.
 
### MAX232
Converts between microcontroller UART (TTL/CMOS, 0–5 V or 0–3.3 V) and RS-232 (uses +/− voltages), via an internal charge pump + external capacitors.
 
```
Microcontroller UART → MAX232 → RS-232 Device
```
 
### ESP32 ↔ Arduino / Peripherals
- 5 V Arduino output → non-tolerant 3.3 V ESP32 input: **needs** a divider/shifter.
- ESP32 3.3 V output *may* register as HIGH on some 5 V devices — but always confirm against the datasheet thresholds.
- Check **both** a peripheral's supply voltage and its signal voltage before connecting to a microcontroller.
---
 
## 2. Bit Masking
 
A **mask** is used with bitwise operators to read, set, clear, or toggle specific bits without touching the rest.
 
| Operation | Formula | Effect |
|---|---|---|
| Read | `value = PORT & MASK;` | Isolates selected bits |
| Set | `PORT = PORT \| MASK;` | Forces selected bits to 1 |
| Clear | `PORT = PORT & ~MASK;` | Forces selected bits to 0 |
| Toggle | `PORT = PORT ^ MASK;` | Flips selected bits |
 
**Example** — keep only lower nibble:
```
PORT  = 1011 0110
MASK  = 0000 1111
AND   = 0000 0110
```
```c
value = PORT & 0x0F;   // read lower 4 bits
P2    = P2   & 0x0F;   // clear upper 4 bits, keep lower 4
```
 
**Rule of thumb:** AND-0 clears, AND-1 preserves.
 
---
 
## 3. Instruction Set Architecture (ISA)
 
ISA = the interface between software and hardware. It defines instructions, registers, data types, addressing modes, instruction formats, and memory access methods.
 
| | Defines |
|---|---|
| **ISA** | *What* the processor can do |
| **Microarchitecture** | *How* it does it internally |
 
Examples: ARM, x86, RISC-V, MIPS.
 
---
 
## 4–6. Memory Architectures
 
| Architecture | Memory/Bus | Fetch + Data Access | Pros | Cons |
|---|---|---|---|---|
| **Von Neumann** | Shared | Cannot overlap (bottleneck) | Simple, flexible memory use | Bus contention limits performance |
| **Harvard** | Separate | Simultaneous | Faster, pipeline-friendly | More complex hardware |
| **Modified Harvard** | Separate I/D cache, shared main memory | Simultaneous (cache level) | Combines speed + flexibility | — |
 
---
 
## 7–9. RISC vs. CISC vs. ARM
 
| | RISC | CISC |
|---|---|---|
| Instructions | Simple, often fixed-length | Complex, variable-length |
| Addressing modes | Few | Many |
| Memory access | Load/store only | Some instructions act directly on memory |
| Registers | Many | Fewer, typically |
| Pipelining | Well suited | Harder |
| Examples | ARM, RISC-V, MIPS | x86 |
 
**Load/store architecture:** data → registers → operate → write back to memory.
 
**ARM** is an ISA family built largely on RISC principles (load/store, large register set, energy-efficient) — used in phones, MCUs, embedded systems, laptops, servers.
> Note: RISC is a *design philosophy*; ARM is a specific *ISA family* that follows it. They are not synonyms.
 
---
 
## 10. VLIW (Very Long Instruction Word)
 
One long instruction packs multiple independent operations executed simultaneously by different functional units, e.g.:
 
```
ADD | MULTIPLY | LOAD | STORE   (one VLIW instruction)
```
 
The **compiler** (not hardware) decides what can run in parallel.
 
| Pros | Cons |
|---|---|
| Instruction-level parallelism | Needs a complex compiler |
| Simpler hardware scheduling | Larger instruction size |
| | Poor cross-generation compatibility |
 
---
 
## 11. Processor Bit Width
 
"N-bit processor" generally refers to the **ALU/general-purpose register width**.
 
⚠️ These are *independent* and don't have to match:
- Processor bit width
- Instruction size
- Address bus width
- Data bus width
*(An 8-bit MCU can have a 16-bit instruction word or 16-bit address bus.)*
 
---
 
## 12–14. Pipelining
 
**Stages:** Fetch → Decode → Execute → Memory Access → Write Back
 
Overlaps instruction execution to improve **throughput**, not the latency of any single instruction.
 
```
Cycle 1: I1-F
Cycle 2: I1-D  I2-F
Cycle 3: I1-E  I2-D  I3-F
```
 
### Formulas
Let k = stages, n = instructions, t = cycle time.
 
| Scenario | Time |
|---|---|
| No pipelining | `nkt` |
| Ideal pipelining | `(k + n − 1)t` |
| Speedup | `nk / (k + n − 1)` |
| Max speedup (large n) | `≈ k` |
 
*A 5-stage pipeline → max theoretical speedup ≈ 5.*
 
### Hazards
 
| Hazard | Cause | Fixes |
|---|---|---|
| **Structural** | Two instructions need the same hardware simultaneously (e.g., shared memory for fetch + data) | Separate resources, separate I/D caches, stalling |
| **Data** | An instruction needs a result not yet produced (`ADD R1,R2,R3` → `SUB R4,R1,R5`) | Stalling, forwarding/bypassing, scheduling |
| **Control** | Branches/jumps — next instruction uncertain | Stalling, branch prediction, speculative execution, delayed branching |
 
---
 
## 15. Cycle Hierarchy
 
**Instruction Cycle ≥ Machine Cycle ≥ Clock Cycle**
 
- Clock cycle: one clock period
- Machine cycle: one basic operation (e.g., memory read/write); ≥1 clock cycles
- Instruction cycle: full fetch-decode-execute; ≥1 machine cycles
---
 
## 16. CPU Performance
 
$$\text{CPU Time} = \text{Instruction Count} \times \text{CPI} \times \text{Clock Cycle Time} = \dfrac{\text{IC} \times \text{CPI}}{\text{Clock Rate}}$$
 
**Levers:** ↓instruction count · ↓CPI · ↓cycle time · ↑clock frequency · better pipelining/branch prediction/caching · ILP · multi-core · SIMD/vector · compiler optimization
 
---
 
## 17. Pipelining vs. Parallel Processing
 
| | Pipelining | Parallel Processing |
|---|---|---|
| Mechanism | Overlaps *stages* of multiple instructions | Multiple units execute *separate tasks* simultaneously |
| Analogy | One assembly line, staggered products | Multiple assembly lines running at once |
 
---
 
## 18. Build Process: ASM → HEX
 
```
.asm --[Assembler]--> .obj --[Linker]--> .abs --[HEX Converter]--> .hex --[Programmer]--> MCU Memory
```
 
| File | Produced by | Contains |
|---|---|---|
| `.asm` | Programmer | Assembly source code |
| `.obj` | Assembler | Machine code, symbols, relocation info (addresses not final) |
| `.abs` | Linker | Resolved symbols + final memory addresses |
| `.hex` | HEX converter | Flash-programmable machine code |
 
---
 
## Cheat-Sheet Summary
 
| Topic | Key takeaway |
|---|---|
| Voltage divider | `Vout = Vin·R2/(R1+R2)` |
| MAX232 | UART ↔ RS-232 level conversion |
| Bit masking | AND=read/clear · OR=set · XOR=toggle |
| Von Neumann | Shared memory/bus |
| Harvard | Separate memory/bus |
| Modified Harvard | Separate cache, shared main memory |
| RISC | Simple, load/store, pipeline-friendly |
| CISC | Complex, variable-length, many addressing modes |
| ARM | RISC-based ISA family (not RISC itself) |
| VLIW | Compiler-scheduled parallel ops per instruction |
| Pipelining | `(k+n−1)t`, speedup `nk/(k+n−1)`, boosts throughput |
| Hazards | Structural / Data / Control |
| CPU time | `IC × CPI × Cycle Time` |
| Pipelining vs. parallelism | Overlap stages vs. simultaneous tasks |
| Toolchain | `.asm → .obj → .abs → .hex → MCU` |
