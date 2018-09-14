//
//  Manager.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef Manager_hpp
#define Manager_hpp

#include <string>
#include <fstream>

class Manager {
private:
    std::string m_file_name;
public:
    Manager(std::string file_name)
    {
        m_file_name = file_name;
    }
    std::string getFileName()
    {
        return m_file_name;
    }
    virtual void Write() = 0;
    virtual void Read() = 0;
};

#endif /* Manager_hpp */
