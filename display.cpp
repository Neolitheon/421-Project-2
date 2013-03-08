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

float Display::accuracy(QVector<SolvedDataPoint> points)
{
    int correct = points.size();
    for (int i=0; i<points.size(); i++)
    {
        //printf("%d%d", int(points[i].classification), int(points[i].calculatedClassification));
        if (points[i].classification != points[i].calculatedClassification)
        {
            correct -= 1;
        }
    }
    return correct;
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
    switch_algorithim = 0;
    switch_data_set = 0;
    switch_analysis = 0;
    perceptron_degree = 2;
}


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
                points = randomize(points, training_size);

                //run algorithim
                QVector<SolvedDataPoint> data_points = run_algorithim(points,training_size, max_it);
                trials_accuracy += accuracy(data_points);

            }
           // printf("max_it:%d size:%d accuracy: %f\n", max_it, training_size, trials_accuracy/100);
            //printf("%d %d %f\n", max_it, training_size, trials_accuracy/100);
            temp.push_back(trials_accuracy/(points.size() - training_size)/100);
        }
        accuracy_points.push_back(temp);
    }

    return accuracy_points;
}

QVector<DataPoint> Display::read_file() {
    QVector<DataPoint> points;
    DataPoint new_point;
    if(switch_data_set == 0 || switch_data_set ==1 || switch_data_set ==2) { //set 0,1,2 to the three irises
            int attr_size = 4;

            QFile file("/Users/naleliunas/Downloads/AI/iris.data");
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream in(&file);
            QString line = in.readLine();
            while (!line.isNull())
            {

                const char *cstring = line.toUtf8().constData();

                splitstring s(cstring);
                vector<string> flds = s.split(',');
                float attr[attr_size];

                char *a;
                for (int k=0; k < flds.size(); k++){
                    a=new char[flds[k].size()+1];
                    a[flds[k].size()]=0;
                    memcpy(a,flds[k].c_str(),flds[k].size());
                    //printf("%s ", a);

                    if (k < attr_size)
                    {
                        attr[k] = atof(a);
                        //printf("%f ", attr[k]);
                    }

                }
                bool classification = false;
                char *true_classification;
                if(switch_data_set == 0) {
                    true_classification = "Iris-setosa";
                } else if(switch_data_set == 1) {
                    true_classification = "Iris-versicolor";
                } else if(switch_data_set == 2) {
                    true_classification = "Iris-virginica";
                }
                if (strcmp(a, true_classification) == 0)
                {
                    classification = true;
                }
                new_point = DataPoint(attr, attr_size, classification);
                points.push_back(new_point);
                //printf("\n");

                line = in.readLine();
            }
            file.close();
    }else if(switch_data_set == 3) { //blood data set

    }
    return points;
}

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

    QVector< QVector<float> > accuracy_points = analyse_accuracy();
    //THESE VALUES NEED TO BE DYNAMICALLY CALCULATED FROM 1.27 / 2 / MAXIT-1 AND POINTS.SIZE()/4-1
    float xsize = 0.0669;
    float zsize = 0.0363;
    float red;
    float blue;
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<36; j++)
        {
            float x = i/19.0*-1.27;
            float z = j/35.0*-1.27;
            //red = accuracy_points[i][j];
            red = 1;
            blue = 1 - red;
            glColor4f(red,0,blue, 1);
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
