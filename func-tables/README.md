## Function table discovery notes

`adb backup -f mybackup.ab com.watch.life`

**Found a _VERY_ useful file**

`veryfit_apk/extracted/apps/com.watch.life/f/Veryfit/deviceFunction$`  
`file function_table.json`  
`function_table.json: JSON text data`

It allows proper verification of the supported device functionality and provides command codes for every v3 function.

## Required commands to unpack backup

```bash
sudo apt install default-jre zlib1g-dev
java -jar abe.jar unpack mybackup.ab mybackup.tar
```
