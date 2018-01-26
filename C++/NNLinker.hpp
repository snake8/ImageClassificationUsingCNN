//
//  NNLinker.hpp
//  ImageClassificationNN
//
//  Created by Daniel Solovich on 1/19/18.
//  Copyright © 2018 Daniel Solovich. All rights reserved.
//

#ifndef NNLinker_hpp
#define NNLinker_hpp

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif
    
     
    int getNeuralNetResult(const char* filename);
    
    void putImageInDataset(const char* path, int label);
    void trainOnDefault(unsigned int nepoches);
    void trainOnUserDataset(unsigned int nepoches);
    
    void printRelativePath(); 
    
    
#ifdef __cplusplus
}
#endif


#endif /* NNLinker_hpp */
