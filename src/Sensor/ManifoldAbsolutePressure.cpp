#include <Arduino.h>
#include "ManifoldAbsolutePressure.h"

ManifoldAbsolutePressure ManifoldAbsolutePressure::TN079800_3280(int pin) {
    // TODO: 0 at vacuum might not be correct, so the reading may not be exact

    return {pin, 0.f, 2.9};
}

ManifoldAbsolutePressure::ManifoldAbsolutePressure(int pin, float readingAtVacuum, float readingAtAtmosphere) :
        pin(pin),
        readingAtVacuum(readingAtVacuum),
        readingAtAtmosphere(readingAtAtmosphere) {
}

Pressure ManifoldAbsolutePressure::read() {
    int reading = analogRead(pin);
    float volt = reading * 5.0 / 1023.0;

    return Pressure::fromBars((volt - readingAtVacuum) / (readingAtAtmosphere - readingAtVacuum));
}

