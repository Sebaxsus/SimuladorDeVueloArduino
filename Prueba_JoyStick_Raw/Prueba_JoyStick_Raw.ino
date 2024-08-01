// Pines del joystick
const int VRx = A0;
const int VRy = A1;
//const int SW = 2;

void setup() {
  // Configurar el pin del botón como entrada con pull-up interno
  //pinMode(SW, INPUT_PULLUP);

  // Iniciar comunicación serial para depuración
  Serial.begin(9600);
}

void loop() {
  // Leer los valores de los ejes X e Y
  int xValue = analogRead(VRx);
  int yValue = analogRead(VRy);

  // Leer el estado del botón
//  int buttonState = digitalRead(SW);

  // Imprimir los valores en la consola serial
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.println(yValue);
  //Serial.print(" | Button: ");
  //Serial.println(buttonState == LOW ? "Pressed" : "Not Pressed");

  // Pequeño retardo para evitar saturar la consola serial
  delay(100);
}
