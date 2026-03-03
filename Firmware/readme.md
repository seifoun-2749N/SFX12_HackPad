# SFX12 Hackpad

Custom macropad — 12 keys + rotary encoder | Seeeduino XIAO (SAMD21) | Windows

---

## Physical Layout

```
[ ENC  ]              [ PS/PR  ]  [ DC/AE  ]             <- ROW 0: Apps
          [ F360/V ]  [ KCD/AR ]  [ YTM/WA ]  [ AI/SL ]  <- ROW 1: Apps
          [ TSK/SET]  [ GPU/AU ]  [MUTE/SS ]  [LOCK/DSK]  <- ROW 2: Shortcuts
                      [ RGB TOG]  [ RGB MOD]               <- ROW 3: RGB
```

Single tap = left action | Double tap = right action
Encoder: CCW = Vol Down | CW = Vol Up

---

## Key Reference

| Key | Single Tap      | Double Tap               | Row       |
|-----|-----------------|--------------------------|-----------|
| K01 | Photoshop       | Premiere Pro             | Apps      |
| K02 | Discord         | After Effects            | Apps      |
| K03 | Fusion 360      | VS Code                  | Apps      |
| K04 | KiCad           | Arduino IDE              | Apps      |
| K05 | YouTube Music   | WhatsApp                 | Apps      |
| K06 | Illustrator     | Streamlabs               | Apps      |
| K07 | Task Manager    | Settings (Win+I)         | Shortcuts |
| K08 | GPU Refresh     | Audio Output Switch      | Shortcuts |
| K09 | Mic Mute        | Screenshot (Win+Shift+S) | Shortcuts |
| K10 | Lock PC (Win+L) | Show Desktop (Win+D)     | Shortcuts |
| K11 | RGB Toggle      | -                        | RGB       |
| K12 | RGB Mode cycle  | -                        | RGB       |

---

## Audio Output Switch Setup (K08 double-tap)

### Step 1 - Install AudioDeviceCmdlets (PowerShell as Admin)
```powershell
Install-Module -Name AudioDeviceCmdlets -Force
```

### Step 2 - Save as C:\Users\<YourName>\switch_audio.ps1
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

### Step 3 - Allow scripts (one-time)
```powershell
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
```

---

## App Launch Notes

Apps using Win+R: photoshop, discord, code, afterfx, illustrator, Adobe Premiere Pro
Apps using Windows Search: Fusion 360, KiCad, Arduino IDE, WhatsApp, Streamlabs
YouTube Music opens via browser: https://music.youtube.com

Tip: If Win+R does not open an app, add its install folder to Windows PATH via
System > Advanced System Settings > Environment Variables.

---

## Tap Dance Timing

TAPPING_TERM = 200ms (in config.h)
- Double-taps feel too fast? Increase to 250 or 300
- Accidental double-taps? Decrease to 150

---

## Build and Flash

```bash
qmk compile -kb sfx12_hackpad -km default
qmk flash -kb sfx12_hackpad -km default
```

Enter bootloader: double-tap reset on the XIAO, or hold matrix [0,0] while plugging in.
