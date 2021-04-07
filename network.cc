#include "network.hpp"

Network::Network(vector<int> &net_layout)
{
    Layer l; // struct of Layer type

    net_topology.push_back(l);
    /// **** setting up input layer neurons ****
    for(int k = 0; k < net_layout[0]; k++) // add first layer with only one input in each neuron
        net_topology[0].neuron_layer.push_back(1);

    /// **** setting up hidden layer neurons ****
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

void Network::feedForward(vector<double> &net_input) // feedForwarding data through network
{
    vector<double> curr_input;
    vector<double> new_input_vector; 

    double input_val = 0;
    double num_data_sets = net_input.size()/net_topology[0].neuron_layer.size(); // amount of input data / number of inputs (how many sets of data to feedforward)   
    double num_of_inputs = net_topology[0].neuron_layer.size();

    for(int m = 0; m < num_data_sets ; m++){ // iterate through each individual input data set

        curr_input = {net_input.begin()+m*num_of_inputs,net_input.begin()+m*num_of_inputs+num_of_inputs}; // get the current data set to forward

        /// **** Forwarding data through input layer ****
        for(int k = 0; k < curr_input.size(); k++){ // forwarding data through input layer
            net_topology[0].neuron_layer[k].forwardData(curr_input[k]); // forward data through each neuron in layer 0
        }

        /// **** Forwarding data through hidden layers ****
        for(int i = 1; i < net_topology.size(); i++){ // iterate through each network layers

            for(int j = 0; j < net_topology[i].neuron_layer.size(); j++){  // iterate through neurons in layer
                
                input_val = net_topology[i-1].neuron_layer[j].getOutput();
                new_input_vector.push_back(input_val); // get output from each neuron and store in input_vector 
            }
            
            for(int l = 0; l < net_topology[i].neuron_layer.size(); l++){  // iterate through neurons in layers
                net_topology[i].neuron_layer[l].forwardData(new_input_vector); // forward data through neuron using new_input_vector

                if(i == net_topology.size() -1) net_output.push_back(net_topology[i].neuron_layer[l].getOutput()); // if iterating through output layer, push data into net_output
            }
            new_input_vector.clear(); // resetting vector for next layer pass
        }
    }
}

vector<double> Network::getNetOutput() // returns the output of the output layer in a vector 
{
    return net_output;
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