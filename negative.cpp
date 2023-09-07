#include "negative.h"

void NegativeFilter::ImplementFilter(Image::Channel &channel) const {
    for (auto &row : channel) {
        for (auto &el : row) {
            el = 1 - el;
        }
    }
}
