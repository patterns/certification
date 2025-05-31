#!/bin/sh


# change to the parent subdir where child projects are located
##cd ~/devel

# cache list of packages
####arduino-cli core update-index

# connect the board to usb, first
# now show whether it is detected
arduino-cli board list
# install core for the board, first
# now show core that installed
####arduino-cli core install arduino:mbed_nano
arduino-cli core list

# add zip libraries (requires conf setting enable_unsafe_install)
# default destination will be ~/Arduino/libraries


# compile sketch (can be 30 mins on rpi)
# upload to board
# classifier
##cd ~/Arduino/libraries/EEP564_Project-Audio_Classification_-_Home_Security_inferencing/examples/nano_ble33_sense && \
##    arduino-cli compile --fqbn arduino:mbed_nano:nano33ble nano_ble33_sense_microphone
##cd ~/Arduino/libraries/EEP564_Project-Audio_Classification_-_Home_Security_inferencing/examples/nano_ble33_sense && \
##    arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:mbed_nano:nano33ble nano_ble33_sense_microphone

arduino-cli monitor -p /dev/ttyACM0 --fqbn arduino:mbed_nano:nano33ble

