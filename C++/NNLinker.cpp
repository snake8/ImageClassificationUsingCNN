//
//  NNLinker.cpp
//  ImageClassificationNN
//
//  Created by Daniel Solovich on 1/19/18.
//  Copyright © 2018 Daniel Solovich. All rights reserved.
//

#include "NNLinker.hpp"
#include "DataFromNNHandle.hpp" 
#include <thread>

int getNeuralNetResult(const char* filename)
{
    NeuralNetwork nn = NeuralNetwork(784, 200, 10,  .1);
    return getNeuralNetworkGues(&nn, filename);    
}


void trainOnDefault(unsigned int nepoches)
{
    std::string pathToData = "/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/mnist_train_100.csv";
    NeuralNetwork nn = NeuralNetwork(784, 200, 10, .1);
    
    std::thread* threads = new std::thread[3];
    
    threads[0] = std::thread(&trainNetwork,
                             &nn,
                             nepoches / 3,
                             pathToData);
    
    threads[1] = std::thread(&trainNetwork,
                             &nn,
                             nepoches / 3,
                             pathToData);
    
    threads[2] = std::thread(&trainNetwork,
                             &nn,
                             nepoches / 3,
                             pathToData);

    if (threads[0].joinable() &&
        threads[1].joinable() &&
        threads[2].joinable())
    {
        threads[0].join();
        threads[1].join();
        threads[2].join();
    }
    
    delete[] threads;
    
}

void trainOnUserDataset(unsigned int nepoches)
{
    std::string pathToData = "/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/user_dataset.csv";
    NeuralNetwork nn = NeuralNetwork(784, 200, 10, .1);
    
    std::thread* threads = new std::thread[3];
    
    threads[0] = std::thread(&trainNetwork,
                             &nn,
                             nepoches / 3,
                             pathToData);
    
    threads[1] = std::thread(&trainNetwork,
                             &nn,
                             nepoches / 3,
                             pathToData);
    
    threads[2] = std::thread(&trainNetwork,
                             &nn,
                             nepoches / 3,
                             pathToData);
    
    if (threads[0].joinable() &&
        threads[1].joinable() &&
        threads[2].joinable())
    {
        threads[0].join();
        threads[1].join();
        threads[2].join();
    }
    
    delete[] threads;
}


void putImageInDataset(const char* path, int label)
{
    createDataset(path, label);
}




#include <mach-o/dyld.h>
void printRelativePath()
{
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0)
        printf("executable path is %s\n", path);
    else
        printf("buffer too small; need size %u\n", size);
}





















