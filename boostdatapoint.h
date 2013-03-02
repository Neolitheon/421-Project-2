#ifndef BOOSTDATAPOINT_H
#define BOOSTDATAPOINT_H

#include "common.h"

class BoostDataPoint
{
public:

    float weight;
    DataPoint* data;

    BoostDataPoint(DataPoint* d, float w):data(d),weight(w){}
    BoostDataPoint(){}
};

#endif // BOOSTDATAPOINT_H
