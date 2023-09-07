#include "edge_detection.h"
#include "threshold.h"
#include "conv_filter.h"
#include "composite_filter.h"
#include "grayscale.h"

static const std::vector<std::vector<double>> MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

EdgeDetection::EdgeDetection(double threshold) : CompositeFilter({}) {
    AddFilter(std::make_unique<GrayscaleFilter>());
    AddFilter(std::make_unique<ConvFilter>(MATRIX));
    AddFilter(std::make_unique<Threshold>(threshold));
}