#include <iostream>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution() {
    kernel = new double*[3];
    stride = 1;
    padding = false;
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){
    kernel = new double*[kh];
    for (int i = 0; i < kh; i++) {
        kernel[i] = new double[kw];
        for (int j = 0; j < kw; j++) {
            kernel[i][j] = customKernel[i][j];
        }
    }
    kernelHeight = kh;
    kernelWidth = kw;
    stride = stride_val;
    padding = pad;
}

// Destructor
Convolution::~Convolution() {
    for (int i = 0; i < kernelHeight; i++) {
        delete[] kernel[i];
    }
    delete[] kernel;
}

// Copy constructor
// I actually am not sure about the copy constructor and the copy assignment operator. 
// I did a bit of research and could not fully understand the concept, that is what I could do.
Convolution::Convolution(const Convolution &other){
    for (int i = 0; i < 3; i++) {
        kernel[i] = new double[3];
        for (int j = 0; j < 3; j++) {
            kernel[i][j] = other.kernel[i][j];
        }
    }

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this; 
    }

    if (kernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }

    for (int i = 0; i < 3; i++) {
        kernel[i] = new double[3];
        for (int j = 0; j < 3; j++) {
            kernel[i][j] = other.kernel[i][j];
        }
    }

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;

    return *this;

}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {

    int inputHeight = input_image.get_height(); int inputWidth = input_image.get_width();
    int p = padding ? 1 : 0;
    int outputHeight = ((inputHeight - kernelHeight + 2*p) / stride) + 1; int outputWidth = ((inputWidth - kernelWidth + 2*p) / stride) + 1; // these are OK

    ImageMatrix output_image(outputHeight, outputWidth);

    for (int i = 0; i < outputHeight; i++) {
        for (int j = 0; j < outputWidth; j++) {
            double sum = 0;
            for (int k = 0; k < kernelHeight; k++) {
                for (int l = 0; l < kernelWidth; l++) {
                    int x = i*stride + k - p;
                    int y = j*stride + l - p;
                    if (x >= 0 && x < inputHeight && y >= 0 && y < inputWidth) { // CROSSES THE BOUNDS !!!!! WHY ???
                        sum += input_image.get_data(x, y) * kernel[k][l];
                    }
                }
            }
            output_image.set_data(i, j, sum); // 0 1 2 OK
        }
    }

    return output_image;
}
