# Positive thermostat, controlled by relay

This project uses an NTC 10k thermistor as a sensor room temperature, a TM1637 display to display values and a potentiometer of 100k to set the desired temperature.
 
Use a common heater connected to the relay, if temperature is not as desired, the relay will switch on  heater, until it reaches the temperature set by potentiometer. The room temperature values and desired temperature are displayed in the diplay. The first two values is room temperature and the
two last is desired temperature.
Activation and deactivation of the heater does not is instantaneous, this is purposeful, so that only occurs when the ambient temperature has stabilized. 

ATTENTION! 
Make sure that the relay supports the heater current. Calculate the amps of your relay, dividing the power by the voltage.
 
This project fits on an ATtiny85.

I did not do a complete schematics to set up this project, sorry. 
But you can still use the images attached in this project to serve as a reference:

## Potentiometer:
![Potentiometer](https://github.com/dantavares/Arttiny/blob/main/Thermostat/potentiometer.jpg?raw=true)

## Relay:
![Relay](https://github.com/dantavares/Arttiny/blob/main/Thermostat/relay.png?raw=true)

## Display:
![Display](https://github.com/dantavares/Arttiny/blob/main/Thermostat/TM1637-4-digit-7-segment-display-pinout.jpg?raw=true)

## Thermistor:
![Display](https://github.com/dantavares/Arttiny/blob/main/Thermostat/thermistor.jpg?raw=true)

## Finished
![finished](https://github.com/dantavares/Arttiny/blob/main/Thermostat/finished.jpeg?raw=true)
