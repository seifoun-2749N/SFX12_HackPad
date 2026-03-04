# SFX12 Hackpad

<div align="center">

<!-- Add your banner/hero image here -->
<img width="1920" height="1080" alt="Affiche HackPad(1)" src="https://github.com/user-attachments/assets/a0ad608b-c370-4724-a11c-bca920ab98a2" />


**A custom 12-key macropad with rotary encoder and WS2812B RGB LEDs, powered by QMK firmware.**

</div>

---

## Overview

The **SFX12 Hackpad** is a fully custom macropad designed for creatives, developers, and power users who want instant one-tap access to their most-used applications and keyboard shortcuts — without ever reaching for the mouse or memorizing complex key combinations.

Built around the **Seeeduino XIAO (SAMD21)**, it packs 12 mechanical switches into an irregular, ergonomic layout alongside a rotary encoder for hardware volume control and a chain of **WS2812B RGB LEDs** for per-board lighting effects. The entire firmware runs on **QMK**, giving complete control over every key, every tap, and every LED.

The standout feature is **tap dance**: every key is double-mapped — a single tap triggers one action, a double tap triggers another. This gives **24 unique actions** across just 12 physical keys, with no layer switching required.

<!-- Add an overview/hero photo of the finished build here -->
![Assembled Build](images/assembled.jpg)

---

## Features

- **12 mechanical switches** in a compact, irregular layout
- **Rotary encoder** (EC11) for smooth hardware volume control
- **6× WS2812B RGB LEDs** with 7 animation modes
- **Tap dance on every key** — single tap and double tap, 24 total actions
- **12 app launchers** across rows 0 and 1 via Win+R and Windows Search
- **Dedicated shortcut row** — Task Manager, GPU refresh, audio switch, screenshot, lock PC, show desktop
- **Audio output cycling** via PowerShell — instantly switch between headphones, speakers, and headsets
- **QMK firmware** — fully open source and endlessly customizable
- **Bootmagic** support — enter bootloader without a physical button press
- **Custom KiCad PCB** — fully documented schematic and layout files included

---

## Hardware

| Component  | Part              | Details                               |
|------------|-------------------|---------------------------------------|
| MCU        | Seeeduino XIAO    | SAMD21G18, 3.3V logic, USB-C          |
| Switches   | MX-compatible     | 12× mechanical switches               |
| Encoder    | EC11              | Rotary encoder with push button       |
| LEDs       | WS2812B           | 6× addressable RGB LEDs               |
| Diodes     | 1N4148            | 12× signal diodes, COL2ROW wiring     |
| PCB        | Custom design     | Designed in KiCad                     |
| Firmware   | QMK               | Open source keyboard firmware         |
| Connection | USB-C             | Via onboard Seeeduino XIAO port       |

### Pin Mapping

| Function  | XIAO Pin | QMK Identifier |
|-----------|----------|----------------|
| Col 0     | A0       | `A2`           |
| Col 1     | A1       | `A1`           |
| Col 2     | A2       | `A10`          |
| Col 3     | A3       | `A11`          |
| Row 0     | A4       | `A4`           |
| Row 1     | A5       | `A5`           |
| Row 2     | A6       | `A6`           |
| Row 3     | A7       | `A7`           |
| Encoder A | A8       | `A0`           |
| Encoder B | A9       | `A3`           |
| RGB Data  | A10      | `B9`           |

---

## PCB & Schematic

<!-- Add your PCB front render here -->
### PCB Front
<img width="1724" height="930" alt="PCB" src="https://github.com/user-attachments/assets/1fc76bcb-e276-4f9b-b6f7-b92f15c2396f" />

<!-- Add your PCB back render here -->
### PCB Back
<img width="1724" height="930" alt="PCB Back" src="https://github.com/user-attachments/assets/45b47787-28cd-4190-b4a0-88df3b74f2d1" />

<!-- Add your schematic screenshot/export here -->
### Schematic
<img width="1245" height="868" alt="image" src="https://github.com/user-attachments/assets/d44a2e43-0c7d-47a0-801b-ce79dcd7400f" />

The PCB was designed from scratch in **KiCad**. The key matrix uses a standard COL2ROW diode configuration with 1N4148 diodes. The WS2812B LEDs are daisy-chained from pin B9. The EC11 encoder sits in the top-left corner of the board, with its A/B signal lines routed to A0 and A3 on the XIAO.

> KiCad project files (schematic, PCB layout, gerbers) are in the `/pcb` directory.

---

## Physical Layout

```
[ ENC  ]             [ K01   ]  [ K02   ]
          [ K03   ]  [ K04   ]  [ K05   ]  [ K06   ]
          [ K07   ]  [ K08   ]  [ K09   ]  [ K10   ]
                     [ K11   ]  [ K12   ]
```

