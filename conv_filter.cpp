#include "conv_filter.h"

ConvFilter::ConvFilter(std::vector<std::vector<double>> matrix) {
    matrix_ = matrix;
    x_padding_ = CalculateXPadding();
    y_padding_ = CalculateYPadding();
}

ssize_t ConvFilter::CalculateXPadding() const {
    return static_cast<ssize_t>(matrix_[0].size() / 2);
}

ssize_t ConvFilter::CalculateYPadding() const {
    return static_cast<ssize_t>(matrix_.size() / 2);
}

void ConvFilter::ImplementFilter(Image::Channel &channel) const {

    const size_t height = channel.size();
    const size_t width = channel[0].size();

    Image::Channel channel_copy(height, std::vector<double>(width));

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            ApplyMatrixToPixel(x, y, channel, channel_copy);
        }
    }
    RewriteChannel(channel, channel_copy);
}

void ConvFilter::ApplyMatrixToPixel(size_t x, size_t y, Image::Channel &channel, Image::Channel &channel_copy) const {
    const ssize_t height = static_cast<ssize_t>(channel.size());
    const ssize_t width = static_cast<ssize_t>(channel[0].size());
    const ssize_t left_bound = static_cast<ssize_t>(x) - x_padding_;
    const ssize_t right_bound = static_cast<ssize_t>(x) + x_padding_;
    const ssize_t lower_bound = static_cast<ssize_t>(y) - y_padding_;
    const ssize_t upper_bound = static_cast<ssize_t>(y) + y_padding_;

    double pixel_value = 0;

    for (ssize_t y_it = lower_bound; y_it <= upper_bound; ++y_it) {
        for (ssize_t x_it = left_bound; x_it <= right_bound; ++x_it) {
            ssize_t x_final = std::min(std::max(0l, x_it), width - 1);
            ssize_t y_final = std::min(std::max(0l, y_it), height - 1);
            pixel_value += matrix_[y_it - lower_bound][x_it - left_bound] * channel[y_final][x_final];
        }
    }
    channel_copy[y][x] = std::min(std::max(0.0, pixel_value), 1.0);
}

void ConvFilter::RewriteChannel(Image::Channel &channel, Image::Channel &channel_copy) const {
    channel = std::move(channel_copy);
}
