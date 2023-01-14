#include <vector>
#include <bitset>
#include <memory>
#include <fstream>
#include <iostream>

#include "bitmap_font.h"

struct FileHeader {
    char bmType[2];
    uint16_t check_sum;
    uint8_t font_size;
    uint8_t reserved;
    uint8_t max_bbox_width;
    uint8_t max_bbox_height;
    uint32_t size;
};

BitmapFont parser_bf_file(std::string bf_file_path, int32_t unicode) {
    std::ifstream in_file_stream;
    in_file_stream.open(bf_file_path, std::ios::in | std::ios::binary);

    FileHeader file_header;
    in_file_stream.read((char*)&file_header, sizeof(FileHeader));

    // printf("%s\n", file_header.bmType);
    // printf("%04X\n", file_header.check_sum);
    // printf("%02X\n", file_header.font_size);
    // printf("%02X\n", file_header.reserved);
    // printf("%02X\n", file_header.max_bbox_width);
    // printf("%02X\n", file_header.max_bbox_height);
    // printf("%08X\n", file_header.size);

    int32_t bitmap_size = (file_header.max_bbox_height * file_header.max_bbox_width + 7) / 8;
    int32_t offset = 12 + unicode * (4 + bitmap_size);
    // std::cout << offset << std::endl;
    // std::cout << bitmap_size << std::endl;
    in_file_stream.seekg(offset, std::ios::beg);

    uint8_t widht, height;
    uint8_t offset_x, offset_y;
    in_file_stream.read(reinterpret_cast<char*>(&widht), sizeof(widht));
    in_file_stream.read(reinterpret_cast<char*>(&height), sizeof(height));
    in_file_stream.read(reinterpret_cast<char*>(&offset_x), sizeof(offset_x));
    in_file_stream.read(reinterpret_cast<char*>(&offset_y), sizeof(offset_y));
    uint8_t* bitmap = new uint8_t[bitmap_size + 1];
    in_file_stream.read(reinterpret_cast<char*>(bitmap), bitmap_size);

    BitmapFont bitmap_font(file_header.max_bbox_height, file_header.max_bbox_width);
    bitmap_font.width_ = widht;
    bitmap_font.height_ = height;
    bitmap_font.offset_x_ = offset_x;
    bitmap_font.offset_y_ = offset_y;
    for (int i = 0; i < bitmap_size; i++) {
        bitmap_font.bitmap_[i] = bitmap[i];
    }
    puts("");
    delete[] bitmap;
    bitmap = nullptr;
    in_file_stream.close();
    return bitmap_font;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Error: Number of arguments must is 2!\n");
        return 1;
    }

    std::string bf_file_path = argv[1];

    parser_bf_file(bf_file_path, L'中').show();
    parser_bf_file(bf_file_path, L'国').show();
    parser_bf_file(bf_file_path, L'，').show();
    parser_bf_file(bf_file_path, L',').show();
    parser_bf_file(bf_file_path, L'A').show();
    parser_bf_file(bf_file_path, L'g').show();
    return 0;
}
