#ifndef DISPLAY_H
#define DISPLAY_H

#include <QGLWidget>
#include <QMatrix4x4>
#include <QVector3D>
#include <string>
#include "structures.h"


using namespace std;

class splitstring : public string {
    vector<string> flds;
public:
    splitstring(const char *s) : string(s) { };
    vector<string>& split(char delim, int rep=0);
};


class Display : public QGLWidget
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = 0);

signals:

public slots:

    void start();
    int return_progress();
    void set_perceptron_degree(int n);
    void set_training_set_size(int n);
    void set_maximum_iterations(int n);
    void set_analysis(bool n);
    void set_data_set(int n);

protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    QVector< QVector<float> > analyse_accuracy();
    QVector<SolvedDataPoint> run_algorithim(QVector<DataPoint> points, int training_size, int max_it);
    QVector<DataPoint> randomize(QVector<DataPoint> points, int training_size);
    QVector<DataPoint> read_file(char* file_name);
private:
    QMatrix4x4  projectionMatrix;       /**< the projectionMatrix to describe our camera projection parameters.*/
    QMatrix4x4  viewMatrix;             /**< the view matrix to describe the location and orientation of our camera. */

    QVector3D eye;
    QVector3D at;
    QVector3D up;

    int switch_algorithim;
    int switch_data_set;
    int switch_analysis;
    int perceptron_degree;
    int maximum_iterations;
    float training_set_size;
    int number;
    int progress;

    QVector< QVector<float> > accuracy_points;
    int calc_finished;

    float accuracy(QVector<SolvedDataPoint> points, int training_size);
};



#endif // DISPLAY_H
