# Smart-AC-Modernizer: Reverse Engineering Legacy IR Protocols

![Project Header](assets/ac_project_banner.jpg)
*(Note: Upload a photo of your ESP32 connected to the AC or the breadboard setup here)*

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Platform](https://img.shields.io/badge/Platform-ESP32-green.svg)
![Protocol](https://img.shields.io/badge/Protocol-NEC%20(112--bit)-orange.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

### 🎯 The Mission
To retrofit a non-smart, legacy **Haier Air Conditioner (Model YRW02)** with modern Cloud/IoT capabilities without modifying the internal appliance hardware.

This project focuses on the **Physical Layer** of IoT: reverse-engineering the proprietary infrared (IR) signal timings, decoding the stateful packet structure, and building a bridge between digital cloud triggers (Blynk) and analog IR hardware.

> **Note:** This research served as the foundational study on IR signal latency that enabled the high-speed synchronization in my primary project: [**Distributed-Room-Ecosystem**](https://github.com/YOUR_USERNAME/Distributed-Room-Ecosystem).

---

### 🕵️‍♂️ The Engineering Challenge: "Stateful" Packets
Unlike simple TV remotes that send a single command (e.g., "Volume Up"), AC remotes send the **entire state** of the machine in every single button press.

**Discovery:**
Through raw signal analysis using a **TSOP4838** receiver, I discovered that this specific Haier remote transmits a massive **112-bit data packet** encoded with a variant of the NEC protocol.



**The Packet Structure (14 Bytes):**
```cpp
// Example: Turn ON, Cool Mode, 24°C, High Fan, Swing Middle
// A complete snapshot of the machine's state is sent with every press.
0xA6 0x82 0x00 0x00 0x40 0x20 0x00 0x20 0x00 0x00 0x00 0x00 0x00 0xA8

```

* **Byte 0:** Header/Model ID
* **Byte 1:** Command Type
* **Byte 5:** Mode & Fan Speed
* **Byte 7:** Temperature
* **Byte 13:** Checksum/End

*For the full breakdown of raw microsecond timings and hex dumps, see **[docs/Haier_AC_YRW02_Protocol_Analysis.txt](https://www.google.com/search?q=docs/Haier_AC_YRW02_Protocol_Analysis.txt)**.*

---

### ⚡ Hardware Architecture

The system uses an ESP32 as a "Man-in-the-Middle," receiving commands from the cloud and blasting them out via a high-power IR emitter.

#### Schematic Overview

Since standard GPIO pins cannot supply enough current for long-range IR transmission, a transistor driver circuit is required.

```text
       ESP32 GPIO Pin (D4)
            │
            R (220Ω)
            │
      Base ─┴─  (NPN Transistor - 2N2222)
           / \
      GND ─   ─ Collector 
                   │
                   ─ (IR LED Cathode)
                   ▲
                   │ (IR LED Anode)
                   │
                +5V / +3.3V

```

**Components:**

* **MCU:** ESP32 Dev Module
* **Sensor:** TSOP4838 (38kHz IR Receiver) for decoding.
* **Emitter:** 940nm IR LED driven by 2N2222 Transistor.

---

### 📂 Repository Structure

This repository documents the chronological workflow of reverse engineering:

| Folder | Description |
| --- | --- |
| **`/src/01_IR_Protocol_Sniffer`** | **The Tool.** Raw signal dumper used to capture microsecond timings from the OEM remote. |
| **`/src/02_AC_Local_Controller`** | **The Test.** Offline firmware to validate that the decoded hex codes actually trigger the AC. |
| **`/src/03_Blynk_AC_Bridge`** | **The Solution.** Production firmware integrating Wi-Fi & Blynk for remote cloud control. |
| **`/docs`** | Contains `Haier_AC_YRW02_Protocol_Analysis.txt` (Raw Data Logs). |

---

### 🚀 Getting Started

1. **Hardware Setup:** Connect your IR LED (with transistor) to the ESP32 pin defined in the code (default: Pin 4).
2. **Flash the Sniffer:** Upload `01_IR_Protocol_Sniffer` and open the Serial Monitor. Point your AC remote at the ESP32 and press buttons to see the raw data.
3. **Flash the Bridge:** Open `03_Blynk_AC_Bridge`.
* Update `secrets_template.h` (or main code) with your Wi-Fi/Blynk credentials.
* Upload to ESP32.


4. **Control:** Open the Blynk app and trigger the virtual pins to send the decoded IR signals.

---

### 🤝 Acknowledgements

* **IRremoteESP8266 Library:** For providing the underlying timing functions.
* **Blynk IoT:** For the mobile interface dashboard.

### 📜 License

Distributed under the MIT License. See `LICENSE` for more information.

*Built by **Aoun Raza** as part of a distributed smart-home research initiative.*

```

```
