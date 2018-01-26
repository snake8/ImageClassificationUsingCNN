//
//  Memory.cpp
//  RNN
//
//  Created by Daniel Solovich on 12/16/17.
//  Copyright © 2017 Daniel Solovich. All rights reserved.
//

#include "Memory.hpp"



void Memory::putMemoryInBackup()
{
    Matrix<double> firstLayerMemory, secondLayerMemory;
    firstLayerMemory = FileProcessing::readDataFromFile("/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memoryFirst.csv");
    secondLayerMemory = FileProcessing::readDataFromFile("/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memorySecond.csv");
    FileProcessing::writeDataInFile(&firstLayerMemory, "/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memoryFirstBackup.csv", false);
    FileProcessing::writeDataInFile(&secondLayerMemory,"/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memorySecondBackup.csv", false);
}

void Memory::makebackup()
{
    Matrix<double> memoryFromFirstLayerBackup, memoryFromSecondLayerBackup;
    memoryFromFirstLayerBackup = FileProcessing::readDataFromFile("/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memoryFirstBackup.csv");
    memoryFromSecondLayerBackup = FileProcessing::readDataFromFile("/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memorySecondBackup.csv");
    FileProcessing::writeDataInFile(&memoryFromFirstLayerBackup, "/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memoryFirst.csv", false);
    FileProcessing::writeDataInFile(&memoryFromSecondLayerBackup, "/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memorySecond.csv", false);
}

