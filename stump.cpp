#include "stump.h"

Stump::Stump(int index,float threshold):index(index),threshold(threshold)
{
}

float Stump::test(QVector<BoostDataPoint*> data)
{
    //TODO
    //calculate error
    //float c0,c1;
    float w_p_gt,w_p_lt/*, w_n_gt, w_n_lt*/ = 0.0;
    for(int i = 0;i<data.size();i++)
    {

        if(data[i]->data->attributes[index]<threshold)
            w_p_lt+=data[i]->weight;
        else
            w_p_gt+=data[i]->weight;

        /*if(data->data->attributes[index]>=threshold)
            w_p_gt+=data->data->weight;
        else
            w_n_gt+=data->data->weight;*/
    }

    if(w_p_gt>w_p_lt)
    {
        direction = GT;
        return w_p_lt;
    }
    else
    {
        direction = LT;
        return w_p_gt;
    }
}

bool Stump::classify(BoostDataPoint subject)
{
    switch(direction)
    {
        case GT:
            return subject.data->attributes[index]>=threshold;
        case LT:
            return subject.data->attributes[index]<threshold;
    }
}
