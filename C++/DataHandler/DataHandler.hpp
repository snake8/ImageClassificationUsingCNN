//  DataHandler.hpp
//  RNN
//
//  Created by Daniel Solovich on 12/12/17.
//  Copyright © 2017 Daniel Solovich. All rights reserved.
//






#ifndef DataHandler_hpp
#define DataHandler_hpp

#include <stdio.h>
#include <fstream>
#include "Matrix.h"
#include "IExceptions.h"




namespace FileProcessing 
{

    void writeDataInFile(Matrix<double>* mat, const char* path, bool savePrevius = true); 
    Matrix<double> readDataFromFile(const char* path); 

}




#endif /* DataHandler_hpp */
