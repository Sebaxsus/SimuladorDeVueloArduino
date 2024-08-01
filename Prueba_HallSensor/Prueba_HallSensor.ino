void setup() {
  Serial.begin(9600);
}

void loop() {
   int hallRead;
  // put your main code here, to run repeatedly:
  hallRead = analogRead(A2);
  Serial.print("Analog Hall Sensor Pin A2: ");
  Serial.println(hallRead);
  delay(100);
  //Sirve Rango 210-800
}
