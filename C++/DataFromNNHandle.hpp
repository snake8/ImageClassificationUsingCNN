//
//  DataFromNNHandle.hpp
//  RNN
//
//  Created by Daniel Solovich on 12/18/17.
//  Copyright © 2017 Daniel Solovich. All rights reserved.
//

#ifndef DataFromNNHandle_hpp
#define DataFromNNHandle_hpp

#define DEBUGE_MODE 1

#if DEBUGE_MODE == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif 


#include <stdio.h>
#include "NN.hpp"
#include "Memory.hpp"
#include "ImageProcessing.hpp"


void trainNetwork(NeuralNetwork* nn, unsigned int epoches, std::string pathToTrainData);
void writeDataFromImageInFile(const char* pathToImage);
void createDataset(const char* pathToImage, int label);

int getNeuralNetworkGues(NeuralNetwork* nn, const char* filename);


#endif /* DataFromNNHandle_hpp */
