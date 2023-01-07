#include <vector>
#include <bitset>
#include <memory>
#include <fstream>
#include <iostream>

#include "bitmap_font.h"

std::vector<BitmapFont> parse_font_file(std::string font_input_path) {
    std::ifstream input_file;
    input_file.open(font_input_path, std::ios::in | std::ios::binary);

    std::vector<BitmapFont> ret_bitmap_ary(1 << 16);
    for (int i = 0; i < (1 << 16); i++) {
        std::unique_ptr<uint8_t> meta_data(new uint8_t[2]);
        input_file.read(reinterpret_cast<char*>(meta_data.get()), 2);
        uint8_t rows = meta_data.get()[0];
        uint8_t cols = meta_data.get()[1];
        // std::cout << (int)rows << " " << (int)cols << std::endl;

        BitmapFont font_bitmap(rows, cols);
        std::unique_ptr<uint8_t> bitmap_data(new uint8_t[font_bitmap.byte_size()]);
        input_file.read(reinterpret_cast<char*>(bitmap_data.get()), font_bitmap.byte_size());
        font_bitmap.set_bitmap(bitmap_data.get());
        ret_bitmap_ary[i] = font_bitmap;
    }

    input_file.close();
    return ret_bitmap_ary;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Error：输入参数个数错误！");
        return 1;
    }

    std::string font_input_path = argv[1];
    char ch = argv[2][0];

    auto bitmap_ary = parse_font_file(font_input_path);

    std::cout << bitmap_ary[ch].row() << " " << bitmap_ary[ch].col() << std::endl;
    bitmap_ary[ch].show();
    return 0;
}
