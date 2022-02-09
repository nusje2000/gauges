#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "Sensor/ManifoldAbsolutePressure.h"
#include "Gauge/BoostGauge.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C boost_screen(U8G2_R0, U8X8_PIN_NONE);

void setup(void) {
    Serial.begin(9600);
    boost_screen.begin();
}

void loop(void) {
    static ManifoldAbsolutePressure sensor = ManifoldAbsolutePressure::TN079800_3280(A3);
    static BoostGauge boostGauge = &boost_screen;
    static bool selectionButtonIsPressed = false;
    static bool inputHasBeenProcessed = false;
    static unsigned long pressStart = 0;
    static BoostDisplayMode boostDisplayMode = ADVANCED;
    static BoostDisplayUnit boostDisplayUnit = BAR;

    if (!selectionButtonIsPressed && digitalRead(PIN3)) {
        inputHasBeenProcessed = false;
        selectionButtonIsPressed = true;
        pressStart = millis();
    }

    if (selectionButtonIsPressed && !digitalRead(PIN3)) {
        selectionButtonIsPressed = false;

        if (!inputHasBeenProcessed) {
            boostDisplayUnit = boostDisplayUnit == BAR ? PSI : BAR;
            boostGauge.setDisplayUnit(boostDisplayUnit);
        }
    }

    if (selectionButtonIsPressed && (millis() - pressStart) > 1000 && !inputHasBeenProcessed) {
        inputHasBeenProcessed = true;
        boostDisplayMode = boostDisplayMode == ADVANCED ? SIMPLE : ADVANCED;
        boostGauge.setDisplayMode(boostDisplayMode);
    }

    boostGauge.update(sensor.read());

    delay(100);
}