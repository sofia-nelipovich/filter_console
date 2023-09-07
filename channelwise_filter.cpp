#include "channelwise_filter.h"

void ChannelWiseFilter::ApplyFilter(Image &image) const {
    for (auto &channel : image.GetChannels()) {
        ImplementFilter(channel);
    }
}