#pragma once

#include "filter.h"
#include <string_view>
#include <vector>
#include <filesystem>

#include <memory>

namespace fs = std::filesystem;

class CLI {
public:
    CLI(int args_number, char **args_vector);

    void ParseArgs(int args_number, char **args_vector);

    std::vector<std::unique_ptr<Filter>> MakeFiltersVector();

    std::string_view GetInputFile() const;

    std::string_view GetOutputFile() const;

    bool IsParsed() const;

private:
    struct FilterStruct {
        std::string_view name;
        std::vector<std::string_view> parameters;
    };

    std::string_view input_file_;
    std::string_view output_file_;
    std::vector<FilterStruct> filters_vector_;
    std::vector<std::unique_ptr<Filter>> filter_ptrs_;
    bool is_parsed_ = true;
};