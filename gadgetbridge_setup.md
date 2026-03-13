# Gadgetbridge setup (idowatch / TOOBUR)

Instructions used to clone Gadgetbridge into this project, add TOOBUR device support, and build on Kubuntu 25.10. The same build supports **Bangle.js** (via the `banglejs` product flavor) and **TOOBUR** (VeryFit/IDO 0x0AF0) in one APK.

---

## 0. Compile and install the GadgetBridge mod

From the project root, after cloning this repo and entering `gadgetbridge`:

```bash
cd gadgetbridge
./gradlew assembleMainDebug
./gradlew installMainDebug
```

If you also build the Bangle.js flavor:

```bash
./gradlew assembleBanglejsDebug
./gradlew installBanglejsDebug
```

Make sure a device is connected with USB debugging enabled and trusted before running the install commands.

## 1. Clone Gadgetbridge

From the idowatch project root:

```bash
git clone https://github.com/d3nd3/gadgetbridge-veryfit.git gadgetbridge
```

This creates `gadgetbridge/` as our working fork on GitHub.

If you want to keep the original Codeberg repository as upstream:

```bash
cd gadgetbridge
git remote add upstream https://codeberg.org/Freeyourgadget/Gadgetbridge.git
git fetch upstream
```

Changes for this repo are expected in `origin` (the fork), and can be synced with:

```bash
git push origin master
```

---

## 2. TOOBUR device support

TOOBUR-family devices (Toobur, Runlio, Biggerfive, Ksix, IDW, etc.) use the same IDO/Realtek 0x0AF0 GATT protocol as Gadgetbridge’s ID115. We added a dedicated TOOBUR device type that reuses ID115’s protocol and support.

### Changes made

- **`gadgetbridge/app/.../devices/toobur/TooburCoordinator.java`**  
  New coordinator: BLE filter on service 0x0AF0; `supports()` matches device names containing (case-insensitive) Toobur, Runlio, Biggerfive, Ksix, IDW, VeryFit, or Ryze. Uses `ID115Support` and `ID115ActivitySampleDao`.

- **`gadgetbridge/app/.../model/DeviceType.java`**  
  Added `TOOBUR(TooburCoordinator.class)` and import for `TooburCoordinator`. Enum entry placed before `ID115` so TOOBUR-named devices are recognized as TOOBUR first.

- **`gadgetbridge/app/.../res/values/strings.xml`**  
  Added `<string name="devicetype_toobur" translatable="false">TOOBUR</string>`.

No new database entities or GBDaoGenerator changes; TOOBUR reuses ID115 activity samples and support.

---

## 3. JDK (Kubuntu 25.10)

