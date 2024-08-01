//Librerias

#include <ClickEncoder.h>
#include <TimerOne.h>
#include <Joystick.h>
#include <HID.h>


// Pines del encoder Collectivo
#define ENC_A 10 //Clk Verde
#define ENC_B 11 //Dt Amarrillo
//#define ENC_BTN 4

// Pines del encoder Pedales
#define ENCP_A 3
#define ENCP_B 2

// Pines del joystick
#define JOY_X A0 //VrX Verde
#define JOY_Y A1 //VrY Amarrillo
//#define JOY_BTN 5

int16_t RyValue = 0;
int16_t XValue = 512;
int16_t YValue = 512;
int16_t RxValue = 512; //Para que los pedales inicien en el medio
//int16_t Accelerator = 0;
//int16_t lastEncoderValue = 0;
//int16_t maxAceValue = 1024;

//Inicializo el encoder Collectivo con la Libreria ClickEncoder
ClickEncoder *encoder;

//Inicializo el encoder Pedales con la Libreria ClickEncoder
ClickEncoder *encoderP;

//Inicializo el objeto de la libreria Joystick 2.0 Con sus respectivos atributos
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
    0, 0, //Botones, HatSwitch
    true,true,true, //X, Y, Z
    true, true,true, //Rx, Ry, Rz
    false, //rudder
    false, //throttle
    false, //Accelerator
    false, //Brake
    false); //Steering
    
//Interrupcion del timer para el encoder
void timerIsr() { 
  encoder->service();
  encoderP->service();
  }

void setup() {
  Serial.begin(9600);

  //Aumento el Rango de entrada de los Axis para utilizar al maximo los valores leidos por el ADC (Analogic-Digital Conversor o Convertidos Analogo-Digital) De arduino
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);
  Joystick.setRxAxisRange(0, 1023);
  
  //Inicio el objeto Joystick con su metodo begin
  Joystick.begin();
  
  //Config Encoder
  encoder = new ClickEncoder(ENC_A, ENC_B);
  encoderP = new ClickEncoder(ENCP_A, ENCP_B);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
}

void loop(){ 
  //Leer el valor del encoder
  int16_t encoderValue = encoder->getValue();
  int16_t encoderPValue = encoderP->getValue();

  //Revisar que se mueva el encoder hacia (Dir)
  
  if (encoderValue != 0) {

    //Incrementar el valor del Ry en multiplos de 66
    
    RyValue += encoderValue * 66;

    //Limitar el Accelerador entre 0 y  1024
    /*                                                Depreciado ya que constrain hace lo mismo
     * 
    if (RyValue > RyValue) {
      RyValue = 1024;
    } else if (RyValue < 0){
      RyValue = 0;
    }
    
    */
    //constrain hace lo mismo que el condicional de arriba,
    //Contiene el valor dado (RyValue) en un rango de terminado por dos argumentos enteros (0, 1024)
    // Syntax 
    //Variable_Para_Almacenar_Resultado = constrain(Valor_a_Contener, Limite_1/Minimo, Limite_2/Maximo);
    RyValue = constrain(RyValue,0,1023);

    //Envio el valor del encoder contenido al Joystick
    Joystick.setRyAxis(RyValue);
    
    //Serial.print("Joy X: ");
    //Serial.print(analogRead(JOY_Y);
    //Serial.print(" Joy Y: ");
    //Serial.print(analogRead(JOY_X);
    Serial.print(" Ry : ");
    Serial.println(RyValue);
  }

  if (encoderPValue != 0) {
    //Incrementar el valor del accelerado en multiplos de 66
    RxValue += encoderPValue * 34;

    //Contiene el valor dado (RyValue) en un rango de terminado por dos argumentos enteros (0, 1023)
    RxValue = constrain(RxValue, 0, 1023);

    //Envio el valor del encoder contenido al Joystick
    Joystick.setRxAxis(RxValue);

    //Muestro los valores en consola para debug
    Serial.print(" Rx : ");
    Serial.println(RxValue);
  }
  
  //JoyStick Plano X Estan invertidos en la prueba con la protoBoard
  XValue = analogRead(JOY_Y);
  //                                 XValue = map(XValue, 0, 1024, 0, 255); Solo sirve si el limete maximo de el rango del joystick Virtual esperado es 255

  //Le paso las lecturas directas ya que mi Limete actual es 1023 - Que es el maximo valor que me lee el ADC (Analogic-Digital Conversor o Convertidos Analogo-Digital) De arduino
  Joystick.setXAxis(XValue);

  //JoyStick Plano Y Estan invertidos en la prueba protoBoard
  YValue = analogRead(JOY_X);
  
  //                                 YValue = map(YValue, 0, 1024, 0, 255);

  //Le paso las lecturas directas ya que mi Limete actual es 1023 - Que es el maximo valor que me lee el ADC (Analogic-Digital Conversor o Convertidos Analogo-Digital) De arduino
  Joystick.setYAxis(YValue);
  
  delay(10);
  
}   
/*
      * !!!!!!!!!!!!!!!!!!!!!!!!!    Notas Importantes
      
      
    Investigar como invertir los controles del Joystick
    Investigar como invertir los controles del Collectico A.K.A Encoder
    Hacer el Rudder con Encoder y si falla con Rx

*/
