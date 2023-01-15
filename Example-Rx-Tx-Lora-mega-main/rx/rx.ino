
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    Serial1.write(Serial.read());
    Serial.println("Serial 1 ");
  }
  if (Serial1.available()) {
    Serial.write(Serial1.read());
    Serial.println("Serial 2 ");
    
  }

}
