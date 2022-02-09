#include "Pressure.h"

Pressure Pressure::fromBars(float pressure) {
    return {pressure};
}

Pressure Pressure::fromPSI(float pressure) {
    return {pressure / Pressure::barsToPSIRatio};
}

float Pressure::inBars() const {
    return pressureInBars;
}

float Pressure::inPSI() const {
    return pressureInBars * Pressure::barsToPSIRatio;
}

Pressure::Pressure(float pressureInBars) : pressureInBars(pressureInBars) {
}

bool Pressure::operator==(Pressure &pressure) const {
    return this->inBars() == pressure.inBars();
}

bool Pressure::operator>(Pressure &pressure) const {
    return this->inBars() > pressure.inBars();
}

bool Pressure::operator>=(Pressure &pressure) const {
    return this->inBars() >= pressure.inBars();
}

bool Pressure::operator<(Pressure &pressure) const {
    return this->inBars() < pressure.inBars();
}

bool Pressure::operator<=(Pressure &pressure) const {
    return this->inBars() <= pressure.inBars();
}

Pressure Pressure::operator-(Pressure &pressure) const {
    return Pressure::fromBars(this->inBars() - pressure.inBars());
}

Pressure Pressure::operator+(Pressure &pressure) const {
    return Pressure::fromBars(this->inBars() + pressure.inBars());
}
