#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <ctime>

using namespace cv;
using namespace std;

class ImageBinarization{
public:
    size_t ReadImage(string path, bool show);
    void AlgorithmBradley();
    void CreateResult(bool show);
private:
    string pathInputImage;
    Mat inputImage;
    Mat resultImage;

    double convertToGray(double R, double G, double B);
};