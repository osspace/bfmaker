#ifndef _BFMAKER_SOURCE_BITMAP_FONT_MAKER_H
#define _BFMAKER_SOURCE_BITMAP_FONT_MAKER_H

#include "bitmap_font.h"
#include <iostream>
#include <unordered_map>
#include <ft2build.h>
#include <freetype/ftglyph.h>
#include <freetype/freetype.h>

class BitmapFontMaker {
public:
    BitmapFontMaker(std::string font_input_path);
    ~BitmapFontMaker();

public:
    BitmapFont get_unicode_bitmap(uint16_t unicode, int32_t pixel);

    int32_t get_max_bearing_y(int32_t pixel);
    std::vector<BitmapFont> get_all_unicode_bitmap(int32_t pixel);

private:
    FT_Library library_ = nullptr;
    FT_Face face_ = nullptr;
    FT_GlyphSlot slot_ = nullptr;
    // 收集错误返回值
    FT_Error error_;

    FT_Matrix matrix; /* transformation matrix */
    FT_Vector pen;    /* untransformed origin  */

    static std::unordered_map<int32_t, int32_t> pixel_to_max_bearing_y;
};

#endif   // end of _BFMAKER_SOURCE_BITMAP_FONT_MAKER_H
