#ifndef STUMP_H
#define STUMP_H

#include "common.h"
#include "boostdatapoint.h"
class Stump
{
    static const int LT = 0;
    static const int GT = 1;
public:

    int direction;
    float threshold;
    int index;

    Stump(int index, float threshold);
    Stump(){}

    float test(QVector<BoostDataPoint *> data);
    bool classify(BoostDataPoint subject);
};

#endif // STUMP_H
