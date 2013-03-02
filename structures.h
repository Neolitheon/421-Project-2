#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QVector>

class DataPoint
{
public:
    bool classification;
    QVector<float> attributes;

    DataPoint(float attr[], int n, bool c)
    {
        classification = c;
        for(int i =0;i<n;i++)
        {
            attributes.push_back(attr[i]);
        }
    }
    DataPoint(){}
};

class SolvedDataPoint
{

public:
    QVector<float> attributes;
    bool classification;
    bool calculatedClassification;
    bool trainingExample;

    SolvedDataPoint(DataPoint d)
    {
        for(int i = 0; i<d.attributes.size(); i++)
        {
            attributes.push_back(d.attributes[i]);
        }
        classification = d.classification;
        calculatedClassification = false;
        trainingExample = false;
    }
    SolvedDataPoint(){}

};

#endif // STRUCTURES_H
