# IRControl Fan, for Attiny85

This project allows you to control a fan using a common infrared remote control. As a matter of pin limit, he will no longer use the physical speed control button. Ideal for fans attached to the wall.

You must first uncomment the lines with "Serial Commands" and compile on an Arduino UNO board, to find out which the code of the keys on your remote control by serial monitor. Change the code according to the desired keys, comment the lines again with Serial and compile for Attiny85.
