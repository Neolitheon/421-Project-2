<<<<<<< HEAD
/*
 *  kernelperceptron.h
 *
 *
 *  Created by Nikolas Aleliunas on 2/25/13.
 *  Copyright 2013 UVic. All rights reserved.
 *
 *  PS: I AM A FLUFFY BUNNY.
 */

#include "structures.h"


        QVector<SolvedDataPoint> kPerceptronSolver(QVector<DataPoint> input, int training, int maxIter, int d);


        float qVectorDotProd(QVector<float> a, QVector<float> b);

=======
/*
 *  kernelperceptron.h
 *  
 *
 *  Created by Nikolas Aleliunas on 2/25/13.
 *  Copyright 2013 UVic. All rights reserved.
 *
 *  PS: I AM A FLUFFY BUNNY.
 */

#include "structures.h"

class kernelPerceptron 
{
	
public: 
	QVector<SolvedDataPoint> kPerceptronSolver(QVector<DataPoint> input, int training, int maxIter, int d);
	
private:
	float qVectorDotProd(QVector<float> a, QVector<float> b);
};
>>>>>>> 80f233be28800210c4751be4cedb19bae07c553a
