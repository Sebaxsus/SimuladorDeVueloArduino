/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

// constants won't change. They're used here to set pin numbers:
const int switch1T1 = 8;     // the number of the pushbutton pin
const int switch1T2 = 9;
const int pushButton = 11;
const int ledPin =  7;      // the number of the LED pin
const int ledPin2 = 2;
// variables will change:
//int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(switch1T1, INPUT_PULLUP);
  pinMode(switch1T2, INPUT_PULLUP);
  pinMode(pushButton,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  Serial.print("Switch Throw 1: ");
  Serial.println(digitalRead(switch1T1));
  Serial.print("Switch Throw 2: ");
  Serial.println(digitalRead(switch1T2));
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(switch1T1) == 1){
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  if (digitalRead(switch1T2) == 1){
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
  }
  Serial.print("PushButton: ");
  Serial.println(digitalRead(pushButton));
  if (digitalRead(pushButton) == 1) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(1000);
}
