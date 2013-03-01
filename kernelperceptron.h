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
		vector<SolvedDataPoint> kPerceptronSolver(vector<DataPoint> input, int training, int maxIter, int d);
	
	private:
		float qVectorDotProd(QVector<float> a, QVector<float> b);
};
