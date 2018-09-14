//
//  Neuron.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef Neuron_hpp
#define Neuron_hpp

#include <vector>
#include "ActivationFunction.hpp"

class Neuron;
class NeuralNetwork;
typedef std::vector<Neuron> Layer;
typedef unsigned long u_long;

struct Connection {
    double weight;
    double deltaWeight;
    Connection(double w)
    {
        weight = w;
        deltaWeight = 0;
    }
};

class Neuron
{
private:
    std::vector<Connection> m_outputWeights;
    double m_gradient;
    double m_outputVal;
    const u_long m_index;
    void calculateOutputGradient(double);
    void calculateHiddenGradient(Layer&);
    void feedForward(const Layer&);
    void updateInputWeights(Layer&);
    
    static double eta; //overall learning rate
    static double alpha; //multiplier of last weight change (step)
    static ActivationFunction * activationFunc;
    static double randomWeight() { return rand() / double(RAND_MAX); }
public:
    Neuron(u_long, u_long);
    Neuron(u_long);
    double getGradient() const;
    double getOutputVal() const;
    std::vector<Connection>& getOutputWeights();
    void setGradient(double);
    void setOutputVal(double);
    
    static void setActivationFunction(ActivationFunction * _activationFunction);
    
    friend class NeuralNetwork;
};

#endif /* Neuron_hpp */
