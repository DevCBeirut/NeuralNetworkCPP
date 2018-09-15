//
//  MatrixNeuralNetworkManager.cpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/12/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#include "MatrixNeuralNetworkManager.hpp"

MatrixNeuralNetworkManager::MatrixNeuralNetworkManager(std::string file_name, MatrixNeuralNetwork** network, ActivationFunction * func) : Manager(file_name)
{
    this->network = network;
    this->func = func;
}

void MatrixNeuralNetworkManager::Write()
{
    std::ofstream out(getFileName());
    if(!out)
        abort();
    
    out.precision(30);
    out << "topology: ";
    int size = (*network)->getTopologySize();
    out << size << ":";
    for(u_long i=0; i<size; i++)
        out << " " << (*network)->getTopology()[i];
    out << std::endl;
    
    Matrix<Weight> * tw;
    for(int i=0; i<size-1; i++)
    {
        tw = (*network)->getWeights()[i];
        for(u_long i=0; i<tw->getRows(); i++)
        {
            for(u_long j=0; j<tw->getColumns(); j++)
                out << tw->getMatrix()[i][j].weight << " " << tw->getMatrix()[i][j].delta_weight << " ";
            out << std::endl;
        }
        out << std::endl;
    }
    
    
    out.close();
}

void MatrixNeuralNetworkManager::Read()
{
    std::ifstream in(getFileName());
    if(!in)
        abort();
    
    if(*network != nullptr)
        delete *network;
    
    std::string line;
    std::string label;
    
    getline(in, line);
    std::stringstream ss(line);
    ss >> label;
    if(in.eof() || label.compare("topology:") != 0)
        abort();
    
    int size;
    int index =0;
    ss >> size;
    ss.get();
    int * topology = new int[size];
    while(!ss.eof())
        ss >> topology[index++];
    
    *network = new MatrixNeuralNetwork(topology, size, func);
    
    Matrix<Weight> * tw;
    for(int i=0; i<size-1; i++)
    {
        tw = (*network)->getWeights()[i];
        for(u_long i=0; i<tw->getRows(); i++)
            for(u_long j=0; j<tw->getColumns(); j++)
                in >> tw->getMatrix()[i][j].weight >> tw->getMatrix()[i][j].delta_weight;
    }
    
    in.close();
}

MatrixNeuralNetwork** MatrixNeuralNetworkManager::getNetwork()
{
    return network;
}
