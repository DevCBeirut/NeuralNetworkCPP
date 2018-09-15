//
//  main.cpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/10/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "NeuralNetwork.hpp"
#include "MatrixNeuralNetwork.hpp"
#include "NeuralNetworkManager.hpp"
#include "TanhActivationFunction.hpp"
#include "TrainingData.hpp"
#include "SigmoidActivationFunction.hpp"
#include "MatrixNeuralNetworkManager.hpp"
#include "INeuralNetwork.hpp"

using namespace std;

void genTrainingData()
{
    ofstream out("trainingData.txt");
    //topology: (the numbers of all layers): (number of neurons in every layer)
    //topology: 3: 2 4 1 -> will create a neural network with 3 layers :
    //2 neurons in the input layer, 4 neurons in the hidden layer, 1 neuron in the outout layers
    //another example :
    //topology: 5: 3 4 4 3 2 -> will create a neural network ok 5 layers
    //input layer containing 3 neurons
    //3 hidden layers containing respectively 4 neurons, 4 neurons, 3 neurons
    //output layer containing 2 neurons
    out << "topology: 3: 2 4 1" << endl;
    for(int i = 2000; i >= 0; --i)
    {
        int n1 = (int)(2.0 * rand() / double(RAND_MAX));
        int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int t = n1 ^ n2;
        out << "in: " << n1 << ".0 " << n2 << ".0 "<< endl;
        out << "out: " << t << ".0" << endl;
    }
    out.close();
}

void Test(INeuralNetwork & myNet)
{
    vector<double> input;
    double x;
    for(int i=0; i<myNet.getInputSize(); i++)
    {
        
        cout << "Enter Input :";
        cin >> x;
        input.push_back(x);
    }
    
    myNet.feedForward(&input[0]);
    
    double * outputs = nullptr;
    myNet.getResults(&outputs);
    
    cout << "Results" << endl;
    
    for(int i=0; i<myNet.getResultsSize(); i++)
        cout << outputs[i];
    
    cout << endl;
}

void Train()
{
    TrainingData trainData("trainingData.txt");
    vector<int> topology;
    trainData.getTopology(topology);
    
    //NeuralNetwork * myNet = new NeuralNetwork(topology);
    //OR
    MatrixNeuralNetwork * myNet = new MatrixNeuralNetwork(&topology[0], (int)topology.size(), new TanhActivationFunction());
    vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;
    while(!trainData.isEof())
    {
        ++trainingPass;
        if(trainData.getNextInputs(inputVals) != topology[0])
            break;
        myNet->feedForward(&inputVals[0]);
        
        trainData.getTargetOutputs(targetVals);
        assert(targetVals.size() == topology.back());
        
        myNet->backProp(&targetVals[0]);
    }
    
    //NeuralNetworkManager manager("data.txt", &myNet);
    //OR
    MatrixNeuralNetworkManager manager("data.txt", &myNet, nullptr);
    
    manager.Write();
}

#define TRAIN
 


int main(int argc, const char * argv[]) {
    
    //initialization of the activation function of a neuron in NeuralNetwork Class
    Neuron::setActivationFunction(new TanhActivationFunction());

    
#ifdef TRAIN
    
    Train();
    
#else
    
    MatrixNeuralNetwork * n = nullptr;
    
    MatrixNeuralNetworkManager m("data.txt", &n, new TanhActivationFunction());
    m.Read();
    
    double * input = new double[2]{0,1};
    n->feedForward(input);
    double* output=nullptr;
    n->getResults(&output);
    cout << output[0] <<endl;
    delete[] input;
    delete[] output;
    
    
    NeuralNetwork * net = nullptr;
    
    NeuralNetworkManager manager("data.txt", &net);
    
    manager.Read();
        
    
    for(int i=0; i<4; i++)
    {
        Test(*n);
    }
    
#endif

}
