#pragma once

#include "filter.h"

#include <memory>

class CompositeFilter : public Filter {
public:
    ~CompositeFilter() override = default;

    explicit CompositeFilter(std::vector<std::unique_ptr<Filter>> filters);

    void ApplyFilter(Image &image) const final;

protected:
    void AddFilter(std::unique_ptr<Filter> filter_ptr);

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};