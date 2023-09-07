#include "gaussian_blur.h"
#include "conv_filter.h"

#include <cmath>

namespace {
double CalculatePixelBlur(ssize_t x, ssize_t y, double sigma) {
    return std::exp(-static_cast<double>(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
}
}  // namespace

GaussianBlur::GaussianBlur(double sigma) : CompositeFilter({}) {
    const size_t matrix_size =
        static_cast<size_t>(std::ceil(3 * sigma)) + static_cast<size_t>(std::ceil(3 * sigma)) % 2 + 3;

    AddFilter(std::make_unique<ConvFilter>(GaussianMatrix(sigma, matrix_size, 1)));
    AddFilter(std::make_unique<ConvFilter>(GaussianMatrix(sigma, 1, matrix_size)));
}

std::vector<std::vector<double>> GaussianBlur::GaussianMatrix(double sigma, size_t width, size_t height) const {
    const ssize_t x_radius = static_cast<ssize_t>(width) / 2;
    const ssize_t y_radius = static_cast<ssize_t>(height) / 2;

    double sum_matrix = 0;
    std::vector<std::vector<double>> matrix(height, std::vector<double>(width));
    for (ssize_t y = -y_radius; y < y_radius + 1; ++y) {
        for (ssize_t x = -x_radius; x < x_radius + 1; ++x) {
            const double pixel_value = CalculatePixelBlur(x, y, sigma);
            sum_matrix += pixel_value;
            matrix[y_radius + y][x_radius + x] = pixel_value;
        }
    }
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            matrix[y][x] /= sum_matrix;
        }
    }
    return matrix;
}