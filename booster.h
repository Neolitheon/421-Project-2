#ifndef BOOSTER_H
#define BOOSTER_H

#include "structures.h"
#include "boostdatapoint.h"
#include "stump.h"

class Booster
{
private:

    int t_i;
    int n_i;
    float err;
    QVector<BoostDataPoint> base_data;
    QVector< QVector<BoostDataPoint*> > data;
    QVector< QVector<Stump> > stumps;
    QVector<Stump> classifier_set;

    Booster(QVector<DataPoint>,int training_index, int iterations);

    void initialize();
    void sort_data();
    QVector<BoostDataPoint*> sort_data_vector(QVector<BoostDataPoint*> subject, int n);
    void train();
    QVector <SolvedDataPoint> classify();
    void free_data();

public:
    static QVector <SolvedDataPoint> boost(QVector<DataPoint>,int training_index, int iterations);
};

#endif // BOOSTER_H
