#include "threshold.h"

Threshold::Threshold(double threshold) : threshold_(threshold){};

void Threshold::ImplementFilter(Image::Channel &channel) const {
    const size_t height = channel.size();
    const size_t width = channel[0].size();

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            if (channel[y][x] > threshold_) {
                channel[y][x] = 1;
            } else {
                channel[y][x] = 0;
            }
        }
    }
}
