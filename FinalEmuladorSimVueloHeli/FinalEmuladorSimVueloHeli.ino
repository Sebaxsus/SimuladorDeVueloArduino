#include <HID.h>
#include <Joystick.h>

//Se crea la instancia del joystick para una HID (Human Interface Device)
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK, 32, 0,true, true, false, false,
false, false, false, false, false, false, false);

// Pines del joystick
const int VRxPin = A0; // Pin analógico para el eje X
const int VRyPin = A1; // Pin analógico para el eje Y
const int SWPin = 2;   // Pin digital para el botón

void setup() {
  // Inicializo la instacia del joystick
  Joystick.begin();

}

void loop() {
  // Leer los valores de los ejes X e Y
  int xValue = analogRead(VRxPin);
  int yValue = analogRead(VRyPin);
  
  // Convertir los valores leídos a un rango de 0 a 1023
  xValue = map(xValue, 0, 1023, 0, 1023);
  yValue = map(yValue, 0, 1023, 0, 1023);

  // Actualizar el estado del joystick
  Joystick.setXAxis(xValue);
  Joystick.setYAxis(yValue);
  //Joystick.setButton(0, buttonState); Por ahora no se usa
  
  // Pequeña pausa antes de la próxima actualización
  delay(10);

}
