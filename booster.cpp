#include "booster.h"
#include <cmath>
#include <iostream>

using namespace std;

QVector<SolvedDataPoint> Booster::boost(QVector<DataPoint> data, int training_index, int iterations)
{
    Booster instance(&data,training_index, iterations);
    instance.train();
    QVector<SolvedDataPoint> result = instance.classify();
    instance.printClassifiers();
    instance.free_data();
    return result;
}

void Booster::free_data()
{
    //delete(data);
    //delete(base_data);
    //delete(stumps);
}

Booster::Booster(QVector<DataPoint> *data, int training_index, int iterations):t_i(training_index), n_i(iterations)
{

    //copy data pointers
    for(int i = 0; i<(*data).size(); i++)
    {
        base_data.push_back(*(new BoostDataPoint(&((*data)[i]),(1.0f/((float)training_index)))));
    }
    initialize();
}

void Booster::printClassifiers()
{
    cout<<"classifiers:"<<endl;
    for(int i = 0; i < classifier_set.size(); i++)
    {
        cout<<"attribute "<<classifier_set[i].index<<" ";
        if(classifier_set[i].direction)
            cout<<"> "<<classifier_set[i].threshold;
        else
            cout<<"< "<<classifier_set[i].threshold;
        cout<<"  ";
    }
    cout<<endl;
}

void Booster::initialize()
{
    //set up classifier structure
    cout<<"num attributes = "<<endl;
    for(int i = 0; i<base_data[0].data->attributes.size(); i++)
    {
        QVector<BoostDataPoint*> vec;
        for(int j = 0; j < t_i; j++)
        {
            vec.push_back(&base_data[j]);
        }
        this->data.push_back(vec);
    }

    sort_data();

    for(int i = 0; i<data.size(); i++)
    {
        QVector< Stump > vec;
        vec.push_back(*(new Stump(i,data[i][0]->data->attributes[i]-0.00005)));
        for(int j = 1;j<data[i].size();j++)
        {
            float x = data[i][j]->data->attributes[i]-data[i][j-1]->data->attributes[i];
            if(abs(x)>0.0001)
            {
                vec.push_back(*(new Stump(i,x/2.0)));
            }
        }
        vec.push_back(*(new Stump(i,data[i][data[i].size()-1]->data->attributes[i]+0.00005)));
        stumps.push_back(vec);
    }
}

void Booster::train()
{
    float err = 1.0;
    for(int i = 0; i < n_i; i++)
    {
        float tmp_err = 1.0;
        int best_attr = 0;
        int best_stump = 0;
        for(int j = 0;j<stumps.size();j++)
        {
            best_stump = 0;
            for(int k = 0; k<stumps[j].size(); k++)
            {
                //cout<<"attributes "<<data[0][0]->data->size()<<endl;
                float e = stumps[j][k].test(data[i]);
                if(e<tmp_err)
                {
                    best_stump = k;
                    tmp_err = e;
                }
            }
            if(tmp_err<err)
            {
                best_attr = j;
                err = tmp_err;
            }
        }
        //TODO: adjust weights.
        float alpha = log((1-err)/err)/2;
        float z = 0.0;
        for(int j = 0;j<base_data.size();j++)
        {
            base_data[j].weight *= exp(-alpha*stumps[best_attr][best_stump].classify(base_data[j]));
            z += base_data[j].weight;
        }

        for(int j = 0;j<base_data.size();j++)
        {
            base_data[j].weight /= z;
        }

        classifier_set.push_back(stumps[best_attr][best_stump]);
    }
}

QVector<SolvedDataPoint> Booster::classify()
{
    QVector<SolvedDataPoint> vec;
    for(int i = 0; i<base_data.size(); i++)
    {
        SolvedDataPoint x = *(new SolvedDataPoint(*(base_data[i].data)));
        x.trainingExample = i<t_i;

        bool verdict = true;
        for(int j = 0;j<classifier_set.size();j++)
        {
            verdict = classifier_set[j].classify(base_data[i]);
            if(!verdict)
               break;
        }
        x.calculatedClassification = verdict;
        vec.push_back(x);
    }
    return vec;
}

void Booster::sort_data()
{
    for(int i = 0; i<data.size();i++)
    {
        data[i] = sort_data_vector(data[i],i);
    }
}

QVector<BoostDataPoint*> Booster::sort_data_vector(QVector<BoostDataPoint*> subject, int n)
{
    if(subject.size()>1)
    {
        //seperate vectors
        int i = 0;
        int s = subject.size()/2;
        QVector<BoostDataPoint*> left, right;
        for(;i<s;i++)
            left.push_back(subject[i]);
        for(;i<subject.size();i++)
            right.push_back(subject[i]);

        //sort subvectors
        left = sort_data_vector(left, n);
        right = sort_data_vector(right, n);

        //return in order
        if(left[0]->data->attributes[n]<right[0]->data->attributes[n])
            return left + right;
        else
            return right +left;
    }
    else
    {
        return subject;
    }
}
