//
//  TrainingData.cpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#include "TrainingData.hpp"

void TrainingData::getTopology(std::vector<int> &topology)
{
    std::string line;
    std::string label;
    
    getline(m_trainingDataFile, line);
    std::stringstream ss(line);
    ss >> label;
    if(this->isEof() || label.compare("topology:") != 0)
        abort();
    
    int n;
    while(!ss.eof())
    {
        
        ss >> n;
        topology.push_back(n);
    }
}

TrainingData::TrainingData(const std::string filename)
{
    m_trainingDataFile.open(filename.c_str());
}

u_long TrainingData::getNextInputs(std::vector<double> &inputVals)
{
    inputVals.clear();
    
    std::string line;
    getline(m_trainingDataFile, line);
    std::stringstream ss(line);
    
    std::string label;
    ss >> label;
    if (label.compare("in:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }
    return inputVals.size();
}

u_long TrainingData::getTargetOutputs(std::vector<double> &targetOutputVals)
{
    targetOutputVals.clear();
    
    std::string line;
    getline(m_trainingDataFile, line);
    std::stringstream ss(line);
    
    std::string label;
    ss >> label;
    if (label.compare("out:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }
    
    return targetOutputVals.size();
}

