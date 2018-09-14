//
//  TrainingData.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef TrainingData_hpp
#define TrainingData_hpp

#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>

class TrainingData
{
public:
    TrainingData(const std::string filename);
    bool isEof(void)
    {
        return m_trainingDataFile.eof();
    }
    void getTopology(std::vector<int> &topology);
    u_long getNextInputs(std::vector<double> &inputVals);
    u_long getTargetOutputs(std::vector<double> &targetOutputVals);
    
private:
    std::ifstream m_trainingDataFile;
};

#endif /* TrainingData_hpp */
