#include "lodepng/lodepng.h"

#include <exception>
#include <format>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <expected>

inline constexpr auto DecodeOneStep(auto &image, std::string_view filename) -> std::expected<uint32_t, uint32_t> {
    uint32_t width, height;
    if (auto error = lodepng::decode(image, width, height, filename.data()); error) {
        return std::unexpected(error);
    }

    return width;
}

inline constexpr auto ToGray(auto &image, auto &gray_image, auto n) {
    for (auto i = 0; i < n; i += 4) {
        gray_image.emplace_back((image[i] + image[i + 1] + image[i + 2]) / 3);
    }
}

int main() {
    std::vector<uint8_t> image;
    uint32_t w = 0;
    std::vector<uint32_t> gray_image;

    constexpr char const ENCODE_MAP[] = {
        '@',
        '&',
        '#',
        'G',
        'H',
        'P',
        'I',
        'L',
        '|',
        '(',
         '[',
         ':',
         '*',
         '"',
         '^',
         '.',
    };

    w = DecodeOneStep(image, "your_image.png").transform_error([](auto error) -> uint32_t {
        std::cout << "decode error: " << error << std::endl;
        std::terminate();
    }).value();

    ToGray(image, gray_image, image.size());
    
    std::stringstream finalstr;
    for (auto i = 0; i < gray_image.size(); ++i) {
        finalstr << ENCODE_MAP[gray_image[i] / 16];

        if ((i + 1) % w == 0) {
            finalstr << std::endl;
        }
    }

    std::ofstream file("result.txt");
    file << finalstr.str();
}
