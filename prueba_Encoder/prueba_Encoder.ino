#include <HID.h>;
#include <Joystick.h>

// Prueba de encoder hecha por mi
#define outputA 3 // Cable Verde
#define outputB 5 // Cable Amarrillo

//Prueba JoyStick
const int VRxPin = A0; // Cable Verde
const int VRyPin = A1; // Cable Amarillo

int counter = 0;
int aState;
int aLastState;

//Prueba JoyStick emulando Throttle con encoder
Joystick_ joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_JOYSTICK,
                   0,    // Número de botones
                   0,    // Número de hat switches
                   false, // Incluir eje X
                   false, // Incluir eje Y
                   false, // Incluir eje Z
                   false, // Incluir eje RX
                   false, // Incluir eje RY
                   false, // Incluir eje RZ
                   true,  // Incluir Throttle
                   true,  // Incluir Accelerator
                   true,  // Incluir Brake
                   true,  // Incluir Steering
                   true); // Incluir Rudder
                   
void setup() {
  pinMode (outputA, INPUT); //Lee 1 y 0
  pinMode (outputB, INPUT); //Lee 1 Y 0

  Serial.begin(9600);

  aLastState = digitalRead(outputA);
}

void rawjoyStick() {
  int xValue = analogRead(VRxPin); //Valor Maximo: 120,Valor Centrado: (±)519  Valor Minimo: 0
  int yValue = analogRead(VRyPin); //Valor Maximo: 1020 ,Valor centrado: (±)517 Valor Minimo: 0

  Serial.print("Joystick X: ");
  Serial.print(xValue);
  Serial.print("Joystick y: ");
  Serial.println(yValue);
}

void encoder() {
  aState = digitalRead(outputA);
  /*
  Serial.print("Entrada 1 ");
  Serial.print(digitalRead(outputA));
  Serial.print(" Entrada 2 ");
  Serial.println(digitalRead(outputB));
  */
  if (aState != aLastState) {
    Serial.print("Entrada A ");
    Serial.print(digitalRead(outputA));
    Serial.print(" Entrada B ");
    Serial.println(digitalRead(outputB));
    if(aState != digitalRead(outputB)) {
      counter ++;
    } else {
      counter --;
    }
    
    Serial.print("Contador: ");
    Serial.println(counter);
  }
  aLastState = aState;
}

void rawEncoder() {
  Serial.print("Entrada A: ");
  Serial.print(digitalRead(outputA));
  Serial.print(" Entrada B: ");
  Serial.println(digitalRead(outputB));
}

void loop (){
  rawEncoder();
  
  

  delay(1000);
}
