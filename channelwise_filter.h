#pragma once

#include "filter.h"

class ChannelWiseFilter : public Filter {
public:
    ~ChannelWiseFilter() override = default;

    void ApplyFilter(Image &image) const final;

protected:
    virtual void ImplementFilter(Image::Channel &channel) const = 0;
};