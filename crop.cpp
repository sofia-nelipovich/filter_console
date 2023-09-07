#include "crop.h"

#include <stdexcept>
#include <algorithm>

void Crop::ImplementFilter(Image::Channel &channel) const {
    size_t height = channel.size();
    size_t width = channel[0].size();
    for (int32_t row_count = 0; row_count < height; ++row_count) {
        if (row_count >= std::min(new_height_, height)) {
            channel.pop_back();
        } else {
            for (int32_t col_count = 0; col_count < width - std::min(new_width_, width); ++col_count) {
                channel[row_count].pop_back();
            }
        }
    }
}
