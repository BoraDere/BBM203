// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {
    Gx = new double*[3];
    Gy = new double*[3];

    for (int i = 0; i < 3; i++) {
        Gx[i] = new double[3];
        Gy[i] = new double[3];
    }

    // Sobel operators
    Gx[0][0] = -1; Gx[0][1] = 0; Gx[0][2] = 1;
    Gx[1][0] = -2; Gx[1][1] = 0; Gx[1][2] = 2;
    Gx[2][0] = -1; Gx[2][1] = 0; Gx[2][2] = 1;

    Gy[0][0] = -1; Gy[0][1] = -2; Gy[0][2] = -1;
    Gy[1][0] = 0; Gy[1][1] = 0; Gy[1][2] = 0;
    Gy[2][0] = 1; Gy[2][1] = 2; Gy[2][2] = 1;
}

// Destructor
EdgeDetector::~EdgeDetector() {
    for (int i = 0; i < 3; i++) {
        delete[] Gx[i];
        delete[] Gy[i];
    }
    delete[] Gx;
    delete[] Gy;
}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    std::vector<std::pair<int, int>> edge_pixels;
    
    Convolution xConvolver(Gx, 3, 3, 1, true); Convolution yConvolver(Gy, 3, 3, 1, true);

    ImageMatrix convolved_x = xConvolver.convolve(input_image); ImageMatrix convolved_y = yConvolver.convolve(input_image);

    int height = input_image.get_height(); int width = input_image.get_width();

    // kinda spaghetti code
    double threshold = 0.0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            threshold += std::sqrt(convolved_x.get_data(i, j) * convolved_x.get_data(i, j) + convolved_y.get_data(i, j) * convolved_y.get_data(i, j))/(height * width);
        }
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = convolved_x.get_data(i, j); double y = convolved_y.get_data(i, j);
            double value = std::sqrt(x*x + y*y);

            if (value > threshold) {
                edge_pixels.push_back(std::make_pair(i, j));
            }
        }
    }

    return edge_pixels;
}

