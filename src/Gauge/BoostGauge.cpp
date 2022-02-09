#include "BoostGauge.h"

BoostGauge::BoostGauge(U8G2 *u8g2) : u8g2(u8g2) {
}

void BoostGauge::update(const Pressure pressure) {
    updateReading(pressure);

    u8g2->clearBuffer();

    if (displayMode == ADVANCED) {
        u8g2->setFont(u8g2_font_logisoso26_tf);
        u8g2->drawStr(0, 36, getReadingText(latestReading));

        u8g2->setFont(u8g2_font_logisoso16_tf);
        u8g2->drawStr(64, 20, "M");
        u8g2->drawStr(80, 20, getReadingText(highestReading));
        u8g2->drawStr(64, 40, getUnitText(displayUnit));

        Pressure barStartFromPressure = Pressure::fromBars(1);
        Pressure barMaximumPressure = Pressure::fromBars(1.8);

        Pressure progressBarPressure = pressure - barStartFromPressure;

        float progress = progressBarPressure.inBars() / (barMaximumPressure - barStartFromPressure).inBars();

        if (progress < 0) progress = 0;
        if (progress > 1) progress = 1;

        const int boxWidth = 118 * progress;

        u8g2->drawFrame(0, 48, 118, 15);
        u8g2->drawBox(0, 48, boxWidth, 15);
    }

    if (displayMode == SIMPLE) {
        u8g2->setFont(u8g2_font_logisoso50_tf);
        u8g2->drawStr(0, 57, getReadingText(latestReading));
    }

    u8g2->sendBuffer();
}

void BoostGauge::updateReading(const Pressure reading) {
    latestReading = reading;

    unsigned long highestReadingRuntime = millis() - highestReadingTimestamp;
    if (reading.inBars() > 1.1 && (highestReadingRuntime < 0 || highestReadingRuntime > 30000)) {
        highestReading = Pressure::fromBars(0.f);
    }

    if (latestReading > highestReading) {
        highestReading = latestReading;
        highestReadingTimestamp = millis();
    }
}

void BoostGauge::setDisplayMode(BoostDisplayMode mode) {
    displayMode = mode;
}

void BoostGauge::setDisplayUnit(BoostDisplayUnit unit) {
    displayUnit = unit;
}

const char *BoostGauge::getUnitText(BoostDisplayUnit unit) {
    if (unit == BAR) {
        return "BAR";
    }

    if (unit == PSI) {
        return "PSI";
    }

    return "???";
}

const char *BoostGauge::getReadingText(Pressure pressure) {
    static char formatted_pressure[6];

    if (displayUnit == BAR) {
        dtostrf(pressure.inBars(), 3, 2, formatted_pressure);
    } else if (displayUnit == PSI) {
        dtostrf(pressure.inPSI(), 3, 1, formatted_pressure);
    } else {
        sprintf(formatted_pressure, "?.??");
    }

    return formatted_pressure;
}
