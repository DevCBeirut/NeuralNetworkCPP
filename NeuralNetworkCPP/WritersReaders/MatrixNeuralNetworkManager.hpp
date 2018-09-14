//
//  MatrixNeuralNetworkManager.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/12/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef MatrixNeuralNetworkManager_hpp
#define MatrixNeuralNetworkManager_hpp

#include "Manager.hpp"
#include "MatrixNeuralNetwork.hpp"
#include <sstream>
#include "ActivationFunction.hpp"

class MatrixNeuralNetworkManager : public Manager {
private:
    MatrixNeuralNetwork** network;
    ActivationFunction * func;
public:
    MatrixNeuralNetworkManager(std::string, MatrixNeuralNetwork**, ActivationFunction * = nullptr);
    virtual void Write();
    virtual void Read();
    MatrixNeuralNetwork** getNetwork();
};


#endif /* MatrixNeuralNetworkManager_hpp */
