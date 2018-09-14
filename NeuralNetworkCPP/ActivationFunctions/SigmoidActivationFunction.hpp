//
//  SigmoidActivationFunction.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/14/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef SigmoidActivationFunction_hpp
#define SigmoidActivationFunction_hpp

#include "ActivationFunction.hpp"

class SigmoidActivationFunction : public ActivationFunction {
public:
    virtual double transferFunction(double);
    virtual double transferFunctionDerivative(double);
};

#endif /* SigmoidActivationFunction_hpp */
