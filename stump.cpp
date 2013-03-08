#include "stump.h"
#include <iostream>

using namespace std;

Stump::Stump(int index,float threshold):index(index),threshold(threshold)
{
    direction = 0;
    this->index = index;
}

float Stump::test(QVector<BoostDataPoint*> data)
{
    //Problem error ia always zero
    //calculate error
    //float c_gt,c_lt;
    float w_gt_p = 0.0;
    float w_gt_n = 0.0;
    float w_lt_p = 0.0;
    float w_lt_n = 0.0;

    for(int i = 0;i<data.size();i++)
    {
        if(data[i]->data->attributes[index]>threshold)
        {
            if(data[i]->data->classification)
                //classified correctly under GT
                w_gt_p += data[i]->weight;
            else
                //classified incorrectly under GT
                w_gt_n += data[i]->weight;
        }
        else
        {
            if(data[i]->data->classification)
                w_gt_n += data[i]->weight;
            else
                w_gt_p += data[i]->weight;
        }

        if(data[i]->data->attributes[index]<threshold)
        {
            if(data[i]->data->classification)
                w_lt_p += data[i]->weight;
            else
                w_lt_n += data[i]->weight;
        }
        else
        {
            if(data[i]->data->classification)
                w_lt_n += data[i]->weight;
            else
                w_lt_p += data[i]->weight;
        }
    }

    float err = 0.0;
    if(w_gt_p>=w_gt_n)
    {
        c_gt = true;
        err += w_gt_n;
    }
    else
    {
        c_gt = false;
        err += w_gt_p;
    }

    if(w_lt_p>=w_lt_n)
    {
        c_lt = true;
        err += w_lt_n;
    }
    else
    {
        c_lt = false;
        err += w_lt_p;
    }

    return err;
    /*if(w_p_gt>w_p_lt)
    {
        direction = GT;
        return w_p_lt;
    }
    else
    {
        direction = LT;
        return w_p_gt;
    }*/
}

bool Stump::classify(BoostDataPoint subject)
{
    /*switch(direction)
    {
        case GT:
            return subject.data->attributes[index]>=threshold;
        case LT:
            return subject.data->attributes[index]<threshold;
    }*/
    //cout<<". Using index "<<index<<endl;
    //cout<<"     subject in method is "<<subject.data->attributes[index]<<endl;
    if(subject.data->attributes[index]>=threshold)
        return c_gt;
    else
        return c_lt;


}
