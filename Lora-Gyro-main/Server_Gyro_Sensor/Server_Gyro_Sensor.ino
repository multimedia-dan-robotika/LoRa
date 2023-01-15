#include <SPI.h>
#include <LoRa.h>

/* LoRa to NodeMCU interface
   VCC      3V3
   GND      GND
   MISO     D6
   MOSI     D7
   SCK      D5
   NSS/CS   D8
   RESET    D4
*/

#define CS 10
#define RESET 9
#define DIO0 2


String AcXS, AcYS, AcZS, GyXS, GyYS, GyZS;
void setup()
{
  Serial.begin(9600);

  LoRa.setPins (CS, RESET, DIO0);
  if (!LoRa.begin(915E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.receive();
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    Serial.println("Received packet: ");
    while (LoRa.available())
    {
      AcXS = LoRa.readStringUntil ('#');
      Serial.print("Accel X : ");
      Serial.println (AcXS);
      AcYS = LoRa.readStringUntil ('#');
      Serial.print("Accel Y : ");
      Serial.println (AcYS);
      AcZS = LoRa.readStringUntil ('#');
      Serial.print("Accel Z : ");
      Serial.println (AcZS);
      Serial.println("========================");
       GyXS = LoRa.readStringUntil ('#');
      Serial.print("Gyro X : ");
      Serial.println (GyXS);
      GyYS = LoRa.readStringUntil ('#');
      Serial.print("Gyro Y : ");
      Serial.println (GyYS);
      GyZS = LoRa.readStringUntil ('#');
      Serial.print("Gyro Z : ");
      Serial.println (GyZS);
    }
  }

    delay (500);
}
