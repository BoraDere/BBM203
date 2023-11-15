#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    blurring_kernel = new double*[3];
    for (int i = 0; i < 3; i++) {
        blurring_kernel[i] = new double[3];
    }

    blurring_kernel[0][0] = 1.0 / 9.0; blurring_kernel[0][1] = 1.0 / 9.0; blurring_kernel[0][2] = 1.0 / 9.0;
    blurring_kernel[1][0] = 1.0 / 9.0; blurring_kernel[1][1] = 1.0 / 9.0; blurring_kernel[1][2] = 1.0 / 9.0;
    blurring_kernel[2][0] = 1.0 / 9.0; blurring_kernel[2][1] = 1.0 / 9.0; blurring_kernel[2][2] = 1.0 / 9.0;

}

ImageSharpening::~ImageSharpening(){
    for (int i = 0; i < 3; i++) {
        delete[] blurring_kernel[i];
    }
    delete[] blurring_kernel;
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    int height = input_image.get_height(); int width = input_image.get_width();
    
    ImageMatrix output_image(height, width);
    Convolution convolver(blurring_kernel, 3, 3, 1, true);
    ImageMatrix blurred_image = convolver.convolve(input_image);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double input_data = input_image.get_data(i, j);
            double blurred_data = blurred_image.get_data(i, j);
            double sharpened_data = input_data + k * (input_data - blurred_data);
            output_image.set_data(i, j, sharpened_data);
        }
    }

    return output_image;
}
