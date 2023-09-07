#pragma once

#include "channelwise_filter.h"

class Threshold : public ChannelWiseFilter {
public:
    explicit Threshold(double threshold);

protected:
    void ImplementFilter(Image::Channel &channel) const override;

private:
    double threshold_;
};