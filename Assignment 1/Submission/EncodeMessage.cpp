#include "EncodeMessage.h"
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>


// Default Constructor
EncodeMessage::EncodeMessage() {
    
}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

bool isPrime(double n) {
    if (n == 0 || n == 1) {
        return false;
    }
    else if (n == 2) {
        return true;
    }
    else if (static_cast<int>(n) % 2 == 0) {
        return false;
    }
    else {
        for (int i = 3; i <= static_cast<int>(n)/2; i++) {
            if (static_cast<int>(n) % i == 0) {
                return false;
            }
        }
        return true;
    }

}

double fibonacci(double n) {
    
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
    
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix& img, const std::string& message, const std::vector<std::pair<int, int>>& positions) {
    ImageMatrix encoded_image = img;
    std::string text = message;
    int size = text.length();
    int index = 0;
    double vals[size];
    double results[size];
    int shift = static_cast<int>((size)/2);

    for (const std::pair<int, int>& position : positions) { // ÇIKMIYOR NEDENNN ???!?!!?!?!?! KONTROL ETTT
        int x = position.first;
        int y = position.second;

        if (!text.empty()) {
            char messageChar = text[0];

            double val = static_cast<double>(messageChar);

            if (isPrime(index)) {
                val += fibonacci(index);
            }

            if (val <= 32) {
                val += 33;
            }
            else if (val >= 127) {
                val = 126;
            }

            vals[index] = val;

            text = text.substr(1);
            index++;
        }
    }

    // I have checked, this way of shifting works but for some reason, sample main.cpp seems to be expecting a different result
    // I have tried different ways but none of them made a change.
    for (int i = 0; i < shift; i++) {
        results[shift - i - 1] = vals[size - i - 1];
    }

    for (int i = 0; i < size - shift; i++) {
        results[i + shift] = vals[i];
    }

    index = 0;

     for (const std::pair<int, int>& position : positions) {
        int x = position.first;
        int y = position.second;

        encoded_image.set_data(x, y, results[index]);
        index++;
    }

    return encoded_image;
}
