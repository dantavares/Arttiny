# Attiny controller for  xbox 360 RF module.

With this project you will be able to recycle an RF module of the XBOX 360, (front card with the power button and the leds) converting it to a USB input. With it you can use any XBOX 360 controller on a PC (Windows and Linux) Raspberry PI and even Android.

Original work by (yaywoop) / additional ideas from Alexander Martinez - modified by dilandou (www.dilandou.com, www.diru.org/wordpress)
Sends LED initialisation code, then sleeps until a button press for sync command.
RF module must be powered with 3.3V, two diodes in series with USB 5v will do. Connect the USB wires to a host computer, and the data and serial wires to Arduino.
of course, make sure to have a common ground 

On Windows you will need to install the necessary drivers, to do this download driver on MS:
https://www.microsoft.com/accessories/en-in/d/xbox-360-controller-for-windows

And follow these steps:
https://github.com/dantavares/Arttiny/blob/main/RF_XBOX360/HOW-TO_Wireless-Xbox360-controller-on-Windows.pdf

Conversion to Attiny13 by Daniel Tavares

![board](https://github.com/dantavares/Arttiny/blob/main/RF_XBOX360/board.jpg?raw=true?raw=true)
