#include <string>
#include <iostream>
#include "bitmap_font_maker.h"

void write_bitmap_to_bin_file(std::string font_output_path, const std::vector<BitmapFont>& bitmap_ary) {
    std::ofstream outfile;
    outfile.open(font_output_path, std::ios::binary);

    for (const auto& bitmap : bitmap_ary) {
        outfile << static_cast<uint8_t>(bitmap.row()) << static_cast<uint8_t>(bitmap.col());
        outfile << bitmap;
    }
    outfile.close();
}

/**
 * @brief
 *
 * @param argc
 * @param argv[1]: 字体文件路径
 * @param argv[2]: 定制字体文件输出路径
 * @param argv[3]: 字体大小
 * @return int
 */
int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Error：输入参数个数错误！\n");
        return 1;
    }

    std::string font_input_path = argv[1];
    std::string font_output_path = argv[2];
    int32_t pixel = atoi(argv[3]);

    // BitmapFontMaker font_render(font_input_path);
    // auto bitmap_ary = font_render.get_all_unicode_bitmap(pixel);
    // std::cout << "Done: 所有字体生成成功！" << std::endl;
    // write_bitmap_to_bin_file(font_output_path, bitmap_ary);

    BitmapFontMaker font_render(font_input_path);
    auto bitmap = font_render.get_unicode_bitmap(L'中', pixel);
    bitmap.show();
    bitmap = font_render.get_unicode_bitmap(L'国', pixel);
    bitmap.show();
    bitmap = font_render.get_unicode_bitmap(L'制', pixel);
    bitmap.show();
    bitmap = font_render.get_unicode_bitmap(L'造', pixel);
    bitmap.show();
    bitmap = font_render.get_unicode_bitmap(L'，', pixel);
    bitmap.show();
    bitmap = font_render.get_unicode_bitmap(L'A', pixel);
    bitmap.show();
    bitmap = font_render.get_unicode_bitmap(L'B', pixel);
    bitmap.show();
    bitmap = font_render.get_unicode_bitmap(L'C', pixel);
    bitmap.show();
    bitmap = font_render.get_unicode_bitmap(L'D', pixel);
    bitmap.show();
    return 0;
}
