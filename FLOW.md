# Bluetooth Command-ID Mapping Flow (VBUS_EVT_APP_SET_UP_HAND_GESTURE = 114)

## End-to-end flow

1. Java call chain:
   - `sources/com/ido/ble/protocol/cmd/obelisk.acorn(UpHandGesture)`  
   - `sources/com/ido/ble/protocol/handler/umbra.basilisk(byte[] bArr, int i2)` calls `Protocol.WriteJsonData(bArr, 114)`
2. JNI entry:
   - `Java_com_veryfit_multi_nativeprotocol_Protocol_WriteJsonData(...)`
   - Logs `app send protocol evt:114(...)`
   - Builds string payload and calls `jni_json_data_notice_data_handle(v13, 114)`
3. Dispatcher:
   - `jni_json_data_notice_data_handle(std::string, int)` iterates registered callbacks from `qword_615190`
   - `jni_json_data_rx_evt_reg(...)` only registers callbacks; it does **not** perform byte mapping
4. Protocol command writer path:
   - Mapping from app event ID to BLE command key happens in protocol write control function `sub_1BA1D0(...)`
   - For `a2 == 114`, branch sets:
     - `v22 = 3`
     - `v23 = 40`
     - then calls `protocol_write_set_head()`
5. Frame assembly:
   - `protocol_write_set_head(__int16 a1, __int64 a2, unsigned int a3, char a4, unsigned int a5)`
   - For `a1 == 0x2803` or equivalent internal packing path, `protocol_write_set_cmd_key` writes:
     - `v15[0] = a1`
     - `v15[1] = HIBYTE(a1)`
   - `protocol_write_set_cmd_key` forwards to `protocol_write_data(...)`
6. Result:
   - `40 decimal = 0x28` becomes the command byte in TX
   - Frame observed: `03 28 ...` matches second byte = command key `0x28`

## Key conclusion

- The correct mapping location is **`sub_1BA1D0`** (protocol write control switch), not:
  - `protocol_write_set_head`
  - `protocol_write_set_cmd_key`
  - `protocol_util_vbus_evt_to_str`
- `sub_1BA1D0` is the function that maps event `114` to command byte `0x28`.

## Symbols confirmed relevant

- `protocol_write_set_head`
- `protocol_write_set_cmd_key`
- `protocol_write_data`
- `protocol_write_init`
- `sub_1BA1D0` (core mapping switch for VBUS control commands)
- `protocol_write_data_add` (referenced by logs when queueing TX frame)
- `jni_json_data_notice_data_handle`
- `jni_json_data_rx_evt_reg`
