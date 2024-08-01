#include <TimerOne.h>

#include <ClickEncoder.h>

#include <Joystick.h>

#include <HID.h>
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
                   false,  // Incluir Accelerator
                   false,  // Incluir Brake
                   false,  // Incluir Steering
                   true); // Incluir Rudder
//Configuracion Pines Joystick
const int VRxPin = A0; // Pin analógico para el eje X
const int VRyPin = A1; // Pin analógico para el eje Y

//Configuracion Pines Encoder
#define outputA 3 // Cable Verde
#define outputB 5 // Cable Amarril

//Variable del encoder
ClickEncoder *throttleEncoder;
int16_t throttleValue = 512; //valor inicial en el medio
int16_t lastThrottleValue = -1;

//funcion de interrupcion del encoder
void timerIsr() { throttleEncoder->service(); }


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Inicio del programa");

  // Inicialización del joystick
  joystick.begin();

  //Configuracion de los pines del encoder
  throttleEncoder = new ClickEncoder(outputA, outputB);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);

  //Configuracion Btn Joystick
  //pinMode(joystickBtn, INPUT_PULLUP);
  
  // Configuración de los pines como entradas
  //pinMode(THROTTLE_PIN, INPUT);
  //pinMode(ACCELERATOR_PIN, INPUT);
  //pinMode(BRAKE_PIN, INPUT);
  //pinMode(STEERING_PIN, INPUT);
  //pinMode(RUDDER_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Lectura y procesamiento del valor del encoder
  throttleValue += throttleEncoder->getValue();
  if (throttleValue != lastThrottleValue) {
    throttleValue = constrain(throttleValue, 0, 1023);
    joystick.setThrottle(throttleValue);
    joystick.sendState();
    lastThrottleValue = throttleValue;
    Serial.print("Throttle: ");
    Serial.println(throttleValue);
  }

  // Lectura del joystick físico
  int rudderXValue = analogRead(VRxPin);
  rudderXValue = map(rudderXValue, 0, 1023, 0, 1023);
  joystick.setRudder(rudderXValue);
  Serial.print("Rudder X: ");
  Serial.println(rudderXValue);
  
  // Lectura del botón del joystick
  //int rudderBtnState = digitalRead(RUDDER_BTN_PIN);
  //joystick.setButton(0, !rudderBtnState);

  // Envío del estado del joystick emulado
  joystick.sendState();

  // Pequeño retraso para evitar lecturas rápidas
  delay(20);
}
