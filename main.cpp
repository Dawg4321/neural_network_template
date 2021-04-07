#include "neuron.hpp"
#include "network.hpp"
#include "layer.hpp"

using namespace std;

// for compilation with g++: clear && g++ main.cpp neuron.cc network.cc -o main && ./main

int main()
{   
    vector<int> t = {2,2,2,2};
    Network net1(t); // create network with above topology

    //net1.printNetwork();

    vector<double> x = {1,0};
    cout << "Input:\n";

    for(int i = 0; i < x.size();i++){
        cout << i + 1<< ". " << x[i] << "\n";
    }

    net1.feedForward(x); // feed forward input through network

    vector<double> y = net1.getNetOutput(); // return output in vector y

    cout << "Output:\n";
    for(int i = 0; i < y.size();i++){
        cout << i + 1<< ". " << y[i] << "\n";
    }
    return 0;
}
