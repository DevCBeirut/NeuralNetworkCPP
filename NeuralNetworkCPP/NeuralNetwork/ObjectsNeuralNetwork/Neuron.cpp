//
//  Neuron.cpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#include "Neuron.hpp"

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;
ActivationFunction* Neuron::activationFunc = nullptr;

void Neuron::setActivationFunction(ActivationFunction *_activationFunct)
{
    activationFunc = _activationFunct;
}

Neuron::Neuron(u_long _myIndex) : m_index(_myIndex)
{}

Neuron::Neuron(u_long _myIndex, u_long numOutputs) : m_index(_myIndex)
{
    for(u_long c = 0; c < numOutputs; c++)
        m_outputWeights.push_back(Connection(randomWeight()));
}

void Neuron::setOutputVal(double x)
{
    m_outputVal = x;
}

double Neuron::getGradient() const
{
    return m_gradient;
}

double Neuron::getOutputVal() const
{
    return m_outputVal;
}

std::vector<Connection>& Neuron::getOutputWeights()
{
    return m_outputWeights;
}

void Neuron::setGradient(double gradient)
{
    m_gradient = gradient;
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;
    
    for(u_long i=0; i<prevLayer.size(); i++)
        sum += prevLayer.at(i).m_outputVal * prevLayer.at(i).m_outputWeights.at(m_index).weight;
        
    m_outputVal = activationFunc->transferFunction(sum);
}

void Neuron::calculateOutputGradient(double tagertVal)
{
    double delta = tagertVal - m_outputVal;
    m_gradient = activationFunc->transferFunctionDerivative(m_outputVal) * delta;
}

void Neuron::calculateHiddenGradient(Layer & nextLayer)
{
    double sum = 0.0;
    for (u_long i = 0; i< nextLayer.size() - 1; i++)
        sum += m_outputWeights.at(i).weight * nextLayer.at(i).m_gradient;
    m_gradient = sum * activationFunc->transferFunctionDerivative(m_outputVal);
}

void Neuron::updateInputWeights(Layer & prevLayer)
{
    for(u_long i = 0; i < prevLayer.size(); i++)
    {
        Neuron &neuron = prevLayer.at(i);
        double oldDeltaWeight = neuron.m_outputWeights.at(m_index).deltaWeight;
        double newDeltaWeight = eta * neuron.getOutputVal() * m_gradient + alpha * oldDeltaWeight;
        neuron.m_outputWeights.at(m_index).deltaWeight = newDeltaWeight;
        neuron.m_outputWeights.at(m_index).weight += newDeltaWeight;
    }
}
