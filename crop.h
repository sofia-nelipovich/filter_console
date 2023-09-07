#pragma once

#include "channelwise_filter.h"

class Crop : public ChannelWiseFilter {
public:
    Crop(int height, int width) : new_height_(height), new_width_(width){};

    ~Crop() override = default;

private:
    size_t new_height_;
    size_t new_width_;

protected:
    void ImplementFilter(Image::Channel &channel) const override;
};