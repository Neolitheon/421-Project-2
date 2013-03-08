#ifndef STUMP_H
#define STUMP_H

#include "common.h"
#include "boostdatapoint.h"
class Stump
{
    static const int LT = 0;
    static const int GT = 1;
public:

    bool c_gt;
    bool c_lt;
    int direction;
<<<<<<< HEAD
    int index;
    float threshold;

=======
    float threshold;
    int index;
>>>>>>> 80f233be28800210c4751be4cedb19bae07c553a

    Stump(int index, float threshold);
    Stump(){}

    float test(QVector<BoostDataPoint *> data);
    bool classify(BoostDataPoint subject);
};

#endif // STUMP_H
