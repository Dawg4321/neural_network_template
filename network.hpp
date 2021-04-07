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

        // forward data through the network
        void feedForward(vector<double> &);

        // return network output
        vector<double> getNetOutput();

        void printNetwork();

};

#endif