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

/*
参数:
参数1: 字体文件输入路径
参数2: 输出二进制文件路径
参数3: 字体像素大小
*/
int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Error：输入参数个数错误！\n");
        return 1;
    }

    std::string font_input_path = argv[1];
    std::string font_output_path = argv[2];
    int32_t pixel = atoi(argv[3]);

    BitmapFontMaker font_render(font_input_path, pixel);
    auto bitmap_ary = font_render.get_all_unicode_bitmap();
    std::cout << "Done: 所有字体生成成功！" << std::endl;
    write_bitmap_to_bin_file(font_output_path, bitmap_ary);

    // BitmapFontMaker font_render(font_input_path, pixel);
    // auto bitmap_ary = font_render.get_unicode_bitmap('A');
    // std::cout << "Done: \'A\'字体生成成功！" << std::endl;
    // write_bitmap_to_bin_file(font_output_path, { bitmap_ary });
    return 0;
}
