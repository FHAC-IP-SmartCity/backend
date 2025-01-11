# 3. Controller:
- RFID - Bus detection
- TCRT - Train detection west station
- PIR - Counter


## RFID
1. Bus drives above CardReader
2. Bus is on bus stop

## TCRT
1. Train drives into station (west)
2. Train is in station (west)

## PIR
1. Car is driving
2. Car count

## Pins
#### RFID
|GND|VCC|RST|MISO |MOSI |SCK |SS |
|---|---|---| --- | --- | --- | --- |
|GND|VCC|17|19|23|18|5|
||||MISO|MOSI|SCK|


#### StatusLED
Pin - 13


#### TCRT
fst - 12
snd - 14

#### PIR
Pin - 27


### Problems
How to update dashboard if bus leaves stop. The Reader reads just once.

### Solution
Glue an unauthorized chip to the end of the bus