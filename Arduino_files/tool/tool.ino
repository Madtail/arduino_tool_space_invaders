void setup() {
  Serial.begin(9600);
}

void loop() {
  //char buffer[1024] = "RESTART";
  //Serial.write(buffer, sizeof(buffer));
  Serial.write("RESTART\n");
  delay(2000);
}
