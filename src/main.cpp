#include <Arduino.h>
#include "myIO.h"
#include "myFan.h"


void setup() {
  setupMyFan();
  Serial.begin(115200);
}

void loop() {
  //rhythmAir();
  randomAir();
}