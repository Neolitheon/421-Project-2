#include "display.h"
#include "booster.h"
#include "kernelperceptron.h"
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <algorithm>
#include <ctime>

//http://www.cplusplus.com/forum/general/4422/
//http://www.cplusplus.com/articles/1UqpX9L8/

vector<string>& splitstring::split(char delim, int rep) {
    if (!flds.empty()) flds.clear();  // empty vector if necessary
    string work = data();
    string buf = "";
    uint i = 0;
    while (i < work.length()) {
        if (work[i] != delim)
            buf += work[i];
        else if (rep == 1) {
            flds.push_back(buf);
            buf = "";
        } else if (buf.length() > 0) {
            flds.push_back(buf);
            buf = "";
        }
        i++;
    }
    if (!buf.empty())
        flds.push_back(buf);
    return flds;
}


Display::Display(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    projectionMatrix(),
    viewMatrix()
{
}

float Display::accuracy(QVector<SolvedDataPoint> points, int training_size)
{
    int correct = 0;
    for (int i=0; i<points.size(); i++)
    {
        //printf("%d%d", int(points[i].classification), int(points[i].calculatedClassification));
        if (points[i].classification == points[i].calculatedClassification && points[i].trainingExample == false)
        {
            correct += 1;
        }
    }
    return correct/float(points.size() - training_size);
}

void Display::initializeGL()
{
    glClearColor(0.7, 0.7, 0.7, 1);
    eye = QVector3D(-0.64, 1, -0.64);
    at = QVector3D(-0.64, 0, -0.64);
    up = QVector3D(0, 0, 1);
    number = 0;
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(NULL));
    switch_algorithim = 2;
    switch_data_set = 0;
    switch_analysis = 1;
    perceptron_degree = 2;
    maximum_iterations = 10;
    training_set_size = 0.25;
    calc_finished = 0;
    progress = 0;
}

void Display::start()
{
    QVector<DataPoint> points;
    QVector<SolvedDataPoint> solved_points;
    switch(switch_analysis)
    {
        case 0:
            accuracy_points = analyse_accuracy();
            calc_finished = 1;
            break;
        case 1:
            points = read_file();
            switch(switch_algorithim)
            {
                case 0:
                case 1:
                    random_shuffle(points.begin(), points.end());
                    break;
                case 2:
                    points = randomize(points, points.size()*training_set_size);
                    break;
            }
            solved_points = run_algorithim(points, points.size()*training_set_size, maximum_iterations);
            for (int i=0; i<solved_points.size(); i++)
            {
                solved_points[i].printString();
            }
            printf("Accuracy: %f",accuracy(solved_points,points.size()*training_set_size));
            fflush(stdout);
            break;
    }


}

//calls read file, calls randomize, calls run_algorithm buttload of times
QVector< QVector<float> > Display::analyse_accuracy()
{
    //read in file, take data points
    QVector<DataPoint> points = read_file();

    QVector< QVector<float> > accuracy_points;
    for (int max_it=1; max_it<21; max_it++)
    {
        QVector<float> temp;
        for (int training_size=1; training_size<points.size()/4; training_size++)
        {
            float trials_accuracy = 0;
            for (int trials=0; trials<100; trials++)
            {
                switch(switch_algorithim)
                {
                    case 0:
                    case 1:
                        random_shuffle(points.begin(), points.end());
                        break;
                    case 2:
                        points = randomize(points, training_size);
                        break;
                }
                //run algorithim
                QVector<SolvedDataPoint> data_points = run_algorithim(points,training_size, max_it);
                trials_accuracy += accuracy(data_points, training_size);

            }
            if(max_it % 5 == 0 || max_it == 1) {
                printf("completed iteration iterations:[%i] Training set : [%f] with accuracy %f \n",max_it,(float)training_size/(float)points.size()*100,trials_accuracy);
            }
            fflush(stdout);
            temp.push_back(trials_accuracy/100.0);
        }
        accuracy_points.push_back(temp);
    }

    return accuracy_points;
}

//takes vector and training size, returns distributed randomized vector
QVector<DataPoint> Display::randomize(QVector<DataPoint> points, int training_size)
{
    QVector<DataPoint> trues;
    QVector<DataPoint> falses;
    for(int i = 0; i < points.size(); i++) {
        if (points[i].classification == true) {
            trues.push_back(points[i]);
        } else {
            falses.push_back(points[i]);
        }
    }
    float ratio = (float)trues.size()/(float)points.size();
    int num_of_trues = ratio * training_size;
    random_shuffle(trues.begin(), trues.end());
    random_shuffle(falses.begin(), falses.end());
    QVector<DataPoint> return_vector;
    for(int i = 0; i < num_of_trues; i++) {
        return_vector.push_back(trues[i]);
    }
    for(int i = 0; i < falses.size(); i++) {
        return_vector.push_back(falses[i]);
    }
    for(int i = num_of_trues; i < trues.size(); i++) {
        return_vector.push_back(trues[i]);
    }
    return return_vector;
}

