# External Peripherals

---

# Electromagnetic Relays (EMRs)

## What is a Relay?

A relay is an electrically operated switch that allows a low-power control circuit to switch a high-power electrical load. It provides electrical isolation between the control circuit and the load circuit, making it useful in applications where a microcontroller or other low-voltage device needs to control high-voltage or high-current equipment.

## Working Principle

An electromagnetic relay mainly consists of a **coil**, an **armature**, a **spring**, and a **set of contacts**.

When current flows through the coil, it generates a magnetic field that attracts the armature. This movement changes the position of the contacts, either closing or opening the circuit connected to the load. When the coil is de-energized, the spring returns the armature to its original position.

Electromagnetic relays have three common terminals:

- Common (COM)
- Normally Open (NO)
- Normally Closed (NC)

In the normal state, the COM terminal is connected to the NC terminal. When the relay coil is energized, the COM terminal switches to the NO terminal.

## Types of Electromagnetic Relays Based on Contacts

### SPST (Single Pole Single Throw)

Has one input and one output contact. It acts as a simple ON/OFF switch and is used to control a single circuit.

### SPDT (Single Pole Double Throw)

Has one common terminal that can connect to either of two outputs (NO or NC). It is used to switch between two circuits.

### DPDT (Double Pole Double Throw)

Consists of two SPDT switches operated by the same coil. It can simultaneously switch two separate circuits and is commonly used in applications such as motor direction control.

## Need for Relay Driver

The relay coil requires a certain amount of current to produce the magnetic field needed to operate the relay. However, the output pins of a microcontroller can supply only a limited amount of current, which is often insufficient to energize the relay coil. Connecting the relay directly to the microcontroller may prevent the relay from operating properly and can even damage the microcontroller.

To overcome this limitation, a relay driver circuit is used. The relay coil is connected to the power supply through a transistor, which acts as an electronic switch. The microcontroller output is connected to the base (or gate) of the transistor through a resistor. When the microcontroller outputs a HIGH signal, a small current flows into the transistor, turning it ON. The transistor then allows a much larger current from the external power supply to flow through the relay coil, energizing it. When the microcontroller outputs a LOW signal, the transistor turns OFF, stopping the current through the coil and de-energizing the relay.

---

# Solid State Relays (SSRs)

## Working Principle

A Solid-State Relay (SSR) operates by using semiconductor devices instead of mechanical contacts.

When a control voltage is applied to the input terminals, it powers an internal LED. The light emitted by the LED is detected by a photosensitive device, such as a phototriac or phototransistor, which provides electrical isolation between the input and output circuits.

This photosensitive device then triggers a power semiconductor, such as a TRIAC, thyristor (SCR), or MOSFET, allowing current to flow through the load.

When the input signal is removed, the semiconductor switches OFF, interrupting the current to the load.

Since no moving parts are involved, SSRs provide silent operation, high switching speed, and a long service life.

---

# Optoisolators (Optocouplers)

## What is an Optoisolator?

An optoisolator, also known as an optocoupler, is an electronic device that transfers electrical signals between two isolated circuits using light.

It provides galvanic isolation, meaning there is no direct electrical connection between the input and output circuits. This protects sensitive electronic components, such as microcontrollers, from high voltages, electrical noise, and voltage spikes present in the load circuit.

## Working Principle

An optoisolator consists of two main components enclosed in a single package:

- Light-emitting diode (LED)
- Photosensitive device (phototransistor, photodiode, phototriac, or photo-SCR)

When an input voltage is applied, current flows through the internal LED, causing it to emit infrared light. This light falls on the photosensitive device, causing it to conduct.

The conducting photosensitive device then produces the required output signal while maintaining complete electrical isolation between the input and output circuits.

When the input signal is removed, the LED turns OFF, the light disappears, and the photosensitive device stops conducting, turning the output OFF.

---

# Stepper Motors

## What is a Stepper Motor?

A stepper motor is a brushless, synchronous electric motor that converts electrical pulses into precise angular movement.

Unlike a conventional DC motor, which rotates continuously when supplied with power, a stepper motor rotates in discrete angular steps. Each input pulse causes the motor shaft to rotate by a fixed angle, making stepper motors ideal for applications requiring accurate position and speed control.

## Types of Stepper Motors

Stepper motors are classified into three main types:

- Permanent Magnet (PM) Stepper Motor
- Variable Reluctance (VR) Stepper Motor
- Hybrid Stepper Motor

### Permanent Magnet Stepper Motor

A Permanent Magnet (PM) stepper motor has a rotor made of permanent magnets and a stator with electromagnetic windings. When the stator windings are energized in sequence, the magnetic poles attract and repel the rotor poles, causing the rotor to rotate in discrete steps.

PM stepper motors provide good torque and are commonly used in low-cost positioning applications.

### Variable Reluctance Stepper Motor

A Variable Reluctance (VR) stepper motor has a soft iron rotor with toothed poles but no permanent magnets.

The stator contains multiple windings that are energized one after another. The rotor always moves to the position where the magnetic reluctance is minimum, aligning its teeth with the energized stator poles.

