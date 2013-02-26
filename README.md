421-Project-1
=============

TODO:
Data Entry/Wrapping Program in Qt -
  UI:
    -List of Data sets (drop down menu)
    -List of Classifications of Data Sets (drop down menu)
    -Chose an algorithim to run on said data set
  
  Programing Structure:
      -Sanitize chosen data set (input into vector of DataPoint objects)
      -randomize order of data set
      -send data to learning algorithim
        -input to each learning algorithim:
            -Vector of the (randomized) DataPoint, the Index of the first non-training example,
      -recive data from learning algorithim 
        -output from learning algorithim:
          -Vector of SolvedDataPoint in the same order as the input. 
      -save results & Statistical Analysis to file
      -Display output Graphically nicely! (good luck)
  
  Chosen representation of Data Sets:
      Object DataPoint:
            float attributes[n]
            bool classification
    
        Object SolvedDataPoint:
            float attributes[n]
            bool classification
            bool calculated_classification
            bool training_set
        
  Notes:
    The size of the training set is chosen here, so fiddle around with it to get better/more efficent results
    The data will be randomized because we don't want to always use the first portion of the data set as the training example.
    Can you save the randomized order to run it the same way to test different training data sizes/learning algorithims?  
    Each data set we choose as weird arbitrary classifications/attributes. 
        For example, iris. If we choose "look for iris-smoochy", set iris-smoochy to 1 in classification, all the rest to 0.
    Running this in Qt! Yaaay!
    Can you make a graph/some graphs out of this type of data?
    Should we be sending the algorithim's final equation back as well?
    
Kernelized Perceptron -
 http://cvit.iiit.ac.in/thesis/ranjeethMS2007/thesis/node21.html Has the algorithim! yaaay.

Boosting With Decsion Stumps


Archive of data sets: http://archive.ics.uci.edu/ml/

  we will be using Iris (Classifications can be: Which flower is it?) and 
  Blood Transfusion (Classifications only on March, so it's all good, no need for a drop down menu there)
  
  
Bonus Tasks:

    Heavenor - See if you can find this: (Easier) Compare the results of your algorithm with and o-the-shelf clas- sicaton algorithm (e.g., based on decision trees or neural nets.) In this case you do not need to write your own version of the competing algorithm. You are free to use any implementation that you are able to nd.
    Nik - See if you can fuck this up terribly: (Medium-Hard) Modify your kernel perceptron algorithm to use a different kernel function (e.g Gaussian-radial or sigmoid)
    Pattie - See if you can do a dance that looks like this: (Medium-Hard) Modify your boosting algorithm to use a different weak classifer (e.g., perceptron, decision trees)
