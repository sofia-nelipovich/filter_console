#include "cli.h"
#include "grayscale.h"
#include "crop.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "gaussian_blur.h"
#include "median.h"

#include <stdexcept>
#include <iostream>

static const int MIN_ARGS_REQUIRED = 3;
static const size_t INPUT_FILE_INDEX = 1;
static const size_t OUTPUT_FILE_INDEX = 2;

namespace {
void PrintHelp() {
    std::cout << "This is a simple image processor.\n";
    std::cout << "-------------------------------------------------------------\n";
    std::cout << "How to input arguments:\n";
    std::cout << "\t./image_processor input_file output_file [-filter [args]]\n";
    std::cout << "-------------------------------------------------------------\n";
    std::cout << "Filters list:\n";
    std::cout << "\t-gs - grayscale\n";
    std::cout << "\t-crop height width - crop\n";
    std::cout << "\t-neg - negative\n";
    std::cout << "\t-sharp - sharpening\n";
    std::cout << "\t-edge threshold - edge detection\n";
    std::cout << "\t-blur sigma - gaussian blur\n";
    std::cout << "\t-median radius - median filter, removing noise\n";
}
}  // namespace

CLI::CLI(int args_number, char **args_vector) {
    ParseArgs(args_number, args_vector);
}

void CLI::ParseArgs(int args_number, char **args_vector) {
    if (args_number == 1) {
        // 1 argument - executable program
        is_parsed_ = false;
        PrintHelp();
    } else if (args_number == 2) {
        // 2 arguments - executable program + input file
        is_parsed_ = false;
        throw std::runtime_error("Not enough arguments!");
    } else {
        // 3 arguments - executable program + input & output file, meaning we can save image in output file
        input_file_ = std::string_view(args_vector[INPUT_FILE_INDEX]);
        output_file_ = std::string_view(args_vector[OUTPUT_FILE_INDEX]);
    }
    for (int i = MIN_ARGS_REQUIRED; i < args_number; ++i) {
        if (args_vector[i][0] == '-') {
            FilterStruct new_filter;
            new_filter.name = args_vector[i];
            filters_vector_.push_back(new_filter);
        } else {
            if (filters_vector_.empty()) {
                throw std::invalid_argument("Wrong filter name: " + std::string(args_vector[i]));
            }
            filters_vector_[filters_vector_.size() - 1].parameters.push_back(args_vector[i]);
        }
    }
}

std::vector<std::unique_ptr<Filter>> CLI::MakeFiltersVector() {
    for (const auto &[filter_name, parameters] : filters_vector_) {
        if (filter_name == "-gs") {
            if (!parameters.empty()) {
                throw std::invalid_argument("Wrong args for gs!");
            }
            filter_ptrs_.push_back(std::make_unique<GrayscaleFilter>());
        }
        if (filter_name == "-crop") {
            int height = 0;
            int width = 0;
            if (parameters.size() != 2) {
                throw std::invalid_argument("Wrong args for crop!");
            }
            try {
                height = std::stoi(std::string(parameters[0]));
                width = std::stoi(std::string(parameters[1]));
            } catch (std::invalid_argument) {
                throw std::invalid_argument("Wrong crop parameters!");
            }
            if (height <= 0 || width <= 0) {
                throw std::invalid_argument("Wrong crop parameters!");
            }
            filter_ptrs_.push_back(std::make_unique<Crop>(height, width));
        }
        if (filter_name == "-neg") {
            if (!parameters.empty()) {
                throw std::invalid_argument("Wrong args for neg!");
            }
            filter_ptrs_.push_back(std::make_unique<NegativeFilter>());
        }
        if (filter_name == "-sharp") {
            if (!parameters.empty()) {
                throw std::invalid_argument("Wrong args for sharp!");
            }
            filter_ptrs_.push_back(std::make_unique<Sharpening>());
        }
        if (filter_name == "-edge") {
            double threshold = 0.0;
            if (parameters.size() != 1) {
                throw std::invalid_argument("Wrong args for edge!");
            }
            try {
                threshold = std::stod(std::string(parameters[0]));
            } catch (std::invalid_argument) {
                throw std::invalid_argument("Wrong edge parameter!");
            }
            filter_ptrs_.push_back(std::make_unique<EdgeDetection>(threshold));
        }
        if (filter_name == "-blur") {
            double sigma = 0;
            if (parameters.size() != 1) {
                throw std::invalid_argument("Wrong args for blur!");
            }
            try {
                sigma = std::stod(std::string(parameters[0]));
            } catch (std::invalid_argument) {
                throw std::invalid_argument("Wrong blur parameter!");
            }
            if (sigma <= 0) {
                throw std::invalid_argument("Wrong blur parameter!");
            }
            filter_ptrs_.push_back(std::make_unique<GaussianBlur>(sigma));
        }
        if (filter_name == "-median") {
            int32_t radius = 0;
            if (parameters.size() != 1) {
                throw std::invalid_argument("Wrong args for median!");
            }
            try {
                radius = std::stoi(std::string(parameters[0]));
            } catch (std::invalid_argument) {
                throw std::invalid_argument("Wrong median parameter!");
            }
            if (radius <= 0) {
                throw std::invalid_argument("Wrong median parameter!");
            }
            filter_ptrs_.push_back(std::make_unique<Median>(radius));
        }
    }
    return std::move(filter_ptrs_);
}

std::string_view CLI::GetInputFile() const {
    return input_file_;
}

std::string_view CLI::GetOutputFile() const {
    return output_file_;
}

bool CLI::IsParsed() const {
    return is_parsed_;
}
