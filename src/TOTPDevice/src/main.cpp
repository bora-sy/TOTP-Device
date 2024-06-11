#include <Arduino.h>
#include "Interaction/LCD.h"
#include "Ds1302.h"


#define BTN1 2
#define BTN2 14
#define BTN3 3

#define PIN_ENA 15
#define PIN_CLK 12
#define PIN_DAT 13

Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  pinMode(BTN1, INPUT_PULLUP);



  LCD::Initialize();
  LCD::PrintCenterRow("Hello");


  rtc.init();
  Serial.printf("Halted: %d\n", rtc.isHalted());
}

void loop() {
  
}
