#!/bin/bash

# to add the device
# device_add usb-kbd,bus=usb-bus.0,port=1,id=kbd00

# to del the device
# device_del kbd00

# to show the plug event 
# udevadm info --name=/dev/input/event3

cat 99-ass04.rules > /etc/udev/rules.d/99-ass04.rules
udevadm control --reload

# uncomment to display the logs
# dmesg | tail -10
