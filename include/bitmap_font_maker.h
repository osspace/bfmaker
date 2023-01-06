#ifndef _BFMAKER_SOURCE_BITMAP_FONT_MAKER_H
#define _BFMAKER_SOURCE_BITMAP_FONT_MAKER_H

#include "bitmap_font.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class BitmapFontMaker {
public:
    BitmapFontMaker(std::string font_input_path, int32_t pixel);
    ~BitmapFontMaker();

public:
    BitmapFont draw_bitmap(FT_Bitmap* bitmap);
    BitmapFont get_unicode_bitmap(uint16_t unicode);

    std::vector<BitmapFont> get_all_unicode_bitmap();

private:
    FT_Library library_ = nullptr;
    FT_Face face_ = nullptr;
    FT_GlyphSlot slot_ = nullptr;
    // 收集错误返回值
    FT_Error error_;
};

#endif   // end of _BFMAKER_SOURCE_BITMAP_FONT_MAKER_H
