#include "DHT.h"

#include <Wire.h>
#include "Adafruit_SI1145.h"

#define DHTPIN 13     // Digital pin connected to the DHT sensor


// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

Adafruit_SI1145 uv = Adafruit_SI1145();

float tempC;
float tempF;
float hum;
float hiC;
float hiF;
float l_vis;
float l_ir;
float l_uv;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();

   if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }

  
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
   hum = dht.readHumidity();
  // Read temperature as Celsius (the default)
  tempC = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  tempF = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(hum) || isnan(tempC) || isnan(tempF)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
   hiF = dht.computeHeatIndex(tempF, hum);
  // Compute heat index in Celsius (isFahreheit = false)
  hiC = dht.computeHeatIndex(tempC, hum, false);

  Serial.print(F("Humidity: "));
  Serial.print(hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(tempC);
  Serial.print(F("°C "));
  Serial.print(tempF);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hiC);
  Serial.print(F("°C "));
  Serial.print(hiF);
  Serial.println(F("°F"));

  Serial.println("===================");
  l_vis=uv.readVisible();
  l_ir=uv.readIR();
  l_uv=uv.readUV()/100.0;
  Serial.print("Vis: "); Serial.println(l_vis);
  Serial.print("IR: "); Serial.println(l_ir);
  
  // Uncomment if you have an IR LED attached to LED pin!
  //Serial.print("Prox: "); Serial.println(uv.readProx());
 
  Serial.print("UV: ");  Serial.println(l_uv);
}
