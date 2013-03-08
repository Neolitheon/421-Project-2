#ifndef BOOSTDATAPOINT_H
#define BOOSTDATAPOINT_H

#include "common.h"

class BoostDataPoint
{
public:

<<<<<<< HEAD
    DataPoint* data;
    float weight;
    int attr_of_interest;
=======
    float weight;
    int attr_of_interest;
    DataPoint* data;
>>>>>>> 80f233be28800210c4751be4cedb19bae07c553a

    BoostDataPoint(DataPoint* d, float w):data(d),weight(w){}
    BoostDataPoint(){}

    void set_attr_of_iterest(int i){attr_of_interest = i;}
};

#endif // BOOSTDATAPOINT_H
