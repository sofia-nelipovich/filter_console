#pragma once

#include "channelwise_filter.h"

class NegativeFilter final : public ChannelWiseFilter {
public:
    ~NegativeFilter() override = default;

protected:
    void ImplementFilter(Image::Channel &channel) const override;
};