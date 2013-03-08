#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QVector>
#include <iostream>
#include <stdio.h>

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
    void printString()
    {
        for (int i=0; i<attributes.size(); i++)
        {
            printf("%f ", attributes[i]);
        }
        printf("%d\n", classification);
    }
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
    void printString()
    {
        for (int i=0; i<attributes.size(); i++)
        {
            printf("%f ", attributes[i]);
        }
        printf("class:%d calc:%d train:%d\n", classification, calculatedClassification, trainingExample);
    }

};

#endif // STRUCTURES_H
