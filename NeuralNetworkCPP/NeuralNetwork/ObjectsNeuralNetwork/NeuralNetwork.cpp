//
//  NeuralNetwork.cpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#include "NeuralNetwork.hpp"

double NeuralNetwork::m_recentAverageSmoothingFactor = 100.0; // Number of training samples to average over

NeuralNetwork::NeuralNetwork(std::vector<int>& topology) : Topology(topology)
{
    u_long nb_layers = topology.size();
    
    for(u_long i = 0; i < nb_layers; i++){
        network.push_back(Layer());
        
        u_long numOutputs = i == topology.size() - 1 ? 0 : topology.at(i + 1);
        
        for(u_long j = 0; j <= topology.at(i); j++)
            network.back().push_back(Neuron(j, numOutputs));
        
        network.back().back().setOutputVal(1.0);
    }
}

NeuralNetwork::~NeuralNetwork()
{
    //delete &Topology;
}

void NeuralNetwork::feedForward(double* inputVals)
{
    for(int i=0; i<Topology[0]; i++)
        network.at(0).at(i).setOutputVal(inputVals[i]);
    
    for(int i=1; i<network.size(); i++)
    {
        Layer& prevLayer = network.at(i-1);
        Layer& currentLayer = network.at(i);
        for(int j=0; j<currentLayer.size()-1; j++)
            currentLayer.at(j).feedForward(prevLayer);
    }
}

void NeuralNetwork::getResults(double* * resultVals)
{
    *resultVals = new double[getResultsSize()];
    
    for(u_long n = 0; n < getResultsSize(); ++n)
        *resultVals[n] = network.back().at(n).getOutputVal();
}

int NeuralNetwork::getResultsSize()
{
    return Topology.back();
}

int NeuralNetwork::getInputSize()
{
    return Topology[0];
}

std::vector<Layer>& NeuralNetwork::getLayers()
{
    return network;
}

double NeuralNetwork::getRecentAverageError() const
{
    return m_recentAverageError;
}

void NeuralNetwork::backProp(double* outputVals)
{
    //calculate error
    Layer& outputLayer = network.back();
    
    double m_error = 0.0;
    double temp;
    
    for(int i=0; i<getResultsSize(); i++)
    {
        temp = (outputLayer.at(i).getOutputVal() - outputVals[i]);
        m_error += temp * temp;
    }
    
    m_error /= outputLayer.size() - 1;
    m_error = std::sqrt(m_error);
    
    m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);
    
    for(int i=0; i<outputLayer.size()-1; i++)
        outputLayer.at(i).calculateOutputGradient(outputVals[i]);
    
    for(u_long i=network.size()-2; i > 0; i--)
    {
        Layer& currentLayer = network.at(i);
        Layer& nextLayer = network.at(i+1);
        for(u_long j=0; j<currentLayer.size(); j++)
            currentLayer.at(j).calculateHiddenGradient(nextLayer);
    }
    
    for(u_long i = network.size()-1; i > 0; i--)
    {
        Layer& currentLayer = network.at(i);
        Layer& prevLayer = network.at(i-1);
        for(u_long j=0; j<currentLayer.size()-1; j++)
            currentLayer.at(j).updateInputWeights(prevLayer);
    }
    
}
