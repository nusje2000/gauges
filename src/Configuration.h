#ifndef GAUGES_CONFIGURATION_H
#define GAUGES_CONFIGURATION_H

enum BoostDisplayUnit {
    PSI,
    BAR
};

enum BoostDisplayMode {
    SIMPLE,
    ADVANCED
};

struct BoostConfiguration {
    Pressure maxBoost = Pressure::fromBars(1.7);
    BoostDisplayMode displayMode = ADVANCED;
    BoostDisplayUnit unit = BAR;
};

#endif //GAUGES_CONFIGURATION_H
