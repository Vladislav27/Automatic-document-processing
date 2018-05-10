#include "ImageBinarization.h"

#define SIZE_AREA 16
#define T 0.15

double ImageBinarization::convertToGray(double R, double G, double B) {
    return 0.2125 * R + 0.7154 * G + 0.0721 * B;
}

size_t ImageBinarization::ReadImage(string path, bool show) {
    pathInputImage = path;
    inputImage = imread(pathInputImage, CV_LOAD_IMAGE_COLOR);
    if(inputImage.empty()) {
        cout <<  "Could not open or find the image" << std::endl;
        exit(-1);
    }

    resultImage = inputImage;

    if (show) {
        namedWindow("Display window", WINDOW_AUTOSIZE);
        imshow("Display window", inputImage);
        waitKey(0);
    }

    return inputImage.total() / 1000000;
}

void ImageBinarization::AlgorithmBradley() {
    int width = inputImage.size().width;
    int height = inputImage.size().height;

    int* integral_image = new int [width * height * sizeof(int)];

    int sum = 0;
    int index;

    for (int i = 0; i < width; i++) {
        sum = 0;
        for (int j = 0; j < height; j++) {
            Vec3b colour = inputImage.at<Vec3b>(j, i);

            sum += convertToGray(colour.val[0], colour.val[1], colour.val[2]);
            index = j * width + i;
            if (i == 0) {
                integral_image[index] = sum;
            }
            else {
                integral_image[index] = integral_image[index - 1] + sum;
            }
        }
    }

    int size = width / SIZE_AREA;
    int count = 0;
    int x1, y1, x2, y2;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            x1 = i - size;
            x2 = i + size;
            y1 = j - size;
            y2 = j + size;

            if (x1 < 0) {
                x1 = 0;
            }
            if (x2 >= width) {
                x2 = width - 1;
            }
            if (y1 < 0) {
                y1 = 0;
            }
            if (y2 >= height) {
                y2 = height - 1;
            }

            count = (x2 - x1) * (y2 - y1);

            sum = integral_image[y2 * width + x2] - integral_image[y1 * width + x2] -
                  integral_image[y2 * width + x1] + integral_image[y1 * width + x1];

            Vec3b colour = inputImage.at<Vec3b>(j, i);
            if (convertToGray(colour.val[0], colour.val[1], colour.val[2]) * count < sum * (1.0 - T)) {
                resultImage.at<Vec3b>(j, i)[0] = 0;
                resultImage.at<Vec3b>(j, i)[1] = 0;
                resultImage.at<Vec3b>(j, i)[2] = 0;
            }
            else {
                resultImage.at<Vec3b>(j, i)[0] = 255;
                resultImage.at<Vec3b>(j, i)[1] = 255;
                resultImage.at<Vec3b>(j, i)[2] = 255;
            }
        }
    }

    delete[] integral_image;
}

void ImageBinarization::CreateResult(bool show) {
    string pathResultImage;
    for(size_t i = 0; i < pathInputImage.size() - 4; i++) {
        pathResultImage += pathInputImage[i];
    }
    pathResultImage += "_result.jpg";
    imwrite(pathResultImage, resultImage);

    if (show) {
        namedWindow("Display window2", WINDOW_AUTOSIZE);
        imshow("Display window2", resultImage);
        waitKey(0);
    }
}