# pico-rp2350-UART-driver
Bare-metal UART driver for rp2350 (Raspberry Pi Pico 2). 

## Buliding
```bash
mkdir build && cd build
cmake ../source
make -j4
```

you can listen to the output through USB if needed
```
screen /dev/tty.usbmodem142301 115200 
```

---
- [RP2350 datasheet](https://pip-assets.raspberrypi.com/categories/1214-rp2350/documents/RP-008373-DS-2-rp2350-datasheet.pdf?disposition=inline)
- [pico-sdk uart.c](statics.teams.cdn.office.net/evergreen-assets/safelinks/2/atp-safelinks.html)
