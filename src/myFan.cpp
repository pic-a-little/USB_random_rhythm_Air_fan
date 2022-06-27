#include <Arduino.h>
#include "myFan.h"
#include <stdlib.h>
#include "myIO.h"

#define minAirFlow (80)

void setupMyFan(){
    pinMode(fanPin, OUTPUT);
    srand((unsigned int)(analogRead(seed1) * analogRead(seed2) * analogRead(seed3)));
}

void randomAir(){
    unsigned long startTime = 0;
    unsigned long rizeOrFallTime = 0;

    int currentAirFlow = 0;
    int maxAirFlow = 0;
    unsigned long rizeDulationMillis = 0;
    unsigned long fullAirFlowMillis = 0;
    unsigned long fallDulationMillis = 0;
    unsigned long intervalMillis = 0;

    maxAirFlow = 100 + rand() % (155);
    rizeDulationMillis = ((1 + rand() % (6)) * 1000);
    fullAirFlowMillis = 1000 + rand() % (3000);
    fallDulationMillis = ((1 + rand() % (6)) * 1000);
    intervalMillis = 2000 + rand() % (17000);

    startTime = millis();
    rizeOrFallTime = startTime + rizeDulationMillis;
    Serial.printf("rizeDulationMillis = %lu\n", rizeDulationMillis);
    while (millis() < rizeOrFallTime){
        currentAirFlow = minAirFlow + (maxAirFlow - minAirFlow+1) * ((millis() - startTime)*1000 / rizeDulationMillis)/1000;
        Serial.printf("currentAirFlow = %d maxAirFlow = %d rizeDulationMillis = %lu rate = %lu\n", currentAirFlow, maxAirFlow, rizeDulationMillis, ((millis() - startTime)*1000 / rizeDulationMillis));
        analogWrite(fanPin, currentAirFlow);
    }

    Serial.printf("fullAirFlowMillis = %lu\n", fullAirFlowMillis);
    delay(fullAirFlowMillis);

    startTime = millis();
    rizeOrFallTime = startTime + fallDulationMillis;
    while (millis() < rizeOrFallTime)
    {
        currentAirFlow = maxAirFlow - (maxAirFlow - minAirFlow+1) * ((millis() - startTime)*1000 / fallDulationMillis)/1000;
        Serial.printf("currentAirFlow = %d maxAirFlow = %d  fallDulationMillis = %lu rate = %lu\n", currentAirFlow, maxAirFlow , fallDulationMillis, 1000 - ((millis() - startTime) * 1000 / fallDulationMillis));
        analogWrite(fanPin, currentAirFlow);
    }
    analogWrite(fanPin, 0);
    Serial.printf("intervalMillis = %lu\n", intervalMillis);
    delay(intervalMillis);
}

void rhythmAir(){
    int i = 0;
    for (i = minAirFlow; i < 255; i = i + 1)
    {
      analogWrite(fanPin, i);
      delay(10);
    }
    delay(3000);
    for (i = 255; i > minAirFlow; i = i - 1)
    {
      analogWrite(fanPin, i);
      delay(10);
    }
    analogWrite(fanPin, 0);
    delay(3000);
}