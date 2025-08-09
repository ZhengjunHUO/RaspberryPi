# RaspberryPi

## Preparation
```sh
sudo systemctl set-default multi-user.target
sudo rm /var/lib/man-db/auto-update
sudo systemctl mask apt-daily-upgrade
sudo systemctl mask apt-daily
sudo systemctl disable apt-daily-upgrade.timer
sudo systemctl disable apt-daily.timer
sudo systemctl disable avahi-daemon.service
sudo systemctl disable bluetooth.service
sudo systemctl disable ModemManager.service
```

## Install WiringPi
```sh
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build debian
mv debian-template/wiringpi-3.x.deb .
sudo apt install ./wiringpi-3.x.deb
```

## Working with C
```sh
gpio readall
gcc -o app app.c -l wiringPi
./app
```
