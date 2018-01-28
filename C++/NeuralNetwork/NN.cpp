#include "NN.hpp"





NeuralNetwork::NeuralNetwork(const size_t input, const size_t hidden, const size_t output, const float lr) :
    inputNeurons(input), hiddenNeurons(hidden), outputNeurons(output), lr(lr)
    {
        wih = FileProcessing::readDataFromFile("/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memoryFirst.csv");
        who = FileProcessing::readDataFromFile("/Users/libowski/Documents/Handwritings/ImageClassificationNN/C++/Data/memorySecond.csv");
        if (!wih || !who)
        {
            wih.resizeMatrix(hiddenNeurons, inputNeurons);
            who.resizeMatrix(outputNeurons, hiddenNeurons);
            
            Matrix<double>::generateRandomMatrixFromMatrix(wih,
                                                           (double)-pow(hiddenNeurons, -.5),
                                                           (double)pow(hiddenNeurons, -.5));
            Matrix<double>::generateRandomMatrixFromMatrix(who,
                                                           (double)-pow(hiddenNeurons, -.5),
                                                           (double)pow(hiddenNeurons, -.5));
        }
    }

NeuralNetwork::~NeuralNetwork()
{
}


Weights NeuralNetwork::train(Matrix<double> &inputs, Matrix<double> &targets)
{
    
    Outputs outputs = calculateOutputs(inputs);
    
    // Calculatign errors
    Matrix<double> outputError = Matrix<double>::min(targets, outputs.finalOutputs);
    Matrix<double> t_who = Matrix<double>::transpose(who);
    Matrix<double> hiddenError = Matrix<double>::getdot(t_who, outputError);
    Matrix<double> t_hiddenOutputs = Matrix<double>::transpose(outputs.hiddenOutputs);
    
    
    // updating weights
    updateWeight(who,
                 t_hiddenOutputs,
                 outputs.finalOutputs,
                 outputError,
                 lr);
    
    updateWeight(wih,
                 inputs,
                 outputs.hiddenOutputs,
                 hiddenError,
                 lr);
    
    return Weights { wih, who };
}


void NeuralNetwork::updateWeight(Matrix<double>& weight,
                                 Matrix<double>& input,
                                 Matrix<double>& output,
                                 Matrix<double>& error,
                                 const float lr)
{
    Matrix<double> outputError, dotProduct1;
    try
    {
        outputError = addMatrices(error, output);
        dotProduct1 = addMatrices(outputError, 1.0 - output);
    }
    catch (SizeError& e)
    {
        std::cout << e.backtrace << std::endl;
        std::cout << e.getError() << std::endl;
        exit(1);
    }
    
    Matrix<double> updateFor  = Matrix<double>::getdot(dotProduct1, input);
    
    for (size_t rows = 0;
         rows < weight.size1();
         rows++)
    {
        for (size_t cols = 0;
             cols < weight.size2();
             cols++)
            weight(rows, cols) += lr * updateFor(rows, cols);
    }
}

Matrix<double> NeuralNetwork::addMatrices(Matrix<double>& mat1, Matrix<double> mat2)
{
    if (mat1 == mat2)
    {
        Matrix<double> multResult = {mat1.size1(), mat2.size2()};
        for (size_t rows = 0;
             rows < mat1.size1();
             rows++)
        {
            for (size_t cols = 0;
                 cols < mat1.size2();
                  cols++)
                multResult(rows, cols) = mat1(rows, cols) * mat2(rows, cols);
        }
        return multResult;
    }
    throw SizeError();
}

Matrix<double> NeuralNetwork::query(Matrix<double>& query)
{
    Outputs outputs = calculateOutputs(query);
    return outputs.finalOutputs;
}



Outputs NeuralNetwork::calculateOutputs(Matrix<double> &inputs)
{
    Matrix<double> t_Inputs = Matrix<double>::transpose(inputs);
    Matrix<double> hiddenInputs = Matrix<double>::getdot(wih, t_Inputs);
    Matrix<double> hiddenOutputs = sigmoidFunction(hiddenInputs);
    Matrix<double> finalInputs = Matrix<double>::getdot(who, hiddenOutputs);
    Matrix<double> finalOutputs = sigmoidFunction(finalInputs);
    return Outputs {hiddenInputs, hiddenOutputs, finalInputs, finalOutputs};
}

Matrix<double> NeuralNetwork::sigmoidFunction(Matrix<double>& mat)
{
    Matrix<double> sigMat = Matrix<double>(mat.size1(), mat.size2());
    for (size_t rows = 0;
         rows < mat.size1();
         rows++)
    {
        for (size_t cols = 0;
             cols < mat.size2();
             cols++)
            sigMat(rows, cols) = 1 / (1 + exp(-mat(rows, cols)));
    }
    return sigMat;
}


