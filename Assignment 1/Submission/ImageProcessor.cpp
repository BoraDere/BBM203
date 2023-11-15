#include "ImageProcessor.h"
#include "EdgeDetector.h"
#include "DecodeMessage.h"
#include "EncodeMessage.h"

std::vector<std::pair<int, int>> edgePixels;

ImageProcessor::ImageProcessor() {
    // Default constructor (if any)
}

ImageProcessor::~ImageProcessor() {
    // Destructor (if any cleanup is needed)
}

std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageSharpening sharpener;
    ImageMatrix sharpenedImage = sharpener.sharpen(img, 2);
    
    EdgeDetector edgeDetector;
    std::vector<std::pair<int, int>> edgePixels = edgeDetector.detectEdges(sharpenedImage);

    DecodeMessage decoder;
    std::string message = decoder.decodeFromImage(sharpenedImage, edgePixels);

    return message;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    EncodeMessage encoder;
    ImageMatrix encodedImage = encoder.encodeMessageToImage(img, message, edgePixels);

    return encodedImage;
}
