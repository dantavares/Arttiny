# Arduino code to communicate with xbox 360 RF module.

Original work by (yaywoop) / additional ideas from Alexander Martinez - modified by dilandou (www.dilandou.com, www.diru.org/wordpress)
First sends LED initialisation code followed by LED startup animation code, then sleeps until a button press for sync command.
RF module must be powered with 3.3V, two diodes in series with USB 5v will do. Connect the USB wires to a host computer, and the data and serial wires to Arduino.
of course, make sure to have a common ground 

Conversion to Attiny13 by Daniel Tavares

![board](https://github.com/dantavares/Arttiny/blob/main/RF_XBOX360/board.jpg?raw=true?raw=true)