The layout is intentionally irregular — the encoder sits alone in the top-left, the two middle rows are full width with 4 keys each, and the bottom row has 2 keys centered underneath.

### Row Assignment

| Row   | Keys              | Function    |
|-------|-------------------|-------------|
| Row 0 | ENC, K01, K02     | Apps        |
| Row 1 | K03, K04, K05, K06 | Apps       |
| Row 2 | K07, K08, K09, K10 | Shortcuts  |
| Row 3 | K11, K12          | RGB Control |

---

## Keymap

All 12 keys use **tap dance** — tap once for the primary action, tap twice within 200ms for the secondary action.

### Rows 0 & 1 — App Launchers

```
[ ENC  ]              [ PS/PR  ]  [ DC/AE  ]
          [ F360/VS]  [ KCD/AR ]  [ YTM/WA ]  [ AI/SL ]
```

| Key | Single Tap    | Double Tap    | Launch Method       |
|-----|---------------|---------------|---------------------|
| K01 | Photoshop     | Premiere Pro  | Win+R               |
| K02 | Discord       | After Effects | Win+R               |
| K03 | Fusion 360    | VS Code       | Windows Search / Win+R |
| K04 | KiCad         | Arduino IDE   | Windows Search      |
| K05 | YouTube Music | WhatsApp      | Browser / Search    |
| K06 | Illustrator   | Streamlabs    | Win+R / Search      |

### Row 2 — Shortcuts

```
          [ TSK/SET]  [ GPU/AU ]  [MUTE/SS ]  [LOCK/DSK]
```

| Key | Single Tap      | Double Tap               | Keys / Method              |
|-----|-----------------|--------------------------|----------------------------|
| K07 | Task Manager    | Settings (Win+I)         | Ctrl+Shift+Esc / Win+I     |
| K08 | GPU Refresh     | Audio Output Switch      | Alt+Ctrl+Shift+B / Script  |
| K09 | Mic Mute        | Screenshot               | Media key / Win+Shift+S    |
| K10 | Lock PC         | Show Desktop             | Win+L / Win+D              |

### Row 3 — RGB Control

```
                     [RGB TOG ]  [RGB MOD ]
```

| Key | Action                        |
|-----|-------------------------------|
| K11 | Toggle RGB lighting on / off  |
| K12 | Cycle to next RGB mode        |

### Encoder

| Action       | Result      |
|--------------|-------------|
| Rotate left  | Volume Down |
| Rotate right | Volume Up   |
| Press        | Mute        |

---

## RGB Lighting

6 WS2812B LEDs are driven from pin B9. Toggle on/off with **K11**, cycle modes with **K12**.

| Mode            | Description                                      |
|-----------------|--------------------------------------------------|
| Static          | Solid color — set hue, saturation, and brightness|
| Breathing       | Slowly pulses brightness up and down             |
| Rainbow Mood    | Gradually cycles through the full hue spectrum   |
| Rainbow Swirl   | Hue rotates across all LEDs simultaneously       |
| Snake           | A lit segment chases around the board            |
| Knight          | Back-and-forth scanning light effect             |
| Static Gradient | Two-color gradient spread across all LEDs        |

---

## App Launch Notes

Apps are launched using two methods:

- **Win+R** — opens the Run dialog, types the command, presses Enter. Fast for apps with a registered run command in Windows PATH.
- **Windows Search** — presses Win, types the app name, presses Enter. Used when the app has no run command.

| App           | Method         | Command / Term              |
|---------------|----------------|-----------------------------|
| Photoshop     | Win+R          | `photoshop`                 |
| Premiere Pro  | Win+R          | `Adobe Premiere Pro`        |
| Discord       | Win+R          | `discord`                   |
| After Effects | Win+R          | `afterfx`                   |
| VS Code       | Win+R          | `code`                      |
| Illustrator   | Win+R          | `illustrator`               |
| Fusion 360    | Windows Search | `Fusion 360`                |
| KiCad         | Windows Search | `KiCad`                     |
| Arduino IDE   | Windows Search | `Arduino IDE`               |
| WhatsApp      | Windows Search | `WhatsApp`                  |
| Streamlabs    | Windows Search | `Streamlabs`                |
| YouTube Music | Win+R browser  | `https://music.youtube.com` |

> **Win+R not launching the app?**  
> The executable isn't in your Windows PATH. Add it via:  
> `System Properties → Advanced → Environment Variables → Path → New`  
> Paste the folder containing the app's `.exe` (e.g. `C:\Program Files\Adobe\Adobe Photoshop 2025\`)

---

## License

Open source hardware. Feel free to study, modify, and build your own version.

---

<div align="center">
Made with ❤️ and too much solder
</div>
