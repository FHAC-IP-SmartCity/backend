# Traffic Light System

### Sensors
1. RFID (1x)
2. Traffic Light (3x)

___
### Pins
#### RFID
| GND  | VCC  | RST  | MISO  | MOSI  | SCK  | SS
|---|---|---|---|---|---|---|
| GND  |  VCC | 17  | 19  | 23  | 18 | 5
|   |   |   |  MISO |MOSI   | SCK| SS


#### Traffic Light 1
|Red|Yellow|Green|
|---|---|---|
|14|13|12|


#### Traffic Light 2
|Red|Yellow|Green|
|---|---|---|
|27|13|26|

___
### Function
1. Track the bus/police car on traffic light
2. Send data to backend - "Bus hat Vorrang"
3. Switch state - "greenState"


### Problems
If the state is switching, the RFID does not track. You need to wait until the yellowState switched
Case is programmed but not used