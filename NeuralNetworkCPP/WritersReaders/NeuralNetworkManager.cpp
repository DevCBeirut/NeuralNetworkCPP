//
//  NeuralNetworkWriter.cpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#include "NeuralNetworkManager.hpp"

NeuralNetworkManager::NeuralNetworkManager(std::string file_name, NeuralNetwork** network) : Manager(file_name)
{
    this->network = network;
}

void NeuralNetworkManager::Write()
{
    std::ofstream out(getFileName());
    if(!out)
        abort();
    
    out.precision(30);
    out << "topology: ";
    out << (*network)->Topology.size() <<":";
    for(u_long i=0; i<(*network)->Topology.size(); i++)
        out << " " << (*network)->Topology.at(i);
    out << std::endl;
    
    for(u_long i=0; i<(*network)->getLayers().size(); i++)
        for(u_long j=0; j<(*network)->getLayers().at(i).size(); j++)
        {
            for(u_long k=0; k<(*network)->getLayers().at(i).at(j).getOutputWeights().size(); k++)
                out << (*network)->getLayers().at(i).at(j).getOutputWeights().at(k).weight << " " <<
                    (*network)->getLayers().at(i).at(j).getOutputWeights()[k].deltaWeight << std::endl;
            
            out<<std::endl;
        }
    out.close();
}

void NeuralNetworkManager::Read()
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
    
    int n;
    
    
    int size;
    ss >> size;
    ss.get();
    
    std::vector<int> * topology = new std::vector<int>();
    
    while(!ss.eof())
    {
        ss >> n;
        topology->push_back(n);
    }
    
    *network = new NeuralNetwork(*topology);
    
    for(u_long i=0; i<(*network)->getLayers().size(); i++)
        for(u_long j=0; j<(*network)->getLayers().at(i).size(); j++)
            for(u_long k=0; k<(*network)->getLayers().at(i).at(j).getOutputWeights().size(); k++)
                in >> (*network)->getLayers().at(i).at(j).getOutputWeights().at(k).weight >>
                    (*network)->getLayers().at(i).at(j).getOutputWeights().at(k).deltaWeight;
    
    in.close();
}

NeuralNetwork** NeuralNetworkManager::getNetwork()
{
    return network;
}
