#ifndef GAUGES_PRESSURE_H
#define GAUGES_PRESSURE_H

class Pressure {
public:
    static Pressure fromBars(float pressure);

    static Pressure fromPSI(float pressure);

    float inBars() const;

    float inPSI() const;

    bool operator==(Pressure &pressure) const;

    bool operator>(Pressure &pressure) const;

    bool operator>=(Pressure &pressure) const;

    bool operator<(Pressure &pressure) const;

    bool operator<=(Pressure &pressure) const;

    Pressure operator-(Pressure &pressure) const;

    Pressure operator+(Pressure &pressure) const;

private:
    Pressure(float pressureInBars);

    constexpr static const float barsToPSIRatio = 14.5038;

    float pressureInBars;
};


#endif //GAUGES_PRESSURE_H
