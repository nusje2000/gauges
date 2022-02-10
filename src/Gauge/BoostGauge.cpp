#include "BoostGauge.h"

BoostGauge::BoostGauge(U8G2 *u8g2, BoostConfiguration *configuration) : u8g2(u8g2), configuration(configuration) {
}

void BoostGauge::update(const Pressure pressure) {
    updateReading(pressure);

    u8g2->clearBuffer();

    if (configuration->displayMode == ADVANCED) {
        u8g2->setFont(u8g2_font_logisoso26_tf);
        u8g2->drawStr(0, 36, getReadingText(latestReading));

        u8g2->setFont(u8g2_font_logisoso16_tf);
        u8g2->drawStr(64, 20, "M");
        u8g2->drawStr(80, 20, getReadingText(highestReading));
        u8g2->drawStr(64, 40, getUnitText(configuration->unit));

        if (highestReading > configuration->maxBoost) {
            u8g2->drawTriangle(118, 40, 102, 40, 110, 25);
            u8g2->setDrawColor(0);
            u8g2->drawLine(110, 30, 110, 35);
            u8g2->drawPixel(110, 37);
            u8g2->setDrawColor(1);
        }

        Pressure barStartFromPressure = Pressure::fromBars(1);
        Pressure progressBarPressure = pressure - barStartFromPressure;

        float progress = progressBarPressure.inBars() / (configuration->maxBoost - barStartFromPressure).inBars();

        if (progress < 0) progress = 0;
        if (progress > 1) progress = 1;

        const int boxWidth = static_cast<int> (118 * progress);

        u8g2->drawFrame(0, 48, 118, 15);
        u8g2->drawBox(0, 48, boxWidth, 15);
    }

    if (configuration->displayMode == SIMPLE) {
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

    if (configuration->unit == BAR) {
        dtostrf(abs(pressure.inBars() - 1), 3, 2, formatted_pressure);
    } else if (configuration->unit == PSI) {
        dtostrf(abs(pressure.inPSI() - 1), 3, 1, formatted_pressure);
    } else {
        sprintf(formatted_pressure, "?.??");
    }

    return formatted_pressure;
}
