#ifndef GAUGES_BOOSTGAUGE_H
#define GAUGES_BOOSTGAUGE_H

#include "../Unit/Pressure.h"
#include "U8g2lib.h"

enum BoostDisplayMode {
    SIMPLE,
    ADVANCED
};

enum BoostDisplayUnit {
    PSI,
    BAR
};

class BoostGauge {
public:
    BoostGauge(U8G2 *u8g2);

    void update(Pressure pressure);

    void setDisplayUnit(BoostDisplayUnit mode);

    void setDisplayMode(BoostDisplayMode unit);

private:
    Pressure highestReading = Pressure::fromBars(0);
    Pressure latestReading = Pressure::fromBars(0);
    unsigned long highestReadingTimestamp = 0;
    BoostDisplayMode displayMode = ADVANCED;
    BoostDisplayUnit displayUnit = BAR;
    U8G2 *u8g2;

    void updateReading(Pressure reading);

    static const char *getUnitText(BoostDisplayUnit unit);

    const char *getReadingText(Pressure pressure);
};


#endif //GAUGES_BOOSTGAUGE_H
