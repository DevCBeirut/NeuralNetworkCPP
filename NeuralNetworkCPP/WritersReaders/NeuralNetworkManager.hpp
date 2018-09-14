//
//  NeuralNetworkWriter.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef NeuralNetworkManager_hpp
#define NeuralNetworkManager_hpp

#include "Manager.hpp"
#include "NeuralNetwork.hpp"
#include <sstream>

class NeuralNetworkManager : public Manager {
private:
    NeuralNetwork** network;
public:
    NeuralNetworkManager(std::string, NeuralNetwork**);
    virtual void Write();
    virtual void Read();
    NeuralNetwork** getNetwork();
};

#endif /* NeuralNetworkManager_hpp */
