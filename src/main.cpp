#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "Sensor/ManifoldAbsolutePressure.h"
#include "Gauge/BoostGauge.h"

BoostConfiguration boostConfiguration;
U8G2_SH1106_128X64_NONAME_F_HW_I2C boost_screen(U8G2_R0, U8X8_PIN_NONE);
BoostGauge boostGauge(&boost_screen, &boostConfiguration);
ManifoldAbsolutePressure mapSensor = ManifoldAbsolutePressure::TN079800_3280(A3);

void setup(void) {
    Serial.begin(9600);
    boost_screen.begin();
}

void loop(void) {
    static bool selectionButtonIsPressed = false;
    static bool inputHasBeenProcessed = false;
    static unsigned long pressStart = 0;

    if (!selectionButtonIsPressed && digitalRead(PIN3)) {
        inputHasBeenProcessed = false;
        selectionButtonIsPressed = true;
        pressStart = millis();
    }

    if (selectionButtonIsPressed && !digitalRead(PIN3)) {
        selectionButtonIsPressed = false;

        if (!inputHasBeenProcessed) {
            boostConfiguration.unit = boostConfiguration.unit == BAR ? PSI : BAR;
        }
    }

    if (selectionButtonIsPressed && (millis() - pressStart) > 1000 && !inputHasBeenProcessed) {
        inputHasBeenProcessed = true;
        boostConfiguration.displayMode = boostConfiguration.displayMode == ADVANCED ? SIMPLE : ADVANCED;
    }

    boostGauge.update(mapSensor.read());
}