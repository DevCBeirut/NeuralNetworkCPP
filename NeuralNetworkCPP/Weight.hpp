//
//  Weight.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/12/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef Weight_hpp
#define Weight_hpp

class Weight{
public:
    double weight;
    double delta_weight;
    Weight(double=0, double=0);
    Weight(Weight&);
    Weight operator+(Weight&);
    Weight operator-(Weight&);
    Weight operator*(Weight&);
    Weight& operator+=(Weight&);
    operator double() const;
};

#endif /* Weight_hpp */
