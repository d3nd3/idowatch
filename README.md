# Toobur GadgetBridge implementation

A **GadgetBridge** implementation for Toobur and other IDO/angelfit-like smartwatches (Realtek 0x0AF0 protocol). This repository is **forked from the [idowatch](https://github.com/idoosmart/idowatch) repo**, which provides the protocol reference, web app, and documentation that this implementation builds on.

## Watches using the same protocol

- [Ryze](http://ryzeabove.com.au)
- [IDO Smart / Life](https://www.idoosmart.com)
- [Cove](https://www.coveiot.com)
- bfit Move 2
- Toobur, Runlio, Biggerfive (and other IDO/VeryFit “skins”)

## Features

- **Pair + get activity:** Connect via BLE (service 0x0AF0), fetch device info and activity (v3), export TCX.
- **Angelfit protocol panel:** GET (device info, func table, time, MAC, battery, SN info, live data, notice status), SET (find phone, hand, music, DND, call alert on/off, time, up hand, one-key SOS, weather switch, **heart rate on/off**, factory defaults), Control (music, photo, find device, single sport, ANCS), Reboot. See **TOOBUR.md** for the full command table and notes (weather data, watch face upload, GadgetBridge integration, etc.).

## Forked from idowatch

The protocol details, BLE layout (0x0AF6, 0x0AF7, 0x0AF1, 0x0AF2), command bytes, and reference implementation in this repo are derived from **idowatch**. TOOBUR.md extends that with Toobur/Realtek hardware notes, firmware protocol (call/SMS notifications, chunked MSG 0x05), watch face upload (.iwf/.iwf.lz), and guidance for adding angelfit-like devices to GadgetBridge (device coordinator, support class, initialization). To clone Gadgetbridge, add TOOBUR device support, and build locally, see **gadgetbridge_setup.md**.

## Other works

- **xssfox/idowatch** ([GitHub](https://github.com/xssfox/idowatch)): Minimal “Pair + Get Activity” web app that **does not mark activities as synced**, so VeryFit/Ryze can still sync the same activities. Single-purpose flow and clear limitations; same v3 activity reassembly and `data_activity` layout. Good reference for a minimal, non-destructive activity downloader.
- **Angelfit** (protocol reference): original protocol — https://github.com/orangebrush/angelfit. A copy is in `angelfit/`; TOOBUR.md documents UUIDs, call status 0x05 0x02 0x01, get notice status 0x02 0x10.
- SDK/API documentation from IDO — https://idoosmart.github.io/Flutter_GitBook/en/
- [veryFit2googlefit](https://github.com/Durun/veryFit2googleFit/tree/master)
- [IAmFit](https://github.com/mmbatha/IAmFit)
