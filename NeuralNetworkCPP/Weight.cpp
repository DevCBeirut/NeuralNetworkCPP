//
//  Weight.cpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/12/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#include "Weight.hpp"

Weight::Weight(Weight& w) : weight(w.weight), delta_weight(w.delta_weight)
{}

Weight::Weight(double _weight, double _delta_weight) : weight(_weight), delta_weight(_delta_weight)
{}

Weight& Weight::operator+=(Weight & w)
{
    weight += w.weight;
    return *this;
}

Weight Weight::operator+(Weight & w)
{
    Weight new_w(weight+w.weight, delta_weight);
    return new_w;
}

Weight Weight::operator-(Weight & w)
{
    Weight new_w(weight-w.weight, delta_weight);
    return new_w;
}

Weight Weight::operator*(Weight & w)
{
    Weight new_w(weight*w.weight, delta_weight);
    return new_w;
}

Weight::operator double() const
{
    return weight;
}


