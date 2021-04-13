#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <iostream>

#include "neuron.hpp"
#include "layer.hpp"

using namespace std;

class Network
{
    private:
        vector<Layer> net_topology; // vector of layer structures
                                    // effectively a vector matrix
        
        vector<double> net_output; // vector to store network output from feedForward

    public:
        Network(vector<int> &);
        ~Network();

        void feedForward(vector<double> &); // forward data through the network
        void propBack(vector<double> &); // propagate backwards through the network

        double calcOutputGrad(double, int); // calculate output gradient for a single val
        double calcHiddenGrad(double &expected, double &actual, int layer_num, int neuron_num); // calculate hidden layer gradient for a single val

        vector<double> getNetOutput(); // return network output

        void printNetwork(); // print network details
};

#endif