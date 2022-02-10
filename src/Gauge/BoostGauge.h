#ifndef GAUGES_BOOSTGAUGE_H
#define GAUGES_BOOSTGAUGE_H

#include "../Unit/Pressure.h"
#include "U8g2lib.h"
#include "../Configuration.h"

class BoostGauge {
public:
    BoostGauge(U8G2 *u8g2, BoostConfiguration *configuration);

    void update(Pressure pressure);

private:
    Pressure highestReading = Pressure::fromBars(0);
    Pressure latestReading = Pressure::fromBars(0);
    unsigned long highestReadingTimestamp = 0;

    U8G2 *u8g2;
    BoostConfiguration *configuration;

    void updateReading(Pressure reading);

    static const char *getUnitText(BoostDisplayUnit unit);

    const char *getReadingText(Pressure pressure);
};


#endif //GAUGES_BOOSTGAUGE_H
