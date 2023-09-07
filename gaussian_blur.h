#pragma once

#include "composite_filter.h"

class GaussianBlur : public CompositeFilter {
public:
    explicit GaussianBlur(double sigma);

    ~GaussianBlur() override = default;

    std::vector<std::vector<double>> GaussianMatrix(double sigma, size_t width, size_t height) const;
};
