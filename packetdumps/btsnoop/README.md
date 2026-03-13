Dial **`*#800#` , Enable bluetooth logging

adb pull /sdcard/oppo_log/debug@stop@2026-03-07_20-41-51-689/btsnoop_hci/btsnoop_hci_20260307_204009.cfa

mergecap -w merged_capture.pcapng *.cfa

open in wireshark and export as json
