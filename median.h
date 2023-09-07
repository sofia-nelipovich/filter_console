#pragma once

#include "channelwise_filter.h"

class Median : public ChannelWiseFilter {
public:
    explicit Median(int32_t radius);

    void ApplyFilterToPixel(size_t y, size_t x, Image::Channel &channel, Image::Channel &channel_copy) const;

protected:
    void ImplementFilter(Image::Channel &channel) const override;

private:
    int32_t radius_;
};