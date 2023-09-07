#include "grayscale.h"

#include <stdexcept>

void GrayscaleFilter::ApplyFilter(Image &image) const {

    static const double BLUE_CONST = 0.114;
    static const double GREEN_CONST = 0.587;
    static const double RED_CONST = 0.299;

    auto &image_channels = image.GetChannels();
    size_t height = image_channels[0].size();
    size_t width = image_channels[0][0].size();

    if (image_channels.size() == 3) {
        // сохраняем в первый канал
        for (int32_t y = 0; y < height; ++y) {
            for (int32_t x = 0; x < width; ++x) {
                image_channels[0][y][x] = image_channels[0][y][x] * BLUE_CONST + image_channels[1][y][x] * GREEN_CONST +
                                          image_channels[2][y][x] * RED_CONST;
            }
        }
        image_channels.pop_back();
        image_channels.pop_back();
    } else if (image_channels.size() != 1) {
        throw std::runtime_error("Something wrong with channels!");
    }
}