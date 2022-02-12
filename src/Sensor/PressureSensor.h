#ifndef GAUGES_PRESSURESENSOR_H
#define GAUGES_PRESSURESENSOR_H

#include "../Unit/Pressure.h"

class PressureSensor {
public:
    PressureSensor(int pin, float readingAtVacuum, float readingAtAtmosphere);

    virtual Pressure read();

protected:
    const int pin;
    const float readingAtVacuum;
    const float readingAtAtmosphere;
};

class TN079800_3280 : public PressureSensor {
public:
    TN079800_3280(int readingPin) : PressureSensor(readingPin, 0.f, 2.9) {}
};


#endif //GAUGES_PRESSURESENSOR_H
