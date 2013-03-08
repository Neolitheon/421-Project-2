#ifndef BOOSTDATAPOINT_H
#define BOOSTDATAPOINT_H

#include "common.h"

class BoostDataPoint
{
public:

    DataPoint* data;
    float weight;
    int attr_of_interest;

    BoostDataPoint(DataPoint* d, float w):data(d),weight(w){}
    BoostDataPoint(){}

    void set_attr_of_iterest(int i){attr_of_interest = i;}
};

#endif // BOOSTDATAPOINT_H
