#ifndef LAYER_H
#define LAYER_H

#include <vector>

#include "neuron.hpp"

struct Layer // structure used to make vector matrix syntax cleaner
{
    std::vector<Neuron> neuron_layer; 
};

#endif