//calls kperceptron/boost with QVector<DataPoints> and returns QVector<SolvedDataPoints> from respective functions
QVector<SolvedDataPoint> Display::run_algorithim(QVector<DataPoint> points, int training_size, int max_it)
{

    QVector<SolvedDataPoint> data_points;

    switch(switch_algorithim)
    {
        case 0:
        case 1:
            data_points = kPerceptronSolver(points, training_size, max_it, perceptron_degree);
            break;
        case 2:
            data_points = Booster::boost(points, training_size, max_it);
            break;
    }
    return data_points;
}

void Display::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(QVector3D(eye.x()*1, eye.y()*2, eye.z()*1), // x15 moves camera away from origin
                      QVector3D(at.x(), at.y(), at.z()),
                      QVector3D(up.x(), up.y(), up.z()));
    glLoadMatrixd(viewMatrix.data());

    glColor4f(1,1,1, 1);
    glBegin(GL_QUADS);
    glVertex3f(0, 0.0f, 0);
    glVertex3f(-1.27, 0.0f, 0);
    glVertex3f(-1.27, 0.0f, -1.27);
    glVertex3f(0, 0.0f, -1.27);
    glEnd();

    if (calc_finished == 0)
        return;

    //THESE VALUES NEED TO BE DYNAMICALLY CALCULATED FROM 1.27 / 2 / MAXIT-1 AND POINTS.SIZE()/4-1
    float xsize = 0.0669;
    float zsize = 0.0363;
    float blue;
    float green;
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<36; j++)
        {
            float x = i/19.0*-1.27;
            float z = j/35.0*-1.27;
            green = accuracy_points[i][j];
            //red =1;
            blue = 1 - green;
            glColor3f(0,green,blue);
            glBegin(GL_QUADS);
            glVertex3f(x, 0.0f, z);
            glVertex3f(x-xsize, 0.0f, z);
            glVertex3f(x-xsize, 0.0f, z-zsize);
            glVertex3f(x, 0.0f, z-zsize);
            glEnd();
        }
    }

}

void Display::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(60.0f, (float)width/(float)height, 0.01f, 50.0f);
    glLoadMatrixd(projectionMatrix.data());
    glMatrixMode(GL_MODELVIEW);
}

//reads file, returns QVector<DataPoints>
QVector<DataPoint> Display::read_file()
{
    QVector<DataPoint> points;

    QFile file;
    if(switch_data_set == 0 || switch_data_set ==1 || switch_data_set ==2) { //set 0,1,2 to the three irises
        file.setFileName("/Users/naleliunas/Documents/421-Project-1/iris.data");
    } else if(switch_data_set == 3) { //blood data set
        file.setFileName("/Users/naleliunas/Documents/421-Project-1/transfusion.data");
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line = in.readLine();
    DataPoint new_point;
    if (switch_data_set == 3) line = in.readLine(); //skip the first line.
    while (!line.isEmpty())
    {

        const char *cstring = line.toUtf8().constData();

        splitstring s(cstring);
        vector<string> flds = s.split(',');
        QVector<float> attr;

        char *a;
        for (int k=0; k < flds.size(); k++){
            a=new char[flds[k].size()+1];
            a[flds[k].size()]=0;
            memcpy(a,flds[k].c_str(),flds[k].size());
            printf("%s ", a);

            if (k < flds.size()-1)
            {
                //attr[k] = atof(a);
                //printf("%f ", attr[k]);
                attr.push_back(atof(a));
            }

        }
        bool classification = false;
        char *true_classification;
        if(switch_data_set == 0 || switch_data_set ==1 || switch_data_set ==2) { //set 0,1,2 to the three irises
            if(switch_data_set == 0) {
                true_classification = "Iris-setosa";
            } else if(switch_data_set == 1) {
                true_classification = "Iris-versicolor";
            } else if(switch_data_set == 2) {
                true_classification = "Iris-virginica";
            }

        } else if(switch_data_set == 3) { //blood data set
            true_classification = "1";
        }
        if (strcmp(a, true_classification) == 0)
        {
            classification = true;
        }
        new_point = DataPoint(attr, (flds.size()-1), classification);
        points.push_back(new_point);
        printf("\n");

        line = in.readLine();
    }
    file.close();
    return points;
}

//returns progress
int Display::return_progress()
{
   return progress;
}

void Display::set_maximum_iterations(int max_it)
{
    maximum_iterations = max_it;
}

void Display::set_perceptron_degree(int degree)
{
    perceptron_degree = degree;
}

void Display::set_training_set_size(int size)
{
    training_set_size = size/100.0;
}

void Display::set_algorithm(int n)
{
    switch_algorithim = n;
}

void Display::set_analysis(bool onetime)
{
    if (onetime)
    {
        switch_analysis = 1;
    }
    else
    {
        switch_analysis = 0;
    }

}

void Display::set_data_set(int n)
{
    switch_data_set = n;
}
