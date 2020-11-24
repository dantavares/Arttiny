# Push a button remotely

There are many devices that use digital logic as input for an action, usually a momentary button, which when pressed puts a high signal for example on the ground, leaving the signal low, when this occurs the device controller understands that the user pressed the button, and must perform the action attached to that button, such as turning on or off.

The idea is to make this logical inversion (high to low or low to high) through an Attiny85, which received this command from an infrared remote control, making it possible for you to control this device through a remote control.

Summarizing the idea of this project is to adapt an infrared remote control, in a device that originally does not have a remote control, without making major changes. In this version it is possible to control only one button, so it is necessary to have one ATtiny per button to be controlled remotely.

It is important to note that the physical button will not lose its functionality, since ATtiny will be connected in parallel to it, so there is no need to remove it.

You need to find out by a multimeter, whether the signal is high or low before pressing it, and what happens when pressing it. If the signal is reversed, this project will probably work. Check the normal signal (without pressing the button) is correct in the code.

## To program the remote control:

1. Press the physical button and hold
2. Press the desired button on the remote control
3. Keep holding for 2 seconds
4. Release the physical button
5. Do the test, if necessary repeat the procedure
  
The key code will be saved permanently, until a new key is reprogrammed.

## Schematics
![circuit](https://github.com/dantavares/Arttiny/blob/main/IR_PushButton/circuit.png?raw=true)
