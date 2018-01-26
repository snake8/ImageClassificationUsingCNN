//
//  DataFromNNHandle.cpp
//  RNN
//
//  Created by Daniel Solovich on 12/18/17.
//  Copyright © 2017 Daniel Solovich. All rights reserved.
//

#include "DataFromNNHandle.hpp"
#include <thread>



static std::mutex mtx;


static Matrix<double>* scaleMatrixForTrainingOnDefaultDataset(Matrix<double>& matrixForScaling, size_t row)
{
    Matrix<double>* scaledMatrix = new Matrix<double>(1, matrixForScaling.size2());
    for (size_t i = 0;
         i < matrixForScaling.size2();
         i++)
        (*scaledMatrix)(0, i) = (matrixForScaling(row, i) / 255.0 * .99) + .01;
    scaledMatrix->removeRow(0);
    return scaledMatrix;
}



static void saveWeights(Weights& weights)
{
    FileProcessing::writeDataInFile(&weights.wih, "/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memoryFirst.csv", false);
    FileProcessing::writeDataInFile(&weights.who, "/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memorySecond.csv", false);
}


void trainNetwork(NeuralNetwork* nn, unsigned int epoches, std::string pathToTrainData)
{
    Matrix<double> allTrainData = FileProcessing::readDataFromFile(pathToTrainData.c_str()), targets(10, 1);
    targets = .01;
    Weights weights;
    for (unsigned int i = 0;
         i < epoches;
         i++)
    {
        mtx.lock();
        std::cout << "--------------------------------------------------------" << std::endl;
        std::cout << "Call form thread: " << std::this_thread::get_id() << std::endl;
        std::cout << "--------------------------------------------------------" << std::endl;
        std::cout << "Train started." << " left: " << epoches - i << std::endl;
        mtx.unlock();
        for (size_t j = 0;
             j < allTrainData.size1();
             j++)
        {
            targets(allTrainData(j, 0), 0) = .99;
            Matrix<double>* trainInputs = scaleMatrixForTrainingOnDefaultDataset(allTrainData, j);
            weights = nn->train(*trainInputs, targets);
            delete trainInputs;
        }
        
        mtx.lock();
        std::cout << "Cycle number: " << i + 1 << ", from: " << epoches << std::endl;
        mtx.unlock();
        
    }
    saveWeights(weights);
}



void writeDataFromImageInFile(const char* pathToImage)
{
    ImageProcessing image((cv::String(pathToImage)));
    const std::vector<double> pixelVector = image.getPixelVector();
    Matrix<double> dataFromImage;
    dataFromImage.insertVector(pixelVector);
    FileProcessing::writeDataInFile(&dataFromImage, "/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/user_numbers.csv", false);
}



static void scaleDataFromImage(Matrix<double>* const dataFromImage)
{
    for (size_t i = 0;
         i < dataFromImage->size1();
         i++)
    {
        for (size_t j = 0;
             j < dataFromImage->size2();
             j++)
            (*dataFromImage)(i, j) = (*dataFromImage)(i, j) / 255.0 * .99 + .01;
    }
}

int getNeuralNetworkGues(NeuralNetwork* nn, const char* filename)
{
    try
    {
        writeDataFromImageInFile(filename);
    }
    catch (FileNotFoundException& e)
    {
        std::cout << e.backtrace << std::endl; 
        return 404;
    }
    Matrix<double> dataFromImage = FileProcessing::readDataFromFile("/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/user_numbers.csv");
    scaleDataFromImage(&dataFromImage);
    Matrix<double> neuralNetworkResult = nn->query(dataFromImage);    
    return static_cast<int>(neuralNetworkResult.getStringIndexWithMaxValue());
}



void createDataset(const char* pathToImage, int label)
{
    ImageProcessing image((cv::String(pathToImage))); 
    std::vector<double> pixelVector = image.getPixelVector();
    pixelVector.insert(pixelVector.begin(), label);
    Matrix<double> pixelMatrix; 
    pixelMatrix.insertVector(pixelVector); 
    FileProcessing::writeDataInFile(&pixelMatrix, "/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/user_dataset.csv"); 
}


