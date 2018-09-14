//
//  INeuralNetwork.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/15/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef INeuralNetwork_hpp
#define INeuralNetwork_hpp


class INeuralNetwork{
public:
    virtual void feedForward(double *)=0;
    virtual void backProp(double *)=0;
    virtual void getResults(double**)=0;
    virtual int getResultsSize()=0;
    virtual int getInputSize()=0;
};

#endif /* INeuralNetwork_hpp */
