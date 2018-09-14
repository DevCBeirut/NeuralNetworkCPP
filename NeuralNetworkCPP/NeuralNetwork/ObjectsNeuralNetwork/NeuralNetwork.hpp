//
//  NeuralNetwork.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include "Neuron.hpp"
#include <cassert>
#include <cmath>
#include "INeuralNetwork.hpp"

class NeuralNetwork : public INeuralNetwork {
private:
    std::vector<Layer> network;
    double m_recentAverageError;
    static double m_recentAverageSmoothingFactor;
public:
    NeuralNetwork(std::vector<int>&);
    ~NeuralNetwork();
    void feedForward(double*);
    void backProp(double*);
    void getResults(double**);
    int getInputSize();
    int getResultsSize();
    std::vector<Layer>& getLayers();
    double getRecentAverageError() const;
    const std::vector<int>& Topology;
};



#endif /* NeuralNetwork_hpp */
