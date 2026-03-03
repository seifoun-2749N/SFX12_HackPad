# SFX12 Hackpad

<div align="center">

<!-- Add your banner/hero image here -->
![SFX12 Hackpad Banner](images/banner.png)

**A custom 12-key macropad with rotary encoder and WS2812B RGB LEDs, powered by QMK firmware.**

[![QMK Firmware](https://img.shields.io/badge/QMK-Firmware-blue?logo=qmk)](https://qmk.fm/)
[![License](https://img.shields.io/badge/License-Open%20Hardware-green)](LICENSE)
[![MCU](https://img.shields.io/badge/MCU-Seeeduino%20XIAO-red)](https://wiki.seeedstudio.com/Seeeduino-XIAO/)
[![KiCad](https://img.shields.io/badge/PCB-KiCad-blue)](https://www.kicad.org/)

</div>

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware](#hardware)
- [PCB & Schematic](#pcb--schematic)
- [Physical Layout](#physical-layout)
- [Keymap](#keymap)
- [RGB Lighting](#rgb-lighting)
- [Firmware Setup](#firmware-setup)
- [Audio Output Switch](#audio-output-switch)
- [App Launch Notes](#app-launch-notes)
- [Customization](#customization)
- [Build Guide](#build-guide)
- [Maintainer](#maintainer)

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
| Col 0     | A2       | `A2`           |
| Col 1     | A1       | `A1`           |
| Col 2     | A10      | `A10`          |
| Col 3     | A11      | `A11`          |
| Row 0     | A4       | `A4`           |
| Row 1     | A5       | `A5`           |
| Row 2     | A6       | `A6`           |
| Row 3     | A7       | `A7`           |
| Encoder A | A0       | `A0`           |
| Encoder B | A3       | `A3`           |
| RGB Data  | B9       | `B9`           |

---

## PCB & Schematic

<!-- Add your PCB front render here -->
### PCB Front
![PCB Front](images/pcb_front.png)

<!-- Add your PCB back render here -->
### PCB Back
![PCB Back](images/pcb_back.png)

<!-- Add your schematic screenshot/export here -->
### Schematic
![Schematic](images/schematic.png)

<!-- Add your KiCad 3D render here -->
### 3D Render
![3D Render](images/3d_render.png)

The PCB was designed from scratch in **KiCad**. The key matrix uses a standard COL2ROW diode configuration with 1N4148 diodes. The WS2812B LEDs are daisy-chained from pin B9. The EC11 encoder sits in the top-left corner of the board, with its A/B signal lines routed to A0 and A3 on the XIAO.

> KiCad project files (schematic, PCB layout, gerbers) are in the `/pcb` directory.

---

## Physical Layout

```
[ ENC  ]              [ K01   ]  [ K02   ]
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
| Press        | — (not available on this build) |

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

<!-- Add an RGB showcase photo here -->
### RGB Showcase
![RGB Lighting](images/rgb_showcase.jpg)

---

## Firmware Setup

### Prerequisites

- [QMK MSYS](https://msys.qmk.fm/) installed (Windows), or QMK CLI on macOS/Linux
- USB-C cable

### Installation

**1. Copy the keyboard folder into QMK:**
```
qmk_firmware/
  keyboards/
    sfx12_hackpad/        ← place this folder here
      keyboard.json
      config.h
      rules.mk
      keymaps/
        default/
          keymap.c
```

**2. Compile:**
```bash
qmk compile -kb sfx12_hackpad -km default
```

**3. Flash:**
```bash
qmk flash -kb sfx12_hackpad -km default
```

### Entering Bootloader Mode

There are two ways to enter bootloader on the Seeeduino XIAO:

- **Double-tap** the reset button on the back of the XIAO — the board appears as a USB drive
- **Bootmagic** — hold the top-left matrix key (position [0,0]) while plugging in USB

QMK will flash the firmware automatically when using `qmk flash`.

### Adjusting Tap Dance Timing

The double-tap detection window is **200ms** by default. Change it in `config.h`:

```c
#define TAPPING_TERM 200
```

| Value  | Best for                                |
|--------|-----------------------------------------|
| `150`  | Fast typists, quick double-taps         |
| `200`  | Default, suits most users               |
| `250`  | If double-taps feel rushed              |
| `300`  | Relaxed tapping, occasional accidentals |

---

## Audio Output Switch

Double-tapping **K08** runs a PowerShell script that cycles through your active audio playback devices — for example, from headphones to speakers to a USB headset and back again.

### Step 1 — Install AudioDeviceCmdlets

Open **PowerShell as Administrator**:

```powershell
Install-Module -Name AudioDeviceCmdlets -Force
```

### Step 2 — Create the Script

Save the following file as `C:\Users\<YourName>\switch_audio.ps1`:

```powershell
Import-Module AudioDeviceCmdlets

$devices = Get-AudioDevice -List | Where-Object { $_.Type -eq 'Playback' }
$current = (Get-AudioDevice -Playback).ID
$idx = 0

for ($i = 0; $i -lt $devices.Count; $i++) {
    if ($devices[$i].ID -eq $current) { $idx = $i; break }
}

$next = $devices[($idx + 1) % $devices.Count]
Set-AudioDevice -ID $next.ID
```

### Step 3 — Allow Script Execution (one-time only)

```powershell
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
```

After this setup, each double-tap of K08 silently switches to the next audio device in your list.

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

## Customization

The keymap is straightforward to modify. All logic lives in `keymaps/default/keymap.c`.

### Change What a Key Does

Find the tap dance callback for the key and edit the actions:

```c
// Example: change K01 from Photoshop/Premiere to Blender/Figma
void td_ps_pr_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1)      launch_search("Blender");
    else if (state->count == 2) launch_run("figma");
}
```

### Available Helper Functions

```c
launch_run("discord");              // Win+R → type command → Enter
launch_search("Arduino IDE");       // Win → type name → Enter
run_ps_script("my_script.ps1");     // runs a .ps1 from your user folder
```

### Send a Key Combination

```c
register_code(KC_LCTL);
register_code(KC_LSFT);
tap_code(KC_Z);                     // Ctrl+Shift+Z
unregister_code(KC_LSFT);
unregister_code(KC_LCTL);
```

### Set a Default RGB Color on Startup

Add this to the bottom of `keymap.c`:

```c
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_CYAN);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
}
```

Available colors: `HSV_RED` `HSV_GREEN` `HSV_BLUE` `HSV_CYAN` `HSV_MAGENTA` `HSV_YELLOW` `HSV_WHITE` `HSV_ORANGE` `HSV_PURPLE`

---

## Build Guide

<!-- Add build step photos as you go — suggested filenames below -->

### Step 1 — Solder the Diodes
![Diodes](images/build_01_diodes.jpg)
Solder all 12× 1N4148 diodes to the PCB. Pay attention to orientation — the cathode (black stripe) must face the column direction (COL2ROW). Bend the legs flat before inserting.

### Step 2 — Solder the Switches
![Switches](images/build_02_switches.jpg)
Press all 12 MX-compatible switches into the PCB footprints and solder from the back. Make sure each switch sits flush before soldering.

### Step 3 — Solder the Encoder
![Encoder](images/build_03_encoder.jpg)
Seat the EC11 encoder and solder all 5 pins — 2 for the push button and 3 for the rotary signal. The encoder should sit flat without rocking.

### Step 4 — Solder the WS2812B LEDs
![LEDs](images/build_04_leds.jpg)
Solder the 6 WS2812B LEDs carefully — they are sensitive to heat. Work quickly with a clean iron tip. Check the notched corner of each LED matches the PCB silkscreen marker for correct orientation.

### Step 5 — Solder the Seeeduino XIAO
![XIAO](images/build_05_xiao.jpg)
Solder the XIAO to its footprint on the board. Ensure all pads make solid contact. After soldering, check for bridges across adjacent pads.

### Step 6 — Flash & Test
Connect the board via USB-C and flash the firmware using `qmk flash`. Before assembling the case, test every key and the encoder using an online keyboard tester to confirm the matrix is wired correctly.

<!-- Add your finished build photo here -->
### Finished Build
![Finished Build](images/build_finished.jpg)

---

## Maintainer

**Seif Eddine Chatti**
GitHub: [@seifoun-2749N](https://github.com/seifoun-2749N)

---

## License

Open source hardware. Feel free to study, modify, and build your own version.

---

<div align="center">
Made with ❤️ and too much solder
</div>
