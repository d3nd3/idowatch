# Toobur / VeryFit protocol workspace

A **GadgetBridge** implementation for Toobur and other IDO/angelfit-like smartwatches (Realtek 0x0AF0 protocol), plus related protocol notes and tooling.

This repository is based on the public [idowatch reference](https://github.com/idoosmart/idowatch), and the local `gadgetbridge/` folder is the working fork maintained at [d3nd3/gadgetbridge-veryfit](https://github.com/d3nd3/gadgetbridge-veryfit).

## Repository layout

- `gadgetbridge/`  
  Main work-in-progress for TOOBUR device support in the GadgetBridge app.
- `research/repositories/`  
  External reference repos kept as gitlink placeholders here for offline reference.  
  Use `research/repositories/README.md` to fetch them after clone.
- Root docs and scripts  
  - [`TOOBUR.md`](TOOBUR.md) – protocol command table, behavior notes, and device compatibility details.
  - [`gadgetbridge_setup.md`](gadgetbridge_setup.md) – cloning, build, and install workflow to run your GadgetBridge mod.

## Watches using the same protocol

- [Ryze](http://ryzeabove.com.au)
- [IDO Smart / Life](https://www.idoosmart.com)
- [Cove](https://www.coveiot.com)
- bfit Move 2
- Toobur, Runlio, Biggerfive (and other IDO/VeryFit “skins”)

## Features

- **Pair + get activity:** Connect via BLE (service 0x0AF0), fetch device info and activity (v3), export TCX.
- **Angelfit protocol panel:** GET (device info, func table, time, MAC, battery, SN info, live data, notice status), SET (find phone, hand, music, DND, call alert on/off, time, up hand, one-key SOS, weather switch, **heart rate on/off**, factory defaults), Control (music, photo, find device, single sport, ANCS), Reboot. See **TOOBUR.md** for the full command table and notes (weather data, watch face upload, GadgetBridge integration, etc.).

## Fork and references

The protocol details, BLE layout (`0x0AF6`, `0x0AF7`, `0x0AF1`, `0x0AF2`), command bytes, and many capture traces in this repo are derived from the public IDO ecosystem references.
TOOBUR.md extends that with Toobur/Realtek hardware notes, firmware protocol details (including chunked `MSG 0x05`), watch face upload (`.iwf` / `.iwf.lz`), and notes for integrating angelfit-like devices into GadgetBridge.

See [`gadgetbridge_setup.md`](gadgetbridge_setup.md) for details on cloning, compiling, and installing the GadgetBridge mod.

## Other references

- **xssfox/idowatch** ([GitHub](https://github.com/xssfox/idowatch)): minimal “Pair + Get Activity” web app, useful for a non-destructive activity-downloader flow.
- **Angelfit** (protocol reference): https://github.com/orangebrush/angelfit (local copy in `research/repositories/angelfit/`).
- **SDK/API docs** from IDO: https://idoosmart.github.io/Flutter_GitBook/en/ (local copy in `research/repositories/Flutter_GitBook/`).
- [veryFit2googlefit](https://github.com/Durun/veryFit2googleFit/tree/master)
- [IAmFit](https://github.com/mmbatha/IAmFit)
