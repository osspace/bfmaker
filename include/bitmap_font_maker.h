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
    BitmapFontMaker(std::string in_font_path, int32_t pixel);
    ~BitmapFontMaker();

public:
    BitmapFont get_unicode_bitmap(uint16_t unicode);
    std::vector<BitmapFont> get_all_unicode_bitmap();
    FT_BBox get_max_ft_bbox();

private:
    FT_Library ft_library_ = nullptr;
    FT_Face ft_face_ = nullptr;
};

#endif   // end of define : _BFMAKER_SOURCE_BITMAP_FONT_MAKER_H
