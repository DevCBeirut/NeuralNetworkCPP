//
//  MatrixNeuralNetwork.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/11/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef MatrixNeuralNetwork_hpp
#define MatrixNeuralNetwork_hpp

#include "Matrix.hpp"
#include "Weight.hpp"
#include "ActivationFunction.hpp"
#include "INeuralNetwork.hpp"

class MatrixNeuralNetwork : public INeuralNetwork {
private:
    double m_recentAverageError;
    static double m_recentAverageSmoothingFactor;
    const int topology_size;
    Matrix<Weight> ** weights;
    ActivationFunction * activationFunc;
    Matrix<double> ** neuron_outputs;
    Matrix<double> ** gradients;
    int * topology;
    static double eta; //overall learning rate
    static double alpha; //multiplier of last weight change (step)
public :
    MatrixNeuralNetwork(int*, int, ActivationFunction *);
    MatrixNeuralNetwork(Matrix<Weight>***, int*, int, ActivationFunction *);
    ~MatrixNeuralNetwork();
    void feedForward(double *);
    void backProp(double *);
    Matrix<Weight>** getWeights();
    Matrix<double>** getA();
    int getResultsSize();
    int getInputSize();
    void getResults(double **);
    int* getTopology();
    int getTopologySize();
};

#endif /* MatrixNeuralNetwork_hpp */
