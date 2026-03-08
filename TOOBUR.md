Most of these brands (Toobur, Runlio, Biggerfive) are essentially "skins" for hardware designed and manufactured by a single major OEM: **Shenzhen DO Intelligent Technology Co., Ltd** (commonly known as **IDO**).


Because these devices prioritize low power consumption over high-speed processing, they don't use "mobile" chips like those from Qualcomm. Instead, they use highly integrated **Microcontroller Units (MCUs)**.


While the exact chip can vary by model year, the "VeryFit" ecosystem predominantly uses two silicon suppliers:

- **Nordic Semiconductor:** The **nRF52 series** (like the nRF52832 or nRF52840) is the "gold standard" for this category. These SoCs are famous for their ultra-low-power Bluetooth LE (Low Energy) performance.
    
- **Realtek:** In ultra-budget models (like the Runlio or older Biggerfive models), you’ll often find **Realtek RTL8762 series** chips. These are cheaper alternatives to Nordic but offer similar Bluetooth 5.0/5.1 stability.
    
- **Goodix:** Some newer models with "Bluetooth Calling" features use Goodix chips, which are optimized for handling both high-fidelity audio and low-energy sensor data simultaneously.


### 2. The Bluetooth "Pipeline"

The "VeryFit" pipeline is a standardized communication bridge designed by IDO to allow thousands of different unbranded watches to talk to a single app.

- **The Protocol:** They use **GATT (Generic Attribute Profile)** over Bluetooth Low Energy. The watch acts as a "Server" containing data (attributes) like heart rate or step count, and the VeryFit app acts as the "Client" that requests that data.
    
- **Data Syncing:** Instead of a constant stream, the watch stores data in its local flash memory in small "packets." When you open the app, it triggers a "Sync" command. The MCU packages the stored sensor data into a compressed binary format and sends it over the BLE link.
    
- **Command Pipe:** The pipeline also works in reverse for notifications. When your phone gets a text, the app sends a specific hex code to the watch’s "Notification Characteristic," which the MCU then parses to display text on the screen.



Nordic nRF52840 or Realtek RTL8762

---

### The Verdict: It’s a Realtek SoC

The UUID **0x0AF0** is the proprietary service used by **Realtek Semiconductor** for their Bluetooth Low Energy (BLE) stack, specifically for their "OTA" (Over-the-Air) firmware update process.

- **Chip Family:** You are likely looking at a **Realtek RTL8762 series** chip (most commonly the RTL8762C or RTL8762D).
    
- **Why it's there:** Realtek dominates the budget fitness tracker market because their "SDK" (Software Development Kit) is extremely easy for manufacturers like **IDO (VeryFit)** to implement quickly.


### A Quick Experiment

If you want to see the Realtek "pipeline" in action:

1. In **nRF Connect**, tap on the **0x0AF0** service to expand it.
    
2. Look for a **Characteristic** (usually a long UUID) with the properties **"Write"** or **"Notify"**.
    
3. This is the "tunnel" the VeryFit app uses to push new watch faces or firmware updates to your wrist.

The services you’ve pulled from nRF Connect tell a very specific story. While **0x1800** (Generic Access) and **0x1801** (Generic Attribute) are standard Bluetooth "housekeeping" services found on almost every device

---

#### 1. The Command Center (0x0AF6 & 0x0AF1)

- **Properties:** READ, WRITE, WRITE NO RESPONSE.
    
- **Purpose:** These are the **Inbound Pipes**. When you change a setting in the app (like turning on "Lift to Wake" or setting an alarm), the app writes a hex command to these characteristics.
    
- **Why two?** Usually, one is for "Control Commands" (settings) and the other is for "Bulk Data" (like pushing a new Watch Face file, which requires "Write No Response" for higher speed).

#### 2. The Heartbeat / Live Data (0x0AF7)

- **Properties:** NOTIFY, READ.
    
- **Descriptor (0x2902):** Notifications Enabled.
    
- **Purpose:** This is the **Active Stream**. When this is "Enabled," the watch doesn't wait for the app to ask for data; it "pushes" updates instantly. This is where your **Live Heart Rate** and **Step Count** increments are sent to the phone in real-time while the app is open.

#### 3. The Health Log / Sync (0x0AF2)

- **Properties:** NOTIFY, READ.
    
- **Purpose:** This is the **History Pipe**. When you pull down to sync the app in the morning, the watch uses this characteristic to dump the last 24 hours of sleep and SpO2 data that was stored in its internal flash memory.

---

### Technical Specs of your SoC (Realtek RTL8762D)

Since we've narrowed it down to this chip family, here is what is actually running on your wrist:

- **Processor:** ARM Cortex-M4F (Running at roughly **40MHz to 90MHz**).
    
- **RAM:** Approx. **192KB to 256KB** (Yes, Kilobytes! It’s incredibly efficient).
    
- **Flash:** Usually **64MB to 128MB** of external SPI flash for those watch faces and health logs.
    
- **Bluetooth:** Version **5.0/5.1** Low Energy.

---

### Fun Fact: Why the "0x2902" Descriptor matters

The `0x2902` you see is the **Client Characteristic Configuration Descriptor (CCCD)**. It acts like a light switch.

- If the value is `0x0000`, the watch stays silent to save battery.
    
- When the VeryFit app connects, it writes `0x0100` to that "switch," which tells the Realtek chip: _"Okay, start broadcasting the sensor data now."_

---

| **Feature**        | **Bangle.js 1** | **Bangle.js 2**     | **Realtek RTL8762D**    |
| ------------------ | --------------- | ------------------- | ----------------------- |
| **Core Processor** | Nordic nRF52832 | **Nordic nRF52840** | **Realtek RTL8762D**    |
| **Architecture**   | ARM Cortex-M4   | ARM Cortex-M4F      | ARM Cortex-M4F          |
| **Clock Speed**    | 64 MHz          | 64 MHz              | **Up to 90 MHz**        |
| **On-Chip RAM**    | 64 KB           | **256 KB**          | **160 KB - 192 KB**     |
| **On-Chip Flash**  | 512 KB          | 1 MB                | **Up to 2 MB** (varies) |
| **External Flash** | 4 MB (SPI)      | 8 MB (QSPI)         | Typically 64MB - 128MB* |
| **Bluetooth**      | 4.2             | 5.0                 | **5.1**                 |

---

Capture correction:
- `new_setup.json` shows that the `03:30:55:01:00` packet is a **watch notification on 0x0AF7**, not a host write. It matches the legacy `protocol_set_notice_ack` shape (`notify_switch=0x55`, `status=1`, `err=0`).
- So the earlier **`0x55 = 85 bpm`** guess was wrong: in this capture, generic `0x03` packets are **setup/status replies**, not evidence of live heart-rate streaming.

### Summary

| Item | Finding |
|------|--------|
| Protocol | IDO/Realtek 0x0AF0 service; host writes use 0x0AF6 and watch notifications use 0x0AF7. VeryFit also enables 0x0AF2 notifications, but 0x0AF2 stays silent in this trace. |
| GPS | None (gps_platform: 0). |
| Activity | Reply received but version 0 / all zeros → no stored activity in the watch at capture time. |
| `0x03` packets | In this trace they are setup/status replies (for example `03:30:55:01:00`), not proof of live HR. |
| Reset / wipe | No explicit `03:27` (factory defaults) or `F0:01` (reboot) command appears in the capture. |
| Connection | VeryFit does more setup than idowatch’s minimal `GET info → activity` flow, but the extra packets are configuration/status traffic rather than a visible reset command. |

### TOOBUR A200 (and compatible) vs older angelfit protocol

The following summarizes how **TOOBUR A200** (and firmware that matches the VeryFit logcat dumps in `logcat_dumps/`) differs from the **older angelfit** protocol. The same GATT layout (0x0AF0, write 0x0AF6, notify 0x0AF7, bulk 0x0AF1/0x0AF2) is used; the differences are in command set, payload sizes, and use of the **v3 (0x33) protocol**.

