#include "network.hpp"

Network::Network(vector<int> &layer_sizes)
{
    Layer l; // struct of Layer type

    net_topology.push_back(l);
    /// **** setting up input layer neurons ****
    for(int k = 0; k < layer_sizes[0]; k++) // add first layer with only one input in each neuron
        net_topology[0].neuron_layer.push_back(1);

    /// **** setting up hidden layer neurons ****
    for(int i = 1; i < layer_sizes.size(); i++ ){ // iterating through desired layers
                                                 // adding layers based off number of outputs in previous layer

        net_topology.push_back(l);  // addign new layer to network topology vector

        for(int j = 0; j < layer_sizes[i]; j++){ // adding number of required neurons to the layer
            
            net_topology[i].neuron_layer.push_back(layer_sizes[i-1]); // add neuron  to with number of inputs which corresponds to number of neurons in previous layer     
        }
    }
}

Network::~Network()
{
}

void Network::feedForward(vector<double> &net_input) // feedForwarding data through network
{
    vector<double> curr_input; // vector to store inputs as data feeds through the network
    
    Layer *prev_layer; // Pointers to point at layers when iterating through them
    Layer *curr_layer; // this is done to clean up the notation

    double num_data_sets = net_input.size()/net_topology[0].neuron_layer.size(); // amount of input data / number of inputs (how many sets of data to feedforward)   
    double num_of_inputs = net_topology[0].neuron_layer.size(); // how many inputers in input layer

    for(int m = 0; m < num_data_sets ; m++){ // iterate through each individual input data set

        curr_input = {net_input.begin()+m*num_of_inputs,net_input.begin()+m*num_of_inputs+num_of_inputs}; // get the current data set to forward through network

        /// **** Forwarding data through input layer ****
        for(int k = 0; k < curr_input.size(); k++) // forwarding data through input layer
            net_topology[0].neuron_layer[k].forwardData(curr_input[k]); // forward data through each neuron in layer 0 (input layer)
        
        curr_input.clear(); // resetting vector for hidden layer passes

        /// **** Forwarding data through hidden layers ****
        for(int i = 1; i < net_topology.size(); i++){ // iterate through each network layers

            prev_layer = &net_topology[i-1]; // setting pointers to point at selected current and previous layers
            curr_layer = &net_topology[i];

            for(int j = 0; j < curr_layer->neuron_layer.size(); j++){  // iterate through neurons in layer
                
                curr_input.push_back( prev_layer->neuron_layer[j].getOutput()); // get output from each preceding neuron and store in curr_input 
            }
            
            for(int l = 0; l < curr_layer->neuron_layer.size(); l++){  // iterate through neurons in layers

                curr_layer->neuron_layer[l].forwardData(curr_input); // forward data through neuron using inputs from curr_input

                if(i == net_topology.size() -1) net_output.push_back(curr_layer->neuron_layer[l].getOutput()); // if iterating through output layer, push data into net_output
            }
            curr_input.clear(); // resetting vector for next layer pass
        }
    }
}

void Network::propBack(vector<double> &target_results)
{
    vector<double> output_gradient;

    Layer *output_layer = &net_topology.back(); // pointer to output layer for easier notation

    int num_of_outputs = net_topology.back().neuron_layer.size(); // int to store number of output neurons
    int error_val = 0; // int to store erro val before pushing into curr_error vector

    double output_sum = 0.0; // double to store sum of output gradiants 

    for (int i = 0; i < target_results.size(); i++){ // calculating gradient within neuron
        output_gradient.push_back(calcOutputGrad(target_results[i], i%num_of_outputs)); // acumulating all the gradients from the output layer
    }

}

double Network::calcOutputGrad(double expected, int neuron_num)
{
    Layer *output_layer = net_topology.back(); // output layer

    double actual = output_layer->neuron_layer[neuron_num].getOutput(); // getting output from neuron

    // error = (expected result - actual result)*transferderivative(actual result)
    return (expected-actual)*output_layer->neuron_layer[neuron_num].activationDerivative(actual);
}

double Network::calcHiddenGrad(double &expected, double &actual, int layer_num, int neuron_num)
{
    // error = (expected result - actual result)*transferderivative(actual result)
    return (expected-actual)*net_topology[layer_num].neuron_layer[neuron_num].activationDerivative(actual);
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