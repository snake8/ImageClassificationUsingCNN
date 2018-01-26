//
//  ImageProcessing.hpp
//  RNN
//
//  Created by Daniel Solovich on 1/2/18.
//  Copyright © 2018 Daniel Solovich. All rights reserved.
//

#ifndef ImageProcessing_hpp
#define ImageProcessing_hpp



#include <stdio.h>
#include "IExceptions.h"
#include "../Matrix/Matrix.h"
#include "Loger.h" 
#include <opencv2/opencv.hpp>


class ImageProcessing {
private:
    const cv::String m_path;
    cv::Mat m_image;
public:
    ImageProcessing(const cv::String& pathToImage);
    void showImage();
    void remove();
    std::vector<double> getPixelVector();
    Matrix<double> getPixelMatrix();
};


#endif /* ImageProcessing_hpp */
