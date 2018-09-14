//
//  SigmoidActivationFunction.cpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/14/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#include "SigmoidActivationFunction.hpp"

double SigmoidActivationFunction::transferFunction(double x)
{
    return 1.0/(1 + std::exp(-x));
}

double SigmoidActivationFunction::transferFunctionDerivative(double x)
{
    double temp = transferFunction(x);
    return temp*(1-temp);
}
