#include <string>
#include <iostream>
#include "bitmap_font_maker.h"

/**
 * @brief
 *
 * @param argc
 * @param argv[1]: 字体文件路径
 * @param argv[2]: 字体
 * @param argv[3]: 字体大小
 * @return int
 */
int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Error: Number of arguments must is 3!\n");
        return 1;
    }
    
    std::string font_input_path = argv[1];
    char font = argv[2][0];
    int font_size = atoi(argv[3]);

    BitmapFontMaker font_render(font_input_path, font_size);
    auto bitmap_ary = font_render.get_all_unicode_bitmap();

    BitmapFont value = bitmap_ary[font];
    value.show();
    return 0;
}
