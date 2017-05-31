# Flightgear Aircraft

This folder contains aircraft specific files for Barry's Autopilot.

## Properties and Nasal scripts:

The autopilot of the Boeing 747-8i is implemented in the nasal script file, located at
```Nasal/AFDS.nas```.

 - Autopilot Engaged: Property ```instrumentation/afds/inputs/AP``` (bool)
 - Autopilot Disengaged: Property ```instrumentation/afds/inputs/AP-disengaged``` (bool)
 - HDG-Mode select: Nasal ```Boeing747.afds.input(0,1); controls.click(4);```
     - Set Property ```instrumentation/afds/inputs/lateral-index = 1```
 - HDG bug: Property ```/autopilot/settings/heading-bug-deg``` (int)
 - HDG HOLD: Nasal ```controls.click(4);Boeing747.afds.input(0,2);```
     - Set Property ```/autopilot/settings/heading-bug-deg = /orientation/heading-magnetic-deg```
     - Set Property ```instrumentation/afds/inputs/lateral-index = 2```
 
 
