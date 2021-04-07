#include "network.hpp"

Network::Network(vector<int> net_layout)
{
    Layer l; // struct of Layer type

    net_topology.push_back(l);
    for(int k = 0; k < net_layout[0]; k++) // add first layer with only one input in each neuron
        net_topology[0].neuron_layer.push_back(1);

    for(int i = 1; i < net_layout.size(); i++ ){ // iterating through desired layers
                                                 // adding layers based off number of outputs in previous layer

        net_topology.push_back(l);  // addign new layer to network topology vector

        for(int j = 0; j < net_layout[i]; j++){ // adding number of required neurons to the layer
            
            net_topology[i].neuron_layer.push_back(net_layout[i-1]);
            
        }
    }
}

Network::~Network()
{
}

void Network::feedForward(vector <double> net_input) // feedForwarding data through network
{

    for(int k = 0; k < net_input.size(); k++){ // forwarding data through input layer
        net_topology[0].neuron_layer[k].forwardData(net_input[k]); // forward data through each neuron in layer 0
    }

    double input_val = 0;
    vector<double> new_input_vector; 

    for(int i = 1; i < net_topology.size(); i++){ // iterate through layers

        for(int j = 0; j < net_topology[i].neuron_layer.size(); j++){  // iterate through neurons
            
            input_val = net_topology[i-1].neuron_layer[j].getOutput();
            new_input_vector.push_back(input_val); // get output from each neuron and store in input_vector
        }
        
        for(int l = 0; l < net_topology[i].neuron_layer.size(); l++){  // iterate through neurons
            net_topology[i].neuron_layer[l].forwardData(new_input_vector); // forward data through neuron using new_input_vector
        }
        new_input_vector.clear(); // resetting vector for next layer pass
    }
}


vector<double> Network::getNetOutput() // returns the output of the output layer in a vector 
{
    vector<double> output_vector;
    for(int i = 0; i < net_topology.back().neuron_layer.size();i++){ // iterate through last layer's neurons
        output_vector.push_back(net_topology.back().neuron_layer[i].getOutput()); // add neuron's output to vector
    }
    return output_vector;
}

void Network::printNetwork(){ // print network details
    cout<< "Neural Network Print\n";

    for(int i = 0; i < net_topology.size(); i++){
    cout << "Layer #" << i+1 << "\n";
    for(int j = 0; j < net_topology[i].neuron_layer.size(); j++){
        net_topology[i].neuron_layer[j].printNeuron();
    }
    }
}