//
//  DataHandler.cpp
//  RNN
//
//  Created by Daniel Solovich on 12/12/17.
//  Copyright © 2017 Daniel Solovich. All rights reserved.
//

#include "DataHandler.hpp"


void FileProcessing::writeDataInFile(Matrix<double>* mat, const char* path, bool savePrevius)  
{
    try 
    {
        std::ofstream file;
        if (savePrevius)
            file = std::ofstream(path, std::ios_base::app);
        else  
            file = std::ofstream(path);
        if (file.is_open()) 
        {
            for (size_t i = 0;
                 i < mat->size1();
                 i++)
            {
                std::string line; 
                for (size_t j = 0;
                     j < mat->size2();
                     j++)
                {
                    auto charInData = std::to_string((*mat)(i, j)); 
                    line += !j ? charInData : "," + charInData;
                }
                file << line << std::endl; 
            }
        } 
        else  
            throw FileNotFoundException(); 
    }
    catch (FileNotFoundException& e) 
    {
        std::cout << e.backtrace << std::endl; 
        std::cout << e.getError() << std::endl; 
        exit(1); 
    }
}


Matrix<double> FileProcessing::readDataFromFile(const char* path) 
{
    try 
    {
        Matrix<double> matrixWithData;
        std::vector<std::vector<double>> vec;
        std::ifstream file;
        file.open(path);
        if (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                std::istringstream split(line);
                double value;
                char sep;
                std::vector<double> nexRow;
                while (split >> value)
                {
                    nexRow.push_back(value);
                    split >> sep;
                }
                vec.push_back(nexRow);
            }
            file.close();
        } else
            throw FileNotFoundException();
        
        if (!vec.size())
            return matrixWithData;
        
        matrixWithData.resizeMatrix(vec.size(), vec[0].size());
        for (size_t rows = 0;
             rows < matrixWithData.size1();
             rows++)
        {
            for (size_t cols = 0;
                 cols < matrixWithData.size2();
                 cols++)
                matrixWithData(rows, cols) = vec[rows][cols];
        }
        return matrixWithData;
    }
    catch (FileNotFoundException& e) 
    {
        std::cout << e.backtrace << std::endl; 
        std::cout << e.getError() << std::endl; 
        exit(1); 
    }
}
