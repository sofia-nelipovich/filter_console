#pragma once

#include "filter.h"

class GrayscaleFilter : public Filter {
public:
    ~GrayscaleFilter() override = default;

    void ApplyFilter(Image &image) const final;
};