VR motors have high stepping accuracy and fast response but generally produce lower torque than permanent magnet and hybrid stepper motors.

### Hybrid Stepper Motor

A Hybrid Stepper Motor combines the features of both permanent magnet and variable reluctance stepper motors.

It has a permanent magnet rotor with finely toothed poles and a toothed stator.

Hybrid stepper motors provide high torque, excellent positioning accuracy, and small step angles, making them the most widely used type in robotics, 3D printers, and industrial automation.

## Working Principle

A hybrid stepper motor consists of a toothed stator carrying multiple phase windings and a permanent magnet rotor divided into two toothed sections with opposite magnetic polarities (North and South). The teeth of the two rotor sections are slightly offset from each other by half a tooth pitch.

When one stator phase is energized, it creates magnetic poles that attract the corresponding rotor teeth while repelling opposite poles.

As the stator phases are energized sequentially according to a predefined excitation sequence, the magnetic field rotates around the stator.

The rotor continuously aligns itself with the energized stator poles, moving one fixed step for every input pulse. Each pulse rotates the shaft by one step angle.

Continuous application of pulses produces continuous rotation, while reversing the excitation sequence reverses the direction of rotation.

Since the rotor follows the rotating magnetic field one step at a time, the motor can achieve precise position control without requiring a feedback sensor in many applications.

## Stepper Motor Formulae

### Step Angle (θ)

```text
Step Angle (θ) = 360° / Number of Steps per Revolution
```

where:

- θ = Step angle (degrees)
- Nr = Number of rotor teeth

### Number of Steps per Revolution

```text
Steps per Revolution = 360° / Step Angle
```

## Unipolar and Bipolar Stepper Motors

Stepper motors can also be classified according to their winding arrangement.

### Unipolar Stepper Motor

A unipolar stepper motor has center-tapped windings, allowing current to flow through only one half of each winding at a time.

Since the current direction does not need to be reversed, the driver circuit is simple. However, only half of the winding is energized at any instant, resulting in lower torque.

### Bipolar Stepper Motor

A bipolar stepper motor has windings without center taps.

To reverse the magnetic field, the current direction through each winding must be reversed using an H-bridge driver.

Because the entire winding is used, bipolar motors produce higher torque and better efficiency than unipolar motors.

---

# DC Motors

## What is a DC Motor?

A DC (Direct Current) motor is an electrical machine that converts electrical energy into mechanical rotational energy.

It operates on the principle that a current-carrying conductor placed in a magnetic field experiences a mechanical force.

DC motors are widely used because they provide high starting torque, simple speed control, and smooth continuous rotation.

## Working Principle

A DC motor works on the principle that a current-carrying conductor placed in a magnetic field experiences a force. This principle is described by Fleming's Left-Hand Rule.

When a DC supply is applied to the motor, current flows through the armature conductors. The magnetic field produced by the field winding (or permanent magnets) interacts with the magnetic field produced by the armature current.

This interaction creates equal and opposite forces on opposite sides of the armature, producing a turning effect known as torque.

As the armature rotates, the commutator reverses the direction of current in each armature coil every half revolution. This ensures that the direction of torque remains the same, allowing the motor to rotate continuously in one direction.

---

# Pulse Width Modulation (PWM)

## What is PWM?

Pulse Width Modulation (PWM) is a technique used to control the average voltage or power delivered to an electrical load by varying the width of a series of digital pulses.

Instead of changing the supply voltage, PWM controls the amount of power supplied by modifying the pulse width (ON time) while keeping the voltage amplitude and frequency constant.

PWM is widely used for controlling the speed of DC motors, the brightness of LEDs, the position of servo motors, and power conversion circuits.

## Working Principle

A PWM signal consists of a sequence of rectangular pulses that alternate between HIGH and LOW states.

The time for which the signal remains HIGH is called the pulse width (ON time), while the time for which it remains LOW is called the OFF time.

PWM works by modifying the pulse length, i.e., changing the duration of the HIGH pulse while keeping the total time period approximately constant.

Increasing the pulse width increases the average voltage delivered to the load, while decreasing the pulse width reduces the average voltage.

For example, if a PWM signal has a 12 V amplitude:

- A pulse that remains HIGH for 25% of the time provides an average voltage of approximately 3 V.
- A pulse that remains HIGH for 50% of the time provides an average voltage of approximately 6 V.
- A pulse that remains HIGH for 75% of the time provides an average voltage of approximately 9 V.

Although the supply voltage always switches between 0 V and 12 V, the load experiences a lower average voltage because of the rapid switching.

## Duty Cycle

The duty cycle is the percentage of one complete cycle during which the PWM signal remains in the HIGH state.

```text
Duty Cycle (%) = (TON / T) × 100
```

where:

- TON = ON time (pulse width)
- T = Total time period (TON + TOFF)

Examples:

- 25% Duty Cycle → Signal is HIGH for 25% of the cycle.
- 50% Duty Cycle → Signal is HIGH for half of the cycle.
- 75% Duty Cycle → Signal is HIGH for 75% of the cycle.
- 100% Duty Cycle → Signal remains continuously HIGH.
