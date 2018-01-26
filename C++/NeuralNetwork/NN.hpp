//
//  NN.hpp
//  NeuralNetworkCPP
//
//  Created by Daniel Solovich on 9/25/17.
//  Copyright © 2017 Daniel Solovich. All rights reserved.
//

#ifndef NN_hpp
#define NN_hpp
#include <stdio.h>
#include "../Matrix/Matrix.h"
#include "../Data/MemoryControll/Memory.hpp" 


#define DEBUGE_MODE 1

#if DEBUGE_MODE == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x) 
#endif


struct Weights
{
    Matrix<double> wih, who; 
};

struct Outputs
{
    Matrix<double> hiddenInputs, hiddenOutputs, finalInputs, finalOutputs;
}; 


class NeuralNetwork
{
private:
    const size_t inputNeurons, hiddenNeurons, outputNeurons;
    const float lr;
    
    
    // + 1 is a bias
    Matrix<double> wih = {hiddenNeurons, inputNeurons + 1};
    Matrix<double> who = {outputNeurons, hiddenNeurons + 1};
    
    Matrix<double> bias_h = Matrix<double>(hiddenNeurons, 1);
    Matrix<double> bias_o = Matrix<double>(outputNeurons, 1);
private:
    static Matrix<double> sigmoidFunction(Matrix<double>& matrix);
    static void updateWeight(Matrix<double>&, Matrix<double>&, Matrix<double>&, Matrix<double>&, const float);
    static Matrix<double> addMatrices(Matrix<double> &mat1, Matrix<double> mat2);
private:
    Outputs calculateOutputs(Matrix<double>&);
public:
    NeuralNetwork() = default;
    NeuralNetwork(size_t, size_t, size_t, float);
    ~NeuralNetwork();
public:
    Weights train(Matrix<double> &inputs, Matrix<double> &targets);
    Matrix<double> query(Matrix<double>& query);
};



#endif /* NN_hpp */


