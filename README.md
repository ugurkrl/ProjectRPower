**Project R Power**

**Atmega328P Based Gas Gauge Monitor With 128x64 OLED Display**

**Usable with powerbank solutions etc.**

**Only Supports 1Wired HDQ Gas Gauge IC's (bq27541,bq27542,bq27545,bq27546 etc.)**

**Planning To Make a SMBUS Version of This for Multi-Cell Batteries**

![Board Image](/HW/GaugeMaster/Pics/PCB.png)

![Block Diagram](/HW/GaugeMaster/Pics/Block.png)

*Crystal Oscillator is 8MHz even it says 16MHz in 3D Model*

**To-Do SW**
1. Clean codes a little bit
1. Add auto shutdown 
1. Or maybe add auto dimming display function (Those cheap 128x64 panels burns so easily. You dont want to see charging icon even when battery isnt charging)
1. Add contrast change ability
1. Add function for second HDQ battery
1. Create Time to Full(or %80 ?) function in sw (since it has removed in bq27541 G1 firmware)
1. It should switch between 0.00W and 00.0W automatically on display. USB Quick Charging causes issues after 9.99W
1. Allow user to switch between Watts and Amperes on display
1. Add extra debugging pages for viewing Ra tables or dumping gasgauge dataflash through UART
1. Add State of Health , Cycle count and QMax monitoring functions to menus
1. Adding charge level graph ? (and use internal eeprom for it)
1. Adding SoH graph ?
1. Add ability to control ip5328p through i2c bus (or not idk). Maybe seperate version for that ? since not all solutions will use same usb charging circuitry

**To-Do HW**
1. Add SMBUS/I²C battery support (40z50 etc.)
1. Add external i2c pads. Since some battery charging solutions can use i2c bus for configuration
1. Reduce size of PGM and BATT pads
1. Change Crystal to SMD variation (THT one is pretty thick) 