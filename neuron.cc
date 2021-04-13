#include "neuron.hpp"

int Neuron::id_tracker = 0; // initialising id_tracker to 0

Neuron::Neuron(int num_of_inputs)
{
    id = ++id_tracker; // set id within neuron

    for(int i = 0; i < num_of_inputs; i++){ // generate random weights based on number of inputs
        neuron_weights.push_back(rand()/double(RAND_MAX));
    }
}

Neuron::~Neuron()
{

}

void Neuron::forwardData(double &input) // pass data through the input neuron
{                                      // (pass input through with no weight applied)
    output = input*neuron_weights[0];
}

void Neuron::forwardData(vector<double> &input_vector) // pass data through neuron
{
    double sum_val = 0;

    for(int i = 0; i < input_vector.size(); i++){ // sum of inputs multiplied by their respective weight 
        sum_val += input_vector[i]*neuron_weights[i];
    }

    output = activationFunction(sum_val); // setting output using activation function
}

double Neuron::activationFunction(double &x) // activation function for feedforwarding
{
    return 1/(1+exp(x*(-1))); // return sigmoid(x)
}
double Neuron::activationDerivative(double &x) // derivation of activation function for backpropagation
{
    return x*(1-x); // return d(sigmoid)/dx
}

double Neuron::getOutput() // return output
{ 
    return output;
}

void Neuron::setOutput(double &input) // set output
{
    output = input;
}

void Neuron::printNeuron() // print neuron weights
{
    cout << "Neuron #" << id << "\nInput Weights:\n";
    
    for(int i = 0; i < neuron_weights.size();i++){
        cout << neuron_weights[i] << "\n";
    }
}