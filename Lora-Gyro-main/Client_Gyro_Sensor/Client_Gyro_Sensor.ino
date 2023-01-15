#include <SPI.h>
#include <LoRa.h>
#include<Wire.h>
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
String AcXS, AcYS, AcZS, GyXS, GyYS, GyZS;
/* LoRa to Nano interface
   VCC      3V3
   GND      GND
   MISO     D12
   MOSI     D11
   SCK      D13
   NSS/CS   D10
   RESET    D9
*/


void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);

  if (!LoRa.begin(915E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.println(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
  AcXS = String(AcX);
  AcYS = String(AcY);
  AcZS = String(AcZ);
  GyXS = String(GyX);
  GyYS = String(GyY);
  GyZS = String(GyZ);
  Serial.print("AcXS = "); Serial.print(AcXS);
  Serial.print(" | AcYS = "); Serial.print(AcYS);
  Serial.print(" | AcZS = "); Serial.print(AcZS);
  Serial.println("Sending packet: ");

  LoRa.beginPacket();

  LoRa.print(AcXS);
    LoRa.print("#");
  LoRa.print(AcYS);
    LoRa.print("#");
  LoRa.print(AcZS);
    LoRa.print("#");
  //LoRa.print(" Temperature:");
  LoRa.print(GyXS);
    LoRa.print("#");
  LoRa.print(GyYS);
    LoRa.print("#");
  LoRa.print(GyZS);
    LoRa.print("#");
  LoRa.endPacket();

  

  delay (500);
}
