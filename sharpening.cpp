#include "sharpening.h"

const std::vector<std::vector<double>> MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

Sharpening::Sharpening() : ConvFilter(MATRIX){};