| Aspect | Older angelfit | TOOBUR A200 / VeryFit dumps |
|--------|----------------|-----------------------------|
| **Notice / call alert** | SET 0x03 0x30 with **5-byte** payload (notify_switch, call_switch, call_delay, etc.). | VeryFit uses **20-byte** SET 0x30 (e.g. `03 30 88 00 00 AA` + padding); reply `03 30 88 01 00`. Legacy 5-byte form can reset state on some devices. |
| **Heart rate on/off** | SET 0x03 0x25 (mode 0x55/0x88/0xAA); SET 0x24 (interval); SET 0x52 (real-time sensor). | **Continuous HR / Stress** toggles in the app use **SET 0x45** (on: `03 45 AA ...`, off: `03 45 55 ...`) and **v3 cmd 0x09** (get/set HR mode state). Legacy 0x25/0x52 are not sent by VeryFit for those toggles; GET 0x02 0x08 is sent in a 4× burst after 0x45 changes. |
| **Alarms** | SET 0x03 0x02 (legacy) with 7-byte payload per alarm. | **Alarms are also exposed via v3**: GET alarm = v3 cmd **0x0F** (`33 DA AD DA AD 01 0C 00 0F ...`). SET may still use 0x03 0x02 or v3; dumps confirm **get alarm** as v3. |
| **Do not disturb** | SET 0x03 0x29 (same key). | Same key; payload format matches (e.g. `03 29 AA 17 00 07 00 02 FE 55 17 00 07 00 00 00` for on). **Readback**: GET 0x02 **0xB1** (not in classic angelfit table); reply includes DND state. |
| **Device / flash** | GET 0x02 0x01 (device info), 0x02 0x02 (func table), etc. | Adds **GET 0x02 0xA7** (flashbin info). GET 0x02 **0x30** returns a **schedule/config block** (e.g. 23:00–07:00), distinct from legacy GET 0x10 notice status. |
| **Screen brightness** | Not in angelfit command table. | **SET 0x03 0x32** (VBUS_EVT_APP_SET_SCREEN_BRIGHTNESS): 12-byte payload; byte 5 = 0x01 (auto off) or 0x03 (auto on 19:00–06:00). |
| **Hand gesture (raise to wake)** | SET 0x03 0x28 with 2-byte payload (on_off, show_second). | **9-byte** payload: `03 28 AA/55 05 01 00 00 17 3B` (on/off + extra fields). |
| **Auto sport detect** | Not in angelfit table. | **SET 0x03 0x49**: off = `03 49 00 00 ...`, on (walk & run) = `03 49 01 01 00 ...`. |
| **Reminders (drink, walk, stress, woman)** | Partially in capture-backed table (0x47, 0x60, 0x41, 0x42, 0x45). | **Confirmed from dumps**: 0x60 (drinking), 0x47 (walk-around), 0x45 (stress/continuous health), 0x41+0x42 (woman health). VeryFit often sends **v3 cmd 0x09** (HR mode sync) immediately after these SETs. |
| **Music / weather** | SET 0x2A (music), SET 0x2D (weather switch). | Same keys; payloads match dumps (e.g. music on `03 2A AA 55`, weather on `03 2D AA 00 00 00`). |
| **Watch face** | Bulk write 0x0AF1; control on 0x0AF6 (exact command unknown). | **v3 protocol**: cmd **0x06** = list/select dial (`33 DA AD DA AD 01 0B 00 06 ...`), cmd **0x07**/**0x08** = write dial/JSON; then GET 0xF0 and **D1 01/02/05** chunked transfer for .iwf. |
| **Activity** | Legacy activity request (varies by firmware). | **v3 only**: activity = v3 cmd/key **0x001a / 0x0042**; no legacy activity path in capture. |
| **HR state readback** | GET 0x02 0x08 (4× burst in capture when HR toggles). | Same GET 0x08; **v3 cmd 0x09** is used to **get/set** HR continuous state (multi-packet; nseq in payload). |

**Summary:** A200 firmware is **backward compatible** on the wire (same GATT, same GET 0x01/0x02, SET 0x29/0x2A/0x2D, etc.) but adds **v3 (0x33)** for activity, alarms, HR mode sync, and watch face operations, and **new or extended SET keys** (0x32, 0x45, 0x47, 0x49, 0x60, 0x41/0x42) plus **GET 0xA7, 0xB1, 0x30**. VeryFit uses the extended SET 0x30 and 0x45 (not legacy 0x25) for call alert and continuous HR/Stress on this device. All confirmed commands from the A200 dumps are implemented in the idowatch **Confirmed features (logcat dumps)** section in `htmlapp/index.html`; see `logcat_dumps/*.txt` for exact TX/RX.

### Sending a notification to the watch

**Is it practical?** Yes. The app already writes to **0x0AF6** for Get Info and Get Activity; sending a notification is just writing a different command to the same characteristic (or possibly **0x0AF1** for bulk data). So it's the same mechanism.

**Exact command?** Not documented in public sources. From web search:

- IDO SDK docs describe *enabling* which app notifications are forwarded (e.g. Set smart reminder, Set v3 smart reminder) but not the raw packet that carries the notification *content* (e.g. "Hello" or caller name).
- TOOBUR "Command Center" says: when the phone gets a text, the app sends "a specific hex code" to the watch; 0x0AF6 is for control commands, 0x0AF1 for bulk/data (e.g. watch faces).
- Some other fitness bands (e.g. Mi Band) use a simple format: header bytes (e.g. `0x05 0x01`) followed by UTF-8 message. IDO protocol is different and the exact bytes are unknown.

**Firmware protocol (protocol.h / protocol_send_notice.c):** Realtek/IDO firmware source defines the exact format.

- **Commands:** `PROTOCOL_CMD_GET=0x02`, `PROTOCOL_CMD_SET=0x03`, `PROTOCOL_CMD_MSG=0x05`. Get device info = **0x02 0x01** (PROTOCOL_KEY_GET_DEVICE_INFO). Legacy angelfit firmware defines Set notification switch as **0x03 0x30** with payload `notify_switch`, `notify_itme1`, `notify_itme2`, `call_switch`, `call_delay` (5 bytes). However, **`new_setup.json` shows VeryFit writing a longer 20-byte packet beginning `03 30 88 00 00 aa` and receiving `03 30 88 01 00` back**, so do not assume the short `03 30 01 00 00 01 03` web-app payload is what VeryFit used on this watch.
- **Call notification:** CMD_MSG 0x05 + KEY_MSG_CALL 0x01. Packets are **chunked in 16-byte payloads**. Each BLE write: **[0x05, 0x01, total, serial]** (4 bytes) + **16 bytes payload**. First payload for call: **[phone_number_length, contact_length]** then phone number bytes, then contact (caller name) bytes, zero-padded to 16 bytes. If content fits in one block: total=1, serial=1; payload = 0, contact_len, contact…, pad to 16.
- **Call status:** **0x05 0x02** (PROTOCOL_KEY_MSG_CALL_STATUS) + 1-byte status. **Angelfit** uses **status 0x01** for “stop/end call” (VBUS_EVT_APP_SET_NOTICE_STOP_CALL). protocol_msg_call_status has `uint8_t status`.
- **SMS notification:** Same chunking; cmd/key = **0x05 0x03** (PROTOCOL_KEY_MSG_SMS). First payload: **type, data_length, phone_number_length, contact_length**, then phone, contact, data text.

**Confirmed:** **Mi Band style (0x05 0x01 + UTF-8)** triggers the **call notification** on many IDO watches. It can stop working if another command (e.g. set-notice **0x03 0x30** or other writes) resets the watch’s call-alert state. **Re-pairing with the VeryFit app** restores call alert and makes 0x05 0x01 work again. So: pair with VeryFit once to enable call notifications; then use the web app with Mi Band format without sending “Enable call alert first” (0x03 0x30), which can reset that state on some devices.

**Reproducibility (why it may work only sometimes):** If the watch’s call-alert state is **reset** by another command (e.g. our “Enable call alert first” **0x03 0x30**, or other set/get commands), **Mi Band style (0x05 0x01 + UTF-8)** may stop triggering the call UI. **Re-pairing with the VeryFit app** restores the state and call notifications work again. So: use VeryFit to enable call alert once; then prefer Mi Band format in the web app and leave “Enable call alert first” unchecked to avoid resetting state. The **firmware chunked format** (0x05 0x01 + total + serial + 16-byte payload) remains an option for devices that expect it.

**What we added:** **Mi Band** (0x05 0x01 + UTF-8) default; **Firmware call** (0x05 0x01 + total + serial + 16-byte payload(s)) with **multi-packet** when caller name > 14 bytes (150 ms delay between chunks); **Firmware SMS** (0x05 0x03 + total + serial + 16B payload(s)) with payload [type, data_length, phone_len, contact_len, sender, message]; **Call status** button: **0x05 0x02** + status byte (0=end/dismiss, 1/2 unknown). Optional **Sender** field for call name / SMS sender; **Enable call alert first** (0x03 0x30) off by default to avoid resetting state.

**If you need SMS or multi-packet call:** The app implements **Firmware SMS** (0x05 0x03, chunked) and **multi-packet Firmware call** (0x05 0x01 when contact > 14 bytes). Use “Sender” for call name / SMS sender; message body in the main text field. Call status **0x05 0x02** + status can dismiss the call UI (status 0 = end).

### V3 protocol – GitHub and official docs (juicy insight)

Web search and official IDO docs surface the following; use them to cross-check our logcat dumps and TOOBUR A200 behaviour.

**Reverse engineering and v3 wire format**

- **xssfox/idowatch** — https://github.com/xssfox/idowatch  
  Reverse-engineering repo (Python + HTML app) for IDO/VeryFit. Same protocol as idowatch; documents 0x0AF0/0x0AF6/0x0AF7 and v3.
- **Bad Smart Watch Auth** — https://sprocketfox.io/xssfox/2025/02/09/ido/  
  Describes v3 in plain terms: first byte **0x33** ("3"); preamble **DA AD DA AD** to detect **new command** vs continuation when BLE splits data; then "service selectorish thing, length, command, sequence fields, data, CRC". Activity request example uses length 0x10, cmd 0x04, sequence 0x0B 0x01, start/stop 0x00, cmd 0x04. **Checksum:** "some sort of CRC16" (device didn't check it in that test). Return data: same header; use sequence numbers to match requests; read until length matches or next preamble. Live demo: https://sprocketfox.io/ido/ (TCX export). Same protocol used by Ryze, Cove, bfit Move, etc.

**Official IDO SMART BAND SDK (GitBook)**

- **Preface / Bluetooth:** https://idoosmart.github.io/IDOGitBook/en/
- **Get v3 HR mode** — https://idoosmart.github.io/IDOGitBook/en/get/IDOGetV3HrFunction.html  
  `getV3HrModeInfoCommand`; model includes **modeType** (0=disable, 1=manual, 2=auto 5min, 3=continuous 5s, 4=default/first sync, 5=custom interval, 6=intelligent 206), time range, **measurementInterval**, **notifyFlag**, high/low HR alert, **hrModeTypes** (5s, 60s, 180s, 300s, 600s, 1800s, smart 255s, 900s). Func table: `funcTable22Model.v3HrData`.
- **V3 heart rate data query** — https://idoosmart.github.io/IDOGitBook/en/query/IDOQueryHrFunction_v3.html  
  Query by year/month/week/day; `IDOSyncSecHrDataInfoBluetoothModel` has itemsCount, secondOffset, silentHeartRate, burnFat/aerobic/limit thresholds and minutes, userMaxHr/userAvgHr, warmUp/anaerobic, heartRates array, highLowHrItems. Matches our v3 cmd 0x09 HR state and GET 0x08 readback.
- **Set v3 HR mode** — Set command list references **Set v3 heart rate mode** (IDOSetV3HrModeFunction).
- **Set alarm** — https://idoosmart.github.io/IDOGitBook/en/set/IDOSetAlarmFunction.html  
  **V2 alarm:** setAllAlarmsCommand. **V3 alarm:** `setV3AllAlarmsCommand` with `IDOSetExtensionAlarmInfoBluetoothModel` (alarmVersion, alarmCount, items). V3-only fields: **repeatTime**, **shockOnOff**, **delayMinute**, **alarmName** (≤23 bytes). Alarm types 0–14 + 42 (custom name).
- **Set watch face ID** — https://idoosmart.github.io/IDOGitBook/en/set/IDOSetWatchDiaFunction.html  
  `setWatchDiaCommand` with **dialId**; func table `funcTable18Model.watchDial`. Matches our v3 cmd 0x06 (list/select) and 0x07/0x08 (write dial/JSON).
- **Set command overview** — https://idoosmart.github.io/IDOGitBook/en/IDOSetUpFunction.html  
  Lists many set commands; v3-related include: Set screen brightness, Set music switch, Set watch face id, Set reminders to move (walk), **Set v3 heart rate mode**, Set pressure switch, **Set menstrual cycle reminders**, **Set menstrual cycle**, **Set drink water reminder**, **Set motion switch** (activity), Set v3 smart reminder, etc. Aligns with our SET 0x32, 0x2A, 0x47, 0x45, 0x41/0x42, 0x60, 0x49 and v3 cmd 0x09.

**Official SDK repos**

- **idoosmart/Flutter_Demo** — https://github.com/idoosmart/Flutter_Demo  
  Flutter SDK demo; Dart + Swift/Java/Kotlin/Obj-C/C. Flutter GitBook: https://idoosmart.github.io/Flutter_GitBook/
- **idoosmart/IDOBlueDemo** — https://github.com/idoosmart/IDOBlueDemo  
  IDO Bluetooth demo (good for seeing which APIs map to v3 vs legacy).

**Takeaways for our dumps**

- v3 **preamble** `33 DA AD DA AD` and **length/cmd/sequence** are confirmed; our activity (0x001a/0x0042), alarm (0x0F), HR mode (0x09), watch face (0x06/0x07/0x08) align with SDK "v3" alarm, v3 HR, and watch dial.
- **V3 HR mode** in SDK (get/set/query) matches our **v3 cmd 0x09** and GET 0x08 burst; modeType 0–6 and intervals (5s, 60s, …) give a semantic map for payloads.
- **V3 alarm** has extra fields (repeatTime, shockOnOff, delayMinute, alarmName); our get_alarm v3 dump is the GET side; set may still use legacy SET 0x02 or v3 set command.
- **Watch face:** set dial by ID (SDK) vs our v3 cmd 0x06 (list) + 0x07/0x08 (write JSON/dial data) — SDK is high-level; our dumps show the actual v3 dial list/write packets.

**Do the resources align with our logcat_dumps?**

| Topic | External resource | Our logcat_dumps | Verdict |
|-------|-------------------|------------------|--------|
| **v3 preamble** | xssfox: first byte 0x33, preamble DA AD DA AD; IDO GitBook implies v3 for HR/alarm/dial. | All v3 TX in dumps start with `33 DA AD DA AD`. | **Align.** |
| **GATT** | xssfox + angelfit: 0x0AF0 service, write 0x0AF6, notify 0x0AF7. | VeryFit uses same; dumps show TX to 0x0AF6, RX on 0x0AF7. | **Align.** |
| **Activity v3** | xssfox: activity request uses length 0x10, **cmd 0x04**, sequence 0x0B 0x01, start/stop 0x00, cmd 0x04. | new_setup.json + idowatch: activity = v3 **cmd/key 0x001a / 0x0042** (different cmd/key). | **Differ.** Likely different device/firmware or xssfox’s 0x04 is an inner/version byte; our dumps are authoritative for A200. |
| **v3 HR (get/set)** | IDO GitBook: getV3HrModeInfoCommand, modeType 0–6, measurementInterval, hrModeTypes (5s, 60s, …). | set_hr_cont_state_on/off + get_hr_cont_state: **v3 cmd 0x09** (nseq in payload); GET 0x02 0x08 4× after SET 0x45. | **Align.** SDK semantics match our v3 0x09 and GET 0x08 usage. |
| **v3 alarm** | IDO GitBook: setV3AllAlarmsCommand; v3-only repeatTime, shockOnOff, delayMinute, alarmName. | get_alarm.txt: **v3 cmd 0x0F** (`33 DA AD DA AD 01 0C 00 0F 00 24 01 00 28 18`). SDK doesn’t document “get alarm” wire format. | **Align.** We add wire detail (cmd 0x0F for get); set may be v3 or legacy 0x02. |
| **Watch face** | IDO GitBook: setWatchDiaCommand(dialId). | ui_select_watch_face: v3 **cmd 0x06**; ui_watch_face_write_json: v3 **cmd 0x07** then 0x08, then GET 0xF0, **D1 01/02/05** chunked. | **Align.** Dumps show the actual v3 dial list (0x06) and write (0x07/0x08) + transfer; SDK is high-level. |
| **SET keys** | IDO Set overview: screen brightness, music, watch face, walk remind, v3 HR, pressure, menstrual, drink water, motion switch. | Dumps: **0x32** (brightness), **0x2A** (music), **0x47** (walk), **0x45** (stress/HR), **0x41/0x42** (woman), **0x60** (drink), **0x49** (auto sport). | **Align.** Same feature set; dumps give exact payloads. |
| **Hand gesture** | Angelfit: SET 0x28 with 2-byte payload (on_off, show_second). | set_hand_gesture_wake_on/off: **9-byte** payload `03 28 AA/55 05 01 00 00 17 3B`. | **Differ.** A200 uses extended 9-byte format; angelfit is legacy 2-byte. (Already in A200 vs angelfit table.) |
| **CRC** | xssfox: “some sort of CRC16”; device didn’t check. | Dumps show last 2 bytes per v3 packet (e.g. F5, BE, CD); we don’t verify CRC in app. | **Align.** No contradiction; we don’t rely on CRC from dumps. |
| **GET 0xA7, 0xB1, 0x30** | Not in angelfit or xssfox. | get_flashbin_info: **GET 0xA7**; set_dnd_*: follow-up **GET 0xB1** (DND readback); GET **0x30** = schedule block. | **Dumps add.** SDK doesn’t document these GET keys; dumps confirm A200/VeryFit use. |

**Summary:** Resources and dumps **align** on v3 preamble, GATT, v3 HR (0x09 + GET 0x08), v3 alarm get (0x0F), watch face (0x06/0x07/0x08), and SET key list. They **differ** on (1) **activity v3 cmd** (xssfox 0x04 vs our 0x001a/0x0042) — treat our dumps as correct for A200; (2) **hand gesture** payload length (angelfit 2-byte vs A200 9-byte). The dumps **add** wire-level detail for GET 0xA7, 0xB1, 0x30 and exact v3 packet bytes the SDK does not publish.

### References / URLs

**IDO protocol, BLE, and testing (general):**

- https://sprocketfox.io/xssfox/2025/02/09/ido/ — Bad Smart Watch Auth; IDO/VeryFit reverse engineering, 0x0AF0/0x0AF6/0x0AF7, v3 protocol, live demo.

**Angelfit (orangebrush) — local `angelfit/` and https://github.com/orangebrush/angelfit:**

- **UUIDConfigure.swift:** Service **0x0AF0**; **write 0x0AF6** (commands: get info, set notice, call/SMS notification, call status); **read/notify 0x0AF7**; **bigWrite 0x0AF1** (health/sync data); **bigRead 0x0AF2**. Same GATT layout as idowatch.
- **protocol_write.c:** **Call status “stop call”** = VBUS_EVT_APP_SET_NOTICE_STOP_CALL → **0x05 0x02 0x01** (struct protocol_cmd: head + cmd1=0x01). So status **0x01** = end/dismiss call in angelfit.
- **Get notice status:** PROTOCOL_KEY_GET_NOTICE_STATUS = **0x10** → **0x02 0x10** (GET cmd + key). Device replies on 0x0AF7 with current notice/call-alert state.
- **protocol_send_notice.h:** PROTOCOL_SEND_NOTICE_TYPE_CALL = 0xF100, TYPE_MSG = 0xF200; for SMS the low byte of type is the message subtype in the payload.
- Commands (including 0x05 0x01/0x02/0x03) use **write (0x0AF6)** with **.withResponse**; health sync uses **bigWrite (0x0AF1)**.

**Command reference (angelfit protocol — all to 0x0AF6, replies on 0x0AF7):**

| Cmd | Key | Description | Payload (after cmd, key) |
|-----|-----|-------------|---------------------------|
| **GET 0x02** | 0x01 | Device info | (none) |
| | 0x02 | Func table | (none) |
| | 0x03 | Device time | (none) → reply: year, month, day, hour, min, sec, week |
| | 0x04 | MAC | (none) → reply: 6 bytes MAC |
| | 0x05 | Battery info | (none) → reply: type, voltage, status, level |
| | 0x06 | SN info | (none) → reply: device-specific serial/SN |
| | 0x10 | Notice status | (none) → reply: notify_switch, status_code, err_code |
| | 0x07 | Unknown (VeryFit) | (none) → reply: 40:24:40:ff:… (see new_setup.json) |
| | 0xF0 | Unknown (VeryFit) | (none) → reply: 00:89:00:89:00:e8:03:8c:00 |
| | 0x08 | Continuous HR / health config? | (none) → in `hr_cont_enabled.json` the app sends 02:08 four times at end of capture when user had just toggled continuous HR; **cross-ref:** same 4× burst in `healthdata_toggles.json` when continuous HR was toggled on then off. Likely readback of state. Reply format on 0x0AF7 not fully documented. |
| | 0xA0 | Live data | (none) → reply: step, calories, distances, active_time, heart_rate |
| | **0x20** | **HR sensor param** | (none) → reply: rate (uint16), led_select (uint8) — debug/spec |
| | **0x21** | **G-sensor param** | (none) → reply: rate (uint16), range (uint8), threshold (uint16) — debug/spec |
| **SET 0x03** | 0x01 | Set device time | year(2), month, day, hour, minute, second, week |
| | **0x02** | **Set alarm** | alarm_id, status, type, hour, minute, repeat, tsnooze_duration — see **Alarm support** below; only if func table alarm_num > 0 |
| | **0x04** | **Sleep goal** | hour, minute (target sleep duration) — only if func table main_func sleep(1) |
| | 0x22 | Set hand | hand_type (0=left, 1=right) |
| | 0x26 | Find phone | status, timeout (seconds) |
| | 0x27 | Factory defaults | (none) — restore default config; only if func table configDefault |
| | 0x28 | Up hand gesture | on_off (0xAA=on, 0x55=off), show_second (2–7) |
| | 0x29 | Do not disturb | switch_flag, start_hour, start_minute, end_hour, end_minute |
| | 0x2A | Music on/off | switch_status: 0xAA=on, 0x55=off (firmware convention; same as VeryFit) |
| | 0x2C | One-key SOS | on_off (0xAA=on, 0x55=off) |
| | 0x2D | Set weather switch | cmd1, cmd2, cmd3 (e.g. 1,0,0 = on; 0,0,0 = off) — only if func table weather(7) is set |
| | 0x30 | Set notice | Legacy angelfit struct = `notify_switch, notify_itme1, notify_itme2, call_switch, call_delay`. In `new_setup.json`, VeryFit instead writes **20 bytes** starting `88:00:00:aa:00…` and gets `03:30:88:01:00` back, so this key is newer / wider than the simple 5-byte form on this watch/app combination. |
| | 0x35 | Unknown (VeryFit) | Writes seen: `03:35:02:00:00:…` and `03:35:01:00:00:…`; replies seen: `03:35:02:00`, `03:35:01:00`, `03:35:02:0f`. Purpose unknown. |
| | 0x41 | Women's health config? | Capture-backed from `healthdata_toggles.json`: setup/default writes are all-zero after the header, while later writes become dated payloads like `03:41:55:07:1c:ea:07:03:07:0e:05:04:00:55` and `03:41:aa:...`; likely part of menstrual / women's-health reminder state. |
| | 0x42 | Women's health detail? | Capture-backed companion to `0x41`: default `03:42:00:00:00:00:00:00:00`, later `03:42:03:03:08:00:03:03:03`; likely the small rule / cycle block paired with `0x41`. |
| | 0x45 | Continuous health config? | Capture-backed from `healthdata_toggles.json`: the payload flips between `03:45:55:09:00:12:00:55:3f:3c:00:50:00:01:00:1e` and `03:45:aa:...`. This is the only plausible watch-side family for VeryFit's continuous-HR / continuous-stress UI in that trace, but the dump does not separate those two features cleanly. |
| | 0x47 | Walk-around reminder? | Capture-backed from `healthdata_toggles.json`: `03:47:01:64:00:09:00:15:00:fe:00:00:73:00:00:00:01` then the same packet with byte 2 = `00`, both ACKed. Likely sedentary / walk-around reminder. |
| | 0x60 | Drinking reminder? | Capture-backed from `healthdata_toggles.json`: `03:60:01:09:00:12:00:3f:1e:00:01:00:00:00:00:00` then `03:60:00:09:00:12:00:3e:1e:00:01:00:00:00:00:00`, both ACKed. Likely drink-water reminder. |
| | **0x24** | **Heart rate interval** | burn_fat_threshold, aerobic_threshold, limit_threshold (3 bytes, 1–255 bpm) — alert thresholds, not on/off |
| | **0x25** | **Heart rate mode** | mode: **0x55=off (close)**, **0x88=auto (continuous)**, **0xAA=manual** — this is the heart rate enable/disable (angelfit CoreDataHandler default 0x88) |
| | **0x52** | **Real-time sensor status** | gsensor_status, heart_rate_sensor_status (2 bytes): **0x55=off, 0xAA=on** per byte. App: Real-time sensors off / HR stream on / both on. |
| **WEATHER 0x0A** | 0x01 | Set weather data | struct protocol_weatch_data: today_type, today_tmp, today_max_temp, today_min_temp, humidity, uv_intensity, aqi, future[3] (each: type, max_temp, min_temp) — only if func table weather(7) is set |
| **APP_CONTROL 0x06** | 0x01 | Music | cmd1: 0x00=start, 0x01=stop |
| | 0x02 | Photo | cmd1: 0x00=start, 0x01=stop |
| | 0x04 | Find device | cmd1: 0x00=start, 0x01=stop |
| | 0x03 | Single sport | cmd1: 0x00=start, 0x01=stop — only if func table single_sport(2) is set |
| | 0x30 | Open ANCS | (none or zeros) |
| | 0x31 | Close ANCS | (none or zeros) |
| **MSG 0x05** | 0x01 | Call notification | chunked: total, serial, 16B payload(s) |
| | 0x02 | Call status | status (0x01=end call) |
| | 0x03 | SMS notification | chunked: total, serial, 16B payload(s) |
| **RESET 0xF0** | 0x01 | Reboot | (none) — watch reboots; connection drops |

**Note:** **BLE_CONTROL (cmd 0x07)** in the firmware is used for *watch → app* events (e.g. user triggers find-phone or one-key SOS on the watch; keys 0x02, 0x03, 0x04, 0x10, 0x11). The app does not send 0x07 to the watch for those; SET/APP_CONTROL cover the app→watch side.

The idowatch htmlapp implements all of the above; GET replies for time, MAC, battery, live data, legacy notice status, SN info, **HR sensor param (0x20)**, and **G-sensor param (0x21)** are parsed and shown in the event log. Capture-backed raw replies such as **GET 0x07 / 0x30 / 0xF0 / 0xA7 / 0xB1**, **`0x03 0x30` notice-status notifications**, and named ACK/status logs for **`0x41 / 0x42 / 0x45 / 0x47 / 0x60`** are also shown. The page no longer treats `03:30:55:01:00` as live HR, and it now includes exact capture-backed buttons for the likely **drink** (`0x60`) and **walk-around** (`0x47`) reminders.

**Commands in protocol but not (yet) in the app:** sport goal (0x03), user info (0x10), unit (0x11), long sit (0x20), lost find (0x21), sys OS (0x23), display mode (0x2B), sport mode select (0x2E), lost find mode (0x40), HR/G-sensor params SET (0x50/0x51), etc. Sending weather data (WEATHER 0x0A 0x01 + payload) has no UI yet—only the weather switch (SET 0x2D) is in the app.

**Observed VeryFit BLE flow (new_setup.json):** GATT discovery maps **0x0AF6** value handle **0x0010**, **0x0AF7** value handle **0x0012** (+ CCCD **0x0013**), **0x0AF2** value handle **0x0015** (+ CCCD **0x0016**), and **0x0AF1** value handle **0x0018**. VeryFit enables notifications on **both `0x0AF7` and `0x0AF2`**, but every application payload in this capture is either a **host write to `0x0AF6`** or a **watch notification on `0x0AF7`**; `0x0AF2` stays silent after its CCCD write.

**Important correction:** `03:30:55:01:00` is **not** a host `SET 0x30` and **not** live HR `85 bpm`. It is a **watch status notification** on `0x0AF7`, likely the legacy `protocol_set_notice_ack` (`notify_switch=0x55`, `status=1`, `err=0`), and it arrives immediately after the first `GET 0x04` write.

**First-session host writes (abbreviated):** `GET 0x04` (MAC) → `GET 0x02` (func table) → `GET 0x07` → `GET 0xF0` → **v3 activity request** (`0x001a/0x0042`) → `GET 0x30` → `GET 0x01` (device info) → `SET 0x10` → v3 `0x0043/0x0044/0x0045` → `GET 0x04` again → `SET 0x11` → `GET 0x04` again → `GET 0xA7` → `GET 0x01` → `SET 0xE3` → `SET 0x01` (time) → v3 `0x0046/0x0047/0x0048` → more config writes (`0x26`, `0x45`, `0x2A`, `0x2D`, `0x24`, `0x41`, `0x42`, `0x43`, `0x60`) → **capture-backed `SET 0x30`** (`03:30:88:00:00:aa:00…`, 20 bytes) → `SET 0x35`. So VeryFit does a broader setup sweep than idowatch’s minimal `GET device info → activity` flow, but the trace does **not** show a factory-defaults or reboot command.

**GET 0x07 / 0x30 / 0xF0 / 0xA7 / 0xB1 (from capture):**
- `GET 0x02 0x07` reply: `02:07:40:24:40:ff:38:4e:d3:ff:0b:08:00:84:95:c7:06:01:00:34` (format unknown).
- `GET 0x02 0x30` reply: `02:30:55:17:00:07:00:00:fe:55:17:00:07:00`; the payload looks like a duplicated **23:00–07:00** schedule/config block, so it is distinct from legacy `GET 0x10` notice status.
- `GET 0x02 0xF0` reply: `02:f0:00:89:00:89:00:e8:03:8c:00`.
- `GET 0x02 0xA7` reply: `02:a7:00:01:01:78:56:34:12`.
- Later sessions also use `GET 0x02 0xB1`, which replies `02:b1:aa:05:01:00:00:17:3b`.

**SET 0x03 0x35 (from capture):** Payloads seen include `03:35:02:00:00:00:00:00:00:00:00:00` and `03:35:01:00:00:00:00:00:00:00:00:00`; replies include `03:35:02:00`, `03:35:01:00`, and `03:35:02:0f`. Purpose unknown (possibly newer notice/sync state). Not in the angelfit command table; keep it capture-only for now.

**Health toggles capture (`healthdata_toggles.json`):**  
The user toggled **five** features in the VeryFit app, **in this order:** (1) **Continuous HeartRate** on then off, (2) **Stress Continuous monitor** on then off, (3) **Drinking Reminder** on then off, (4) **Walk around Reminder** on then off, (5) **Menstrual Reminder** on then off. From the dump, the **commands that correspond to each** (by chronological appearance in the capture) are:

| # | App feature (user order) | Watch-side command(s) | Observed in capture (chronological) |
|---|---------------------------|------------------------|--------------------------------------|
| 1 | Continuous HeartRate on → off | **SET 0x45** | `03:45:aa:...` (on) then `03:45:55:...` (off). Single on/off pair in the toggle section (e.g. lines 1352942, 1360642). |
| 2 | Stress Continuous on → off | **None observed** | No second SET 0x45 pair and no other key toggled in that slot. Stress may be **app-only** or share 0x45 (firmware would then use the same 0x45 state for both; capture shows only one 0x45 on→off pair). |
| 3 | Drinking Reminder on → off | **SET 0x60** | `03:60:01:...` (on) then `03:60:00:...` (off). |
| 4 | Walk around Reminder on → off | **SET 0x47** | `03:47:01:...` (on) then `03:47:00:...` (off). |
| 5 | Menstrual Reminder on → off | **SET 0x41** + **0x42** | `03:41:aa:...` + `03:42:03:...` (on) then `03:41:55:...` (off); 0x42 sent immediately after each 0x41. |

Right after the **0x45** on→off pair, the app sends **GET 0x02 0x08** (`02:08`) four times (readback of HR/health state). So the sequence in the capture is: 0x45 on, 0x45 off → GET 0x08 (×4) → 0x60 on, 0x60 off → 0x47 on, 0x47 off → 0x41/0x42 on, 0x41/0x42 off.

- **Confirmed:** `0x60` (Drinking), `0x47` (Walk), `0x41`+`0x42` (Menstrual) all toggle with ACKs when the user flips those app switches.
- **Continuous HR / Stress:** The dump contains **no** `SET 0x03 0x25` (legacy HR mode) and **no** `SET 0x03 0x52` (real-time sensor) when those toggles were changed. The only other health-config key that changes state is **0x45** (payload: `03:45:aa:...` = on, `03:45:55:...` = off). So VeryFit’s **Continuous HeartRate** and/or **Stress Continuous** use this newer path; this capture does **not** show whether 0x45 is HR-only, Stress-only, or a shared “continuous monitoring” flag for both. **Cross-ref:** `hr_cont_enabled.json` confirms the same **0x45** on/off and **GET 0x08** (02:08, 4× burst) for the continuous-HR toggle.

**Continuous HR capture (`hr_cont_enabled.json`):**  
This capture is from a session where the user **toggled continuous HR** and then ended the capture. It nails the continuous-HR behaviour:

- **SET 0x45** appears in this file as well: `03:45:aa:...` (on) and `03:45:55:...` (off), matching `healthdata_toggles.json`. So **continuous HR on/off is watch-side via 0x45**.
- At the **very end** of the log (right before the user stopped the capture), the app sends **GET 0x02 0x08** (`02:08`) **four times** in a row (host → watch on 0x0AF6). No other SET commands appear in that final stretch. So when the continuous-HR toggle/screen is active, the app also uses **GET 0x08** — likely to read back the current continuous-HR (or health) config/state from the watch. The watch may reply on 0x0AF7 (not shown in the same snippet). Idowatch can send `02:08` via the “GET 0x08” button to probe the reply.

**Cross-ref `healthdata_toggles.json`:** The same continuous-HR operation (on then off) was performed there: the dump contains both **03:45:aa** (on) and **03:45:55** (off), and **GET 0x08** (`02:08`) in the same **four-times-in-a-row** burst pattern (e.g. around the 03:45 toggles). So both captures confirm **SET 0x45** for on/off and **GET 0x08** when the app is on that screen or reading back state.

**v3 (0x33) reassembly (confirmed from capture):** First packet: preamble `33 da ad da ad`, then [serial] [totalLen_lo] [totalLen_hi] [cmd_lo] [cmd_hi] [key_lo] [key_hi] [checksum…]. Copy from **offset 1** for **totalLen** bytes. Continuation packet: `33` followed by 12 bytes (often zeros), then payload; **append from offset 13 only**. A final short packet (e.g. `33 af 42`) may be checksum-only; only append when `arr.length > 13`.

**v3 cmd/key pairs observed in new_setup.json:** Activity = **0x001a / 0x0042**. First setup sweep: **0x0007 / 0x0043**, **0x0008 / 0x0044**, **0x000f / 0x0045**; after time set: **0x0007 / 0x0046**, **0x0008 / 0x0047**, **0x000f / 0x0048**; then **0x000c / 0x0049**, **0x0009 / 0x004A**, **0x0005 / 0x004B**. Later sessions continue with **0x0004 / 0x004C**, **0x0007 / 0x004D**, **0x0008 / 0x004E**, **0x000f / 0x004F**, **0x000c / 0x0050**, **0x0009 / 0x0051**, **0x0005 / 0x0052**, and a long run of **0x0004 / 0x0053** through **0x0004 / 0x0067**. A separate later sweep also uses keys **0x0002** through **0x0032**. So the earlier `0x53–0x64` note was incomplete; the highest observed key in this capture is **0x67**.

**Alarm support (SET 0x03 0x02):** The angelfit app **can set alarms on the watch**. Command is **SET 0x03 0x02** with payload **struct protocol_set_alarm** (after the 2-byte header): **alarm_id** (uint8, 0..alarm_num−1), **status** (uint8: **0xAA = on/enabled**, **0x55 = off/disabled** — angelfit uses 0xAA when syncing or deleting; new alarm default in DB is 0x55), **type** (uint8: 0=wake_up, 1=sleep, 2=sport, 3=medicine, 4=dating, 5=party, 6=meeting, 7=custom — must match func table alarm_type bits), **hour**, **minute** (uint8), **repeat** (uint8: bitmask for repeat days, or 0xFF for “all days” in sync), **tsnooze_duration** (uint8: snooze duration in minutes). The **func table** (GET 0x02 0x02) gives **alarm_num** (max alarms) and **alarm_type** (which types the watch supports). The iOS app syncs alarms by: (1) `protocol_set_alarm_clean()`, (2) `protocol_set_alarm_add(alarm)` for each alarm from DB, (3) `protocol_set_alarm_start_sync()` — firmware sends them one-by-one with 50 ms between packets, waiting for BLE reply each time. To set a single alarm from idowatch you would send one packet: `[0x03, 0x02, alarm_id, status, type, hour, minute, repeat, tsnooze_duration]` (7 bytes after cmd/key). The idowatch htmlapp now has an **Alarms** section: set single alarm (slot, on/off, type, time, repeat, snooze) and **full alarm sync** (add multiple alarms to a list, then sync all to the watch with 300 ms between each).

**Heart rate enable/disable (angelfit):** The protocol has an explicit on/off via **SET 0x03 0x25** (heart rate mode). Payload is one byte: **0x55 = close (HR off)**, **0x88 = auto (continuous monitoring on)**, **0xAA = manual (manual measurement on)**. Source: `angelfit/AngelFit/Protocol_c/protocol.h` (`struct protocol_heart_rate_mode`), `protocol_exec.c` (VBUS_EVT_APP_SET_HEART_RATE_MODE), `CoreDataHandler.swift` default `heartRateMode = 0x88` with comment "auto:0x88 close:0x55 manual:0xAA". GET 0x02 0x20 returns heart rate sensor params (rate, led_select). SET 0x03 0x24 sets HR alert thresholds (burn_fat, aerobic, limit); SET 0x03 0x52 sets real-time sensor stream status (gsensor_status, heart_rate_sensor_status). Only supported if func table reports heart_rate (main_func bit 5) or heart_rate_monitor (ohter2 bit 3). **Sync order in angelfit:** config sync sends SET_HEART_RATE_MODE only when **ohter2.heartRateMonitor** is true (ohter2 bit 3); SET_HEART_RATE_INTERVAL is also in the sync list. Some firmware may require **SET 0x03 0x24** (heart rate interval: burn_fat, aerobic, limit thresholds, e.g. 135, 96, 160) to be sent before SET 0x03 0x25 (mode). The idowatch "Start continuous HR" sequence sends interval → mode → real-time stream, with 600 ms delays between commands. **Important limit:** `healthdata_toggles.json` does **not** show VeryFit using `0x25` for its own continuous-health toggles on this watch, so `0x25` remains a useful manual / angelfit-style control, not a confirmed mirror of the VeryFit UI flow.

**Heart rate troubleshooting (auto HR not activating):** (1) **Func table:** Ensure GET 0x02 0x02 shows **main_func bit 5 (heart_rate)** and **ohter2 bit 3 (heart_rate_monitor)** set; otherwise the watch may ignore SET 0x25. (2) **Order and delays:** Try **Alternative order** in idowatch: enable real-time HR stream (SET 0x52, HR byte 0xAA) *first*, then SET 0x24 (interval), then SET 0x25 (mode 0x88), with 600 ms between each. Some devices only apply mode when the sensor stream is already on. (3) **Mode byte:** Angelfit uses **0x55/0x88/0xAA**; the IDO SDK v2 model uses numeric modes **0=off, 1=manual, 2=automatic, 3=continuous**. If 0x88 does nothing, try sending mode byte **2** (SET 0x03 0x25 0x02) via "Heart rate: on (v2 byte 2)". (4) **Interval first:** Always send SET 0x03 0x24 (e.g. 135, 96, 160) before or in the same sequence as SET 0x25; some firmware ignore 0x25 until interval is set.

**Sleep (goal + data / REM stages):** **SET 0x03 0x04** sets the **sleep goal** (target duration): payload **struct protocol_set_sleep_goal** = **hour**, **minute** (2 bytes). Only supported if func table **main_func sleep(1)** is set. **Sleep data** is requested via **HEALTH_DATA** (cmd **0x08**): **0x08 0x04 0x01** = request today's sleep (key PROTOCOL_KEY_DAY_SLEEP, sync type START); **0x08 0x06 0x01** = request history sleep (PROTOCOL_KEY_HISTORY_SLEEP). The watch may then stream multi-packet sleep data on 0x0AF7 (cmd 0x08, key 0x04 or 0x06). Payload format (e.g. 8-minute bins with stage: awake/light/deep/REM) is device-specific and not fully parsed in angelfit protocol_health.c; idowatch logs raw sleep packets in the Sleep section and event log.

**Weather support:** The protocol supports weather only if the **func table** reports it (byte "ohter" bit 7 = weather). Two commands exist: (1) **SET 0x03 0x2D** (set weather switch) with payload cmd1, cmd2, cmd3 — typically cmd1=1 to enable, 0 to disable. (2) **WEATHER 0x0A 0x01** (set weather data) with **struct protocol_weatch_data**: after the 2-byte header (0x0A 0x01), 7 bytes (today_type, today_tmp, today_max_temp, today_min_temp, humidity, today_uv_intensity, today_aqi) and 3×3 bytes for future[3] (each: type, max_temp, min_temp). So the app can enable/disable the weather feature and push current (and optional forecast) weather to the watch.

**Func table (GET 0x02 0x02):** The **function table** is a **device capability bitmap**. When the app sends **Get func table** (0x02 0x02), the watch replies with **struct protocol_get_func_table**: after the 2-byte header (0x02 0x02), **15 bytes** in order:

| Offset | Field        | Meaning (bits = flags) |
|--------|--------------|--------------------------|
| 0      | main_func    | Main: sport(0), sleep(1), single_sport(2), live_data(3), OTA(4), heart_rate(5), ANCS(6), timeline(7) |
| 1      | alarm_num    | Number of alarms supported (0–255) |
| 2      | alarm_type   | Alarm types: wake_up(0), sleep(1), sport(2), medicine(3), dating(4), party(5), meeting(6), custom(7) |
| 3      | control      | Control: photo(0), music(1) |
| 4      | call         | Call: incoming(0), contacts(1), id(2) |
| 5      | msg          | Notify: SMS(0), mail(1), QQ(2), WeChat(3), Weibo(4), Facebook(5), Twitter(6) |
| 6      | ohter        | Other: long_sit(0), lost_find(1), one_key_SOS(2), find_phone(3), find_device(4), config_default(5), up_hand_gesture(6), weather(7) |
| 7      | msg_config   | SMS config: show_contacts(0), show_id(1), show_content(2) |
| 8      | msg2        | Notify2: WhatsApp(0), Messenger(1), Instagram(2), LinkedIn(3), calendar(4), Skype(5), alarm_clock(6), Pokeman(7) |
| 9      | ohter2       | Other2: static_HR(0), do_not_disturb(1), display_mode(2), heart_rate_monitor(3), … |
| 10     | sport_type1  | Sport: walk(0), run(1), bike(2), on_foot(3), swim(4), mountain_climbing(5), badminton(6), other(7) |
| 11     | sport_type2  | Fitness(0), spinning(1), ellipsoid(2), treadmill(3), sit_up(4), push_up(5), dumbbell(6), weightlifting(7) |
| 12     | sport_type3  | Bodybuilding(0), yoga(1), rope_skipping(2), table_tennis(3), basketball(4), football(5), volleyball(6), tennis(7) |
| 13     | sport_type4  | Golf(0), baseball(1), skiing(2), roller_skating(3), dance(4), walk(5) |
| 14     | main_func1   | e.g. log_in(0) |

The app uses this to show/hide features (e.g. only offer “Find phone” if find_phone bit is set), show alarm count, and know which notification and sport types the device supports. See `protocol_func_table.c` and `protocol_func_table.h` in angelfit for the full bit definitions.

**Firmware protocol source (Realtek/IDO):**

- **protocol.h** — Command codes: CMD_GET=0x02, CMD_SET=0x03, CMD_MSG=0x05; KEY_GET_DEVICE_INFO=0x01, KEY_SET_NOTIF=0x30, KEY_MSG_CALL=0x01, **KEY_MSG_CALL_STATUS=0x02**, KEY_MSG_SMS=0x03; struct protocol_set_notice (notify_switch, call_switch, call_delay), protocol_msg_call (total, serial, data[16]), protocol_msg_call_content (phone_number_len, contact_len, data), **protocol_msg_call_status (status)**.
- **protocol_send_notice.c** — Call/SMS send: 16-byte payload chunks; call first payload = notice_call_head (phone_number_length, contact_length) + phone + contact; SMS first payload = notice_msg_head (type, data_length, phone_number_length, contact_length) + phone + contact + data. PROTOCOL_NOTICE_ONE_PACK_SZIE = 16.

**IDO SDK (GitBook) — set/notification-related:**

- https://idoosmart.github.io/IDOGitBook/en/ — IDO SMART BAND SDK (preface).
- https://idoosmart.github.io/IDOGitBook/en/IDOBluetooth.html — Bluetooth Management Library.
- https://idoosmart.github.io/IDOGitBook/en/IDOSetUpFunction.html — Set command function overview (list of set APIs).
- https://idoosmart.github.io/IDOGitBook/en/set/IDOSetNoticeFunction.html — Set smart reminder (enable which app notifications are forwarded; no raw packet format).
- https://idoosmart.github.io/IDOGitBook/en/set/IDOSetNoticeStateFunction.html — Set v3 smart reminder (notification status per app).
- https://idoosmart.github.io/IDOGitBook/en/set/IDOSetNoticeStateFunction.html — Set v3 smart reminder (third-party app notification state).
- https://idoosmart.github.io/IDOGitBook/en/set/IDOSetFindPhoneFunction.html — Set find phone.

**Other projects / examples:**

- https://github.com/idoosmart/Flutter_Demo — IDO Flutter SDK demo.
- https://www.b4x.com/android/forum/threads/send-ble-alert-to-smart-band-mi-band-5.138022/ — Sending BLE alert to Mi Band 5 (header 0x05 0x01 + UTF-8; different vendor, used as a format guess).
- https://medium.com/fmisec/heres-how-i-send-a-notification-to-smart-band-77f835b33d90 — Send notification to smart band (M4, Mi Band 3): nRF 0x2a46 value first byte 01=Email, 03=Call, 04=Missed Call, 05=SMS/MMS; then count; then message.
- https://colmi.puxtril.com/commands/ — Colmi BLE API: command 114 “3rd Party Push Message”, PushMessageSource enum (SMS=1, QQ=2, WeChat=3, PhoneAction=4, Facebook=5, WhatsApp=6, Twitter=7, Skype=8, Line=9).
- https://0110.be/posts/Access_Mi_Band_from_Android_-_Notes_on_the_Bluetooth_LE_Protocol — Mi Band BLE protocol notes (older firmware).

### Watch face upload (VeryFit / .iwf)

VeryFit can send custom watch faces to the watch. The flow (from user reports, e.g. Ksix Compass) is:

1. **Source:** Watch faces are stored under the app as **.zip** files (e.g. in `/data/data/com.watch.life/files/Veryfit/dial/7733/` on Android). The server sends .zip (e.g. cw1.zip, w24.zip); VeryFit unzips and shows the folder.
2. **Build:** When sending to the watch, VeryFit builds **ido_watch_plate_data.iwf** from the unzipped folder (binary of all elements), then compresses it to **ido_watch_plate_data.iwf.lz**.
3. **Send:** The **.iwf.lz** file is sent to the watch over BLE.

**BLE path:** The **bulk write** characteristic is **0x0AF1** (angelfit: `bigWrite`; used there for health data sync). VeryFit likely uses 0x0AF1 for watch face payload; a control command on **0x0AF6** may be sent first to start the transfer (exact command unknown). TOOBUR section "Command Center" describes 0x0AF6 and 0x0AF1 as control vs bulk data.

**Transfer format (from reverse engineering):** The data sent is **not** a single LZ stream. It is **chunked blocks** with a **4-byte length prefix** before each block (little-endian), then the raw data for that block:

```
<block length (4 bytes)><data block><next block length (4 bytes)><data block>...<last block length (4 bytes)><data block>
```

So the .iwf.lz file (or the payload VeryFit sends) is this block-prefixed format; the per-block data may be compressed (e.g. LZ-like) and is **device-specific**.

**.iwf format:** The .iwf (pre-compression) is a container with simple headers and offset/length block descriptions; frames are often RGB565 or RGB565 + 4-bit alpha. It can be unpacked into JSON config and images (PNG, etc.). Different models (IDW13, IDW19, Ksix Compass, etc.) may expect different resolutions or formats.

**Compression:** The .iwf.lz compression is **not** standard LZ; it is custom and may vary by device. Users report trying LZ4, ZIP, or uncompressed and the watch may ACK every ~10 packets but the face does not appear—so the exact compression matters. For some devices "compression format 2" is mentioned. To reproduce, you need the exact file content (from app cache or server response for your watch model), then match the compression and chunking.

**Existing work:**

- **GadgetBridge** has been extended with watch face upload support for at least one model (e.g. **Ksix Compass**), including building .iwf, compressing to .iwf.lz, and sending over BLE.
- **CadranEditor** (Qt/C++, by sptech38): creates 240x240 watch faces for Ksix Compass, builds .iwf, compresses to .iwf.lz, and can send via GadgetBridge.
- **VeryWatchTool / IWFmake** (CoolSteel712): editors for IDW19 and others; .iwf/.zip creation; ".iwf.lz creation" was planned.
- XDA threads: Need help making my own watch faces in .iwf format (Veryfit Watch Face Format); IWF Editor for Milouz IDW19; UPDATED Local Watch Face App.

**Practical approach:** To implement upload for a specific watch: (1) Sniff VeryFit BLE traffic (nRF Connect or HCI snoop) while sending a known watch face; (2) Capture the exact file from app cache or server for that model; (3) Match the chunking (4-byte length + blocks) and compression; (4) Send via 0x0AF1 (and any start/end commands on 0x0AF6 if present in the capture).

### GadgetBridge and angelfit-like (IDO / 0x0AF0) devices

**Does GadgetBridge support angelfit/IDO/VeryFit (0x0AF0) devices?**  
**No.** Mainline GadgetBridge does not include a device coordinator or protocol implementation for the IDO/Realtek 0x0AF0 service (angelfit protocol). **GloryFit** support in GadgetBridge is a **different** protocol (different GATT services; not 0x0AF0). So watches that use VeryFit/angelfit (e.g. Ksix Compass, many IDO-based brands) are not supported out of the box.

**Ksix Compass:** There is an open **device request** ([issue #3487](https://codeberg.org/Freeyourgadget/Gadgetbridge/issues/3487)) for Ksix Compass with no implementation yet. Some users (e.g. sptech38 on XDA) have added Ksix support in **private forks** (e.g. with CadranEditor for watch face upload); that work is not merged upstream.

**How to try to get angelfit-like devices working in GadgetBridge:**

1. **Reference the protocol**  
   Use idowatch and the angelfit repo as the protocol reference: service **0x0AF0**, write **0x0AF6**, notify/read **0x0AF7**, bulk write **0x0AF1**, bulk read **0x0AF2**. TOOBUR.md and the angelfit `protocol.h` / `protocol_write.c` define GET/SET/MSG commands and payloads.

2. **Follow the new-gadget tutorial**  
   - [New gadget tutorial](https://gadgetbridge.org/internals/development/new-gadget/)  
   - Add a **device type** in `DeviceType` and a **DeviceCoordinator** (e.g. `AngelfitDeviceCoordinator` or `IDODeviceCoordinator`) that:
     - Returns a name pattern matching your watch (e.g. `Pattern.compile("Ksix.*|IDW.*|...", Pattern.CASE_INSENSITIVE)` if you know the advertised names).
     - Uses **BLE scan filters** for service UUID **0x0AF0** so only these devices are discovered.
     - Implements `getBondingStyle()` (e.g. `BONDING_STYLE_BOND` for BLE pairing).
     - Declares supported features via `supportsXXX()`.
   - Implement **DeviceSupport** extending `AbstractBTLESingleDeviceSupport` (or `AbstractBTLEMultiDeviceSupport` if needed). Use `Transaction` and `BtLEQueue` for GATT: connect, discover 0x0AF0/0x0AF6/0x0AF7 (and 0x0AF1/0x0AF2 if you do bulk transfer), enable notifications on 0x0AF7, then send commands (e.g. GET 0x02 0x01 for device info) and parse replies to mark the device initialized.

3. **Implement initialization and features**  
   In `initializeDevice()`: send GET device info (0x02 0x01), optionally GET func table (0x02 0x02), set time (0x03 0x01), etc. Map protocol replies to GadgetBridge’s device state and database (e.g. battery, firmware, activity sync). Reuse the command bytes and parsing from idowatch/angelfit (GET/SET/Control/MSG as in TOOBUR command table).

4. **Optional: device request and docs**  
   File a [device request](https://codeberg.org/Freeyourgadget/Gadgetbridge/issues/new?template=.gitea%2fissue_template%2fdevice_request.yml) on Codeberg and link TOOBUR.md (or a short protocol summary) so maintainers can see the protocol. Contributing a full or partial implementation (e.g. discovery + device info + time sync + activity sync) as a PR is the way to get angelfit-like devices into mainline GadgetBridge.

5. **Bluetooth inspection**  
   Use [Inspect Bluetooth packets](https://gadgetbridge.org/internals/development/bluetooth/) and nRF Connect or HCI snoop to confirm your watch uses 0x0AF0 and matches the angelfit command set before coding.
