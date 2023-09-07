#pragma once

#include "channelwise_filter.h"

class ConvFilter : public ChannelWiseFilter {
public:
    explicit ConvFilter(std::vector<std::vector<double>> matrix);

    ~ConvFilter() override = default;

protected:
    void ImplementFilter(Image::Channel &channel) const final;

    void ApplyMatrixToPixel(size_t x, size_t y, Image::Channel &channel, Image::Channel &channel_copy) const;

    void RewriteChannel(Image::Channel &channel, Image::Channel &channel_copy) const;

    ssize_t CalculateXPadding() const;

    ssize_t CalculateYPadding() const;

private:
    std::vector<std::vector<double>> matrix_;
    ssize_t x_padding_;
    ssize_t y_padding_;
};