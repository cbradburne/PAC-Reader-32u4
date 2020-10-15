# PAC-Reader-32u4

PAC code RFID Reader (PAC ONEPROX GS3-MT)

For Arduino Leonardo 32u4 boards (Pro Micro)

Reads PAC code, outputs to USB HID keyboard including carriage return.

Work in progress.

PAC seems to use a baud-rate of 9600.

The start code from the fobs seems to be 3 bytes (in Hex) 181818.
I have 2 new fobs and 1 older one. The new fobs have a length, including the header, of 16 bytes. The older one 15 bytes, but fortunately the fobs sends the code out multiple times so the 16th byte gets filled in by the first byte of the next time round (18)

