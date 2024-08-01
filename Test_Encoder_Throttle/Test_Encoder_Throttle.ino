#include <TimerOne.h>

#include <ClickEncoder.h>

#include <Joystick.h>

#include <HID.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
                   JOYSTICK_TYPE_MULTI_AXIS, 
                   32, 0,                  // 32 botones, 0 hat switches
                   true, true, false,      // X, Y, no Z axis
                   false, false, false,    // no Rx, Ry, Rz
                   false, true,           // no rudder, throttle
                   false, false, false);   // no accelerator, brake, steering

ClickEncoder *encoder;
int16_t lastEncoderValue = 0;
int16_t throttleValue = 0;

void timerIsr() { encoder->service(); }

#define encoderDt 5
#define encoderCLK 3

void setup() {
  Serial.begin(9600);
  
  encoder = new ClickEncoder(encoderDt, encoderCLK);
  encoder->setAccelerationEnabled(true);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  
  Joystick.begin();
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t encoderValue = encoder->getValue();

  if (encoderValue != 0) {
    throttleValue += encoderValue * 20;
    if (throttleValue > 1024) {
      throttleValue = 1024;
    } else if (throttleValue < 0){
    throttleValue = 0;
    }
    Joystick.setThrottle(throttleValue);
    Serial.print("Throttle: ");
    Serial.println(throttleValue);
  }
  
  delay(100);
}
