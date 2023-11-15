#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <utility> 

#include "ImageMatrix.h"
#include "Convolution.h"
#include "DecodeMessage.h"
#include "EncodeMessage.h"
#include "ImageSharpening.h"
#include "EdgeDetector.h"
#include "ImageProcessor.h"

void main(){

    // Create a matrix directly using direct initialization
    const double* directData1[3] = {
        new double[3]{1.0, 2.0, 3.0},
        new double[3]{4.0, 5.0, 6.0},
        new double[3]{7.0, 8.0, 9.0}
    };

    ImageMatrix matrix1(directData1, 3, 3);

}
