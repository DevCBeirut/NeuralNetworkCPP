//
//  ActivationFunction.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef ActivationFunction_hpp
#define ActivationFunction_hpp

#include <cmath>

class ActivationFunction
{
public:
    virtual ~ActivationFunction(){};
    virtual double transferFunction(double) = 0 ;
    virtual double transferFunctionDerivative(double)= 0 ;
};
#endif /* ActivationFunction_hpp */
