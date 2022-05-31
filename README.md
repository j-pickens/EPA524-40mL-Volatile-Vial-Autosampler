<p align="center">
<img src="/Images/UnderDevelopment.png" width="200">
</p>

<p align="center">
<img src="/Images/EPA524-40mL-Volatile-Vial-Autosampler.png" width="200">
</p>

# EPA524-40mL-Volatile-Vial-Autosampler

*TL;DR* Do-it-yourself [EPA524](https://www.epa.gov/sites/default/files/2015-06/documents/epa-524.2.pdf) compliant refrigerated 40mL vial Autosampler.  

## Overview

This autosampler is broken down into three pieces; refrigerated case, electronic control system, and IO peripherals.

The refrigerated case is comprised of extruded aluminum railing. The railing is filled with insulation foam sheets and secured with plastic siding. The unit is cooled using a TEC cooling block.

The electronics control system manages all functions of the autosampler using a Raspberry Pi. The Raspberry Pi and all peripherals are powered by an ATX Power Supply (PC Power Supply). The Raspberry Pi controls the peripherals via I2C protocol using Node-Red.

There are eight peripherals; valve relay, sample syringe, standard syringe, needle assembly, vial belt, temperature sensor, and pressure sensor. The valve array uses two four-channel i2c relays. Each of the eight relays is wired to control one of six valves. These valves are used to control the direction of fluids in the autosampler. The NEMA stepper motors that control the two syringes, vial belt, and needle assembly are controlled by an Arduino Uno with a CNC shield. The shield controls the four stepper motors, and their respective end stops.  The temperture sensor montiors the temperture within the refrigeratoed case.  Lastly, the Pressure sensor monitors the pressure of the N2 supply line. 

### Hardware
|Qty | Hardware|Link  |Cost| Notes|
|--|--|--|--|--|
|| **BODY**||||
|###| Aluminum Rail|url|cost|notes| 
|###| T-Nuts |url|cost|notes| 
|###| T-Nut screws |url|cost|notes| 
|4| Feet |url|cost|notes| 
|###| T-Slot angle bracket |url|cost|notes| 
|| **Vial Belt**||||
|### kg| PLA |url|cost|notes| 
|###| Nuts for Belt |url|cost|notes| 
|###| Screw for Belt |url|cost|notes|
|###| 40mL vials |url|cost|notes|
|| **Needle Assembly**||||
|| **Electronics**||||
|1| Power Supply|url|cost|notes|  
|1| Power Supply Board|url|cost|notes| 
|1| Raspberry Pi 4|url|cost|notes| 
|1| Arduino |url|cost|notes| 
|1| Arduino CNC Shield|url|cost|notes|  
|4| Stepper Motor|url|cost|notes| 
|4| Motor Drivers|url|cost|notes| 
|1| Phat Stack|url|cost|notes| 
|1| i2c Temperture Sensor |url|cost|notes| 
|1| i2c Relay Board |url|cost|notes| 
|| **Cooling**||||
|###| Foam board |url|cost|notes| 
|###| Radiator |url|cost|notes| 


## Total $00.00


## Support Websites




## Authors

* **[John Pickens](https://www.linkedin.com/in/john-pickens-5643121/)** 
* **[S James Parsons Jr](https://www.linkedin.com/in/sjamesparsonsjr/)** 


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


