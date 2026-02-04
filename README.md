# XGZP6847 Arduino Library

This library allows easy reading of the **XGZP6847 pressure & temperature sensor** via I2C.  

## Features
- Read pressure (24-bit) and temperature (16-bit)
- Handles positive and negative values
- Converts raw values to bar (pressure) and °C (temperature)
- Simple start/measure API

## Usage

Note: The K value is selected according to the positive pressure value only.
Positive Pressure Range (kPa)	K Value
500 < P ≤ 1000	8
260 < P ≤ 500	 16
130 < P ≤ 260	 32
65 < P ≤ 130   64
32 < P ≤ 65	  128
16 < P ≤ 32	  256
8 < P ≤ 16	  512
4 < P ≤ 8	   1024
2 ≤ P ≤ 4    2048
1 ≤ P < 2    4096



```cpp
#include <XGZP6847.h>

XGZP6847 sensor(0x6D, 21, 22); // address, SDA, SCL

void setup() {
  Serial.begin(115200);
  sensor.begin();
}

void loop() {
  sensor.startMeasurement();
  while (!sensor.measurementFinished());
  
  float pressure = sensor.readPressureBar();
  float temp = sensor.readTemperatureC();

  Serial.print("Pressure: "); Serial.print(pressure); Serial.print(" bar  ");
  Serial.print("Temp: "); Serial.println(temp);
}
