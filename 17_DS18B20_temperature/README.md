# enable onewire
```sh
sudo raspi-config   # Interfacing options -> 1-wire -> reboot

tail /boot/firmware/config.txt 
# See
# [all]
# dtoverlay=w1-gpio
```

# check out device
ls /sys/bus/w1/devices/28-xxxxxx
```
