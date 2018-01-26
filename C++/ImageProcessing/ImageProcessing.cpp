//
//  ImageProcessing.cpp
//  RNN
//
//  Created by Daniel Solovich on 1/2/18.
//  Copyright © 2018 Daniel Solovich. All rights reserved.
//

#include "ImageProcessing.hpp"

ImageProcessing::ImageProcessing(const cv::String &pathToImage) :
    m_path(pathToImage)
{
    m_image = cv::imread(pathToImage);
    if (m_image.empty()) throw FileNotFoundException();
}

void ImageProcessing::showImage()
{
    try
    {
        if (m_image.data)
        {
            cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
            cv::imshow("Display window", m_image);
            cv::waitKey(0);
        }
        else throw ImageHasNoData();
    }
    catch (ImageHasNoData& e)
    {
        std::cout << e.backtrace << std::endl;
        std::cout << e.getError() << std::endl;
        exit(1);
    }
}

void ImageProcessing::remove()
{
    std::remove(m_path.c_str());
}



std::vector<double> ImageProcessing::getPixelVector()
{
    std::vector<double> pixelVector;
    pixelVector.reserve(m_image.rows * m_image.cols);
    for (int i = 0; i < m_image.rows; i++)
    {
        for (int j = 0; j < m_image.cols; j++)
        {
            cv::Vec3b intensity = m_image.at<cv::Vec3b>(static_cast<int>(i), static_cast<int>(j));
            double  blue = (double)intensity.val[0];
            double green = (double)intensity.val[1];
            double red = (double)intensity.val[2];
            pixelVector.emplace_back(blue + green + red);
        }
    }
    return pixelVector;
}

Matrix<double> ImageProcessing::getPixelMatrix()
{
    Matrix<double> pixelMatrix(m_image.rows, m_image.cols);
    for (size_t i = 0; i < pixelMatrix.size1(); i++)
    {
        for (size_t j = 0; j < pixelMatrix.size2(); j++)
        {
            cv::Vec3b intensity = m_image.at<cv::Vec3b>(static_cast<int>(i), static_cast<int>(j));
            double  blue = (double)intensity.val[0];
            double green = (double)intensity.val[1];
            double red = (double)intensity.val[2];
            pixelMatrix(i, j) = (blue + green + red) / 3;
        }
    }
    return pixelMatrix; 
}





