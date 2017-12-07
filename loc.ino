#include "config.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.   
It requires the use of SoftwareSerial, and assumes that you have a 9600-baud serial 
GPS device hooked up on pins 8(rx) and 9(tx).*/
static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
AdafruitIO_Feed *location = io.feed("location");
int value = 0;
void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

}

void loop()
{
  io.run();
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    float lati = gps.location.lat();
    float lon = gps.location.lng();
    float ele = 0.0;
    Serial.print(lati);
    Serial.print(F(","));
    Serial.print(lon);
 location->save(value, lati, lon, ele);
  }
  else
  {
    Serial.print(F("INVALID"));
  }  
  Serial.println();
}
