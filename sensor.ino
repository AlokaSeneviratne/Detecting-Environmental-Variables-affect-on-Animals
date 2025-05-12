#include <Wire.h>  // for I2C with RTC module
#include <Adafruit_GFX.h>
#include "RTClib.h"       //to show time
#include "DHT.h"
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
RTC_DS3231 rtc;

String data = "";

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define DHTPIN 4     
#define AOUT_PIN 34

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (!bmp.begin())
  {
    Serial.println("BMP180 Sensor not found ! ! !");
    while (1)
    {
    
    }
  }
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  } 
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  int value = analogRead(AOUT_PIN);
  DateTime now = rtc.now();

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C   Moisture value: "));
  Serial.print(value);
  Serial.print(F("  Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.print(F(" hPa   Temp = "));
  Serial.print(bmp.readTemperature());
  Serial.println(F("ºC"));
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.print("  ");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print("  ");
  Serial.print(now.day(), DEC);
  Serial.print("-");
  Serial.print(now.month(), DEC);
  Serial.print("-");
  Serial.println(now.year(), DEC);
  delay(2000);
}
