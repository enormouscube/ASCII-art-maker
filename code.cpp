#include "lodepng/lodepng.h"

#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <expected>

//decoding function
inline auto DecodeOneStep(auto &image, std::string_view filename) -> std::expected<uint32_t, uint32_t> {
    uint32_t width, height;
    auto error = lodepng::decode(image, width, height, filename.data());
    if (error) std::cout << "I CAN'T WORK!!\n";
    return width;
}


//turning image to grayscale function
void ToGray(std::vector<unsigned char> &image, std::vector<unsigned> &gray_image, int n) {
    for (int i = 0; i < n; i += 4) gray_image.push_back((image[i] + image[i + 1] + image[i + 2]) / 3);
}

int main() {
    std::vector<unsigned char> image;
    unsigned w = 0;
    std::vector<unsigned> gray_image;

    //map to encode image to ASCII
    std::map<unsigned, char> ENCODE_MAP = { {(unsigned)0, '@'},
{(unsigned)1, '&'},
{(unsigned)2, '#'},
{(unsigned)3, 'G'},
{(unsigned)4, 'H'},
{(unsigned)5, 'P'},
{(unsigned)6, 'I'},
{(unsigned)7, 'L'},
{(unsigned)8, '|'},
{(unsigned)9, '('},
{(unsigned)10, '['},
{(unsigned)11, ':'},
{(unsigned)12, '*'},
{(unsigned)13, '"'},
{(unsigned)14, '^'},
{(unsigned)15, '.'},
    };

    w = DecodeOneStep(image, "your_image.png");
    ToGray(image, gray_image, image.size());
    
    //turning image into string to write it into file
    std::string finalstr = "";
    for (int i = 0; i < gray_image.size(); ++i) {
        finalstr += ENCODE_MAP[gray_image[i] / 16];
        if ((i + 1) % w == 0) finalstr += "\n";
    }

    //writing string into file
    std::ofstream file;
    file.open("result.txt");
    if (file.is_open()) file << finalstr;
    file.close();
    return 0;
}
