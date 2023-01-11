#include <string>
#include <iostream>
#include "bitmap_font_maker.h"

void wirte_file_header_to_bin_file(std::string font_output_path, int32_t pixel) {
    std::ofstream outfile;
    outfile.open(font_output_path, std::ios::binary);

    outfile << "BF";
    outfile << static_cast<uint8_t>(pixel);
    outfile << static_cast<uint8_t>(0X00);
    outfile << static_cast<uint32_t>(1 << 16);
    outfile.close();
}

void write_bitmap_to_bin_file(std::string font_output_path, const std::vector<BitmapFont>& bitmap_ary) {
    std::ofstream outfile;
    outfile.open(font_output_path, std::ios::binary | std::ios::app);

    for (const auto& bitmap : bitmap_ary) {
        outfile << bitmap;
    }
    outfile.close();
}

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
        printf("Error：输入参数个数错误！\n");
        return 1;
    }

    std::string font_input_path = argv[1];
    std::string bf_file_name = argv[2];
    std::string bf_file_path = bf_file_name + ".bf";
    int32_t pixel = atoi(argv[3]);

    // BitmapFontMaker font_render(font_input_path);
    // auto bitmap_ary = font_render.get_all_unicode_bitmap(pixel);
    // std::cout << "Done: 所有字体生成成功！" << std::endl;
    // wirte_file_header_to_bin_file(bf_file_path, pixel);
    // write_bitmap_to_bin_file(bf_file_path, bitmap_ary);

    BitmapFontMaker font_render(font_input_path);
    auto bitmap = font_render.get_unicode_bitmap(L'中', pixel);
    bitmap.show();
    // bitmap = font_render.get_unicode_bitmap(L'国', pixel);
    // bitmap.show();
    // bitmap = font_render.get_unicode_bitmap(L'制', pixel);
    // bitmap.show();
    // bitmap = font_render.get_unicode_bitmap(L'造', pixel);
    // bitmap.show();
    // bitmap = font_render.get_unicode_bitmap(L'，', pixel);
    // bitmap.show();
    // bitmap = font_render.get_unicode_bitmap(L'A', pixel);
    // bitmap.show();
    // bitmap = font_render.get_unicode_bitmap(L'B', pixel);
    // bitmap.show();
    // bitmap = font_render.get_unicode_bitmap(L'C', pixel);
    // bitmap.show();
    // bitmap = font_render.get_unicode_bitmap(L'D', pixel);
    // bitmap.show();
    return 0;
}
