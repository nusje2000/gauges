#include <Arduino.h>
#include "PressureSensor.h"

PressureSensor::PressureSensor(int pin, float readingAtVacuum, float readingAtAtmosphere) :
        pin(pin),
        readingAtVacuum(readingAtVacuum),
        readingAtAtmosphere(readingAtAtmosphere) {
}

Pressure PressureSensor::read() {
    int reading = analogRead(pin);
    float volt = reading * 5.0 / 1023.0;

    return Pressure::fromBars((volt - readingAtVacuum) / (readingAtAtmosphere - readingAtVacuum));
}

