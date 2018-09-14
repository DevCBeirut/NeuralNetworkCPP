//
//  TanhActivationFunction.cpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#include "TanhActivationFunction.hpp"

double TanhActivationFunction::transferFunction(double x)
{
    return std::tanh(x)+ 0.03*x;
}

double TanhActivationFunction::transferFunctionDerivative(double x)
{
    return 1-x*x+ 0.03;
}
