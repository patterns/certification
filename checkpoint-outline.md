flash attempt #1 failed with:
[husky@nixpi:~/devel/demo2]$ cd opensk

[husky@nixpi:~/devel/demo2/opensk]$ ./tools/configure.py --certificate=crypto_data/opensk_cert.pem --private-key=crypto_data/opensk.key
info: Private key is valid.
Traceback (most recent call last):
  File "/home/husky/devel/demo2/opensk/./tools/configure.py", line 223, in <module>
    main(parser.parse_args())
  File "/home/husky/devel/demo2/opensk/./tools/configure.py", line 107, in main
    if cert.not_valid_before_utc > now:
TypeError: can't compare offset-naive and offset-aware datetimes

[husky@nixpi:~/devel/demo2/opensk]$ ./deploy.py --board=nrf52840_dongle_dfu --opensk --programmer=nordicdfu
fatal: Your version of tockloader seems incompatible: found 1.9.0, expected 1.5.x.

newer nrfutil (after 2022) is x86_64, the 2022 is the version installed by pip for python3.10. Does this mean openocd is the only option if we can't obtain a x86 machine?
From GH issue#667 (https://github.com/google/OpenSK/issues/667):

Ok, I was finally able to get it to flash with the latest tool using:
.\nrfutil_.exe pkg generate --hw-version 52 --sd-req=0x00 --application .\nrf52840_dongle_dfu_merged.hex --application-version 1 OpenSK.zip
.\nrfutil_.exe dfu usb-serial -p com8 -pkg OpenSK.zip

That is using the latest (closed source) tool from NordicSemi

There was no real clear instructions on the fact that it needed to be packaged into a zip file first, then flashed. Perhaps this is how it works in the standard scripts but this is left out of any doco here when discussing manually flashing it.

/////
success generating zip from hex:
adafruit-nrfutil dfu genpkg --dev-type=52 --sd-req=0 --application-version=1 --application=targdevel/nrf52840_dongle_dfu_merged.hex targdevel/opensk_dfu.zip

now flashing (needs dialout group membership?):
adafruit-nrfutil dfu serial --package=targdevel/opensk_dfu.zip -p /dev/ttyACM0 -b 115200
/////
it is possible to take the HEX file created by adafruit-nrfutil 
BUT do not use adafruit-nrfutil to generate the ZIP
because the x86 nrfutil (v7.12) can't display that ZIP
insead use the x86 nrfutil to generate the ZIP from the HEX, then flash the ZIP
nrfutil dfu usb-serial --package=generated-opensk-dfu.zip -p /dev/ttyACM0

make sure the user is a member of the dialout group (and logout/restart session)
sudo usermod -aG dialout $USER
/////
for the checkpoint report

   I. 
  II. 
 III. explain significance of WebAuthN.io verification with registration and authentication (USB key+PIN)
      A. zero passwords are used
      B. should be familiar (compare to banking debit card and PIN)
      C. show the diagrams from WebAuthN FAQ
      D. show another site?
         1. 
         2. Cloudflare/GH/LinkedIn/Slack? or as final demonstration, time permitting

  IV. explain What is wrong with passwords (pass phrase)?
      A. You have to trust providers to follow best practice. Facebook fined for storing plain text
      B. Best practice changes. NIST no longer advocates periodic schedule.
      C. Password managers.
         1. cite the most popular passwords in 2024 ranked by Nord
         2. Too many passwords as each site implements their own (non-shared) auth
         3. Increased password strength makes memorizing difficult
      D. sharing auth was error-prone, OAuth2 (Auth0/Okta)
      E. password databases are targets
         1. show the HIBP password search
         2. cite the RockYou2024 articles
      F. OWASP Cheatsheet has three levels of compliance
         1. show Moodle, Open edX, and Canvas LMS treatment?
      G. Predictions of obsolete algorithms when quantum computers are available?

   V. definition of the authentication types in MFA/2FA
      A. something you have/possess
         1. biometrics (fingerprint, voice, retina); Edna scene in the Incredibles
         2. private key
      B. something you know (secret)
         1. PIN
         2. pass phrase
         3. personal data (SSN, birth, maiden)

  VI. hardware key
      1. explain what is a hardware key
         A. public key encryption (PGP)
         B. similar to TLS/SSL, SSH, crypto wallets
      2. show which companies support hw keys (FIDO Alliance)
         A. Google, Apple, MS, Cloudflare
      3. Pros and Cons
         A. Con, WebAuthN is web browser dependent
            1. show GH issue# with Apple incompatibility
         B. Con, Losing the hw key
            1. No locksmith (no keymaster)
         C. Con, Few choices
            1. Yubikey @ $50 (subscription?)
            2. Solokey (open source, crowd funded)
            3. OpenSK (open source, academia/Google)

 VII. OpenSK on nRF52840 dongle
      1. show diagram of the steps
      2. URLs of project files and code, Digikey SKU
      3. what are the crypto_data/opensk_cert.pem and crypto_data/opensk.key files?
      4. walk through source code triggered by the WebAuthN protocol
     
XIII. outline next steps for final report
      1. use Go library for WebAuthN to make a demo site (and show no passwords in db)

Bibliography


//////////
