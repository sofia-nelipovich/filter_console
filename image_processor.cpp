#include "image.h"
#include "bmp_file.h"
#include "cli.h"
#include "composite_filter.h"

int main(int argc, char **argv) {
    CLI cli(argc, argv);

    if (!cli.IsParsed()) {
        return 0;
    }

    Image image;
    BMPFile input_file(cli.GetInputFile());

    auto filters = cli.MakeFiltersVector();
    input_file.OpenImage(image);

    CompositeFilter composite_filter(std::move(filters));
    composite_filter.ApplyFilter(image);

    BMPFile output_file(cli.GetOutputFile());
    output_file.SaveImage(image);
    return 0;
}
