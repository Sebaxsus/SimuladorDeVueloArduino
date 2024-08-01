/*
  Tell DCS-BIOS to use a serial connection and use interrupt-driven
  communication. The main program will be interrupted to prioritize
  processing incoming data.
  
  This should work on any Arduino that has an ATMega328 controller
  (Uno, Pro Mini, many others).
 */
#define DCSBIOS_IRQ_SERIAL 

#include "DcsBios.h"
#include "C:\Users\sebax\Saved Games\DCS\Scripts\DCS-BIOS\doc\Addresses.h"

#define outputA 3 // Cable Verde
#define outputB 5 // Cable Amarril
//const int pinPushBtn 11;

/* paste code snippets from the reference documentation here */
//DcsBios::RotaryEncoder throttle("THROTTLE", "-1600", "+1600", outputA, outputB);
//DcsBios::LED masterCaution(0x1012, 0x0800, 13);
/Sirven Los Dos Indicadores
DcsBios::LED lowRpmInd(UH_1H_LOW_RPM_IND_AM, 2);
DcsBios::LED masterCautionInd(UH_1H_MASTER_CAUTION_IND_AM, 7);
//Sirve Goat
DcsBios::Switch2Pos cmFlareBtn("CM_FLARE_BTN", 11);
// Primer Pin Reset - Segundo Pin Test
DcsBios::Switch3Pos clpResetTestSw("CLP_RESET_TEST_SW", 8, 9);
void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}
