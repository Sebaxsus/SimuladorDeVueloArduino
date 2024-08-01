const int switch1T1 = 8;     // the number of the pushbutton pin
const int switch1T2 = 9;
const int pushButton = 11;
const int ledPin =  7;      // the number of the LED pin
const int ledPin2 = 2;

void setup() {
  // put your setup code here, to run once:
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(switch1T1, INPUT);
  pinMode(switch1T2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Cuando el estado de entrada del switch sea 0 Significa que se activo
  if (digitalRead(switch1T1) == 0){
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  if (digitalRead(switch1T2) == 0){
    digitalWrite(ledPin2, HIGH);
  }else{
    digitalWrite(ledPin2, LOW);
  }
  //Cuando se presione el pushBotton el estado sera 0
  if (digitalRead(pushButton) == 0){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
}
