//
//  TanhActivationFunction.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef TanhActivationFunction_hpp
#define TanhActivationFunction_hpp

#include "ActivationFunction.hpp"

class TanhActivationFunction : public ActivationFunction {
public:
    virtual double transferFunction(double);
    virtual double transferFunctionDerivative(double);
};

#endif /* TanhActivationFunction_hpp */
