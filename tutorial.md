# Tutorial

## Create your Neural Network

### Creating New Neural Network (not trained) with 2 input neurons, 4 neurons in the hidden layer, 1 output neuron

##### NeuralNetwork and MatrixNeuralNetwork works exactly the same, but the aspect of the implementation is different

#### NeuralNetwork implementation where Every Neuron is an object  having properties and connections...

##### Topology
topology: (the numbers of all layers): (number of neurons in every layer)
topology: 3: 2 4 1
will create a neural network with 3 layers :
2 neurons in the input layer, 4 neurons in the hidden layer, 1 neuron in the outout layers
another example :
topology: 5: 3 4 4 3 2
will create a neural network ok 5 layers
input layer containing 3 neurons
3 hidden layers containing respectively 4 neurons, 4 neurons, 3 neurons
output layer containing 2 neurons


```C++
vector<int> topology;
topology.push_back(2);
topology.push_back(4);
topology.push_back(1);
NeuralNetwork * myNet = new NeuralNetwork(topology);
```

#### MatrixNeuralNetwork implementation based on Matrix Multiplications

```C++
int * topology = new int[3]{2, 4, 1};
MatrixNeuralNetwork * myNet = new MatrixNeuralNetwork(topology, 3, new TanhActivationFunction());
```

### Feed Forward The NeuralNetwork and get Results

```C++
double* inputs = new double[2]{0, 1};
myNet->feedForward(input);
double* output=nullptr;
myNet->getResults(&output);
for(int i=0; i<myNet->getResultsSize(); i++)
    cout << output[i] << endl;
delete[] input;
delete[] output;
```
### Train you Neural Network

#### TrainingData class reading data from file to feed the neural network

#### TrainingData file structure :

```txt
topology: 3: 2 4 1
in: 0.0 0.0
out: 0.0
in: 1.0 0.0
out: 1.0
```

##### in: input neurons values
##### out: output neurons values

```C++
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
```

### Saving and Loading Trained Neural Networks

#### Manager is the abstract class responsible for reading, writing your network

##### Saving

```C++
//After Training your network

//NeuralNetworkManager manager("data.txt", &myNet);
//OR
MatrixNeuralNetworkManager manager("data.txt", &myNet, nullptr);
//PS:On saving your matrix neural network, you dont need to pass the Activation Function Object to the manager
//thats why you see nullptr in manager contructor

manager.Write();
```
##### Reading

```C++
MatrixNeuralNetwork * n = nullptr;
MatrixNeuralNetworkManager m("data.txt", &n, new TanhActivationFunction());
m.Read();

NeuralNetwork * net = nullptr;
NeuralNetworkManager manager("data.txt", &net);
manager.Read();
```


