Arm-bike/sw
===========

TO-DO:
------
+ Driver for Nokia 5510 LCD with HW SPI
+ Driver for MPR121 I2C touch sensor
+ Driver for STLM75M2E I2C temp sensor
+ Driver for UART GPS communication
+ Driver for PC data logging (FTDI230XS UART to USB serial)
+ Driver for PWM -> power LED
+ User interface (txt)
+ User interface (graphic)
+ Testing
+ RTOS & interrupts

x_driver.h
----------

### Graphical LCD driver (`GLCD_driver.h/.c`)
##### Done: 75% (HW SPI for 100%)

+ 1. 5. 2012		Working LCD driver with bit-banging. Write_: data, command, string, graphic; clear RAM; gotoxy                    
+ 2. 5. 2012		Improved code -> from 14% to 50% better timing. Still 92ms for full screen. HW SPI!
+ 9. 5. 2012		Code fully commented.

### PWM LED driver (`pwm.h/.c`)
##### Done: 30%

+ 7. 5. 2012  		1 channel working. Need to incorporate Fvpb and set duyt-cycle functions into pwm.h. Free 1 more PWM channel!!                    

### MPR121 I2C touch sensor driver (`mpr121.h/.c`)
##### Done: 70%

+ 12. 5. 2012  		Started with studying I2C lib.
+ 13. 5. 2012 		Created mpr121.h/.c. Added register addresses, basic function wrappers and few function walkthroughs.
+ 15. 5. 2012		Succesfully reading data from MPR121!

### UART0 GPS driver (`.h/.c`)
##### Done: 10%

+ 15. 5. 2012  		Started with GPS data reading over UART0 with interrupts