
// Beispiel zum lesen der Werte



#include <XGZP6847.h>

XGZP6847 sensor;

void setup() {
  Serial.begin(115200);
  sensor.begin();
}

void loop() {
  sensor.startMeasurement();
  while (!sensor.measurementFinished());

  Serial.print("Pressure: "); Serial.print(sensor.readPressureBar()); Serial.print(" bar, ");
  Serial.print("Temp: "); Serial.println(sensor.readTemperatureC());

  delay(500);
}
