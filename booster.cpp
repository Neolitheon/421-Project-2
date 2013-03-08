#include "booster.h"
#include <cmath>
#include <iostream>
#include <QtAlgorithms>

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
        cout<<"for attribute "<<classifier_set[i].index<<": ";
        cout<<classifier_set[i].c_gt<<" if greater than "<<classifier_set[i].threshold<<", "<<classifier_set[i].c_lt<<" otherwise"<<endl;
    }
    cout<<endl;
}

void Booster::initialize()
{
    //set up classifier structure
    //cout<<"num attributes = "<<endl;
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
        Stump * stump = new Stump(i,data[i][0]->data->attributes[i]-0.00005);
        vec.push_back(*(stump));
        for(int j = 1;j<data[i].size();j++)
        {
            float x = data[i][j]->data->attributes[i]-data[i][j-1]->data->attributes[i];
            if(abs(x)>0.0001)
            {
                stump = new Stump(i,(x/2.0)+data[i][j-1]->data->attributes[i]);
                vec.push_back(*(stump));
            }
        }
        stump = new Stump(i,data[i][data[i].size()-1]->data->attributes[i]+0.00005);
        vec.push_back(*(stump));
        stumps.push_back(vec);
    }
}

void Booster::train()
{
    for(int i = 0; i < n_i; i++)
    {  
        float err = 0.5;
        int best_attr = 0;
        int best_stump = 0;
        for(int j = 0;j<stumps.size();j++)
        {
            float tmp_err = 0.5;
            float best_stump_for_attribute = 0;
            for(int k = 0; k<stumps[j].size(); k++)
            {
<<<<<<< HEAD
                //cout<<"attributes "<<data[0][0]->data->attributes->size()<<endl;
                float e = stumps[j][k].test(data[j]);
=======
                //cout<<"attributes "<<data[0][0]->data->size()<<endl;
                float e = stumps[j][k].test(data[i]);
>>>>>>> 80f233be28800210c4751be4cedb19bae07c553a
                if(abs(0.5-e)>abs(0.5-tmp_err))
                {
                    best_stump_for_attribute = k;
                    tmp_err = e;
                    cout<<"new max err for attribute "<<j<<" is "<<tmp_err<<" on stump "<<best_stump<<" with threshold "<<stumps[best_attr][best_stump].threshold<<endl;
                }
            }
            if(abs(0.5-tmp_err)>abs(0.5-err))
            {
                best_attr = j;
                best_stump = best_stump_for_attribute;
                err = tmp_err;
                cout<<"new max err for iterration "<<best_attr<<" is "<<tmp_err<<" on stump "<<best_stump<<" with threshold "<<stumps[best_attr][best_stump].threshold<<endl;
            }
        }

        cout<<"new classifier is at stump ["<<best_attr<<"]["<<best_stump<<"] with threshold "<<stumps[best_attr][best_stump].threshold<<endl;
        //TODO: adjust weights.
        cout<<"error on iterration "<<i<<" = "<<err<<endl;

        classifier_set.push_back(stumps[best_attr][best_stump]);
        if(abs(0.5-err)<0.02)
        {
            float alpha = log((1-err)/err)/2;
            float z = 0.0;
            for(int j = 0;j<base_data.size();j++)
            {
                //cout<<"base_data[j] = "<<base_data[j].data->attributes[best_attr]<<endl;
                base_data[j].weight *= exp(-alpha*stumps[best_attr][best_stump].classify(base_data[j]));
                z += base_data[j].weight;
            }
            cout<<"Z on iterration "<<i<<" = "<<z<<endl;
            for(int j = 0;j<base_data.size();j++)
            {
                base_data[j].weight /= z;
            }
            //cout<<"stump on this iteration is"<<stumps[2][0].threshold<<endl;

            cout<<"after itteration 1:"<<endl;
            printClassifiers();
            /*if(err<0.02)
            {
                break;
            }*/
        }
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

bool attributeLessThan(const BoostDataPoint *p1, const BoostDataPoint *p2)
{
    return p1->data->attributes[p1->attr_of_interest] < p2->data->attributes[p2->attr_of_interest];
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
        //cout<<"left = "<<left[0]->data->attributes[n]<<" right = "<<right[0]->data->attributes[n]<<endl;

        QVector<BoostDataPoint*> merged_result;
        int l = 0;
        int r = 0;
        for(;l<left.size() && r<right.size();)
        {
            if(left[l]->data->attributes[n]<right[r]->data->attributes[n])
            {
                //cout<<"left smaller"<<endl;
                merged_result.push_back(left[l++]);
                //return left + right;
            }
            else
            {
                //cout<<"right smaller"<<endl;
                merged_result.push_back(right[r++]);
                //return right + left;
            }
        }

        for(;l<left.size();l++)
        {
            merged_result.push_back(left[l]);
        }
        for(;r<right.size();r++)
        {
            merged_result.push_back(right[r]);
        }

        return merged_result;
    }
    else
    {
        return subject;
    }
}
