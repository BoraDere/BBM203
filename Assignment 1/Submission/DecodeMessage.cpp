// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>
#include <cmath>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string message = ""; std::string bString = "";

    for (const std::pair<int, int>& pixel : edgePixels) {
        int x = pixel.first;
        int y = pixel.second;

        int height = image.get_height();
        int width = image.get_width();

        if (x >= 0 && x < height && y >= 0 && y < width) {
            double data = image.get_data(x, y);
            int lsb = static_cast<int>(std::fmod(data, 2.0)); // since binary, fmod of 2.0 will give us the lsb
            bString += std::to_string(lsb);
        } 
    }

    while (bString.length() % 7 != 0) { // padding with 0
        bString = "0" + bString; 
    }

    for (int i = 0; i < bString.length(); i += 7) { // kinda grouping by 7
        std::string b = bString.substr(i, 7);
        int ascii = std::stoi(b, nullptr, 2);
        
        if (ascii <= 32) {
            ascii += 33;
        } 
        else if (ascii >= 127) {
            ascii = 126;
        }
        
        message += static_cast<char>(ascii);
    }

    return message;
}
