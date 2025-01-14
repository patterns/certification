# 2024.12.15 report

##   I. Problem

##  II. Previous works

## III. Approach
###     A. OpenSK

##  IV. Experiments

###     A. nrf52840 USB dongle
           1. Build OpenSK on Raspberry Pi4 with NixOS
           2. Run nrfutil and adafruit-nrfutil
              a. This is old Python version and fails
              b. The adafruit-nrfutil can successfully generate the merged HEX file, but it is not compatible with the newer nrfutil
           3. Run newer nrfutil [90] from x86 PC with Mint Linux
              a. generate (ZIP) command
              b. flash (deploy) command
           3. 
              b. Successfully verified at WebAuthn.io

###     B. Raspberry Pi Pico 
           1. Attempted the "hello world" serial port program in OpenSK
              a. Flash of the kernel appears successful [95]
              b. Tockloader does not detect the Pico, but instead offers a simulator.
           2. Attempt the blink program in official Raspberry Pi Pico SDK
              a. Blink is successful

###     C. Adafruit kb2040
           1. Attempted to build from source of the pico-fido project [100]
              a. First from the main branch which failed.
              b. Second from the release v6.0 branch which also failed.
           2. Downloaded the release 6.0 pre-built UF2 file
              a. The kb2040 will mount as a USB mass storage volume and allow the UF2 file to be saved.
              b. Successfully verified at WebAuthn.io

##   V. References / bibliography

 90. https://devzone.nordicsemi.com/nordic/nordic-blog/b/blog/posts/nrf-util-unified-command-line-utility
 95. https://github.com/google/opensk/boards/raspberry_pi_pico/
100. https://github.com/polhenarejos/pico-fido.git


