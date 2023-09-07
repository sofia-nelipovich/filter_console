#pragma once

#include "composite_filter.h"

class EdgeDetection : public CompositeFilter {
public:
    explicit EdgeDetection(double threshold);

    ~EdgeDetection() override = default;
};