# Design-of-an-Educational-Dual-Core-Music-Synthesizer
A bespoke, hybrid (analogue-digital) music synthesizer designed as an interactive pedagogical tool for engineering students to master foundational analogue electronics concepts.

## 📖 Project Overview

Analogue electrical concepts often prove difficult for engineering students to master through theory alone. This project bridges that gap. By modelling a subtractive synthesis architecture using fundamental analogue subsystems (oscillators, mixers, active filters), this synthesizer provides a direct, multisensory feedback loop. 

Students can observe raw mathematical transfer functions physically manifesting on an oscilloscope and audibly changing in real-time, bridging the gap between theoretical equations and physical electronics.

### 🎯 Key Educational Objectives

This project was developed for a final-year BEng Electronic and Electrical Engineering module, demonstrating:
* **Signal Generation:** Constructing stable Voltage-Controlled Oscillators (VCOs) using op-amp integrators and Schmitt triggers.
* **Signal Combination:** Utilizing summing amplifiers for harmonic mixing and practical demonstrations of signal heterodyning (beat frequencies).
* **Active Filtering:** Implementing and mathematically verifying a second-order Sallen-Key low-pass filter (-12 dB/octave roll-off).
* **Digital Control:** Bridging embedded C++ (Arduino) with physical hardware via SPI communication to control MCP4201 digital potentiometers.

---

## 🛠️ System Architecture

The synthesizer utilizes a **hybrid analogue-digital design**, ensuring robust analogue signal processing is paired with precise digital sequencing.

*See the `schematics/` folder for full Multisim circuit diagrams.*

### 1. Signal Generation (VCO Stage)
* **Core:** Two independent relaxation oscillators.
* **Op-Amps:** TL082CN J-FET op-amps (chosen for high 1 TΩ input impedance and 13 V/µs slew rate).
* **Waveforms:** Concurrently outputs linear triangular waves and sharp pulse waves (f ≈ 100 Hz per 1 V input).

### 2. Signal Combination (Mixer Stage)
* **Topology:** Two-stage inverting summing amplifiers.
* **Output:** Generates a harmonically dense 30 V peak-to-peak master mix, successfully driving the op-amps to their ±15 V physical limits.

### 3. Filtering Stage (VCF)
* **Topology:** Second-order Sallen-Key low-pass filter.
* **Parameters:** Designed with 5.6 nF capacitors and 33 kΩ resistors for a strict 861.2 Hz cut-off frequency.

### 4. Digital Control
* **Microcontroller:** Arduino.
* **Interface:** MCP4201 digital potentiometer (8-bit resolution, SPI protocol).
* **Function:** Translates digital pitch commands into precise DC voltage levels to drive the VCOs.

---

## 🔬 Experimental Validation

The system's functionality was strictly validated using a Keysight DSOX1102G oscilloscope.

* **Hardware Tolerances & Heterodyning:** Component tolerances (±10% capacitors) caused a measured 72.1 Hz frequency mismatch between the two VCOs. The mixing stage utilized this to generate a distinct 71.43 Hz beat frequency (a 0.93% error margin from theory).
* **Filter Roll-off (FFT Analysis):** Fast Fourier Transform data proved the Sallen-Key filter behaved exactly as predicted by linear network theory. Harmonics two octaves above the cut-off (3444 Hz) experienced a measured magnitude drop of 24 dB, confirming the -12 dB/octave specification.
* **Digital Quantization Limits:** Experimental testing confirmed that the Arduino's 8-bit output resolution causes predictable frequency drift (max error margin 0.32%), providing a tangible lesson on the limits of digital-to-analogue conversion.

---
