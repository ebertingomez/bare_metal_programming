#!/bin/sh
#stty -F /dev/ttyACM0 38400 raw -echo -echoe -echok -crtscts clocal
stty -f /dev/cu.usbmodem000770868477 38400 raw -echo -echoe -echok -crtscts clocal