Gadgetbridge’s [setup docs](https://gadgetbridge.org/internals/development/setup-environment/) recommend **OpenJDK 21** for building.

```bash
sudo apt update
sudo apt install openjdk-21-jdk git adb
```

Set `JAVA_HOME` so Gradle finds the JDK (e.g. in `~/.bashrc` or before building):

```bash
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
```

Optional: set as default Java:

```bash
sudo update-alternatives --config java   # pick the java-21 entry
```

---

## 4. Android SDK

The build needs the Android SDK. Either set `ANDROID_HOME` or create a project-local `local.properties` with `sdk.dir`.

**Note:** The Debian/Ubuntu `android-sdk` package does **not** include Google’s `sdkmanager` binary, so `sdkmanager --licenses` will fail with “command not found” unless you install one of the options below.

### Option A: System SDK (apt) + Python sdkmanager

Install the SDK and the Python-based `sdkmanager` (drop-in compatible with Google’s):

```bash
sudo apt update
sudo apt install android-sdk sdkmanager
```

Accept licenses (writes to `/usr/lib/android-sdk/licenses`; sudo required):

```bash
yes | sudo sdkmanager --sdk_root=/usr/lib/android-sdk --licenses
```

Install platform and build-tools (Gadgetbridge uses compileSdk 36 and build-tools 36.0.0):

```bash
sudo sdkmanager --sdk_root=/usr/lib/android-sdk "platform-tools" "platforms;android-36" "build-tools;36.0.0"
```

If `android-36` or `36.0.0` are not available, list and pick the newest:

```bash
sdkmanager --sdk_root=/usr/lib/android-sdk --list
```

You may see a warning like “Observed package id 'build-tools;29.0.3' in inconsistent location .../debian”. It is harmless and can be ignored.

### Option A2: System SDK + Google cmdline-tools (optional)

If you prefer Google’s official sdkmanager instead of the Python one:

```bash
sudo apt install android-sdk google-android-cmdline-tools-19.0-installer
```

Then use the full path to sdkmanager. On Ubuntu the path is often `cmdline-tools/19.0` (not `latest`). Check with:

```bash
find /usr/lib/android-sdk -name sdkmanager
```

Example (path may vary; use the one from `find`):

```bash
yes | sudo /usr/lib/android-sdk/cmdline-tools/19.0/bin/sdkmanager --sdk_root=/usr/lib/android-sdk --licenses
sudo /usr/lib/android-sdk/cmdline-tools/19.0/bin/sdkmanager --sdk_root=/usr/lib/android-sdk "platform-tools" "platforms;android-36" "build-tools;36.0.0"
```

### Option B: Android Studio

Install [Android Studio](https://developer.android.com/studio); the installer will put the SDK in e.g. `~/Android/Sdk`. Use that path for `sdk.dir` below.

### Point the project at the SDK

Create or edit `gadgetbridge/local.properties` (do not commit; it’s machine-specific):

**If using apt SDK (`/usr/lib/android-sdk`):**

```properties
sdk.dir=/usr/lib/android-sdk
```

**If using Android Studio SDK:**

```properties
sdk.dir=/home/YOUR_USERNAME/Android/Sdk
```

Alternatively, set the environment variable and omit `sdk.dir`:

```bash
export ANDROID_HOME=/usr/lib/android-sdk
# or
export ANDROID_HOME=$HOME/Android/Sdk
```

---

## 5. Build

From the Gadgetbridge directory:

```bash
cd gadgetbridge
./gradlew assembleDebug
```

To build a specific flavor (e.g. main debug APK):

```bash
./gradlew assembleMainDebug
```

### Bangle.js release (includes TOOBUR)

To build the **Bangle.js** variant (for use with Bangle.js watches) **with TOOBUR/VeryFit support included** — one APK for both Bangle.js and TOOBUR:

```bash
./gradlew assembleBanglejsRelease
```

- **Debug (install alongside mainline):** `./gradlew assembleBanglejsDebug`
- **Release APK output:** `app/build/outputs/apk/banglejs/release/` (or `banglejsRelease/` depending on Gradle version)

The `banglejs` product flavor only changes app identity and permissions (e.g. app name “Bangle.js Gadgetbridge”, `INTERNET_ACCESS=true`). It does **not** exclude any device coordinators, so TOOBUR (and all other devices) remain in the build. You can use this single APK for both your Bangle.js and your TOOBUR.

To install the mainline debug build to a connected device:

```bash
./gradlew installMainDebug
```

To install the Bangle.js debug build (so you can use both Bangle.js and TOOBUR with one app):

```bash
./gradlew installBanglejsDebug
```

---

## 6. Troubleshooting

- **“SDK location not found”** — Create `gadgetbridge/local.properties` with `sdk.dir=/usr/lib/android-sdk` (or your SDK path), or set `ANDROID_HOME`.
- **“sdkmanager: command not found”** — The `android-sdk` package does not include sdkmanager. Install the Python wrapper: `sudo apt install sdkmanager` (see §4 Option A).
- **“License for package ... not accepted”** — Run `yes | sudo sdkmanager --sdk_root=/usr/lib/android-sdk --licenses` (or with full path e.g. `/usr/lib/android-sdk/cmdline-tools/19.0/bin/sdkmanager` if using Google cmdline-tools), then install components: `sudo sdkmanager --sdk_root=/usr/lib/android-sdk "build-tools;36.0.0" "platforms;android-36"`.

---

## 7. Reference

- Gadgetbridge setup: https://gadgetbridge.org/internals/development/setup-environment/
- TOOBUR protocol and commands: [TOOBUR.md](TOOBUR.md) in this repo
- Plan used for TOOBUR integration: clone ID115-style 0x0AF0 support, add TooburCoordinator with name-based matching, reuse ID115Support and ID115 activity storage.
