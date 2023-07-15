#include <string>
#include <iostream>
#include "bitmap_font_maker.h"

/**
 * @brief
 *
 * @param argc
 * @param argv[1]: 字体文件路径
 * @param argv[2]: bf文件名
 * @param argv[3]: 字体大小
 * @return int
 */
int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Error: Number of arguments must is 3!\n");
        return 1;
    }
    
    std::string font_input_path = argv[1];
    std::string bf_file_name = argv[2];
    std::string bf_file_path = bf_file_name + ".bf";
    int32_t pixel = atoi(argv[3]);

    BitmapFontMaker font_render(font_input_path, pixel);
    auto bitmap_ary = font_render.get_all_unicode_bitmap();

    std::ofstream outfile;
    outfile.open(bf_file_path, std::ios::binary);
    [&]() -> void {
        outfile << "BF";
        char* byte_stream = new char[4];
        uint16_t check_sum = 0X0000;
        memcpy(byte_stream, &check_sum, 2);
        outfile.write(byte_stream, 2);
        memcpy(byte_stream, &pixel, 1);
        outfile.write(byte_stream, 1);
        uint8_t reserved = 0X00;
        memcpy(byte_stream, &reserved, 1);
        outfile.write(byte_stream, 1);
        memcpy(byte_stream, &bitmap_ary[0].bbox_width_, 1);
        outfile.write(byte_stream, 1);
        memcpy(byte_stream, &bitmap_ary[0].bbox_height_, 1);
        outfile.write(byte_stream, 1);
        int32_t size = 1 << 16;
        memcpy(byte_stream, &size, 4);
        outfile.write(byte_stream, 4);
        delete[] byte_stream;
        byte_stream = nullptr;
    }();   // 文件头
    [&]() -> void {
        char* byte_stream = new char[2];
        for (auto bitmap : bitmap_ary) {
            memcpy(byte_stream, &bitmap.width_, 1);
            outfile.write(byte_stream, 1);
            memcpy(byte_stream, &bitmap.height_, 1);
            outfile.write(byte_stream, 1);
            memcpy(byte_stream, &bitmap.offset_x_, 1);
            outfile.write(byte_stream, 1);
            memcpy(byte_stream, &bitmap.offset_y_, 1);
            outfile.write(byte_stream, 1);
            outfile.write(reinterpret_cast<const char*>(bitmap.bitmap_.data()), bitmap.bitmap_.size());
        }
        outfile.close();
    }();   // 文件体

    std::cout << bitmap_ary[0].bitmap_.size() << std::endl;
    printf("Done: bf file generated successfully");
    return 0;
}
