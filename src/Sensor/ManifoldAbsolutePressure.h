#ifndef GAUGES_MANIFOLDABSOLUTEPRESSURE_H
#define GAUGES_MANIFOLDABSOLUTEPRESSURE_H

#include "../Unit/Pressure.h"

class ManifoldAbsolutePressure {
public:
    static ManifoldAbsolutePressure TN079800_3280(int pin);

    Pressure read();

private:
    ManifoldAbsolutePressure(int pin, float readingAtVacuum, float readingAtAtmosphere);

    const int pin;
    const float readingAtVacuum;
    const float readingAtAtmosphere;
};


#endif //GAUGES_MANIFOLDABSOLUTEPRESSURE_H
