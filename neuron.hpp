#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include <cmath>


using namespace std;

class Neuron
{
    private:
        static int id_tracker; // stores next available id
        int id;
        
        double output;

        vector<double> neuron_weights;

    public:
        Neuron(int);
        ~Neuron();

        // forward data through neuron
        void forwardData(double &); 
        void forwardData(vector<double> &);

        // activation functions for the neuron
        double activationFunction(double &);
        double activationDerivative(double &);
        
        // setters and getters
        double getOutput();
        void setOutput(double &);

        // print neuron details
        void printNeuron();
};

#endif