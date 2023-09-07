#include "median.h"

Median::Median(int32_t radius) : radius_(radius){};

void Median::ImplementFilter(Image::Channel &channel) const {
    size_t height = channel.size();
    size_t width = channel[0].size();

    Image::Channel channel_copy(height, std::vector<double>(width));

    for (size_t row = 0; row < height; ++row) {
        for (size_t column = 0; column < width; ++column) {
            ApplyFilterToPixel(row, column, channel, channel_copy);
        }
    }
    channel = std::move(channel_copy);
}

void Median::ApplyFilterToPixel(size_t y, size_t x, Image::Channel &channel, Image::Channel &channel_copy) const {
    const ssize_t height = static_cast<ssize_t>(channel.size());
    const ssize_t width = static_cast<ssize_t>(channel[0].size());
    const ssize_t left_bound = static_cast<ssize_t>(x) - radius_;
    const ssize_t right_bound = static_cast<ssize_t>(x) + radius_;
    const ssize_t lower_bound = static_cast<ssize_t>(y) - radius_;
    const ssize_t upper_bound = static_cast<ssize_t>(y) + radius_;

    std::vector<double> vector_of_pixels;

    for (ssize_t y_it = lower_bound; y_it <= upper_bound; ++y_it) {
        for (ssize_t x_it = left_bound; x_it <= right_bound; ++x_it) {
            ssize_t x_final = std::min(std::max(0l, x_it), width - 1);
            ssize_t y_final = std::min(std::max(0l, y_it), height - 1);
            vector_of_pixels.push_back(channel[y_final][x_final]);
        }
    }
    std::sort(vector_of_pixels.begin(), vector_of_pixels.end());
    channel_copy[y][x] = vector_of_pixels[vector_of_pixels.size() / 2];
};
